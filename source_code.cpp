

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int day;
    float temp_max;
    float temp_min;
    float humidity;
    float rainfall;
    float wind_speed;
    char condition[20];
} WeatherData;


void inputWeatherData(WeatherData data[], int days);
void displayWeatherData(WeatherData data[], int days);
void analyzeTemperature(WeatherData data[], int days);
void analyzeRainfall(WeatherData data[], int days);
void analyzeHumidity(WeatherData data[], int days);
void predictNextDay(WeatherData data[], int days);
void displayMenu();
void saveToFile(WeatherData data[], int days);
void displayASCIIGraph(WeatherData data[], int days);


int main() {
    WeatherData data[31];  
    int days, choice;
    
    printf("========================================\n");
    printf("   WEATHER DATA ANALYZER SYSTEM\n");
    printf("========================================\n\n");
    
    printf("Enter number of days for weather data (7-30): ");
    scanf("%d", &days);
    
    if(days < 7 || days > 30) {
        printf("Invalid input! Setting to 7 days.\n");
        days = 7;
    }
    
    inputWeatherData(data, days);
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayWeatherData(data, days);
                break;
            case 2:
                analyzeTemperature(data, days);
                break;
            case 3:
                analyzeRainfall(data, days);
                break;
            case 4:
                analyzeHumidity(data, days);
                break;
            case 5:
                displayASCIIGraph(data, days);
                break;
            case 6:
                predictNextDay(data, days);
                break;
            case 7:
                saveToFile(data, days);
                break;
            case 8:
                printf("\nThank you for using Weather Data Analyzer!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while(choice != 8);
    
    return 0;
}


void inputWeatherData(WeatherData data[], int days) {
    printf("\n--- Enter Weather Data ---\n");
    for(int i = 0; i < days; i++) {
        printf("\nDay %d:\n", i + 1);
        data[i].day = i + 1;
        
        printf("Maximum Temperature (°C): ");
        scanf("%f", &data[i].temp_max);
        
        printf("Minimum Temperature (°C): ");
        scanf("%f", &data[i].temp_min);
        
        printf("Humidity (%%): ");
        scanf("%f", &data[i].humidity);
        
        printf("Rainfall (mm): ");
        scanf("%f", &data[i].rainfall);
        
        printf("Wind Speed (km/h): ");
        scanf("%f", &data[i].wind_speed);
        
        printf("Weather Condition (Sunny/Cloudy/Rainy/Stormy): ");
        scanf("%s", data[i].condition);
    }
    printf("\nData input completed!\n");
}


void displayWeatherData(WeatherData data[], int days) {
    printf("\n========== WEATHER DATA RECORDS ==========\n");
    printf("%-5s %-8s %-8s %-10s %-10s %-12s %-12s\n", 
           "Day", "Max(°C)", "Min(°C)", "Humidity", "Rain(mm)", "Wind(km/h)", "Condition");
    printf("------------------------------------------------------------------------\n");
    
    for(int i = 0; i < days; i++) {
        printf("%-5d %-8.1f %-8.1f %-10.1f %-10.1f %-12.1f %-12s\n",
               data[i].day, data[i].temp_max, data[i].temp_min,
               data[i].humidity, data[i].rainfall, data[i].wind_speed,
               data[i].condition);
    }
    printf("\n");
}


void analyzeTemperature(WeatherData data[], int days) {
    float sum_max = 0, sum_min = 0;
    float max_temp = data[0].temp_max;
    float min_temp = data[0].temp_min;
    int max_day = 1, min_day = 1;
    
    for(int i = 0; i < days; i++) {
        sum_max += data[i].temp_max;
        sum_min += data[i].temp_min;
        
        if(data[i].temp_max > max_temp) {
            max_temp = data[i].temp_max;
            max_day = data[i].day;
        }
        
        if(data[i].temp_min < min_temp) {
            min_temp = data[i].temp_min;
            min_day = data[i].day;
        }
    }
    
    printf("\n========== TEMPERATURE ANALYSIS ==========\n");
    printf("Average Maximum Temperature: %.2f°C\n", sum_max/days);
    printf("Average Minimum Temperature: %.2f°C\n", sum_min/days);
    printf("Highest Temperature: %.2f°C (Day %d)\n", max_temp, max_day);
    printf("Lowest Temperature: %.2f°C (Day %d)\n", min_temp, min_day);
    printf("Temperature Range: %.2f°C\n", max_temp - min_temp);
    printf("\n");
}


void analyzeRainfall(WeatherData data[], int days) {
    float total_rain = 0;
    int rainy_days = 0;
    
    for(int i = 0; i < days; i++) {
        total_rain += data[i].rainfall;
        if(data[i].rainfall > 0) {
            rainy_days++;
        }
    }
    
    printf("\n========== RAINFALL ANALYSIS ==========\n");
    printf("Total Rainfall: %.2f mm\n", total_rain);
    printf("Number of Rainy Days: %d\n", rainy_days);
    printf("Average Rainfall: %.2f mm/day\n", total_rain/days);
    if(rainy_days > 0) {
        printf("Average Rainfall on Rainy Days: %.2f mm\n", total_rain/rainy_days);
    }
    printf("Dry Days: %d\n", days - rainy_days);
    printf("\n");
}


void analyzeHumidity(WeatherData data[], int days) {
    float sum_humidity = 0;
    float max_humidity = data[0].humidity;
    float min_humidity = data[0].humidity;
    
    for(int i = 0; i < days; i++) {
        sum_humidity += data[i].humidity;
        if(data[i].humidity > max_humidity) max_humidity = data[i].humidity;
        if(data[i].humidity < min_humidity) min_humidity = data[i].humidity;
    }
    
    float avg_humidity = sum_humidity / days;
    
    printf("\n========== HUMIDITY ANALYSIS ==========\n");
    printf("Average Humidity: %.2f%%\n", avg_humidity);
    printf("Maximum Humidity: %.2f%%\n", max_humidity);
    printf("Minimum Humidity: %.2f%%\n", min_humidity);
    
    if(avg_humidity < 30) {
        printf("Classification: Dry\n");
    } else if(avg_humidity < 60) {
        printf("Classification: Moderate\n");
    } else {
        printf("Classification: Humid\n");
    }
    printf("\n");
}


void displayASCIIGraph(WeatherData data[], int days) {
    printf("\n========== TEMPERATURE TREND GRAPH ==========\n");
    printf("(Each * represents maximum temperature)\n\n");
    

    float max = data[0].temp_max;
    float min = data[0].temp_max;
    for(int i = 0; i < days; i++) {
        if(data[i].temp_max > max) max = data[i].temp_max;
        if(data[i].temp_max < min) min = data[i].temp_max;
    }
    

    for(int temp = (int)max + 1; temp >= (int)min - 1; temp--) {
        printf("%3d°C |", temp);
        for(int i = 0; i < days; i++) {
            if((int)data[i].temp_max >= temp) {
                printf(" * ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
    
    printf("     +");
    for(int i = 0; i < days; i++) {
        printf("---");
    }
    printf("\n      ");
    for(int i = 0; i < days; i++) {
        printf("D%-2d", data[i].day);
    }
    printf("\n\n");
}


void predictNextDay(WeatherData data[], int days) {

    int period = (days >= 3) ? 3 : days;
    float pred_max = 0, pred_min = 0, pred_humidity = 0, pred_wind = 0;
    
    for(int i = days - period; i < days; i++) {
        pred_max += data[i].temp_max;
        pred_min += data[i].temp_min;
        pred_humidity += data[i].humidity;
        pred_wind += data[i].wind_speed;
    }
    
    pred_max /= period;
    pred_min /= period;
    pred_humidity /= period;
    pred_wind /= period;
    

    int recent_rainy = 0;
    for(int i = days - period; i < days; i++) {
        if(data[i].rainfall > 0) recent_rainy++;
    }
    float rain_probability = (recent_rainy * 100.0) / period;
    
    printf("\n========== NEXT DAY PREDICTION ==========\n");
    printf("Predicted Maximum Temperature: %.2f°C\n", pred_max);
    printf("Predicted Minimum Temperature: %.2f°C\n", pred_min);
    printf("Predicted Humidity: %.2f%%\n", pred_humidity);
    printf("Predicted Wind Speed: %.2f km/h\n", pred_wind);
    printf("Rainfall Probability: %.2f%%\n", rain_probability);
    
    if(rain_probability > 60) {
        printf("Predicted Condition: Rainy\n");
    } else if(rain_probability > 30) {
        printf("Predicted Condition: Cloudy\n");
    } else {
        printf("Predicted Condition: Sunny\n");
    }
    
    printf("\n* Prediction based on %d-day moving average\n\n", period);
}


void saveToFile(WeatherData data[], int days) {
    FILE *file = fopen("weather_data.txt", "w");
    
    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fprintf(file, "WEATHER DATA ANALYSIS REPORT\n");
    fprintf(file, "=============================\n\n");
    
    for(int i = 0; i < days; i++) {
        fprintf(file, "Day %d:\n", data[i].day);
        fprintf(file, "  Max Temp: %.1f°C\n", data[i].temp_max);
        fprintf(file, "  Min Temp: %.1f°C\n", data[i].temp_min);
        fprintf(file, "  Humidity: %.1f%%\n", data[i].humidity);
        fprintf(file, "  Rainfall: %.1f mm\n", data[i].rainfall);
        fprintf(file, "  Wind Speed: %.1f km/h\n", data[i].wind_speed);
        fprintf(file, "  Condition: %s\n\n", data[i].condition);
    }
    
    fclose(file);
    printf("\nData saved to 'weather_data.txt' successfully!\n\n");
}


void displayMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Display Weather Data\n");
    printf("2. Temperature Analysis\n");
    printf("3. Rainfall Analysis\n");
    printf("4. Humidity Analysis\n");
    printf("5. Display Temperature Graph\n");
    printf("6. Predict Next Day Weather\n");
    printf("7. Save Data to File\n");
    printf("8. Exit\n");
    printf("===============================\n");
    printf("Enter your choice: ");
}
