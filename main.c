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
#include <stdlib.h>
#include <string.h>

#include "MP-STRUCTS.h"
#include "Admin.c"
#include "Security.c"
#include "Guest.c" 
#include "sim.c"

//array sizes
#define MAX_ADMIN 2
#define MAX_GUEST 5
#define MAX_SEC 5
#define MAX_REPORTS 50
#define SENSORS 5

//colors
#define RED "\e[0;91m"
#define DEFAULT "\x1b[0m"
#define PINK "\e[38;5;212m"


/* login authenticates user credentials against all account types
@param ADMINS - array of admin accounts
@param GUESTS - array of guest accounts 
@param GUARDS - array of security accounts
@param nAdmins - number of admin accounts
@param nGuests - number of guest accounts
@param nGuards - number of security accounts
@return 1 for admin, 2 for guest, 3 for security, -1 for failed login
 */
int login(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards){
	String username, password;
	int i, j, k, isGuest = 0, isAdmin = 0, isSecu = 0;
	printf(DEFAULT"Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

 
    for (i = 0; i < nAdmins && !isAdmin; i++) {
        if (strcmp(ADMINS[i].username, username) == 0 && 
            strcmp(ADMINS[i].a_password, password) == 0) {
            isAdmin = 1;
        }
    }
    
    for (j = 0; j < nGuests && !isGuest; j++) {
        if (strcmp(GUESTS[j].user, username) == 0 && 
            strcmp(GUESTS[j].g_password, password) == 0) {
            isGuest = 1;
        }
    }
    for(k = 0; k < nGuards && !isSecu; k++) {
    	if (strcmp(GUARDS[k].user, username) == 0 &&
			strcmp(GUARDS[k].s_password,password) == 0) {
				isSecu = 1;
			}
	}
    if(isAdmin == 1 && isGuest == 0 && isSecu == 0){
    	return 1;
	} else if(isGuest == 1 && isAdmin == 0 && isSecu == 0){
		return 2;
	} else if(isGuest == 0 && isAdmin == 0 && isSecu == 1){
		return 3;
	}

	return -1;
}

int main () {
	adminType ADMINS[MAX_ADMIN]; 		// array of struct for admin
	int nADMINS;
	
	guestType GUESTS[MAX_GUEST]; 		// array of struct for guests
	int nGUESTS;
	
	secuType GUARDS[MAX_SEC];
	int nGUARDS;
	addressType address;
	
	int sensorStatus[SENSORS] = {0};
	
	nADMINS = initializeAdmin(ADMINS);
	nGUESTS = initializeGuests(GUESTS);
	nGUARDS = initializeGuards(GUARDS);
	
	printf(RED"WELCOME TO THE SECURITY SYSTEM DASHBOARD\n");
	int check = 0;
	do{ 
		check = login(ADMINS,GUESTS,GUARDS,nADMINS,nGUESTS,nGUARDS);
		if(check == 1){
			adMenu(ADMINS,GUESTS,GUARDS,nADMINS,nGUESTS,nGUARDS,address, sensorStatus);
		
		} else if (check == 2) {
			gMenu(ADMINS,GUESTS,GUARDS,nADMINS,nGUESTS,nGUARDS,address, sensorStatus);
		
		} else if (check == 3){
			sMenu(ADMINS,GUESTS,GUARDS,nADMINS,nGUESTS,nGUARDS,address);
		
		} else {
			printf("Account does not exist or the password is incorrect. Please try again.\n");
		}
	}while(check != 0);
	
	return 0;
}


