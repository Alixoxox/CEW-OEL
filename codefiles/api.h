#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

// Callback function for handling API responses
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

#endif // API_H
