#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "file_io.h"
#include "api.h"

// Function to write raw JSON data to a file
void write_raw_data(const char *data) {
    FILE *file = fopen("raw_data.json", "w");
    if (file) {
        fputs(data, file);
        fclose(file);
    } else {
        perror("Failed to open raw_data.json");
    }
}


// Function to write processed weather data to a formatted CSV file
void write_processed_data(const struct WeatherData *data) {
    FILE *file = fopen("processed_data.csv", "a+");
    if (file) {
        fprintf(file, "Location: %s, %s, %s\n", data->location_name, data->region, data->country);
        fprintf(file, "Coordinates: %.6f, %.6f\n", data->latitude, data->longitude);
        fprintf(file, "Temperature: %.2f°C\n", data->temperature);
        fprintf(file, "Feels Like: %.2f°C\n", data->feels_like);
        fprintf(file, "Humidity: %.2f%%\n", data->humidity);
        fprintf(file, "Condition: %s\n", data->condition);
        fprintf(file, "Wind Direction: %s\n", data->wind_direction);
        fprintf(file, "-----------------------------------\n");
        fclose(file);
    } else {
        perror("Failed to open processed_data.csv");
    }
}
