#ifndef API_H
#define API_H

struct WeatherData {
    char location_name[100];
    double temperature;
    double humidity;
    char condition[100];
    double latitude;
    double longitude;
    char region[100];
    char country[100];
    char wind_direction[100];
    double feels_like;
};

void fetch_weather_data(const char *location, const char *api_key, struct WeatherData *data, char **raw_data); // Updated declaration

void parse_weather_data(const char *json_response, struct WeatherData *data);

#endif // API_H
