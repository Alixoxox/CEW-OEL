#include <stdio.h>
#include <curl/curl.h>
#include <jansson.h>
#include "api.h"

// Function to handle the API response
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;

    // Parse the JSON response
    json_error_t error;
    json_t *root = json_loadb(contents, totalSize, 0, &error);

    if (!root) {
        fprintf(stderr, "Error parsing JSON: %s\n", error.text);
        return totalSize;
    }

    // Append raw data
    FILE *rawFile = fopen("Data/Weather_Raw_Data.txt", "a");
    if (rawFile) {
        fwrite(contents, size, nmemb, rawFile);
        fclose(rawFile);
    } else {
        perror("Failed to open Weather_Raw_Data.txt");
    }

    // Extract "main" and "wind" objects
    json_t *mainObject = json_object_get(root, "main");
    json_t *windObject = json_object_get(root, "wind");

    if (mainObject && json_is_object(mainObject) && windObject && json_is_object(windObject)) {
        // Extract weather parameters
        json_t *tempJson = json_object_get(mainObject, "temp");
        json_t *humidityJson = json_object_get(mainObject, "humidity");
        json_t *pressureJson = json_object_get(mainObject, "pressure");
        json_t *speedJson = json_object_get(windObject, "speed");

        if (tempJson && humidityJson && pressureJson && speedJson) {
            double temperature = json_number_value(tempJson);
            double humidity = json_number_value(humidityJson);
            double pressure = json_number_value(pressureJson);
            double windSpeed = json_number_value(speedJson);

            // Append processed data to Weather_Processed.csv
            FILE *processedFile = fopen("Data/Weather_Processed.csv", "a+");
            if (processedFile) {
                // Add header if the file is empty
                fseek(processedFile, 0, SEEK_END);
                if (ftell(processedFile) == 0) {
                    fprintf(processedFile, "Temperature,Humidity,Pressure,Wind Speed\n");
                }
                fprintf(processedFile, "%.2f,%.2f,%.2f,%.2f\n", temperature, humidity, pressure, windSpeed);
                fclose(processedFile);

                // Print data to the terminal
                printf("\n------------------------------x---------------------\n");
                printf("| %-12s | %-8s | %-9s | %-10s |\n", "Temperature", "Humidity", "Pressure", "Wind Speed");
                printf("----------------------------------------------------\n");
                printf("| %-12.2f | %-8.2f | %-9.2f | %-10.2f |\n", temperature, humidity, pressure, windSpeed);
                printf("------------------------------x---------------------\n\n");
            } else {
                perror("Failed to open Weather_Processed.csv");
            }

            // Append wind speed data
            FILE *windSpeedFile = fopen("Data/Wind_Speed_Data.txt", "a+");
            if (windSpeedFile) {
                fprintf(windSpeedFile, "%.2f\n", windSpeed);
                fclose(windSpeedFile);
            } else {
                perror("Failed to open Wind_Speed_Data.txt");
            }

            if (windSpeed > 2.5) {
                // Log to Anomaly.log for extreme weather
                FILE *anomalyFile = fopen("Data/Anomaly.log", "a+");
                if (anomalyFile) {
                    fprintf(anomalyFile, "Extreme weather detected: %.2f km/h wind speed at Date: %s, Time: %s\n",
                            windSpeed, __DATE__, __TIME__);

                    fclose(anomalyFile);
                    char command[256];
                    snprintf(command, sizeof(command), "notify-send 'Extreme Weather Detected' 'Wind Speed: %.2f km/h'", windSpeed);
                    system(command);
                } else {
                    perror("Failed to open Anomaly.log");
                }
            } else {
                // Send a system notification for pleasant weather
                char pleasantWeatherCommand[256];
                snprintf(pleasantWeatherCommand, sizeof(pleasantWeatherCommand),
                         "notify-send 'Pleasant Weather' 'Wind Speed: %.2f km/h'", windSpeed);
                system(pleasantWeatherCommand);
            }
        }
    }

    // Clean up JSON object
    json_decref(root);
    return totalSize;
}
