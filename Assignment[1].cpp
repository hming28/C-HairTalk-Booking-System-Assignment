#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
//#include <bits/stdc++.h>

using namespace std;


// login & logout
struct User {
    string username;
    string password;
};

struct Admin {
    string username;
    string password;
};

struct Expert {
    string name;
    //vector<string> specializations; 
    string workingHours;
};

struct Booking {
    char username[50];
    char phonenumber[20];
    char service[50];
    char expert[50];
    int date;
    char time[20];
    char endtime[20];
};


// Login feature
bool login(User& user);

// --- Pass by value ---
void welcomeMessage(string name) {
    cout << "👋 Hello, " << name << "! You are now logged in.\n";
}

// --- Pass by address ---
void clearUser(User* user) {
    user->username = "";
    user->password = "";
}

void signUp(User* newUser);

// --- Login System ---
void loginsystem(User& user);
// End Login & Sign Up

// --- Admin Login ---
bool adminLogin(Admin& admin);
// End admin Login

// --- expert Login ---
int expertLogin(string experts[]);
// End expert Login


// availability (count)
const int NUM_SERVICE = 6;
const int NUM_EXPERTS = 3;
const int NUM_DATES = 31;
const int NUM_SLOTS = 9;

// int availability[NUM_EXPERTS][NUM_DATES][NUM_SLOTS]; 3d arrays
//int availability[NUM_EXPERTS * NUM_DATES][NUM_SLOTS];

int getAvailabilityIndex(int expertIndex, int dateIndex) {
    return expertIndex * NUM_DATES + dateIndex;
}

// Function to access availability using 3D-style indexing
int& getAvailability(int expertIndex, int dateIndex, int slotIndex, int availability[][NUM_SLOTS]) {
    int rowIndex = getAvailabilityIndex(expertIndex, dateIndex);
    return availability[rowIndex][slotIndex];
}


// 6 services
void serviceslist(string services[], string serviceshours[], float servicesprice[]);

// 3 experts
void expertslist(string experts[]);

//date
string DateLabel(int day);

//check weekend
bool isWeekend(int day);

// Start Sharing Function
// 0 Function check input is integer
void checkInput(const string& prompt, int min, int max, int* result);

// 1 Function to display and select service
// 3D array: [expertIndex][dateIndex][timeIndex]
//  3 experts, 31 dates, 9 time slots
int selectService(string services[], string serviceshours[], float servicesprice[]);

// 2 Function to display and select expert
int selectExpert(string experts[], int specializations[][NUM_SERVICE], int serviceIndex);

// 3 Function to display and select weeks
int selectWeeks(int& startDay, int& endDay);

// 4 Function to display and select date
int selectDate(int startDay, int endDay);

// 5 Function to display availability for specific expert and date (case 3)
void showAvailability(string services[], string experts[], string timeSlots[], string endTimes[], int serviceIndex, int expertIndex, int dateIndex, int dateChoice, int weekChoice, int availability[][NUM_SLOTS]);

// Helper functions for expert work limit validation
double calculateExpertDailyHours(int expertIndex, int dateIndex, string experts[], string services[], double serviceHours[], int availability[][NUM_SLOTS]);
double calculateExpertWeeklyHours(int expertIndex, int startDay, int endDay, string experts[], string services[], double serviceHours[], int availability[][NUM_SLOTS]);
bool checkExpertWorkLimits(int expertIndex, int dateIndex, int startDay, int endDay, double serviceHours, string experts[], string services[], double serviceHoursArray[], int availability[][NUM_SLOTS]);

//End Sharing Function


//start case 1
void displayCustomerMenu();
void displayInfomation();
void calender();
void ClearScreen();
// === Case 1: View Services and Experts ===
// View Services and Experts
void displayServicesAndExperts(string services[], string serviceshours[], float servicesprice[], string experts[]);
// End of Case 1

// Start ===== CASE 2: CHECK AVAILABILITY =====
void displayAvailability(string services[], string serviceshours[], float servicesprice[], double serviceHours[], string experts[], string timeSlots[], string endTimes[], int availability[][NUM_SLOTS]);
// End of Case 2

// Start ===== CASE 3: BOOK APPOINTMENT =====
void bookAppointment(const User& currentUser, float servicesprice[], double serviceHours[], string services[], string serviceshours[], string experts[], string timeSlots[], string endTimes[], int specializations[][NUM_SERVICE], int availability[][NUM_SLOTS]);
// End of Case 3

// Start ===== CASE 4: VIEW MY BOOKINGS =====
//load current booking history
void loadBookings(string services[], string experts[], string timeSlots[], double serviceHours[], int availability[][NUM_SLOTS]);

void viewMyBookings(const User& currentUser);
// End of Case 4

// Start ===== CASE 5: FEEDBACK =====
bool userHasBooking(const User& currentUser);
void leaveFeedback(const User& currentUser, string services[], string experts[]);
// End of Case 5


// Start admin menu
// Admin function declarations
void adminSystem(string services[], string serviceshours[], float servicesprice[], string experts[], string timeSlots[], double serviceHours[], int specializations[][6]);
//End admin menu

// ===== ADMIN FUNCTIONS IMPLEMENTATION =====
// 1. View Individual Expert Schedule
void viewIndividualExpertSchedule(string services[], string serviceshours[], float servicesprice[], string experts[], string timeSlots[], double serviceHours[], int specializations[][6]);

// 2. View Overall Schedule
void viewOverallSchedule(string services[], string experts[], string timeSlots[]);

// 3. View Customer List
void viewCustomerList(string services[], string experts[]);

// 4. Generate Sales Reports
void generateSalesReports(string services[]);

// 5. View Expert Bonus Entitlements
void viewExpertBonusEntitlements(string services[], string experts[], double serviceHours[]);


// Start expert
// --- Expert System ---
void expertSystem(string experts[], string services[], double serviceHours[]);

// Start expert case 1-3
void viewExpertSchedule(int login, string experts[]);
void viewExpertCustomers(int login, string experts[]);
void viewExpertBonus(int login, string experts[], string services[], double serviceHours[]);


int main() {
    string choice;
    // int month;

    int availability[NUM_EXPERTS * NUM_DATES][NUM_SLOTS] = { {0} };


    string timeSlots[NUM_SLOTS] = { "10:00AM", "11:00AM", "12:00PM",
                                   " 1:00PM", " 2:00PM", " 3:00PM",
                                   " 4:00PM", " 5:00PM", " 6:00PM" };

    string endTimes[NUM_SLOTS] = { "11:00AM", "12:00PM", " 1:00PM",
                                   " 2:00PM", " 3:00PM", " 4:00PM",
                                   " 5:00PM", " 6:00PM", " 7:00PM" }; // 6-7 PM is the last slot

    string services[NUM_SERVICE] = { "Hair Cut","Hair Wash","Hair Coloring",
                          "Hair Treatment", "Hair Styling", "Scalp Care" };

    string serviceshours[NUM_SERVICE] = { "(1 hour)","(0.5 hour)","(2.5 hour)",
      "(1.5 hour)", "(1 hour)", "(0.75 hour)" };

    float servicesprice[NUM_SERVICE] = { 30, 15, 200, 100, 80, 60 };

    //⭐
    string experts[NUM_EXPERTS] = { "Jian Hao", "Kah Weng", "Jia Xiong" };

    // 3 experts × 6 services
    int specializations[NUM_EXPERTS][NUM_SERVICE] = {
        // Hair Cut, Hair Wash, Coloring, Treatment, Styling, Scalp
        {1, 1, 0, 1, 1, 0}, // Mr. Jian Hao
        {1, 0, 1, 1, 0, 1}, // Mr. Kah Weng
        {0, 1, 1, 0, 1, 1}  // Mr. Jia Xiong
    };

    // work hours
    double serviceHours[NUM_SERVICE] = { 1.0,      // Hair Cut: 1 hour
                                       0.5,      // Hair Wash: 30 minutes
                                       2.5,      // Hair Coloring: 2.5 hours
                                       1.5,      // Hair Treatment: 1.5 hours
                                       1.0,      // Hair Styling: 1 hour
                                       0.75 };    // Scalp Care: 45 minutes



    loadBookings(services, experts, timeSlots, serviceHours, availability);
    // Main Menu
    string mainchoice;
    while (true) {
        //ClearScreen();
        cout << string(50, '=') << endl;
        cout << right << setw(36) << "HAIR TALK BOOKING SYSTEM" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Customer Services" << endl;
        cout << "2. Admin Dashboard" << endl;
        cout << "3. Expert Portal" << endl;
        cout << "4. Exit" << endl;
        cout << string(50, '-') << endl;
        cout << "Please select your choice (1-4): ";
        cin >> mainchoice;

        if (mainchoice.length() != 1 || mainchoice[0] < '1' || mainchoice[0] > '4') {
            cout << "Invalid input! Please enter only ONE digit between 1 and 4." << endl << endl;
            continue;
        }

        switch (mainchoice[0]) {
        case '1': {
            bool inCustomerMenu = true;
            User currentUser; // Declare user variable but don't login yet
            //ClearScreen();
            displayInfomation();
            while (inCustomerMenu) {
                displayCustomerMenu();
                cin >> choice;

                if (choice.length() != 1 || (choice[0] < '1' || choice[0] > '7')) {
                    cout << "Invalid input! Please enter only ONE digit between 1 and 7." << endl << endl;
                    continue;
                }

                switch (choice[0]) {
                case '1':
                    displayServicesAndExperts(services, serviceshours, servicesprice, experts);
                    break;
                case '2':
                    displayAvailability(services, serviceshours, servicesprice, serviceHours, experts, timeSlots, endTimes, availability);
                    break;
                case '3':
                    // Login required for booking
                    if (currentUser.username == "" || currentUser.password == "") {
                        cout << "\nLogin required to book an appointment.\n";
                        loginsystem(currentUser);
                        if (currentUser.username == "" || currentUser.password == "") {
                            cout << "Login cancelled. Returning to customer menu.\n";
                            break;
                        }
                    }
                    bookAppointment(currentUser, servicesprice, serviceHours, services, serviceshours, experts, timeSlots, endTimes, specializations, availability);
                    break;
                case '4':
                    // Login required to view bookings
                    if (currentUser.username == "" || currentUser.password == "") {
                        cout << "\nLogin required to view your bookings.\n";
                        loginsystem(currentUser);
                        if (currentUser.username == "" || currentUser.password == "") {
                            cout << "Login cancelled. Returning to customer menu.\n";
                            break;
                        }
                    }
                    viewMyBookings(currentUser);
                    break;
                case '5':
                    // Login required to leave feedback
                    if (currentUser.username == "" || currentUser.password == "") {
                        cout << "\nLogin required to leave feedback.\n";
                        loginsystem(currentUser);
                        if (currentUser.username == "" || currentUser.password == "") {
                            cout << "Login cancelled. Returning to customer menu.\n";
                            break;
                        }
                    }
                    if (!userHasBooking(currentUser)) {
                        cout << "You must have at least one booking before leaving feedback.\n";
                        break;
                    }
                    leaveFeedback(currentUser, services, experts);
                    break;
                case '6':
                    cout << "Returning to Main Menu..." << endl << endl;
                    inCustomerMenu = false;
                    break;
                case '7':
                    cout << "Exiting program. Goodbye!\n";
                    return 0;
                default:
                    cout << "\nInvalid choice. Please enter the correct choice (1-7)." << endl;
                    break;
                }
            }
            break;
        }

                // Experts Portal
        case '2':
            adminSystem(services, serviceshours, servicesprice, experts, timeSlots, serviceHours, specializations);
            break;
        case '3':
            expertSystem(experts, services, serviceHours);
            break;
        case '4':
            cout << "Exiting program. Goodbye!\n";
            return 0;
        }
    }

    return 0;
}
// End main


