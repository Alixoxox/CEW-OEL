#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h> // Include cJSON header
#include "api.h" // Include your header file with the WeatherData struct definition

// Struct for holding the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function for writing received data into MemoryStruct
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, struct MemoryStruct *mem) {
    size_t realsize = size * nmemb; // Calculate the real size of the data

    // Reallocate memory to hold the new data
    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0; // Out of memory
    }

    // Copy the received data to the end of the memory block
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize; // Update the size
    mem->memory[mem->size] = 0; // Null-terminate the string

    return realsize; // Return the size of the data processed
}

// Updated function signature
void fetch_weather_data(const char *location, const char *api_key, struct WeatherData *data, char **raw_data) {
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk; // Create a MemoryStruct to hold the data
    chunk.memory = malloc(1); // Initial allocation (1 byte)
    chunk.size = 0; // No data yet

    curl_global_init(CURL_GLOBAL_ALL); // Initialize libcurl

    curl = curl_easy_init();
    if (curl) {
        // Construct the URL for the weather API using api_key
        char url[256]; // Make sure this is large enough for the URL
        snprintf(url, sizeof(url), "https://api.weatherapi.com/v1/current.json?key=%s&q=%s", api_key, location);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Successfully received data, now parse the JSON
            parse_weather_data(chunk.memory, data); // Parse the JSON data into WeatherData

            // Store raw data
            *raw_data = strdup(chunk.memory); // Duplicate the raw memory to raw_data
        }

        // Cleanup
        curl_easy_cleanup(curl);
        free(chunk.memory); // Free the memory allocated for response data
    }

    curl_global_cleanup(); // Cleanup libcurl
}


void parse_weather_data(const char *json_response, struct WeatherData *data) {
    // Parse the JSON string into a cJSON object
    cJSON *json = cJSON_Parse(json_response);
    if (json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return; // Exit if JSON parsing fails
    }

    // Get the "location" and "current" sections from the JSON
    cJSON *location = cJSON_GetObjectItem(json, "location");
    cJSON *current = cJSON_GetObjectItem(json, "current");

    if (location && current) { // Check if both sections are present

        // Get the location name
        cJSON *name = cJSON_GetObjectItem(location, "name");
        if (name && name->valuestring) {
            strncpy(data->location_name, name->valuestring, sizeof(data->location_name) - 1);
            data->location_name[sizeof(data->location_name) - 1] = '\0'; // Ensure null-termination
        }

        // Get the region and country
        cJSON *region = cJSON_GetObjectItem(location, "region");
        if (region && region->valuestring) {
            strncpy(data->region, region->valuestring, sizeof(data->region) - 1);
            data->region[sizeof(data->region) - 1] = '\0'; // Ensure null-termination
        }

        cJSON *country = cJSON_GetObjectItem(location, "country");
        if (country && country->valuestring) {
            strncpy(data->country, country->valuestring, sizeof(data->country) - 1);
            data->country[sizeof(data->country) - 1] = '\0'; // Ensure null-termination
        }

        // Get the latitude and longitude
        cJSON *lat = cJSON_GetObjectItem(location, "lat");
        cJSON *lon = cJSON_GetObjectItem(location, "lon");
        if (lat && cJSON_IsNumber(lat)) {
            data->latitude = lat->valuedouble; // Store latitude
        }
        if (lon && cJSON_IsNumber(lon)) {
            data->longitude = lon->valuedouble; // Store longitude
        }

        // Get the current weather condition
        cJSON *condition = cJSON_GetObjectItem(current, "condition");
        if (condition) {
            cJSON *condition_text = cJSON_GetObjectItem(condition, "text");
            if (condition_text && condition_text->valuestring) {
                strncpy(data->condition, condition_text->valuestring, sizeof(data->condition) - 1);
                data->condition[sizeof(data->condition) - 1] = '\0'; // Ensure null-termination
            }
        }

        // Get temperature, humidity, and feels-like temperature
        cJSON *temp = cJSON_GetObjectItem(current, "temp_c");
        if (temp && cJSON_IsNumber(temp)) {
            data->temperature = temp->valuedouble; // Store temperature
        }

        cJSON *humidity = cJSON_GetObjectItem(current, "humidity");
        if (humidity && cJSON_IsNumber(humidity)) {
            data->humidity = humidity->valuedouble; // Store humidity
        }

        cJSON *feels_like = cJSON_GetObjectItem(current, "feelslike_c");
        if (feels_like && cJSON_IsNumber(feels_like)) {
            data->feels_like = feels_like->valuedouble; // Store feels-like temperature
        }

        // Get the wind direction
        cJSON *wind_dir = cJSON_GetObjectItem(current, "wind_dir");
        if (wind_dir && wind_dir->valuestring) {
            strncpy(data->wind_direction, wind_dir->valuestring, sizeof(data->wind_direction) - 1);
            data->wind_direction[sizeof(data->wind_direction) - 1] = '\0'; // Ensure null-termination
        }
    }

    // Clean up and free the JSON object
    cJSON_Delete(json);
}
