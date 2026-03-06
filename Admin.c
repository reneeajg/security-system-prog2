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
#define MAX_ADMIN 2


/*
initializeAdmin: scans admins.txt for available admin information and saves them into the ADMINS array of structure
Parameters:
ADMINS[] - array of structure for admin
Returns: 0 if file is empty, otherwise, returns the amount of accounts read by the function 
*/
int initializeAdmin(adminType ADMINS[]){
    int ctr = 0;
    adminType s;
    FILE *fp = fopen("admins.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s\n", s.username, s.a_password, s.contact_info) == 3) {
        ADMINS[ctr] = s;
        ctr++;
    }  

    fclose(fp);
    return ctr;
}

/*
displayAdmin: Displays the admin array of structure in the CLI and adminsout.txt file
Parameters:
ADMINS[] - array of structure for admin
n - number of admins
Returns: none
*/
void displayAdmin(adminType ADMINS[], int n){
    FILE *fp = fopen("adminsout.txt", "w");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    printf("\nList of Admins:\n");
    printf("---------------------------------------------------------\n");
    fprintf(fp, "List of Admins:\n");
    fprintf(fp, "---------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("ADMIN #%d\t", i + 1);
        printf("%s\t", ADMINS[i].username);
        printf("| CONTACT: %s\t\n", ADMINS[i].contact_info);
        printf("---------------------------------------------------------\n");

        fprintf(fp, "ADMIN #%d\n", i + 1);
        fprintf(fp, "USERNAME: %s\n", ADMINS[i].username);
        fprintf(fp, "Contact: %s\t\n", ADMINS[i].contact_info);
        fprintf(fp, "---------------------------------------------------------\n");
    }

    fclose(fp);
}

/*
appendAdmin: Adds an admin account to the ADMINS[] array
Parameters:
ADMINS[] - array of structure for admin
*numAdmins - number of accounts in the array
Returns: none
*/
void appendAdmin(adminType ADMINS[], int *numAdmins){

    adminType newAdmin;
    FILE *fp = fopen("admins.txt", "a"); //appends the original admin file, kasi if yung bago, it will only count the ones inputted during run time (kumbaga inde historical) 

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
		exit(1);
    }

    if (*numAdmins == MAX_ADMIN) {
    	printf("Maximum number of accounts reached!\n");
	} else {
		
		printf("Enter username: ");
	    scanf("%s", newAdmin.username);
		printf("Enter password: ");
		scanf("%s", newAdmin.a_password);
	    printf("Enter Contact Info: ");
	    scanf("%s", newAdmin.contact_info);
	
	    
	    fprintf(fp, "\n%s %s %s", newAdmin.username,newAdmin.a_password, newAdmin.contact_info);
	    
	    fclose(fp);
	
	    
	    ADMINS[*numAdmins] = newAdmin;
	    (*numAdmins)++; 
	
	    printf("New admin added successfully!\n");
	
	    
	    displayAdmin(ADMINS, *numAdmins);
	}

}