//void function
// Login feature
bool login(User& user) {
    string username, password;
    cout << endl << string(21, '=') << " Login " << string(22, '=') << endl;
    cin.ignore();
    cout << "Enter your username: ";
    getline(cin, username);
    while (username.empty()) {
        cout << "Username cannot be empty. Please re-enter: ";
        getline(cin, username);
    }

    // Step 1: Check if username exists first
    ifstream inFile("users.txt");
    string line;
    bool usernameFound = false;
    string fileUsername, filePassword;

    while (getline(inFile, line)) {
        size_t userPos = line.find("Username: ");
        size_t passPos = line.find(" | Password: ");
        if (userPos != string::npos && passPos != string::npos) {
            fileUsername = line.substr(userPos + 10, passPos - (userPos + 10));
            filePassword = line.substr(passPos + 13);
            if (fileUsername == username) {
                usernameFound = true;
                break; // Stop reading because we found it
            }
        }
    }
    inFile.close();

    // Step 2: Immediately respond if username doesn't exist
    if (!usernameFound) {
        cout << "❌ Username not found. Please try again.\n";
        return false;
    }

    // Step 3: Now ask for password (masking to be added later)
    cout << "Enter your password: ";
    getline(cin, password);
    while (password.empty()) {
        cout << "Password cannot be empty. Please re-enter: ";
        getline(cin, password);
    }

    if (password == filePassword) {
        user.username = username;
        user.password = password;
        cout << "✅ Welcome back, " << user.username << "!\n";
        return true;
    }
    else {
        cout << "❌ Incorrect password.\n";
        return false;
    }
}
//end

// Sign up feature
void signUp(User* newUser) {
    string username, password;
    cout << endl << string(20, '=') << " Sign Up " << string(21, '=') << endl;
    cin.ignore();
    cout << "Enter your username: ";
    getline(cin, username);
    while (username.empty()) {
        cout << "Username cannot be empty. Please re-enter: ";
        getline(cin, username);
    }
    cout << "Enter your password: ";
    getline(cin, password);
    while (password.empty()) {
        cout << "Password cannot be empty. Please re-enter: ";
        getline(cin, password);
    }

    // Check if username already exists
    ifstream inFile("users.txt");
    string fileUsername, filePassword;
    while (getline(inFile, fileUsername) && getline(inFile, filePassword)) {
        if (fileUsername == username) {
            cout << "⚠️ This username is already taken.\n";
            return;
        }
    }
    inFile.close();

    // Save to file in readable format
    ofstream outFile("users.txt", ios::app);
    outFile << "Username: " << username << " | Password: " << password << endl;
    outFile.close();

    newUser->username = username;
    newUser->password = password;

    cout << "✅ Registration successful!\n";
}
//end

