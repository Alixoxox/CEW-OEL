#include <stdio.h>
#include <stdlib.h>

// Function to clear the contents of a file
void clearFile(const char *filePath) {
    FILE *file = fopen(filePath, "w"); // Open in write mode to clear contents
    if (file == NULL) {
        fprintf(stderr, "Error clearing file: %s\n", filePath);
        return;
    }
    fclose(file); // Close the file after clearing
}

int main() {
    const char *filePath = "Data/Wind_Speed_Data.txt";

    // Opening the file to read the contents
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading\n");
        return 1; // Return an error code
    }

    char str_wind[100];  // str_wind array to store each line read from the file
    double sum = 0.0;    // Variable to store the sum of wind speeds
    double windSpeed;    // Variable to store each wind speed
    int count = 0;       // Variable to store the count of wind speeds

    // Reading each line from the file until the end of the file is reached
    while (fgets(str_wind, sizeof(str_wind), file) != NULL) {
        // Converting the read string stored in str_wind to a double
        windSpeed = strtod(str_wind, NULL);

        // Checking if the conversion was successful
        if (windSpeed != 0 || (windSpeed == 0 && str_wind[0] == '0')) {
            // Accumulate the sum and increment the count
            sum += windSpeed;
            count++;
        }
    }
    fclose(file);

    // Checking if any wind speeds were read
    if (count > 0) {
        // Calculating the mean
        double mean = sum / count;

        // Printing the mean
        printf("Mean wind speed: %.2f km/h \n", mean);
    } else {
        // If there were no wind speeds in the file
        printf("No wind speeds found in the file\n");
    }

    // Clear the file after processing
    clearFile(filePath);

    return 0;
}