/*
adMenu: Dashboard for all the admin’s controls
Parameters:
ADMINS[] - array of struct for admin
GUEST[] - array of struct for guest
GUARDS - array of struct for guards
nAdmins - number of admin accounts
nGuests - number of guest accounts
nGuards - number of guard accounts
Address - structure for the home address
sensorStatus[] - integer array for sensor status
*/
void adMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards, addressType address, int sensorStatus[]) {
    int choice;
    
    do {
        printf(RED "\nWELCOME, ADMIN!\n");
        printf(DEFAULT "1. Accounts Manager\n2. Simulate Security Event\n3. Sensor Control Panel\n4. View Reports\n5. Logout\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                accManager(ADMINS, GUESTS, GUARDS, nAdmins, nGuests, nGuards, address);
                break;
            case 2:
                if (!isSensorActive(sensorStatus)) {  
                    printf("Sensors have not been configured. Please configure them first.\n");
                } else {
                    adminSimulation(sensorStatus);
                }
                break;
            case 3:
                sensorControlPanel(sensorStatus); 
                break;
            case 4:
                viewReports();
                break;
            case 5:
                printf("Logging you out...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
}

/*
editAdminPassword: Edits the password of the logged in admin user
Parameters:
ADMINS[] - array of structure for admin
nadmins - number of admins
Returns: none
*/
void editAdminPassword(adminType ADMINS[], int nadmins){
	int i, found = 0;
	String username, npassword, cpassword;
	
	
	printf("Hello admin, please enter your username: ");
    scanf("%s", username);

    for (i = 0; i < nadmins; i++) {
        if (strcmp(ADMINS[i].username, username) == 0) {
            found = 1;
            printf("Enter new password: ");
            scanf("%s", npassword);
            if(strcmp(ADMINS[i].a_password,npassword) != 0) {
            	do {
                printf("Confirm new password: ");
                scanf("%s", cpassword);
                	if (strcmp(npassword, cpassword) != 0) {
                    printf("Passwords do not match! Try again.\n");
                	}
            	} while (strcmp(npassword, cpassword) != 0);
            strcpy(ADMINS[i].a_password, cpassword);
            printf("Password updated successfully.\n");
			} else {
				printf("Current and new password match. Please try again.\n");
			}
        }
    }

    if (!found) {
        printf("Username not found.\n");
    }
    
    updateAdminFile(ADMINS,nadmins);
}

/*
accManager: Dashboard for managing the accounts of the system
Parameters:
ADMINS[] - array of struct for admin
GUEST[] - array of struct for guest
GUARDS - array of struct for guards
nAdmins - number of admin accounts
nGuests - number of guest accounts
nGuards - number of guard accounts
address - structure for the home address
Returns: none
*/
void accManager(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards,addressType address) {
    int choice;
    do {
        printf(RED"\nWELCOME TO THE ACCOUNT MANAGER\n"DEFAULT);
        printf("1. Display Accounts\n");
        printf("2. Change Password\n");
        printf("3. Edit Address\n");
        printf("4. Add Account\n");
        printf("5. Delete Account\n");
        printf("6. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAdmin(ADMINS, nAdmins);
                displayGuest(GUESTS, nGuests);
                displayGuards(GUARDS, nGuards);
                break;
            case 2: {
                editAdminPassword(ADMINS,nAdmins);
                break;
            }
            case 3:
                createAddress(&address);
                break;
            case 4: {
            	int ans2;
                do {
                    printf(RED"Select account type to create.\n"DEFAULT);
                    printf("1. Admin\n2. Guest\n3. Security\n4. Back\nChoice: ");
                    scanf("%d", &ans2);

                    switch (ans2) {
                        case 1: appendAdmin(ADMINS, &nAdmins); break;
                        case 2: appendGuest(GUESTS, &nGuests); break;
                        case 3: appendGuards(GUARDS, &nGuards); break;
                        case 4: printf("Going back...\n"); break;
                        default: printf("Invalid choice! Try again.\n");
                    }
                } while (ans2 != 4);
				break;
			}
            case 5:
                deleteAccount(ADMINS, GUESTS, GUARDS,&nAdmins, &nGuests,&nGuards);
                break;
            case 6:
                printf("Returning to the previous menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

/*
deleteAccount: Deletes an account existing in the system
Parameters:
ADMINS[] - array of struct for admin
GUEST[] - array of struct for guest
GUARDS - array of struct for guards
*nAdmins - number of admin accounts
*nGuests - number of guest accounts
*nGuards - number of guard accounts
returns: none
*/
void deleteAccount(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int *nAdmins, int *nGuests, int *nGuards) {
    String username, password;
    int i, j, found = 0;

    printf("Enter the username of the account to delete: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (i = 0; i < *nAdmins; i++) {
        if (strcmp(ADMINS[i].username, username) == 0 &&
			strcmp(ADMINS[i].a_password,password) == 0) {
            found = 1;
            printf("Admin account '%s' deleted.\n", username);
            for (j = i; j < *nAdmins - 1; j++) {
                ADMINS[j] = ADMINS[j + 1];
            }
            (*nAdmins)--;
        }
    }

    if (!found) {
        for (i = 0; i < *nGuests; i++) {
            if (strcmp(GUESTS[i].user, username) == 0 && 
				strcmp(GUESTS[i].g_password, password) == 0) {
                found = 1;
                printf("Guest account '%s' deleted.\n", username);
                for (j = i; j < *nGuests - 1; j++) {
                    GUESTS[j] = GUESTS[j + 1];
                }
                (*nGuests)--;
            }
        }
    }
    
    if (!found) {
        for (i = 0; i < *nGuards; i++) {
            if (strcmp(GUARDS[i].user, username) == 0 && 
				strcmp(GUARDS[i].s_password, password) == 0) {
                found = 1;
                printf("Guest account '%s' deleted.\n", username);
                for (j = i; j < *nGuards - 1; j++) {
                    GUARDS[j] = GUARDS[j + 1];
                }
                (*nGuards)--;
            }
        }
    }

    if (!found) {
        printf("Username '%s' not found or password is incorrect.\n", username);
    }
    
    updateAdminFile(ADMINS, *nAdmins);
    updateGuestFile(GUESTS, *nGuests);
}

/*
updateAdminFile: updates the admins.txt file for when the admin adds or deletes an admin, or changes the password
Parameters:
ADMINS[] - array of struct for admin
nAdmins - number of admin accounts
Returns: none
*/
void updateAdminFile(adminType ADMINS[], int nAdmins) {
    FILE *fp = fopen("admins.txt", "w");
    if (fp == NULL) {
        printf("Error opening admins.txt for updating!\n");
    }
	int i;
    for (i = 0; i < nAdmins; i++) {
        fprintf(fp, "%s %s %s\n", ADMINS[i].username, ADMINS[i].a_password, ADMINS[i].contact_info);
    }

    fclose(fp);
}

/*
createAddress: Asks user to create an address when the loadAdress does not find an existing home address, otherwise asks if the user wants to edit the existing address
Parameters:
*address - pointer variable for struct address
Returns: none
*/
void createAddress(addressType *address) {
    if (loadAddress(address)) {
        printf("Existing address found.\n");
        displayAddress(*address);
        printf("\nWould you like to edit it?\n[1 = Yes / 0 = No]:  ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            editAddress(address);
            saveAddress(*address);
        }
    } else {
        printf("WELCOME! No existing address found. Please input your address.\n");
        editAddress(address);
        saveAddress(*address);
    }
}

/*
editAddress: Asks the user to edit their address details
Parameters:
*address - pointer variable for struct address
Returns: none
*/
void editAddress(addressType *address) {
    printf("Enter block #: ");
    scanf("%d", &address->block);
    printf("Enter lot #: ");
    scanf("%d", &address->lot);
    printf("Enter street name: ");
    scanf(" %s", address->street);
    printf("Enter subdivision/residence name: ");
    scanf(" %s", address->subd);
    printf("Enter barangay name: ");
    scanf(" %s", address->brgy);

    printf("Address details have been updated.\n");
    displayAddress(*address);
}

/*
displayAddress: displays the current address
Parameters:
address - variable for struct address
Returns: none
*/
void displayAddress(addressType address) {
    printf("Block %d, Lot %d, %s St., %s Residences, Brgy. %s\n", address.block, address.lot, address.street, address.subd, address.brgy);
}

/*
saveAddress: saves the address to a text file
Parameters:
address - pointer variable for struct address
Returns: none
*/
void saveAddress(addressType address) {
    FILE *fp = fopen("address.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
    }
    fprintf(fp, "%d %d %s %s %s\n", address.block, address.lot, address.street, address.subd, address.brgy);
    fclose(fp);
}

/*
loadAddress: saves the address to a text file
Parameters:
address - pointer variable for struct address
Returns: none
*/
int loadAddress(addressType *address) {
    FILE *fp = fopen("address.txt", "r");
    if (fp == NULL) {
        return 0;  
    }
    if (fscanf(fp, "%d %d %s %s %s", &address->block, &address->lot, address->street, address->subd, address->brgy) != 5) {
        fclose(fp);
        return 0;  
    }
    fclose(fp);
    return 1;
}