// --- Login System ---
void loginsystem(User& user) {
    string choice;
    bool inLoginMenu = true;

    while (inLoginMenu) {
        cout << endl << string(18, '=') << " USER SYSTEM " << string(19, '=') << endl;
        cout << "1. Login \n2. Sign Up \n3. Exit \nSelect option: ";
        cin >> choice;
        // if method check integer
        if (choice.length() != 1 || choice[0] < '1' || choice[0] > '3') {
            cout << "Invalid input! Please enter only ONE digit between 1 and 3." << endl;
            continue;
        }

        switch (choice[0]) {
        case '1':
            if (login(user)) {
                welcomeMessage(user.username);
                return;
            }
            break;

        case '2':
            signUp(&user);
            welcomeMessage(user.username);
            return;
            break;

        case '3':
            cout << "Exiting login system...\n";
            user.username = "";
            user.password = "";
            return;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

    }
}
// End Login & Sign Up


// --- Admin Login ---
bool adminLogin(Admin& admin) {
    string username, password;
    cout << endl << string(18, '=') << "🔐 Admin Login " << string(17, '=') << endl;
    cin.ignore(); // clear buffer
    cout << "Enter Admin Username: ";
    getline(cin, username);
    while (username.empty()) {
        cout << "Admin username cannot be empty. Please re-enter: ";
        getline(cin, username);
    }
    cout << "Enter Admin Password: ";
    getline(cin, password);
    while (password.empty()) {
        cout << "Admin password cannot be empty. Please re-enter: ";
        getline(cin, password);
    }

    //Option 1: Hardcoded (simplest way, exam-friendly)
    if (username == "Hao Ming" && password == "haoming123") {
        admin.username = username;
        admin.password = password;
        cout << "✅ Welcome, Admin " << admin.username << "!\n";
        return true;
    }

    cout << "❌ Invalid Admin Credentials!\n";
    return false;
}
// End admin Login


// --- expert Login ---
int expertLogin(string experts[]) {
    string username, password;
    cout << endl << string(17, '=') << "🔐 Expert Login " << string(17, '=') << endl;
    cin.ignore(); // clear buffer
    cout << "Enter expert Username: ";
    getline(cin, username);
    while (username.empty()) {
        cout << "Expert username cannot be empty. Please re-enter: ";
        getline(cin, username);
    }
    cout << "Enter expert Password: ";
    getline(cin, password);
    while (password.empty()) {
        cout << "Expert password cannot be empty. Please re-enter: ";
        getline(cin, password);
    }

    // Expert passwords
    string expertspassword[3] = { "jianhao123","kahweng123","jiaxiong123" };

    for (int i = 0; i < 3; i++) {
        if (username == experts[i] && password == expertspassword[i]) {
            cout << "✅ Welcome, Expert " << username << "!\n";
            return i; // return index of the expert
        }
    }

    cout << "❌ Invalid expert Credentials!\n";
    return -1; // login failed
}
// End expert Login


// 6 services
void serviceslist(string services[], string serviceshours[], float servicesprice[]) {
    // Header
    cout << "Services Offered:" << endl;
    cout << left << setw(4) << "No."
        << left << setw(15) << "Service"
        << left << setw(13) << "Hours"
        << right << setw(6) << "Price" << endl;

    cout << string(40, '-') << endl;

    for (int i = 0; i < NUM_SERVICE; ++i) {
        cout << left << setw(4) << (to_string(i + 1) + ".")
            << setw(15) << services[i]
            << setw(13) << serviceshours[i] // hours
            << "RM " << fixed << right << setprecision(2) // price
            << setw(6) << servicesprice[i]
            << endl;
    }
}

// 3 experts
void expertslist(string experts[]) {
    cout << "\nAvailable Experts:\n";
    for (int i = 0; i < NUM_EXPERTS; ++i) {
        cout << (i + 1) << ". " << "Mr. " << experts[i] << endl;
    }
}

// 0 = available, 1 = booked
// int availability[3][NUM_DATES][NUM_SLOTS] = {{{0}}};

//date
string DateLabel(int day) {
    const string weekdays[7] = { "Sunday",   "Monday", "Tuesday", "Wednesday",
                                "Thursday", "Friday", "Saturday" };
    // Assuming December 1st is a Monday (weekday index = 1)
    int weekdayIndex = (day) % 7; // Adjust if needed for accurate weekday
    return "December " + to_string(day) + " (" + weekdays[weekdayIndex] + ")";
}

bool isWeekend(int day) {
    // Assuming December 1 is Monday (weekday index = 1)
    int weekday = (day) % 7;
    return weekday == 0 || weekday == 6; // Sunday or Saturday
}

// Start Sharing Function
// 0 Function check input is integer
void checkInput(const string& prompt, int min, int max, int* result) {
    while (true) {
        cout << prompt;
        cin >> *result;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        if (*result < min || *result > max) {
            cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        return; // result is valid and stored at the pointer location
    }
}


// 1 Function to display and select service
// 3D array: [expertIndex][dateIndex][timeIndex]
//  3 experts, 31 dates, 9 time slots

int selectService(string services[], string serviceshours[], float servicesprice[]) {
    int serviceChoice;
    serviceslist(services, serviceshours, servicesprice);

    //check input is integer
    cout << string(50, '-') << endl;
    checkInput("Enter service (1-6): ", 1, 6, &serviceChoice);

    return serviceChoice;
}

// 2 Function to display and select expert
int selectExpert(string experts[], int specializations[][NUM_SERVICE], int serviceIndex) {
    int expertChoice;

    cout << "\nExperts available for this service:" << endl;

    // Show only experts who can do the selected service
    for (int i = 0; i < NUM_EXPERTS; i++) {
        if (specializations[i][serviceIndex] == 1) {
            cout << (i + 1) << ". " << "Mr. " << experts[i] << endl;
        }
    }

    // Force valid input
    while (true) {
        cout << string(50, '-') << endl;
        checkInput("Choose an expert: ", 1, 3, &expertChoice);

        if (expertChoice >= 1 && expertChoice <= NUM_EXPERTS &&
            specializations[expertChoice - 1][serviceIndex] == 1) {
            return expertChoice; // ✅ valid expert

        }
        else {
            cout << "Invalid choice. Please select an expert that matches the service.\n";
        }
    }
}


// 3 Function to display and select weeks
int selectWeeks(int& startDay, int& endDay) {
    int weekChoice;
    calender();
    do {
        cout << "\nSelect Week:\n";
        cout << "1. Week 1 (Dec 1 - 6)\n";
        cout << "2. Week 2 (Dec 7 - 13)\n";
        cout << "3. Week 3 (Dec 14 - 20)\n";
        cout << "4. Week 4 (Dec 21 - 27)\n";
        cout << "5. Week 5 (Dec 28 - 31)\n";
        cout << string(50, '-') << endl;
        checkInput("Enter week (1-5): ", 1, 5, &weekChoice);

        if (weekChoice == 1) { startDay = 1; endDay = 7; }
        else if (weekChoice == 2) { startDay = 8; endDay = 14; }
        else if (weekChoice == 3) { startDay = 15; endDay = 21; }
        else if (weekChoice == 4) { startDay = 22; endDay = 28; }
        else if (weekChoice == 5) { startDay = 29; endDay = 31; }
        else {
            cout << "❌ Invalid week.Please enter 1 to 5 only";
            continue;
        }

        break;// ✅ valid week, exit loop
    } while (true);

    return weekChoice;
}



// 4 Function to display and select date
int selectDate(int startDay, int endDay) {
    int dateChoice;
    do {
        cout << "Select date (" << startDay << "-" << endDay << ", weekdays only): " << endl;
        checkInput("Enter date: ", 1, 31, &dateChoice);

        // Check range
        if (dateChoice < startDay || dateChoice > endDay) {
            cout << "Invalid date, must be within week range (" << startDay << "-" << endDay << ").\n";
        }
        // Check weekend
        else if (isWeekend(dateChoice)) {
            cout << "Weekends are not available.\n";
        }
        else {
            break;  // ✅ valid input
        }
    } while (true);

    return dateChoice;
}


// 5 Function to display availability for specific expert and date (case 3)
void showAvailability(string services[], string experts[], string timeSlots[], string endTimes[], int serviceIndex, int expertIndex, int dateIndex, int dateChoice, int weekChoice, int availability[][NUM_SLOTS]) {
    cout << "\n📅 Availability for " << services[serviceIndex] << " with "
        << experts[expertIndex] << " on \n" << DateLabel(dateChoice)
        << " [Week " << weekChoice << "]\n";

    for (int i = 0; i < NUM_SLOTS; i++) {
        // Force lunch break slot (index 2) to always be unavailable
        if (i == 2) {
            cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i]
                << " ❌ Lunch Break\n";
            getAvailability(expertIndex, dateIndex, i, availability) = 1;
            continue;
        }

        if (getAvailability(expertIndex, dateIndex, i, availability) == 0) {
            cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i]
                << " ✅ Available\n";
        }
        else {
            cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i]
                << " ❌ Unavailable\n";
        }
    }
}
//End Sharing Function

// Helper functions for expert work limit validation
// limit - daily hours 6 hours , weekly hours 30 hours
double calculateExpertDailyHours(int expertIndex, int dateIndex, string experts[], string services[], double serviceHours[], int availability[][NUM_SLOTS]) {
    double totalHours = 0.0;

    // Read bookings from file to calculate actual hours worked
    ifstream in("bookings.dat");
    if (!in) return 0.0;

    string line;
    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {
                string service, expert, dateStr;

                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = bookingRecord[i].substr(12);
                    }
                    else if (bookingRecord[i].rfind("Date: ", 0) == 0) {
                        dateStr = bookingRecord[i].substr(6);
                    }
                }

                // Check if this booking is for the selected expert and date
                if (expert == experts[expertIndex]) {
                    int bookingDate = 0;
                    if (!dateStr.empty()) {
                        stringstream ss(dateStr);
                        ss >> bookingDate;
                    }

                    if (bookingDate == dateIndex + 1) { // dateIndex is 0-based, bookingDate is 1-based
                        // Find service hours
                        for (int i = 0; i < NUM_SERVICE; i++) {
                            if (service == services[i]) {
                                totalHours += serviceHours[i];
                                break;
                            }
                        }
                    }
                }
            }
            lineCount = 0;
        }
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();
    return totalHours;
}

double calculateExpertWeeklyHours(int expertIndex, int startDay, int endDay, string experts[], string services[], double serviceHours[], int availability[][NUM_SLOTS]) {
    double totalHours = 0.0;

    // Read bookings from file to calculate actual hours worked
    ifstream in("bookings.dat");
    if (!in) return 0.0;

    string line;
    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {
                string service, expert, dateStr;

                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = bookingRecord[i].substr(12);
                    }
                    else if (bookingRecord[i].rfind("Date: ", 0) == 0) {
                        dateStr = bookingRecord[i].substr(6);
                    }
                }

                // Check if this booking is for the selected expert and within the week
                if (expert == experts[expertIndex]) {
                    int bookingDate = 0;
                    if (!dateStr.empty()) {
                        stringstream ss(dateStr);
                        ss >> bookingDate;
                    }

                    if (bookingDate >= startDay && bookingDate <= endDay) {
                        // Find service hours
                        for (int i = 0; i < NUM_SERVICE; i++) {
                            if (service == services[i]) {
                                totalHours += serviceHours[i];
                                break;
                            }
                        }
                    }
                }
            }
            lineCount = 0;
        }
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();
    return totalHours;
}

bool checkExpertWorkLimits(int expertIndex, int dateIndex, int startDay, int endDay, double serviceHours, string experts[], string services[], double serviceHoursArray[], int availability[][NUM_SLOTS]) {
    // Check weekly limit (30 hours max)
    double currentWeeklyHours = calculateExpertWeeklyHours(expertIndex, startDay, endDay, experts, services, serviceHoursArray, availability);
    if (currentWeeklyHours + serviceHours > 30.0) {
        cout << "❌ Expert " << experts[expertIndex] << " has reached weekly work limit (30 hours max).\n";
        cout << "   Current weekly hours: " << fixed << setprecision(1) << currentWeeklyHours << " hrs\n";
        cout << "   Requested service: " << serviceHours << " hrs\n";
        cout << "   Total would be: " << (currentWeeklyHours + serviceHours) << " hrs (exceeds 30 hour limit)\n";
        return false;
    }

    // Check daily limit (6 hours max)
    double currentDailyHours = calculateExpertDailyHours(expertIndex, dateIndex, experts, services, serviceHoursArray, availability);
    if (currentDailyHours + serviceHours > 6.0) {
        cout << "❌ Expert " << experts[expertIndex] << " has reached daily work limit (6 hours max).\n";
        cout << "   Current daily hours: " << fixed << setprecision(1) << currentDailyHours << " hrs\n";
        cout << "   Requested service: " << serviceHours << " hrs\n";
        cout << "   Total would be: " << (currentDailyHours + serviceHours) << " hrs (exceeds 6 hour limit)\n";
        return false;
    }

    return true;
}

//Start Customer Menu
void displayCustomerMenu() {
    void ClearScreen();
    cout << endl << string(50, '=') << endl;
    cout << right << setw(31) << "CUSTOMER MENU" << endl;
    cout << string(50, '=') << endl;
    cout << "1. View Services and Experts" << endl;
    cout << "2. Check Appointment Availability" << endl;
    cout << "3. Book Appointment (Login Required)" << endl;
    cout << "4. View My Bookings (Login Required)" << endl;
    cout << "5. Feedback (Login Required)" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "7. Exit" << endl;
    cout << string(50, '-') << endl;
    cout << "Enter your choice (1-7): ";
}

