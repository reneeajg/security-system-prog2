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
#define MAX_SEC 5

/*
initializeGuards: scans guards.txt for available guest information and saves them into the GUARDS array of structure
Parameters:
GUARDS[] - array of structure for guest
Returns: 0 if file is empty, otherwise, returns the amount of accounts read by the function 
*/
int initializeGuards(secuType GUARDS[]){
	int ctr = 0;
    secuType g;
    FILE *fp;
	fp = fopen("guards.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    while (fscanf(fp, "%s %s", g.user, g.s_password) == 2) {
        GUARDS[ctr] = g;
        ctr++;
    } 

    fclose(fp);
    return ctr;
}

/*
displayGuards: Displays the guards array of structure in the CLI and guardsout.txt file
Parameters:
GUARDS[] - array of structure for guards
n - number of guards
Returns: none
*/
void displayGuards(secuType GUARDS[], int n) {
    FILE *fp = fopen("guardsout.txt", "w");

    if (fp == NULL) {
       	fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    printf("\nList of Guards:\n");
    printf("---------------------------------------------------------\n");
    fprintf(fp, "List of Guards:\n");
    fprintf(fp, "---------------------------------------------------------\n");
    
    int i;
    for (i = 0; i < n; i++) {
        printf("Guard #%d\t", i + 1);
        printf("%s\n", GUARDS[i].user);
        printf("---------------------------------------------------------\n");

        fprintf(fp, "Guard #%d\t", i + 1);
        fprintf(fp, "%s\n", GUARDS[i].user);
        fprintf(fp, "---------------------------------------------------------\n");
    }

    fclose(fp);
}

/*
appendGuards: Adds a guard account to the GUARDS[] array
Parameters:
GUARDS[] - array of structure for guard
*n - number of accounts in the array
Returns: none
*/
void appendGuards(secuType GUARDS[], int *n) {

    secuType newGuard;
    FILE *fp = fopen("guards.txt", "a"); 
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }
    
	if (*n == MAX_SEC) {
		printf("Maximum number of accounts have been reached!\n"); 
	} else {
	    printf("Enter guard username: ");
	    scanf("%s", newGuard.user);
	    printf("Create password: ");
	    scanf("%s", newGuard.s_password);
	
	    fprintf(fp, "\n%s %s",newGuard.user, newGuard.s_password);
	    
	    fclose(fp);
	
	    GUARDS[*n] = newGuard;
	    (*n)++; 
	
	    printf("New security account added successfully!\n");
	
	    displayGuards(GUARDS, *n);
	}

}

/*
sMenu: Dashboard for all the guards’ controls
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
void sMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards, addressType address){
	int choice;
	
	do{
		printf(RED"\nWELCOME, SECURITY!\n");
		printf(DEFAULT"1. View Reports\n2. Change Password\n3. Logout\nChoice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: viewReports(); break;
			case 2: editGuardPassword(GUARDS,nGuards); break;
			case 3: printf("Logging you out...\n"); break;
			default: printf("Invalid choice! try again.\n");
		}
	}while(choice != 2);
}

/*
editGuardtPassword: Edits the password of the logged in guard user
Parameters:
GUARDS[] - array of structure for guards
nguarsd- number of guards
Returns: none
*/
void editGuardPassword(secuType GUARDS[], int nguards){
	int i, found = 0;
	String username, npassword, cpassword;
	
	
	printf("Hello, security personnel, please enter your username: ");
    scanf("%s", username);
    

    for (i = 0; i < nguards; i++) {
        if (strcmp(GUARDS[i].user, username) == 0) {
            found = 1;
            printf("Enter new password: ");
            scanf("%s", npassword);
            if(strcmp(GUARDS[i].s_password,npassword) != 0){
            	do {
                printf("Confirm new password: ");
                scanf("%s", cpassword);
	                if (strcmp(npassword, cpassword) != 0) {
	                    printf("Passwords do not match! Try again.\n");
	                }
	            } while (strcmp(npassword, cpassword) != 0);
	            strcpy(GUARDS[i].s_password, cpassword);
	            printf("Password updated successfully.\n");
			} else {
				printf("Current and new password match. Please try again.\n");
			}
        }
    }

    if (!found) {
        printf("Username not found.\n");
    }
    
    updateGuardFile(GUARDS,nguards);
}

/*
updateGuardFile: updates the guards.txt file for when the admin adds or deletes an admin, or changes the password
Parameters:
GUARDS[] - array of struct for guard
nGuards- number of guard accounts
Returns: none
*/
void updateGuardFile(secuType GUARDS[], int nGuards) {
    FILE *fp = fopen("guards.txt", "w");
    if (fp == NULL) {
        printf("Error opening guests.txt for updating!\n");
        return;
    }
	int i;
    for (i = 0; i < nGuards; i++) {
        fprintf(fp, "%s %s\n", GUARDS[i].user, GUARDS[i].s_password);
    }

    fclose(fp);
}

