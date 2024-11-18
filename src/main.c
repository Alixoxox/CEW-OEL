#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "api.h"
#include "file_io.h"
#include "alerts.h"

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);  // Converts each character to lowercase
    }
}
int is_empty(const char *str){
    for (int i=0; str[i];i++){
    if (!isspace(str[i])){
        return 0;
        }
   }
   return 1;
}
int main() {
    char location[100];
    char api_key[] = "3a69e50f28f648afbce180111240211";
    struct WeatherData data;
    char *raw_weather_data = NULL; // To hold raw JSON data

    while (1) {
        printf("Enter location (City Name) or 'e' to exit: ");
        scanf("%99s", location);

        if (is_empty(location)){
            printf("It is neccessary to enter name of location ");
            free(raw_weather_data);
            continue;
        }

        // Convert user input to lowercase
        to_lowercase(location);

        // Exit condition if user enters 'e'
        if (strcmp(location, "e") == 0) {
            return 0;
        }

        // Fetch weather data
        fetch_weather_data(location, api_key, &data, &raw_weather_data);  // Pass pointer to raw_weather_data

        // Convert fetched location name to lowercase for comparison
        to_lowercase(data.location_name);

        // Check if the data matches the input
        if (strcmp(data.location_name, location) != 0) {
            printf("Incorrect location. Please enter a valid city name.\n");
            free(raw_weather_data); // Free memory allocated for raw data
            continue;  // Prompt again if the location is invalid
        }

        // Check for missing data from the API
        if (data.temperature == 0.0 && data.humidity == 0.0 && data.location_name[0] == '\0') {
            printf("API doesn't have data for this location.\n");
            free(raw_weather_data); // Free memory allocated for raw data
            continue;  // Prompt again if data is unavailable
        }

        // Save raw JSON data
        write_raw_data(raw_weather_data); // Save raw data to file
        free(raw_weather_data); // Free memory after writing

        // Save processed data
        write_processed_data(&data); // Save processed data
        // If valid data is found, exit the loop
        // Proceed to display weather info if a valid location is entered
        printf("\n-------------------------------Weather Info----------------------------------------\n");
        printf("Now Showing Info...\n");
        printf("\tLocation: %s, %s, %s\n", data.location_name, data.region, data.country);
        printf("\tCoordinates: %.3f, %.3f\n", data.latitude, data.longitude);
        printf("\tCondition: %s\n", data.condition);
        printf("\tFeels like: %.2f°C\n", data.feels_like);
        printf("\tTemperature: %.2f°C\n", data.temperature);
        printf("\tHumidity: %.2f%%\n", data.humidity);
        printf("\tWind direction: %s\n", data.wind_direction);
        printf("\t\t------------------------------------------");
        check_alerts(data.temperature, data.humidity,data.feels_like);
    }
}