// View Beauty Centre Information
void displayInfomation() {
    void ClearScreen();
    cout << endl;
    cout << string(50, '=') << endl;
    cout << right << setw(38) << "WELCOME TO HAIRTALK CENTER" << endl;
    cout << string(50, '=') << endl;
    cout << R"(     
 _   _    _    ___ ____ _____  _    _     _  __
| | | |  / \  |_ _|  _ \_   _|/ \  | |   | |/ /
| |_| | / _ \  | || |_) || | / _ \ | |   | ' / 
|  _  |/ ___ \ | ||  _ < | |/ ___ \| |___| . \
|_| |_/_/   \_\___|_| \_\|_/_/   \_\_____|_|\_\ )"
<< endl;
    cout << string(50, '=') << endl;
    cout << "We deliver expert hair styling and colouring with \nprecision, "
        "creativity band personalised service \nsince 2015."
        << endl << endl;
    cout << "📍 Location        : 35 H, 35 H, Jalan Kenanga 3/25, \n                     Taman Kenanga, 75200 Malacca " << endl;
    cout << "⏰ Operating Hours : Monday - Friday, 10AM - 6PM" << endl;
    cout << "📞 Phone Number    : 06-36789111" << endl;
    cout << "📧 Email           : hairtalk@gmail.com" << endl << endl;
    cout << "Business Vision and Mission" << endl << string(27, '-') << "\nTo be the leading hair salon in Malaysia, offering \nexceptional hair styling and colouring services \nwith precision, creativity, and \npersonalised service." << endl;
    cout << string(50, '-') << endl;
}


//start case 1
// === Case 1: View Services and Experts ===
// View Services and Experts
void displayServicesAndExperts(string services[], string serviceshours[], float servicesprice[], string experts[]) {
    void ClearScreen();
    cout << endl << string(50, '=') << endl;
    cout << right << setw(36) << "SERVICES AND EXPERTS" << endl;
    cout << string(50, '=') << endl;

    cout <<
        R"(     
Specialization Availability:
    Services         1    2    3    4    5    6
-------------------------------------------------
Mr. Jian Hao      | ✅ | ✅ | ❌ | ✅ | ✅ | ❌
Mr. Kah Weng      | ✅ | ❌ | ✅ | ✅ | ❌ | ✅
Mr. Jia Xiong     | ❌ | ✅ | ✅ | ❌ | ✅ | ✅
)" << endl << endl;

    serviceslist(services, serviceshours, servicesprice);


    // experts available
    cout << endl;
    expertslist(experts);
    cout << endl << "Operating Hours\n" << string(15, '-') << endl << "Mon–Fri, 10AM–6PM" << endl;
}

// Calender
void calender() {
    cout << R"(
        ┌────────────────────┐
        │ December      2025 |
        ├──┬──┬──┬──┬──┬──┬──┤
        │Su│Mo│Tu│We│Th│Fr│Sa│
        ├──┼──┼──┼──┼──┼──┼──┤
        │  │01│02│03│04│05│06│  ← Week 1
        ├──┼──┼──┼──┼──┼──┼──┤
        │07│08│09│10│11│12│13│  ← Week 2
        ├──┼──┼──┼──┼──┼──┼──┤
        │14│15│16│17│18│19│20│  ← Week 3
        ├──┼──┼──┼──┼──┼──┼──┤
        │21│22│23│24│25│26│27│  ← Week 4
        ├──┼──┼──┼──┼──┼──┼──┤
        │28│29│30│31│  │  │  │  ← Week 5
        └──┴──┴──┴──┴──┴──┴──┘)"
        << endl;
}
// End of Case 1

// Start ===== CASE 2: CHECK AVAILABILITY =====
void displayAvailability(string services[], string serviceshours[], float servicesprice[], double serviceHours[], string experts[], string timeSlots[], string endTimes[], int availability[][NUM_SLOTS]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(38) << "APPOINTMENT AVAILABILITY" << endl;
    cout << string(50, '=') << endl;

    cout <<
        R"(     
Specialization Availability:
    Services         1    2    3    4    5    6
-------------------------------------------------
Mr. Jian Hao      | ✅ | ✅ | ❌ | ✅ | ✅ | ❌
Mr. Kah Weng      | ✅ | ❌ | ✅ | ✅ | ❌ | ✅
Mr. Jia Xiong     | ❌ | ✅ | ✅ | ❌ | ✅ | ✅
)" << endl << endl;

    // Step 1: Service selection
    int serviceChoice = selectService(services, serviceshours, servicesprice);
    int serviceIndex = serviceChoice - 1; // array index because start from 0-based

    // // Inside bookAppointment, right after you get the serviceIndex
    // double hours = serviceHours[serviceIndex];
    // int slotsNeeded = ceil(hours); // ceil(2.5) becomes 3. ceil(1.0) becomes 1.


    // Step 2: Week selection
    int startDay, endDay;
    int weekChoice = selectWeeks(startDay, endDay);

    // Step 3: Date selection within that week
    int dateChoice = selectDate(startDay, endDay);
    int dateIndex = dateChoice - 1;

    // Step 4: Show availability for all experts
    cout << "\n📅 Availability for " << services[serviceIndex]
        << " on Dec " << dateChoice << "\n"
        << " [Week " << weekChoice << "]\n";
    cout << string(50, '=') << endl;

    for (int e = 0; e < NUM_EXPERTS; e++) {
        cout << "Expert: " << "Mr. " << experts[e] << "\n";
        for (int i = 0; i < NUM_SLOTS; i++) {
            // Force lunch break slot (index 2) to always be unavailable
            if (i == 2) {
                cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i]
                    << " ❌ Lunch Break\n";
                continue;
            }
            if (getAvailability(e, dateIndex, i, availability) == 0)
                cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i] << " ✅ Available\n";
            else
                cout << "[" << (i + 1) << "] " << timeSlots[i] << " - " << endTimes[i] << " ❌ Unavailable\n";

        }
        cout << endl;
    }
    cout << string(50, '-') << endl;
}
// End of Case 2

