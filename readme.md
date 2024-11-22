# Environmental Monitoring Project

## Prerequisites

Before running the Environmental Monitoring Project, make sure you have the following installed on your Linux system:

1. **libcurl** 
   To handle HTTP requests, install libcurl:
   ```bash
   sudo apt-get install libcurl4-openssl-dev
   ```

2. **Jansson** 
   To handle JSON encoding/decoding, install Jansson:
   ```bash
   sudo apt-get install libjansson-dev
   ```

## Running the Project

1. **To print output on the terminal**, use the following command:
   ```bash
   ./automate.sh
   ```

2. **To automate the project**, run it in the background with `nohup`:
   ```bash
   nohup ./automate.sh &
   ```

3. **To view the output** of the automated task, check the `nohup.out` file:
   ```bash
   cat nohup.out
   ```
4. **To go/view the processed data output**
   Go to the `Data/Weather_Processed.csv` directory and view the contents using the following commands:
   ```bash
   cd Data
   cat Weather_Processed.csv
   ```
    
## Customizing the Time Interval

To change the interval (time in seconds) and the number of iterations:

1. Open the `automate.sh` file.
2. Modify the `interval` and `no_of_iterations` variables to your desired values:
   - `interval` is the time in seconds between each task (e.g., 1800 for 30 minutes).
   - `no_of_iterations` is the number of times the task will run.

Example:
```bash
interval=1800   # 30 minutes
no_of_iterations=10
```
Save the file after making changes.
