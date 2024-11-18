
#include <stdio.h>
#include <stdlib.h>
#include "alerts.h"

void check_alerts(double temperature, double humidity,double feels_like) {
    const double TEMP_THRESHOLD = 30.0; // Example threshold for temperature
    const double HUMIDITY_THRESHOLD = 60.0; // Example threshold for humidity
    const double FEELS_LIKE_THRESHOLD=35.0;
    printf("\nChecking alerts: Temperature = %.2f, Humidity = %.2f \n", temperature, humidity); // Debug output

    if (temperature>TEMP_THRESHOLD && humidity>HUMIDITY_THRESHOLD){
        printf("WARNING: Extreme heat Conditions Detected\n");
        system("notify-send 'High Humidity And High Temp Alert!' \n'Please Stay in a chilled Enivornment.Avoid Going Out in Heat.\nTake necessary precautions for your health'");
    }
    else if (temperature > TEMP_THRESHOLD ||feels_like>FEELS_LIKE_THRESHOLD) {
        printf("Alert: High Temperature Detected!\n");
        system("notify-send 'High Temperature Alert!' 'Temperature has exceeded the threshold. Stay in a cool enivornment'");
        }

    else if (humidity > HUMIDITY_THRESHOLD) {
        printf("Alert: High Humidity Detected!\n");
        system("notify-send 'High Humidity Alert!' 'Humidity exceeded the threshold.'");
    }
}