// Start ===== CASE 3: BOOK APPOINTMENT =====
void bookAppointment(const User& currentUser, float servicesprice[], double serviceHours[], string services[], string serviceshours[], string experts[], string timeSlots[], string endTimes[], int specializations[][NUM_SERVICE], int availability[][NUM_SLOTS]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(34) << "BOOK APPOINTMENT" << endl;
    cout << string(50, '=') << endl;
    int timeChoice;
    int askpayment, payment;
    string cardholdername, cardnum, expirydate, cvv;
    string bank;
    string username, password;
    string phonenumber;

    cout <<
        R"(     
Specialization Availability:
    Services         1    2    3    4    5    6
-------------------------------------------------
Mr. Jian Hao      | ✅ | ✅ | ❌ | ✅ | ✅ | ❌
Mr. Kah Weng      | ✅ | ❌ | ✅ | ✅ | ❌ | ✅
Mr. Jia Xiong     | ❌ | ✅ | ✅ | ❌ | ✅ | ✅
)" << endl << endl;

    // Step 1: Service selection
    int serviceChoice = selectService(services, serviceshours, servicesprice);
    int serviceIndex = serviceChoice - 1;

    // Inside bookAppointment, right after you get the serviceIndex
    double hours = serviceHours[serviceIndex];
    int slotsNeeded = ceil(hours); // ceil(2.5) becomes 3. ceil(1.0) becomes 1.

    // Step 2: Expert selection
    int expertChoice = selectExpert(experts, specializations, serviceIndex);
    int expertIndex = expertChoice - 1;

    // Step 3: Week + Date selection
    int startDay, endDay;
    int weekChoice = selectWeeks(startDay, endDay); // choose week
    int dateChoice = selectDate(startDay, endDay); // choose date
    int dateIndex = dateChoice - 1;

    // Step 3.5: Check expert work limits before proceeding
    if (!checkExpertWorkLimits(expertIndex, dateIndex, startDay, endDay, hours, experts, services, serviceHours, availability)) {
        cout << "\n❌ Cannot proceed with booking due to expert work limit restrictions.\n";
        cout << "Please select a different expert or time slot.\n\n";
        return;
    }

    // Step 4: Show available slots
    showAvailability(services, experts, timeSlots, endTimes, serviceIndex, expertIndex, dateIndex, dateChoice, weekChoice, availability);


    // Step 5: Choose time slot
    int timeIndex;
    while (true) {
        cout << string(50, '-') << endl;
        checkInput("Select a starting time slot: ", 1, 10, &timeChoice);
        timeIndex = timeChoice - 1; // Convert to 0-based index



        // --- New Logic Starts Here ---

        // 1. Basic check for valid slot number
        if (timeChoice < 1 || timeChoice > NUM_SLOTS) {
            cout << "❌ Invalid slot number. Please try again.\n";
            continue;
        }

        // 2. Check if the booking would go past closing time
        if (timeIndex + slotsNeeded > NUM_SLOTS) {
            cout << "❌ Not enough time for this service from the selected slot. Please choose an earlier time.\n";
            continue;
        }

        // 3. Check if ALL required slots are available
        bool allSlotsFree = true;
        for (int i = 0; i < slotsNeeded; ++i) {
            if (getAvailability(expertIndex, dateIndex, timeIndex + i, availability) == 1) {
                allSlotsFree = false; // Found a booked slot!
                cout << "❌ Sorry, the time " << timeSlots[timeIndex + i] << " is unavailable.\n";
                break; // No need to check further
            }

        }

        if (allSlotsFree) {
            break; // ✅ All slots are free, exit the loop!
        }
        else {
            cout << "Please select a different starting time.\n";
        }
    }

    // Step 6: Ask for payment confirmation
    while (true) {
        checkInput("Do you want to make payment? (1 for Yes, 2 for No): ", 1, 2, &askpayment);

        if (askpayment == 1) {
            cout << "Proceed to Payment\n";
            cout << string(50, '-') << endl;
            cout << "Please enter your phone number: +60-";
            cin >> phonenumber;

            // if method check integer
            if (phonenumber.length() != 9 && phonenumber.length() != 10) {
                cout << "Invalid input! Please enter correct phone number\nexample: +60-XXXXXXXXX" << endl;
                continue;
            }
            else {
                break;
            }

            break;
        }
        else if (askpayment == 2) {
            cout << "Cancel Bookings\n" << endl;
            return;
        }
        else {
            cout << "Invalid option. Please try again.\n";
            continue;
        }
    }

    float basePrice = servicesprice[serviceChoice - 1];
    // Calculate service charge and total amount
    double serviceCharge = basePrice * 0.06;
    double totalAmount = basePrice + serviceCharge;

    while (true) {
        cout << endl << string(50, '=') << endl;
        cout << right << setw(28) << "PAYMENT" << endl;
        cout << string(50, '=') << endl;
        cout << "Customer Name: " << currentUser.username << endl;
        cout << "Contact Number: +60-" << phonenumber << endl;
        cout << "Selected Service: " << services[serviceChoice - 1] << endl;
        cout << "Base Price: RM " << fixed << setprecision(2) << servicesprice[serviceChoice - 1] << endl;
        cout << "Service Charge (6%): RM " << fixed << setprecision(2) << serviceCharge << endl;
        cout << string(50, '-') << endl;
        cout << "Total Amount to Pay: RM" << fixed << setprecision(2) << totalAmount << endl << endl;
        cout << "Select Payment Method:\n";
        cout << "[1] Credit Card\n";
        cout << "[2] Online Banking\n";
        cout << "[3] E-Wallet\n";
        cout << "[4] Cancel Payment\n";
        cout << string(50, '-') << endl;
        cout << "Enter your choice: ";
        checkInput("Enter your choice: ", 1, 4, &payment);
        cout << endl;


        if (payment == 1) {
            cout << "Enter Cardholder Name: ";
            cin.ignore();
            getline(cin, cardholdername);
            while (cardholdername.empty()) {
                cout << "Cardholder name cannot be empty. Please re-enter: ";
                getline(cin, cardholdername);
            }

            // Card Number Validation
            while (true) {
                cout << "Enter Card Number (16 digits): ";
                cin >> cardnum;

                // Check if card number is exactly 16 digits and all numeric
                if (cardnum.length() == 16) {
                    bool validCard = true;
                    for (int i = 0; i < 16; i++) {
                        if (!isdigit(cardnum[i])) {
                            validCard = false;
                            break;
                        }
                    }
                    if (validCard) {
                        break; // Valid card number
                    }
                    else {
                        cout << "Card number must contain only digits. Please re-enter.\n";
                    }
                }
                else {
                    cout << "Card number must be exactly 16 digits. Please re-enter.\n";
                }
            }

            // Expiry Date Validation
            while (true) {
                cout << "Enter Expiry Date (MM/YY): ";
                cin >> expirydate;

                // Check format MM/YY (5 characters total)
                if (expirydate.length() == 5 && expirydate[2] == '/') {
                    // Check if MM and YY parts are numeric
                    bool validFormat = true;
                    for (int i = 0; i < 5; i++) {
                        if (i != 2 && !isdigit(expirydate[i])) {
                            validFormat = false;
                            break;
                        }
                    }

                    if (validFormat) {
                        // Extract month and year
                        int month = stoi(expirydate.substr(0, 2));
                        int year = stoi(expirydate.substr(3, 2));

                        // Validate month (01-12)
                        if (month >= 1 && month <= 12) {
                            // Basic year validation (assuming current year is 2025, so YY should be 25 or higher)
                            if (year >= 25) {
                                break; // Valid expiry date
                            }
                            else {
                                cout << "Card has expired. Please enter a valid expiry date.\n";
                            }
                        }
                        else {
                            cout << "Invalid month. Please enter MM between 01-12.\n";
                        }
                    }
                    else {
                        cout << "Invalid format. Please enter in MM/YY format (e.g., 12/25).\n";
                    }
                }
                else {
                    cout << "Invalid format. Please enter in MM/YY format (e.g., 12/25).\n";
                }
            }

            // CVV Validation
            while (true) {
                cout << "Enter CVV (3 digits): ";
                cin >> cvv;

                // Check if CVV is exactly 3 digits and all numeric
                if (cvv.length() == 3) {
                    bool validCVV = true;
                    for (int i = 0; i < 3; i++) {
                        if (!isdigit(cvv[i])) {
                            validCVV = false;
                            break;
                        }
                    }
                    if (validCVV) {
                        break; // Valid CVV
                    }
                    else {
                        cout << "CVV must contain only digits. Please re-enter.\n";
                    }
                }
                else {
                    cout << "CVV must be exactly 3 digits. Please re-enter.\n";
                }
            }

            cout << "Processing payment...\nPayment Successful!\n";
            break;
        }
        else if (payment == 2) {
            cout << "1. Maybank\n2. CIMB Bank\n3. Public Bank\n4. RHB Bank\n5. Hong Leong Bank\n";
            while (true) {
                cout << string(50, '-') << endl;
                cout << "Select Bank: ";
                cin >> bank;
                cout << endl;

                // Check length and valid range
                if (bank.length() == 1 && bank[0] >= '1' && bank[0] <= '5') {
                    break; // valid input → exit loop
                }
                else {
                    cout << "Invalid input! Please enter only ONE digit between 1 and 5.\n";
                }
            }

            if (bank[0] >= '1' && bank[0] <= '5') {
                cout << "Enter Username: ";
                cin.ignore();
                getline(cin, username);
                while (username.empty()) {
                    cout << "Banking username cannot be empty. Please re-enter: ";
                    getline(cin, username);
                }
                cout << "Enter Password: ";
                cin >> password;
                cout << "Processing payment...\nPayment Successful!\n";
                break;
            }
            else {
                cout << "Invalid bank selection. Try again.\n";
            }
        }
        else if (payment == 3) {
            cout << "Processing payment via E-Wallet...\nPayment Successful!\n";
            break;
        }
        else if (payment == 4) {
            cout << "Payment Cancelled.\n";
            return;
        }
        else {
            cout << "Invalid payment option. Try again.\n";
        }
    }

    // Step 6: Mark as booked
    for (int i = 0; i < slotsNeeded; ++i) {
        //availability[expertIndex][dateIndex][timeIndex + 2] = 1;
        getAvailability(expertIndex, dateIndex, timeIndex + i, availability) = 1; // Mark each slot as booked
    }

    // Save booking
    Booking booking;

    strcpy_s(booking.username, currentUser.username.c_str()); // from login
    strcpy_s(booking.phonenumber, phonenumber.c_str());
    strcpy_s(booking.service, services[serviceChoice - 1].c_str());
    strcpy_s(booking.expert, experts[expertChoice - 1].c_str());
    booking.date = dateChoice;
    strcpy_s(booking.time, timeSlots[timeChoice - 1].c_str());
    strcpy_s(booking.endtime, endTimes[timeIndex + slotsNeeded - 1].c_str());




    ofstream out("bookings.dat", ios::app); // no binary mode
    out << "Customer: " << booking.username << "\n";
    out << "Phone Number: +60-" << booking.phonenumber << "\n";
    out << "Service: " << booking.service << "\n";
    out << "Expert: Mr. " << booking.expert << "\n";
    out << "Date: " << booking.date << " December 2025" << "\n";
    out << "Time: " << booking.time << " to " << booking.endtime << "\n";
    out << "Total Paid: RM" << fixed << setprecision(2) << totalAmount << "\n";
    out << "-------------------------\n\n";
    out.close();

    cout << "\n✅ Booking Confirmed!\n";
    cout << "Customer: " << booking.username << endl;
    cout << "Phone Number: +60-" << booking.phonenumber << endl;
    cout << "Service: " << booking.service << endl;
    cout << "Expert: Mr. " << booking.expert << endl;
    cout << "Date: 2025 December " << booking.date << endl;
    cout << "Time: " << booking.time << " to " << booking.endtime << endl;
    cout << "Total Paid: RM" << fixed << setprecision(2) << totalAmount << endl << endl;
}
// End of Case 3

