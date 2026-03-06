/***********************************************************************************
**********************
This is to certify that this project is our own work, based on our personal efforts in studying and
applying the concepts learned. We have constructed the functions and their respective algorithms and
corresponding code by ourselves. The program was run, tested, and debugged by our own efforts. We
further certify that we have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

		CHUNG, JOSH MATTHEW A., 12339997
		GUERRA, RENEE ANGELI J., 12475688
************************************************************************************
*********************/

/*
displayIntruder - shows the house layout based on sensor status and intruder location
@param sensorStatus - array tracking active/inactive sensors
@param intruderLocation - index of triggered sensor 
*/
void displayIntruder(int sensorStatus[SENSORS], int intruderLocation) {
    printf(DEFAULT"\n===================================\n");
    printf("      HOUSE SECURITY SIMULATION    \n");
    printf("===================================\n");

    printf("     [Front Door]      [Back Door] \n");

    if (sensorStatus[0] == 1) {
        printf("         [X]                ");
    } else {
        printf("         [ ]                ");
    }

    if (sensorStatus[1] == 1) {
        printf("[X]       \n");
    } else {
        printf("[ ]       \n");
    }

    if (intruderLocation == 0) {
        printf("        O  (Intruder!)       \n");
        printf("        |                   \n");
        printf("       / \\                  \n");
    } else if (intruderLocation == 1) {
        printf("                        O (Intruder!)\n");
        printf("                        |            \n");
        printf("                       / \\           \n");
    }

    printf("\n    [Living Room]     [Bedroom]   \n");

    if (sensorStatus[2] == 1) {
        printf("         [X]               ");
    } else {
        printf("         [ ]               ");
    }

    if (sensorStatus[3] == 1) {
        printf("[X]       \n");
    } else {
        printf("[ ]       \n");
    }

    if (intruderLocation == 2) {
        printf("      O (Intruder!)        \n");
        printf("      |                    \n");
        printf("     / \\                   \n");
    } else if (intruderLocation == 3) {
        printf("                     O (Intruder!)   \n");
        printf("                     |               \n");
        printf("                    / \\              \n");
    }

    printf("\n            [Garage]            \n");

    if (sensorStatus[4] == 1) {
        printf("                [X]               \n");
    } else {
        printf("                [ ]               \n");
    }

    if (intruderLocation == 4) {
        printf("               O (Intruder!)       \n");
        printf("               |                   \n");
        printf("              / \\                  \n");
    }

    printf("===================================\n");
}

/* generateReport records a security event in the report
@param report - pointer to SecurityReport struct
@param location - where event occurred
@param panicPressed - 1 if panic button pressed, 0 otherwise
@param eventTime - time of event
@return none
Pre-condition: report pointer is valid, location/time strings formatted correctly */
void generateReport(SecurityReport *report, String20 location, int panicPressed, String20 eventTime) {
    int success = 1;
    
    if (report == NULL) {
        printf("Error: Null report pointer\n");
        success = 0;
    }
    else if (report->count >= 50) {
        printf("Warning: Maximum report capacity reached (50 events). This event was not recorded.\n");
        success = 0;
    }
    else if (strlen(location) == 0 || strlen(eventTime) == 0) {
        printf("Error: Invalid location or time data\n");
        success = 0;
    }

    if (success) {
        strcpy(report->events[report->count].location, location);
        strcpy(report->events[report->count].time, eventTime);
        report->events[report->count].panic_pressed = panicPressed;
        report->count++;
    }
}

