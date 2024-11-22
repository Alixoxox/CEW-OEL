#include <stdio.h>
#include <curl/curl.h>
#include <jansson.h>
#include "api.h"

int main() {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize a libcurl easy handle
    CURL *curl = curl_easy_init();

    // Set the API URL
    const char *url = "https://api.openweathermap.org/data/2.5/weather?units=metric&q=karachi&appid=7821014de233ecf098180185706f59ca";

    if (curl) {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set the callback function to handle the API response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}