// Start ===== CASE 4: VIEW MY BOOKINGS =====
//load current booking history
void loadBookings(string services[], string experts[], string timeSlots[], double serviceHours[], int availability[][NUM_SLOTS]) {
    ifstream in("bookings.dat");
    if (!in) {
        // File doesn't exist - this is normal for first run
        // Just return, availability array will remain all 0s (available)
        return;
    }

    string line;
    string bookingRecord[10]; // Store one complete booking record
    int lineCount = 0;


    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            // End of one booking record, process it
            if (lineCount > 0) {
                string customer, service, expert, dateStr, timeStr;

                // Extract booking details from the record
                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Customer: ", 0) == 0) {
                        customer = bookingRecord[i].substr(10);
                    }
                    else if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = bookingRecord[i].substr(12);
                    }
                    else if (bookingRecord[i].rfind("Date: ", 0) == 0) {
                        dateStr = bookingRecord[i].substr(6);
                    }
                    else if (bookingRecord[i].rfind("Time: ", 0) == 0) {
                        timeStr = bookingRecord[i].substr(6);
                    }
                }

                // Find service index
                int serviceIndex = -1;
                for (int i = 0; i < NUM_SERVICE; i++) {
                    if (service == services[i]) {
                        serviceIndex = i;
                        break;
                    }
                }

                // Find expert index
                int expertIndex = -1;
                for (int i = 0; i < NUM_EXPERTS; i++) {
                    if (expert == experts[i]) {
                        expertIndex = i;
                        break;
                    }
                }

                // Parse date (extract day number)
                int day = 0;
                if (!dateStr.empty()) {
                    stringstream ss(dateStr);
                    ss >> day; // Extract day number
                }

                // Parse time to find time slot index
                int timeIndex = -1;
                if (!timeStr.empty()) {
                    // Extract start time from "10:00AM to 11:00AM" format
                    string startTime = timeStr.substr(0, timeStr.find(" to "));

                    // Find matching time slot
                    for (int i = 0; i < NUM_SLOTS; i++) {
                        if (timeSlots[i] == startTime) {
                            timeIndex = i;
                            break;
                        }
                    }
                }

                // Mark slots as unavailable if all data is valid
                if (serviceIndex != -1 && expertIndex != -1 && timeIndex != -1 && day > 0) {
                    double hours = serviceHours[serviceIndex];
                    int slotsNeeded = ceil(hours);

                    // Block all the slots this booking occupies
                    for (int i = 0; i < slotsNeeded; ++i) {
                        if (timeIndex + i < NUM_SLOTS) { // Safety check
                            getAvailability(expertIndex, day - 1, timeIndex + i, availability) = 1;
                        }
                    }
                }
            }
            lineCount = 0; // Reset for next booking
        }
        else if (!line.empty() && lineCount < 10) {
            // Store this line as part of current booking record
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();
}

void viewMyBookings(const User& currentUser) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(30) << "MY BOOKINGS" << endl;
    cout << string(50, '=');
    ifstream in("bookings.dat");
    if (!in) {
        cout << "No bookings found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find("Customer: " + currentUser.username) != string::npos) {
            found = true;
            cout << "\n" << line << "\n";
            for (int i = 0; i < 5; i++) { // next 5 lines of booking details
                getline(in, line);
                cout << line << "\n";
            }
        }
    }
    in.close();

    if (!found) {
        cout << "\nYou have no bookings yet.\n";
    }
}
// End of Case 4


// Start ===== CASE 5: FEEDBACK =====
bool userHasBooking(const User& currentUser) {
    ifstream in("bookings.dat");
    if (!in) return false;
    string line;
    while (getline(in, line)) {
        if (line.find("Customer: " + currentUser.username) != string::npos) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

void leaveFeedback(const User& currentUser, string services[], string experts[]) {
    // Optional: allow selecting which booking to rate later. For now, capture details manually.
    cout << endl << string(50, '=') << endl;
    cout << right << setw(28) << "FEEDBACK" << endl;
    cout << string(50, '=') << endl;

    // Rating 1-5
    int rating;
    checkInput("Rate your experience (1-5): ", 1, 5, &rating);

    // Flush newline before getline
    cin.ignore();

    // Feedback comment (non-empty)
    string comment;
    cout << "Write your feedback: ";
    getline(cin, comment);
    while (comment.empty()) {
        cout << "Feedback cannot be empty. Please re-enter: ";
        getline(cin, comment);
    }

    // Optionally capture service and expert from last booking of this user for better context
    string lastService = "";
    string lastExpert = "";
    string lastDate = "";
    ifstream bin("bookings.dat");
    if (bin) {
        string line;
        string rec[12];
        int cnt = 0;
        while (getline(bin, line)) {
            if (line.find("-------------------------") != string::npos) {
                bool isUser = false;
                string service, expert, dateStr;
                for (int i = 0; i < cnt; ++i) {
                    if (rec[i].rfind("Customer: ", 0) == 0 && rec[i].substr(10) == currentUser.username) {
                        isUser = true;
                    }
                    else if (rec[i].rfind("Service: ", 0) == 0) {
                        service = rec[i].substr(9);
                    }
                    else if (rec[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = rec[i].substr(12);
                    }
                    else if (rec[i].rfind("Date: ", 0) == 0) {
                        dateStr = rec[i].substr(6);
                    }
                }
                if (isUser) {
                    lastService = service;
                    lastExpert = expert;
                    lastDate = dateStr;
                }
                cnt = 0;
            }
            else if (!line.empty() && cnt < 12) {
                rec[cnt++] = line;
            }
        }
        bin.close();
    }

    ofstream out("feedbacks.dat", ios::app);
    out << "Customer: " << currentUser.username << "\n";
    if (!lastService.empty()) out << "Service: " << lastService << "\n";
    if (!lastExpert.empty()) out << "Expert: Mr. " << lastExpert << "\n";
    if (!lastDate.empty()) out << "Date: " << lastDate << "\n";
    out << "Rating: " << rating << "\n";
    out << "Comment: " << comment << "\n";
    out << "-------------------------\n\n";
    out.close();

    cout << "\nThank you for your feedback!\n\n";
}
// ===== End Feedback Implementation =====
// End of Case 5

// Start admin menu
void adminSystem(string services[], string serviceshours[], float servicesprice[], string experts[], string timeSlots[], double serviceHours[], int specializations[][6]) {
    Admin admin;
    if (adminLogin(admin)) {
        bool inAdminMenu = true;
        while (inAdminMenu) {
            // Show Admin Menu
            cout << "\n" << string(50, '=') << endl;
            cout << right << setw(32) << "ADMIN DASHBOARD" << endl;
            cout << string(50, '=') << endl;
            cout << "1. View Individual Expert Schedule\n";
            cout << "2. View Overall Schedule\n";
            cout << "3. View Customer List\n";
            cout << "4. Generate Sales Reports\n";
            cout << "5. View Expert Bonus Entitlements\n";
            cout << "6. Logout\n";
            cout << "7. Exit" << endl;
            cout << string(50, '-') << endl;

            int adminchoice;
            checkInput("Enter your choice (1-7): ", 1, 7, &adminchoice);

            switch (adminchoice) {
            case 1:
                viewIndividualExpertSchedule(services, serviceshours, servicesprice, experts, timeSlots, serviceHours, specializations);
                break;
            case 2:
                viewOverallSchedule(services, experts, timeSlots);
                break;
            case 3:
                viewCustomerList(services, experts);
                break;
            case 4:
                generateSalesReports(services);
                break;
            case 5:
                viewExpertBonusEntitlements(services, experts, serviceHours);
                break;
            case 6:
                cout << "Logging out...\n\n";
                inAdminMenu = false;
                break;
            case 7:
                cout << "Exiting program. Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}
//End admin menu

// ===== ADMIN FUNCTIONS IMPLEMENTATION =====
// 1. View Individual Expert Schedule
void viewIndividualExpertSchedule(string services[], string serviceshours[], float servicesprice[], string experts[], string timeSlots[], double serviceHours[], int specializations[][6]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(35) << "INDIVIDUAL EXPERT SCHEDULE" << endl;
    cout << string(50, '=') << endl;

    // no need ask for service direct ask expert
    cout << "Select Expert:\n";
    for (int i = 0; i < NUM_EXPERTS; i++) {
        cout << (i + 1) << ". Mr. " << experts[i] << endl;
    }
    int expertChoice;
    cout << string(50, '-') << endl;
    checkInput("Enter expert choice (1-3): ", 1, 3, &expertChoice);
    int expertIndex = expertChoice - 1;

    // Select week using existing function concept
    int startDay, endDay;
    int weekChoice = selectWeeks(startDay, endDay);

    cout << endl << "Viewing Expert Schedules – Week " << weekChoice << endl;
    cout << "Expert: Mr. " << experts[expertIndex] << endl;
    cout << string(50, '=') << endl;

    cout << left << setw(8) << "Date"
        << setw(8) << "Time"
        << setw(20) << "Service"
        << setw(15) << "Customer" << endl;
    cout << string(50, '-') << endl;

    int totalHours = 0;
    bool hasBookings = false;

    // Read bookings from file to show actual customer data
    ifstream in("bookings.dat");
    if (in) {
        string line;
        string bookingRecord[10];
        int lineCount = 0;

        while (getline(in, line)) {
            if (line.find("-------------------------") != string::npos) {
                if (lineCount > 0) {
                    string customerName, service, expert, date, time;

                    for (int i = 0; i < lineCount; i++) {
                        if (bookingRecord[i].rfind("Customer: ", 0) == 0) {
                            customerName = bookingRecord[i].substr(10);
                        }
                        else if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                            service = bookingRecord[i].substr(9);
                        }
                        else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                            expert = bookingRecord[i].substr(12);
                        }
                        else if (bookingRecord[i].rfind("Date: ", 0) == 0) {
                            date = bookingRecord[i].substr(6);
                        }
                        else if (bookingRecord[i].rfind("Time: ", 0) == 0) {
                            time = bookingRecord[i].substr(6);
                        }
                    }

                    // Check if this booking is for the selected expert and week
                    if (expert == experts[expertIndex]) {
                        int bookingDate = stoi(date);
                        if (bookingDate >= startDay && bookingDate <= endDay) {
                            hasBookings = true;
                            cout << left << setw(8) << "Dec " + to_string(bookingDate)
                                << setw(8) << time.substr(0, 4) // Show only time like "10AM"
                                << setw(20) << service
                                << setw(15) << customerName << endl;

                            // Calculate hours based on selected service duration
                            for (int i = 0; i < NUM_SERVICE; ++i) {
                                if (service == services[i]) {
                                    totalHours += serviceHours[i];
                                    break;
                                }
                            }
                        }
                    }
                }
                lineCount = 0;
            }
            else if (!line.empty() && lineCount < 10) {
                bookingRecord[lineCount] = line;
                lineCount++;
            }
        }
        in.close();
    }

    if (!hasBookings) {
        cout << "No bookings found for this expert in Week " << weekChoice << endl;
    }

    cout << string(50, '-') << endl;
    cout << "Total Hours this Week: " << totalHours << " hrs" << endl;
    cout << string(50, '-') << endl;
}
// end case 1

// 2. View Overall Schedule
void viewOverallSchedule(string services[], string experts[], string timeSlots[]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(30) << "OVERALL SCHEDULE" << endl;
    cout << string(50, '=') << endl;

    // Header
    cout << left << setw(8) << "Date"
        << setw(8) << "Start"
        << setw(8) << "End"
        << setw(18) << "Service"
        << setw(12) << "Customer"
        << "Expert" << endl;
    cout << string(66, '-') << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No bookings found.\n";
        cout << string(50, '-') << endl;
        return;
    }

    string line;
    string record[12];
    int count = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (count > 0) {
                string customer, service, expert, dateStr, timeStr;
                for (int i = 0; i < count; ++i) {
                    if (record[i].rfind("Customer: ", 0) == 0) customer = record[i].substr(10);
                    else if (record[i].rfind("Service: ", 0) == 0) service = record[i].substr(9);
                    else if (record[i].rfind("Expert: Mr. ", 0) == 0) expert = record[i].substr(12);
                    else if (record[i].rfind("Date: ", 0) == 0) dateStr = record[i].substr(6);
                    else if (record[i].rfind("Time: ", 0) == 0) timeStr = record[i].substr(6);
                }

                // Parse day from date (e.g., "12 December 2025" -> 12)
                int day = 0;
                if (!dateStr.empty()) {
                    stringstream ss(dateStr);
                    ss >> day; // read leading integer day
                }

                // Parse start and end times from "HH:MMAM to HH:MMAM"
                string startTime = "";
                string endTime = "";
                size_t toPos = timeStr.find(" to ");
                if (toPos != string::npos) {
                    startTime = timeStr.substr(0, toPos);
                    endTime = timeStr.substr(toPos + 4);
                }
                else {
                    startTime = timeStr;
                }

                cout << left << setw(8) << ("Dec " + to_string(day))
                    << setw(8) << startTime
                    << setw(8) << endTime
                    << setw(18) << service
                    << setw(12) << customer
                    << ("Mr. " + expert) << endl;
            }
            count = 0;
        }
        else if (!line.empty() && count < 12) {
            record[count++] = line;
        }
    }
    in.close();

    cout << string(50, '-') << endl;
}
// end case 2

// 3. View Customer List
void viewCustomerList(string services[], string experts[]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(35) << "ALL REGISTERED CUSTOMERS" << endl;
    cout << string(50, '=') << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No customer data found.\n";
        return;
    }

    string line;
    int customerCount = 0;
    bool found = false;

    cout << left << setw(15) << "Name"
        << setw(18) << "Service Booked"
        << setw(18) << "Assigned Expert" << endl;
    cout << string(50, '-') << endl;

    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {
                found = true;
                customerCount++;

                string customerName, service, expert;

                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Customer: ", 0) == 0) {
                        customerName = bookingRecord[i].substr(10);
                    }
                    else if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = bookingRecord[i].substr(12);
                    }
                }

                cout << left << setw(15) << customerName
                    << setw(18) << service
                    << setw(18) << "Mr. " + expert << endl;
            }
            lineCount = 0;
        }
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();

    if (!found) {
        cout << "No customers found.\n";
    }
    else {
        cout << string(50, '-') << endl;
        cout << "Total Customers: " << customerCount << endl;
    }

    // ⭐ Search feedback by rating functionality
    cout << "\nSearch feedback by rating range (1-5) \n";
    int minRating, maxRating;
    cin.ignore();
    checkInput("Enter minimum rating (1-5): ", 1, 5, &minRating);
    while (minRating < 1 || minRating > 5) {
        cout << "Invalid rating. Please enter between 1-5: ";
        cin >> minRating;
    }
    checkInput("Enter maximum rating (1-5): ", 1, 5, &maxRating);
    while (maxRating < 1 || maxRating > 5 || maxRating < minRating) {
        cout << "Invalid rating. Please enter between 1-5 and >= minimum: ";
        cin >> maxRating;
    }

    cout << "\nSearching feedback with rating between " << minRating << " and " << maxRating << "..." << endl;
    cout << string(50, '-') << endl;

    // Read feedbacks.dat and search by rating
    ifstream fin("feedbacks.dat");
    if (!fin) {
        cout << "No feedback data found.\n";
        cout << string(50, '-') << endl;
        return;
    }

    string fline;
    string fRec[12];
    int fcnt = 0;
    bool anyFeedback = false;
    int feedbackCount = 0;

    while (getline(fin, fline)) {
        if (fline.find("-------------------------") != string::npos) {
            if (fcnt > 0) {
                // Process one feedback record
                string fbCustomer, service, expert, date, rating, comment;
                for (int i = 0; i < fcnt; ++i) {
                    if (fRec[i].rfind("Customer: ", 0) == 0) fbCustomer = fRec[i].substr(10);
                    else if (fRec[i].rfind("Service: ", 0) == 0) service = fRec[i].substr(9);
                    else if (fRec[i].rfind("Expert: Mr. ", 0) == 0) expert = fRec[i].substr(12);
                    else if (fRec[i].rfind("Date: ", 0) == 0) date = fRec[i].substr(6);
                    else if (fRec[i].rfind("Rating: ", 0) == 0) rating = fRec[i].substr(8);
                    else if (fRec[i].rfind("Comment: ", 0) == 0) comment = fRec[i].substr(9);
                }

                // Check if rating is within range
                if (!rating.empty()) {
                    int ratingValue = stoi(rating);
                    if (ratingValue >= minRating && ratingValue <= maxRating) {
                        anyFeedback = true;
                        feedbackCount++;

                        // Display customer info
                        cout << "Customer: " << fbCustomer << endl;
                        if (!service.empty()) cout << "Service: " << service << endl;
                        if (!expert.empty()) cout << "Expert: Mr. " << expert << endl;
                        if (!date.empty()) cout << "Date: " << date << endl;

                        // Display feedback on next row
                        cout << "Feedback: Rating " << rating << " - " << comment << endl;
                        cout << string(50, '-') << endl;
                    }
                }
            }
            fcnt = 0;
        }
        else if (!fline.empty() && fcnt < 12) {
            fRec[fcnt++] = fline;
        }
    }
    fin.close();

    if (!anyFeedback) {
        cout << "No feedback found with rating between " << minRating << " and " << maxRating << "." << endl;
    }
    else {
        cout << "Total feedback found: " << feedbackCount << " entries" << endl;
    }

    cout << string(50, '-') << endl;
}
// end case 3

