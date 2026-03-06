
#define SENSORS 5

typedef char String[51];
typedef char String20[21];  
typedef char report[256];

/* SecurityEvent stores details of a single security incident
@param date - date of event (YYYY-MM-DD format)
@param time - time of event (HH:MM format)
@param location - where event occurred
@param panic_pressed - 1 if panic button was pressed, 0 otherwise
 */
typedef struct {
    String20 date;          
    String20 time;         
    String20 location;     
    int panic_pressed;      
} SecurityEvent;

/* SecurityReport contains multiple security events and metadata
@param events - array of SecurityEvent records
@param count - number of events in report
@param reportDate - date report was generated
@param reportTime - time report was generated
 */
typedef struct {
    SecurityEvent events[50];  
    int count;               
    String20 reportDate;
    String20 reportTime;
} SecurityReport;

/* Address stores complete physical address components
@param block - address block number
@param lot - address lot number
@param street - street name
@param subd - subdivision name
@param brgy - barangay name
 */
struct Address {
    int block;
    int lot;
    String street;
    String subd;
    String brgy;
};

typedef struct Address addressType;

/* Sensor tracks location and status of security sensors
@param location - where sensor is installed
@param activity - current activity status
 */
struct Sensor {
	String location;
    String activity;
};

/* Admin stores administrator account credentials
@param a_password - administrator password
@param username - login username
@param contact_info - contact details
 */
struct Admin {
    String a_password;
    String username;
    String contact_info;
};

typedef struct Admin adminType;

/* Guest stores guest user account credentials
@param user - login username
@param g_password - guest password */
struct Guest {
    String user;
    String g_password;
};

typedef struct Guest guestType;

/* Security stores guard account credentials
@param user - login username
@param s_password - security password
 */
struct Security{
	String user;
	String s_password;
};

typedef struct Security secuType;

// function prototypes


int login(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[],int nAdmins, int nGuests, int nGuards);

// admin
int initializeAdmin(adminType ADMINS[]);
void displayAdmin(adminType ADMINS[], int n);
void appendAdmin(adminType ADMINS[], int *numAdmins);
void adMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[],int nAdmins, int nGuests, int nGuards,addressType address,int sensorStatus[]);
void editAdminPassword(adminType ADMINS[], int nadmins);
void accManager(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards,addressType address);
void deleteAccount(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int *nAdmins, int *nGuests, int *nGuards);
void updateAdminFile(adminType ADMINS[], int nAdmins);

//address
void createAddress(addressType *address);
void editAddress(addressType *address);
void displayAddress(addressType address);
void saveAddress(addressType address);
int loadAddress(addressType *address);

// guest
int initializeGuests(guestType GUESTS[]);
void displayGuest(guestType GUESTS[], int n);
void appendGuest(guestType GUESTS[], int *numGUESTS);
void gMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nGuards, int nAdmins, int nGuests,addressType address, int sensorStatus[]);
void editGuestPassword(guestType GUESTS[], int nguests);
void updateGuestFile(guestType GUESTS[], int nGuests);

//guards
int initializeGuards(secuType GUARDS[]);
void displayGuards(secuType GUARDS[], int n);
void appendGuards(secuType GUARDS[], int *n);
void sMenu(adminType ADMINS[], guestType GUESTS[], secuType GUARDS[], int nAdmins, int nGuests, int nGuards,addressType address);
void editGuardPassword(secuType GUARDS[], int nguards);
void updateGuardFile(secuType GUARDS[], int nGuards);

// simulation
void displayIntruder(int sensorStatus[SENSORS], int intruderLocation);
void adminSimulation(int sensorStatus[SENSORS]);

void generateReport(SecurityReport *report, String20 location, int panicPressed, String20 eventTime);
void displayReports(SecurityReport *report, String20 reportDate, String20 reportTime);
void appendSecurityReport(SecurityReport *report, String20 reportDate, String20 reportTime);
void inputDateTime(String20 date, String20 time);
void viewReports();

void sensorSetup(int sensorStatus[SENSORS]);
void displaySensorsStatus(int sensorStatus[SENSORS]);
void sensorControlPanel(int sensorStatus[SENSORS]);
int isSensorActive(int sensorStatus[]);