/* displayReports shows security events and saves to files
@param report - pointer to SecurityReport struct
@param reportDate - date of report
@param reportTime - time of report
@return none
Pre-condition: report contains valid events */
void displayReports(SecurityReport *report, String20 reportDate, String20 reportTime) {
    FILE *logFile;
    int i;
    char panicStatus[20];
    
    appendSecurityReport(report, reportDate, reportTime);

    logFile = fopen("security_log.txt", "w");
    if (logFile == NULL) {
        printf("Error: Could not create log file\n");
        return;
    }

    fprintf(logFile, "=== SECURITY REPORT ===\n");
    fprintf(logFile, "Report Date: %s\n", reportDate);
    fprintf(logFile, "Report Time: %s\n", reportTime);
    fprintf(logFile, "---------------------------------\n");
    fprintf(logFile, "TIME     | LOCATION          | PANIC BUTTON\n");
    fprintf(logFile, "---------|-------------------|-------------\n");

    for (i = 0; i < report->count; i++) {
        if (report->events[i].panic_pressed == 1) {
            strcpy(panicStatus, "PRESSED");
        } else {
            strcpy(panicStatus, "Not Pressed");
        }
        
        fprintf(logFile, "%-8s | %-17s | %s\n",
               report->events[i].time,
               report->events[i].location,
               panicStatus);
    }

    fprintf(logFile, "===================================\n");
    fclose(logFile);

    printf("\n\n=== SECURITY SIMULATION REPORT ===\n");
    printf("Report Date: %s\n", reportDate);
    printf("Report Time: %s\n", reportTime);
    printf("---------------------------------\n");
    printf("TIME     | LOCATION          | PANIC BUTTON\n");
    printf("---------|-------------------|-------------\n");

    for (i = 0; i < report->count; i++) {
        if (report->events[i].panic_pressed == 1) {
            strcpy(panicStatus, "PRESSED");
        } else {
            strcpy(panicStatus, "Not Pressed");
        }
        
        printf("%-8s | %-17s | %s\n", 
               report->events[i].time,
               report->events[i].location,
               panicStatus);
    }
    printf("===================================\n\n");
}

/* appendSecurityReport adds report to history file
@param report - pointer to SecurityReport struct
@param reportDate - date of report
@param reportTime - time of report
@return none
Pre-condition: report contains valid events */
void appendSecurityReport(SecurityReport *report, String20 reportDate, String20 reportTime) {
    int success = 1;
    FILE *file = NULL;
    
    file = fopen("security_history.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open security history file\n");
        success = 0;
    }

    if (success) {
        int i;
        char panicStatus[20];
        
        fprintf(file, "\n=== SECURITY REPORT ===\n");
        fprintf(file, "Report Date: %s\n", reportDate);
        fprintf(file, "Report Time: %s\n", reportTime);
        fprintf(file, "---------------------------------\n");
        fprintf(file, "TIME     | LOCATION          | PANIC BUTTON\n");
        fprintf(file, "---------|-------------------|-------------\n");

        for (i = 0; i < report->count; i++) {
            if (report->events[i].panic_pressed == 1) {
                strcpy(panicStatus, "PRESSED");
            } else {
                strcpy(panicStatus, "Not Pressed");
            }
            
            fprintf(file, "%-8s | %-17s | %s\n",
                   report->events[i].time,
                   report->events[i].location,
                   panicStatus);
        }

        fprintf(file, "===================================\n");
        
        if (fclose(file) != 0) {
            printf("Warning: Error closing security history file\n");
        }
    }
}
/* viewReports displays all historical security reports
@param none
@return none
 */
void viewReports() {
    FILE *file = fopen("security_history.txt", "r");
    int success = 1;
    
    if (file == NULL) {
        printf("No security reports found in history.\n");
        success = 0;
    }

    if (success) {
        printf("\n=== SECURITY REPORT HISTORY ===\n");
        
        report line;
        int lineCount = 0;
        
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            lineCount++;
        }
        
        if (lineCount == 0) {
            printf("\nFile is empty - no reports available.\n");
        }
        
        if (fclose(file) != 0) {
            printf("Warning: Error closing history file\n");
        }
    }
}