// 4. Generate Sales Reports
void generateSalesReports(string services[]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(30) << "SALES REPORT" << endl;
    cout << string(50, '=') << endl;

    cout << "Sales Report – December 2025\n";
    cout << string(60, '-') << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No sales data found.\n";
        return;
    }

    string line;
    double totalSales = 0.0;
    //int totalBookings = 0;

    // Service categories - reuse existing service names
    double serviceSales[NUM_SERVICE] = { 0 };
    int serviceBookings[NUM_SERVICE] = { 0 };

    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {
                //totalBookings++;

                string service, totalPaid;

                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Total Paid: RM", 0) == 0) {
                        totalPaid = bookingRecord[i].substr(14);
                    }
                }

                double amount = stod(totalPaid);
                totalSales += amount;

                // Update service sales using existing service names
                for (int i = 0; i < NUM_SERVICE; i++) {
                    if (service == services[i]) {
                        serviceSales[i] += amount;
                        serviceBookings[i]++;
                        break;
                    }
                }
            }
            lineCount = 0;
        }
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();

    // Display in the format from the example
    cout << left << setw(17) << "Service Type"
        << setw(17) << "Total Bookings"
        << "Total Sales (RM)" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < NUM_SERVICE; i++) {
        if (serviceBookings[i] > 0) { // Only show services that have bookings
            cout << left << setw(17) << services[i]
                << setw(17) << serviceBookings[i]
                << "RM" << fixed << setprecision(2) << serviceSales[i] << endl;
        }
    }

    cout << string(60, '-') << endl;
    cout << "Total Revenue: RM" << fixed << setprecision(2) << totalSales << endl;
    cout << string(60, '-') << endl;
}
//end case 4

