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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED "\e[0;91m"
#define DEFAULT "\x1b[0m"
#define MAX_GUEST 5
#define SENSORS 5

/*
initializeGuest: scans guests.txt for available guest information and saves them into the GUESTS array of structure
Parameters:
GUESTS[] - array of structure for guest
Returns: 0 if file is empty, otherwise, returns the amount of accounts read by the function 
*/
int initializeGuests(guestType GUESTS[]){
	int ctr = 0;
    guestType g;
    FILE *fp;
	fp = fopen("guests.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    while (fscanf(fp, "%s %s", g.user, g.g_password) == 2) {
        GUESTS[ctr] = g;
        ctr++;
    }  

    fclose(fp);
    return ctr;
}

/*
displayGuest: Displays the guest array of structure in the CLI and guestsout.txt file
Parameters:
GUESTS[] - array of structure for guest
n - number of admins
Returns: none
*/
void displayGuest(guestType GUESTS[], int n) {
    FILE *fp = fopen("guestsout.txt", "w");

    if (fp == NULL) {
       	fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    printf("\nList of Guests:\n");
    printf("---------------------------------------------------------\n");
    fprintf(fp, "List of Guests:\n");
    fprintf(fp, "---------------------------------------------------------\n");
    
    int i;
    for (i = 0; i < n; i++) {
        printf("Guest #%d\t", i + 1);
        printf("%s\n", GUESTS[i].user);
        printf("---------------------------------------------------------\n");

        fprintf(fp, "Guest #%d\t", i + 1);
        fprintf(fp, "%s\n", GUESTS[i].user);
        fprintf(fp, "---------------------------------------------------------\n");
    }

    fclose(fp);
}

/*
appendGuest: Adds a guest account to the GUESTS[] array
Parameters:
GUESTS[] - array of structure for guest
*numGUESTS - number of accounts in the array
Returns: none
*/
void appendGuest(guestType GUESTS[], int *numGUESTS) {

    guestType newGuest;
    FILE *fp = fopen("guests.txt", "a"); 

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    if (*numGUESTS == MAX_GUEST) {
	    printf("Maximum number of accounts reached!\n");
	} else {
	    printf("Enter guest username: ");
	    scanf("%s", newGuest.user);
	    printf("Create password: ");
	    scanf("%s", newGuest.g_password);

	    fprintf(fp, "\n%s %s",newGuest.user, newGuest.g_password);
	    fclose(fp); 
	
	    GUESTS[*numGUESTS] = newGuest;
	    (*numGUESTS)++; 
	
	    printf("New guest account added successfully!\n");
	
	    displayGuest(GUESTS, *numGUESTS);
	}

}

/*
gMenu: Dashboard for all the guests’ controls
Parameters:
ADMINS[] - array of struct for admin
GUEST[] - array of struct for guest
GUARDS - array of struct for guards
nAdmins - number of admin accounts
nGuests - number of guest accounts
nGuards - number of guard accounts
Address - structure for the home address
sensorStatus[] - integer array for sensor status
Returns: none
*/
void gMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nGuards, int nAdmins, int nGuests, addressType address, int sensorStatus[]) {
    int choice;
    do {
        printf(RED "\nWELCOME, GUEST!\n");
        printf(DEFAULT "1. Record Security Simulation\n2. View Reports\n3. Edit Password\n4. Logout\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isSensorActive(sensorStatus)) {  
                    printf("Sensors have not been configured. Returning to menu.\n");
                } else {
                    adminSimulation(sensorStatus);
                }
                break;
            case 2:
                viewReports();
                break;
            case 3:
                editGuestPassword(GUESTS,nGuests);
                break;
            case 4:
                printf("Logging you out...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

/*
editGuestPassword: Edits the password of the logged in guest user
Parameters:
GUESTS[] - array of structure for guest
nguests- number of admins
Returns: none
*/
void editGuestPassword(guestType GUESTS[], int nguests){
	int i, found = 0;
	String username, npassword, cpassword;
	
	
	printf("Hello guest, please enter your username: ");
    scanf("%s", username);

    for (i = 0; i < nguests; i++) {
        if (strcmp(GUESTS[i].user, username) == 0) {
            found = 1;
            printf("Enter new password: ");
            scanf("%s", npassword);
            if(strcmp(GUESTS[i].g_password,npassword) != 0) {
            	do {
                printf("Confirm new password: ");
                scanf("%s", cpassword);
	                if (strcmp(npassword, cpassword) != 0) {
	                    printf("Passwords do not match! Try again.\n");
	                }
	            } while (strcmp(npassword, cpassword) != 0);
	            strcpy(GUESTS[i].g_password, cpassword);
	            printf("Password updated successfully.\n");
			} else {
				printf("Current and new password match. Please try again.\n");
			}
        }
    }

    if (!found) {
        printf("Username not found.\n");
    }
    
    FILE *fp = fopen("guests.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    for (i = 0; i < nguests; i++) {
        fprintf(fp, "%s %s\n", GUESTS[i].user, GUESTS[i].g_password);
    }

    fclose(fp);
}

/*
updateGuestFile: updates the guests.txt file for when the admin adds or deletes an admin, or changes the password
Parameters:
GUESTS[] - array of struct for guest
nGuests - number of guest accounts
Returns: none
*/
void updateGuestFile(guestType GUESTS[], int nGuests) {
    FILE *fp = fopen("guests.txt", "w");
    if (fp == NULL) {
        printf("Error opening guests.txt for updating!\n");
        return;
    }
	int i;
    for (i = 0; i < nGuests; i++) {
        fprintf(fp, "%s %s\n", GUESTS[i].user, GUESTS[i].g_password);
    }

    fclose(fp);
}