/* inputDateTime - gets valid date/time input from user
@param date - string to store date (YYYY-MM-DD)
@param time - string to store time (HH:MM)
@return none */
void inputDateTime(String20 date, String20 time) {
    int dateValid = 0;
    int timeValid = 0;
    int attempts = 0;
    int maxAttempts = 3;  
    int shouldExit = 0;  
    
    printf("\n=== REPORT GENERATION ===\n");
    
    // Date input with retry
    while (!dateValid && attempts < maxAttempts && !shouldExit) {
        printf("Enter report date (YYYY-MM-DD): ");
        if (scanf("%20s", date) != 1) {
            printf("Error reading date.\n");
        }
        else if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
            printf("Invalid date format. Please use YYYY-MM-DD format.\n");
        }
        else {
            dateValid = 1;
        }
        attempts++;
        
        if (!dateValid && attempts < maxAttempts) {
            printf("%d attempts remaining.\n", maxAttempts - attempts);
        }
        else if (!dateValid) {
            printf("Maximum attempts reached for date.\n");
            shouldExit = 1;
        }
    }

    attempts = 0;
    
    while (!timeValid && attempts < maxAttempts && !shouldExit) {
        printf("Enter report time (HH:MM): ");
        if (scanf("%20s", time) != 1) {
            printf("Error reading time.\n");
        }
        else if (strlen(time) != 5 || time[2] != ':') {
            printf("Invalid time format. Please use HH:MM format.\n");
        }
        else {
            timeValid = 1;
        }
        attempts++;
        
        if (!timeValid && attempts < maxAttempts) {
            printf("%d attempts remaining.\n", maxAttempts - attempts);
        }
        else if (!timeValid) {
            printf("Maximum attempts reached for time.\n");
            shouldExit = 1;
        }
    }

    if (shouldExit) {
        strcpy(date, "");
        strcpy(time, "");
    }
}

/*
adminSimulation - simulates emergency situations
@param sensorStatus - array of active/inactive sensors
@param intruderLocation - index of triggered sensor
Return: none
*/
void adminSimulation(int sensorStatus[SENSORS]) {
    int choice;
    int intruderLocation = -1;
    int run = 1;
    char panicChoice;
    int restartChoice;
    SecurityReport report;
    String20 locations[5];
    String20 eventDate;
    String20 eventTime;
    
    strcpy(locations[0], "Front Door");
    strcpy(locations[1], "Back Door");
    strcpy(locations[2], "Living Room");
    strcpy(locations[3], "Bedroom");
    strcpy(locations[4], "Garage");
    
    report.count = 0;
    
    while (run == 1) {
        displayIntruder(sensorStatus, intruderLocation);

        printf(DEFAULT"\nWhich sensor was tripped?\n");
        printf("1. Front Door\n");
        printf("2. Back Door\n");
        printf("3. Living Room\n");
        printf("4. Bedroom\n");
        printf("5. Garage\n");
        printf("6. Exit and Generate Report\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            int sensorIndex = choice - 1;
            
            if (sensorStatus[sensorIndex] == 1) {
                intruderLocation = sensorIndex;
                
                displayIntruder(sensorStatus, intruderLocation);
                printf("\nAlert! Intruder detected at %s!\n", locations[sensorIndex]);

                printf("\nPress panic button? [Y/N]: ");
                scanf(" %c", &panicChoice);

                if (panicChoice == 'Y' || panicChoice == 'y') {
                    printf("\n[PANIC BUTTON PRESSED!]\n");
                    inputDateTime(eventDate, eventTime);
                    generateReport(&report, locations[sensorIndex], 1, eventTime);
                    
                    printf("\nWould you like to:\n");
                    printf("1. Restart simulation\n");
                    printf("2. Exit and generate report\n");
                    printf("Enter choice (1 or 2): ");
                    scanf("%d", &restartChoice);

                    if (restartChoice == 1) {  
                        intruderLocation = -1; 
                    } else if (restartChoice == 2) {
                        run = 0; 
                    }
                } else {
                    printf(RED"Report has not been recorded.\n");
                }
            } else {
                printf("\nSensor at %s is not active! No intruder detected.\n", locations[sensorIndex]);
            }
        } 
        else if (choice == 6) {
            printf("\nExiting Simulation...\n");
            run = 0;
        } 
        else {
            printf("\nInvalid choice! Please enter 1-6.\n");
        }
    }
    
    if (report.count > 0) {
        displayReports(&report, eventDate, eventTime);
    } else {
        printf("\nNo security events recorded.\n");
    }
}