// 5. View Expert Bonus Entitlements
void viewExpertBonusEntitlements(string services[], string experts[], double serviceHours[]) {
    cout << endl << string(50, '=') << endl;
    cout << right << setw(35) << "EXPERT BONUS ENTITLEMENTS" << endl;
    cout << string(50, '=') << endl;

    cout << "Expert Bonus Report – December 2025\n";
    cout << string(70, '-') << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No booking data found.\n";
        return;
    }

    // Initialize expert data
    struct ExpertData {
        double totalHours = 0;
        double totalServiceCharges = 0;
    };

    ExpertData expertData[NUM_EXPERTS];

    string line;
    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {
                string service, expert, totalPaid;

                for (int i = 0; i < lineCount; i++) {
                    if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                        service = bookingRecord[i].substr(9);
                    }
                    else if (bookingRecord[i].rfind("Expert: Mr. ", 0) == 0) {
                        expert = bookingRecord[i].substr(12);
                    }
                    else if (bookingRecord[i].rfind("Total Paid: RM", 0) == 0) {
                        totalPaid = bookingRecord[i].substr(14);
                    }
                }

                // Find service hours and expert index using existing arrays
                double hours = 0;
                int expertIndex = -1;

                for (int i = 0; i < NUM_SERVICE; i++) {
                    if (service == services[i]) {
                        hours = serviceHours[i];
                        break;
                    }
                }

                for (int i = 0; i < NUM_EXPERTS; i++) {
                    if (expert == experts[i]) {
                        expertIndex = i;
                        break;
                    }
                }

                if (expertIndex != -1) {
                    expertData[expertIndex].totalHours += hours;
                    expertData[expertIndex].totalServiceCharges += stod(totalPaid);
                }
            }
            lineCount = 0;
        }
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }

    in.close();

    // Display in table format like the example
    cout << left << setw(15) << "Expert"
        << setw(15) << "Total Hours"
        << setw(15) << "Service Value"
        << setw(10) << "Bonus %"
        << "Bonus (RM)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < NUM_EXPERTS; i++) {
        double totalHours = expertData[i].totalHours;
        double serviceValue = expertData[i].totalServiceCharges;

        // Calculate bonus using existing rules
        double bonusRate = 0;
        if (totalHours >= 30) {
            bonusRate = 50;
        }
        else if (totalHours >= 25) {
            bonusRate = 25;
        }

        double bonusAmount = (bonusRate / 100.0) * serviceValue;

        cout << left << setw(15) << "Mr. " + experts[i]
            << setw(15) << totalHours
            << "RM" << setw(14) << fixed << setprecision(2) << serviceValue
            << setw(10) << bonusRate << "RM" << fixed << setprecision(2) << bonusAmount << endl;
    }
    cout << string(70, '-') << endl;
    cout << string(70, '-') << endl;
}
// End admin case

// Start exeprt menu
void expertSystem(string experts[], string services[], double serviceHours[]) {
    int login = expertLogin(experts);
    if (login == -1) return; // stop if login failed

    int expertchoice;
    do {
        cout << "\n" << string(50, '=') << endl;
        cout << right << setw(30) << "EXPERT PORTAL" << endl;
        cout << string(50, '=') << endl;
        cout << "1. View My Schedule\n";
        cout << "2. View My Customers\n";
        cout << "3. View My Bonus\n";
        cout << "4. Logout\n";
        cout << "5. Exit" << endl;
        cout << string(50, '-') << endl;

        checkInput("Enter your choice (1-5): ", 1, 5, &expertchoice);
        cout << endl;

        switch (expertchoice) {
        case 1:
            viewExpertSchedule(login, experts);
            break;

        case 2:
            viewExpertCustomers(login, experts);
            break;


        case 3:
            viewExpertBonus(login, experts, services, serviceHours);
            break;

        case 4:
            cout << "Logging out..." << endl;
            break;

        case 5:
            cout << "Exiting..." << endl;
            cout << "Thank you for using Hair Talk Booking System!" << endl;
            exit(0);
            break;
        }
    } while (expertchoice != 4 && expertchoice != 5);
}

void viewExpertSchedule(int login, string experts[]) {
    cout << string(10, '-') << "📅 SCHEDULE FOR Mr. " << experts[login] << string(11, '-') << endl;
    cout << string(50, '=') << endl;
    cout << "Your Upcoming Appointments:\n";
    cout << string(50, '-') << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No bookings found.\n";
        return;
    }

    string line;
    bool found = false;


    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {

        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {


                bool isForThisExpert = false;
                for (int i = 0; i < lineCount; ++i) {
                    if (bookingRecord[i].find("Expert: Mr. " + experts[login]) != string::npos) {
                        isForThisExpert = true;
                        break;
                    }
                }


                if (isForThisExpert) {
                    found = true;
                    cout << endl;
                    for (int i = 0; i < lineCount; ++i) {

                        if (bookingRecord[i].find("Expert: Mr. ") == string::npos) {
                            cout << bookingRecord[i] << endl;
                        }
                    }
                    cout << string(50, '-') << endl;
                }
            }

            lineCount = 0;
        }

        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }
    in.close();

    if (!found) {
        cout << "\nNo upcoming appointments for Mr. " << experts[login] << ".\n";
    }
    cout << string(50, '-') << endl;
}

void viewExpertCustomers(int login, string experts[]) {
    cout << string(17, '-') << "👥 MY CUSTOMERS" << string(18, '-') << endl;
    cout << string(50, '=') << endl;
    cout << "Your Customer:\n";
    cout << string(50, '-') << endl << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No bookings found.\n";
        return;
    }
    string line;
    bool foundCustomer = false; //  check are find the at least one customer


    // used the temporary string array to store a complete record

    string bookingRecord[10];
    int lineCount = 0;

    while (getline(in, line)) {
        // when read a '-' line, will process the record
        if (line.find("-------------------------") != string::npos) {
            if (lineCount > 0) {

                // 1. check this record is for this expert
                bool isForThisExpert = false;
                for (int i = 0; i < lineCount; ++i) {
                    if (bookingRecord[i].find("Expert: Mr. " + experts[login]) != string::npos) {
                        isForThisExpert = true;
                        break;
                    }
                }

                // 2. if yes, get the data and print
                if (isForThisExpert) {
                    foundCustomer = true; // we are find the customer
                    string customerName, phoneNumber, service, date;

                    // get the data fromt the temporary record
                    for (int i = 0; i < lineCount; ++i) {
                        if (bookingRecord[i].rfind("Customer: ", 0) == 0) {
                            customerName = bookingRecord[i].substr(10);
                        }
                        else if (bookingRecord[i].rfind("Phone Number: ", 0) == 0) {
                            phoneNumber = bookingRecord[i].substr(14);
                        }
                        else if (bookingRecord[i].rfind("Service: ", 0) == 0) {
                            service = bookingRecord[i].substr(9);
                        }
                        else if (bookingRecord[i].rfind("Date: ", 0) == 0) {
                            date = bookingRecord[i].substr(6);
                        }
                    }

                    // the layout
                    cout << "Customer: " << customerName << endl;
                    cout << "Phone: " << phoneNumber << endl;
                    cout << "Service: " << service << endl;
                    cout << "Date: " << date << endl;
                    cout << string(50, '-') << endl;
                }
            }
            // 3. reset count, prepare for next record
            lineCount = 0;
        }
        // will store
        else if (!line.empty() && lineCount < 10) {
            bookingRecord[lineCount] = line;
            lineCount++;
        }
    }
    in.close();

    // ifloop exit , and no find the customer , will print the message
    if (!foundCustomer) {
        cout << "You have no customers yet.\n";
    }
    cout << string(50, '=') << endl;
}

void viewExpertBonus(int login, string experts[], string services[], double serviceHours[]) {
    cout << string(50, '=') << endl;
    cout << setw(35) << "💰 BONUS CALCULATION" << endl;
    cout << string(50, '=') << endl;
    cout << "📊 Performance Summary:" << endl;
    cout << string(50, '-') << endl << endl;

    ifstream in("bookings.dat");
    if (!in) {
        cout << "No bookings found.\n";
        return;
    }

    string line;
    int totalBookings = 0;
    double totalHoursWorked = 0.0;
    double totalEarnings = 0.0;

    // Parse bookings and accumulate stats for this expert
    string record[12];
    int count = 0;
    while (getline(in, line)) {
        if (line.find("-------------------------") != string::npos) {
            if (count > 0) {
                string expert, service, amountStr;
                for (int i = 0; i < count; ++i) {
                    if (record[i].rfind("Expert: Mr. ", 0) == 0) expert = record[i].substr(12);
                    else if (record[i].rfind("Service: ", 0) == 0) service = record[i].substr(9);
                    else if (record[i].rfind("Total Paid: RM", 0) == 0) amountStr = record[i].substr(14);
                }

                if (expert == experts[login]) {
                    totalBookings++;
                    // hours
                    for (int si = 0; si < NUM_SERVICE; ++si) {
                        if (service == services[si]) {
                            totalHoursWorked += serviceHours[si];
                            break;
                        }
                    }
                    // earnings
                    if (!amountStr.empty()) totalEarnings += stod(amountStr);
                }
            }
            count = 0;
        }
        else if (!line.empty() && count < 12) {
            record[count++] = line;
        }
    }
    in.close();

    // Bonus calculation
    double bonusRate = 0.0;
    if (totalHoursWorked >= 30.0) bonusRate = 0.50;
    else if (totalHoursWorked >= 25.0) bonusRate = 0.25;
    double bonusAmount = totalEarnings * bonusRate;
    double totalComp = totalEarnings + bonusAmount;

    cout << fixed << setprecision(2);
    cout << "Total Bookings: " << totalBookings << endl;
    cout << "Total Hours Worked: " << totalHoursWorked << " hrs" << endl;
    cout << "Total Earnings: RM" << totalEarnings << endl;
    cout << "Bonus Rate: " << (bonusRate * 100) << "%" << endl;
    cout << "💰 Bonus Amount: RM" << bonusAmount << endl;
    cout << "💵 Total Compensation: RM" << totalComp << endl;
}


void ClearScreen() { cout << "\033[2J\033[1;1H"; }