/* isSensorActive - checks if any sensor is active
@param sensorStatus - array of sensor states
@return 1 if any sensor active, 0 otherwise
 */
int isSensorActive(int sensorStatus[]) {
	int active = 0;
	int i;
    for (i = 0; i < SENSORS; i++) {
        if (sensorStatus[i] != 0) {
            active = 1;  
        }
    }
    if(active) {
    	return 1;
	} else
		return 0;
}

/* sensorSetup - configures sensor activation states
@param sensorStatus - array to modify
@return none */
void sensorSetup(int sensorStatus[SENSORS]) {
    int x;
    char AllSensors;
    int activity;

    printf(RED"\nSENSOR SETUP\n");
    printf(DEFAULT"Hello Admin. Welcome to the Sensor Setup!\n");

    for (x = 0; x < SENSORS; x++) {
        sensorStatus[x] = 0;
    }

    printf("The security system has 5 programmable sensors.\n");
    printf("Do you want to ACTIVATE all sensors? Choose [Y/N]: ");
    scanf(" %c", &AllSensors);

    if (AllSensors == 'Y' || AllSensors == 'y') {
        for (x = 0; x < SENSORS; x++) {
            sensorStatus[x] = 1;  
        }
    } else {
        printf("Choose which sensors to activate or deactivate individually.\n");
        for (x = 0; x < SENSORS; x++) {
            printf("Current Status: Sensor %d ", x + 1);
            if (sensorStatus[x] == 1) {
                printf("ACTIVE [X]\n");
            } else {
                printf("INACTIVE [ ]\n");
            }

            printf("Choose activity for Sensor %d (0 - Deactivate, 1 - Activate): ", x + 1);
            scanf("%d", &activity);
            sensorStatus[x] = activity;  
        }
    }
}

/* displaySensorsStatus - shows current sensor states
@param sensorStatus - displays status of the sensors
@return none
 */
void displaySensorsStatus(int sensorStatus[SENSORS]) {
    int x;
    printf("\nCurrent status of all the sensors:\n");
    for (x = 0; x < SENSORS; x++) {
        printf("Sensor %d: ", x);
        if (sensorStatus[x]) {
            printf("ACTIVE\n");
        } else {
            printf("INACTIVE\n");
        }
    }
}

/* sensorControlPanel - provides sensor management menu
@param sensorStatus - array to manage
@return none
 */
void sensorControlPanel(int sensorStatus[SENSORS]) {
    int choice;
    char continueS;
    
    printf("---------------------");
    printf(RED"\n\nSENSOR CONTROL PANEL\n");
    printf("Welcome to the Sensor Control Panel!\n");
    
    do {
        printf(DEFAULT"\nOptions:\n");
        printf("1. Display Sensor Setup\n");
        printf("2. Configure Sensor Status\n"); 
        printf("3. Back to Main Menu\n");
        printf("Choose [1/2/3]: ");
        scanf("%d", &choice);
    
        switch (choice) {
            case 1: { 
                displaySensorsStatus(sensorStatus);
                break;
            }
            case 2: {
                sensorSetup(sensorStatus);
                break;
            }
            case 3: {
            	printf("Returning to main menu...\n");
                continueS = 'N';
				break;
			}
            default: {
                printf("Invalid choice. Please try again.\n");
            }   
        }
        
        if (choice != 4) {
            printf("\nWould you like to continue in Sensor Control Panel? [Y/N]: ");
            scanf(" %c", &continueS);
        }
    } while (continueS == 'Y' || continueS == 'y');

    printf("Exiting Sensor Control Panel...\n");
}
