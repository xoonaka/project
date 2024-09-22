#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cctype>
#include <algorithm>
#include <regex>

using namespace std;

int getNextCustomerID() {
    ifstream inFile("customer_counter.txt");
    int counter = 1;  // Start from 1 instead of 0
    if (inFile.is_open()) {
        inFile >> counter;
        inFile.close();
    }
    ofstream outFile("customer_counter.txt");
    if (outFile.is_open()) {
        outFile << (counter + 1);  // Write the next number
        outFile.close();
    }
    return counter;  // Return the current number, not the next one
}

void clearScreen() { cout << "\033[2J\033[1;1H"; }

void displayLogo() {
    cout << R"(
  ,--,                          __                                                            
,--.'|                        ,'  , `.  ,--,                                                    
|  | :            ,--,     ,-+-,.' _ |,--.'|         ,---,    ,---.           ,--,               
:  : '          ,'_ /|  ,-+-. ;   , |||  |,      ,-+-. /  |  '   ,'\        ,'_ /|   .--.--.    
|  ' |     .--. |  | : ,--.'|'   |  ||`--'_     ,--.'|'   | /   /   |  .--. |  | :  /  /    '   
'  | |   ,'_ /| :  . ||   |  ,', |  |,,' ,'|   |   |  ,"' |.   ; ,. :,'_ /| :  . | |  :  /`./   
|  | :   |  ' | |  . .|   | /  | |--' '  | |   |   | /  | |'   | |: :|  ' | |  . . |  :  ;_     
'  : |__ |  | ' |  | ||   : |  | ,    |  | :   |   | |  | |'   | .; :|  | ' |  | |  \  \    `.  
|  | '.'|:  | : ;  ; ||   : |  |/     '  : |__ |   | |  |/ |   :    |:  | : ;  ; |   `----.   \ 
;  :    ;'  :  --'   \   | |-'      |  | '.'||   | |--'   \   \  / '  :  `--'   \ /  /--'  / 
|  ,   / :  ,      .-./   ;/          ;  :    ;|   |/        `----'  :  ,      .-/'--'.     /  
 ---'   `------'   '---'           |  ,   / '---'                  ------'      `--'---'   
                                   ---`-'                                                   
                                 ,--.'|                                                         
                                 |  | :     ,---.           .---.                               
                        ,----._,.:  : '    '   ,'\         /. ./|                               
                       /   /  ' /|  ' |   /   /   |     .-'-. ' |                               
                      |   :     |'  | |  .   ; ,. :    /_/ \: |                               
                      |   | .\  .|  | :  '   | |: : .-'.. '   ' .                               
                      .   ; ';  |'  : |_'   | .; :/  ' |`-' /                               
                      '   .   . ||  | '.'|   :    |' /   \ |   \                                  
                       `---'| |;  :    ;\   \  /  \   \  \    \                               
                       .'_/\: ||  ,   /  `----'    \   \ |                                
                       |   :    : ---`-'              '---"                                    
                        \   \  /                                                                
                         ---'                                                                 
    )" << endl;
}

void displayAboutUs() {
    clearScreen();
    displayLogo();
    cout << "\nAbout Us\n";
    cout << "--------\n";
    cout << "Welcome Luminous Glow, where beauty meets relaxation. \n";
    cout << "Established in 2010, we have been providing top-notch beauty \n";
    cout << "and wellness services to our valued clients for over a decade. \n";
    cout << "Our team of expert aestheticians and therapists are dedicated \n";
    cout << "to enhancing your natural beauty and promoting overall well-being. \n";
    cout << "From rejuvenating facials to luxurious spa treatments and glamorous \n";
    cout << "makeovers, we offer a wide range of services tailored to meet your \n";
    cout << "individual needs. At Luminous Glow, we believe in using only the \n";
    cout << "finest products and cutting-edge techniques to ensure you leave \n";
    cout << "feeling refreshed, confident, and glowing. Your journey to radiance \n";
    cout << "starts here!\n";
}

void displayService(const string& service, const string& details, int treatmentCost, int consultationCost) {
    clearScreen();
    displayLogo();
    cout << service << " Service\n\n" << details << "\n\nTreatment :120 minutes || RM " << treatmentCost << "\nConsultation : 60 minutes || RM " << consultationCost << endl;
}

void displayServiceList(bool& returnToMainMenu) {
    clearScreen();
    displayLogo();
    cout << "Our Service List:\n\n";
    cout << "S1 : Facial Service\n";
    cout << "S2 : Spa Service\n";
    cout << "S3 : Makeup Service\n";
    cout << "V  : View Appointment\n";
    cout << "M  : Back to Main Menu\n\n";
    cout << "Enter your choice (S1, S2, S3, V, or M): ";

    string choice;
    cin >> choice;
    for (char& c : choice) c = toupper(c);

    if (choice == "S1") displayService("S1 : Facial", "Our exclusive V-Lift facial sculpting treatment, combined with the \npatented far infrared ceramic wand, opens up meridians to soften \nthe skin from the inside out, leaving it firm and revitalized. This \ncomfortable treatment lifts the apple cheeks and contours the jawline \nby 5 degree, addressing mild to severe aging signs while reducing \ndullness, sallowness, puffiness, and dark circles.\n", 500, 150);
    else if (choice == "S2") displayService("S2 : Spa", "Our Spa treatment by using an exclusive \"Far-infrared Ceramic Wands\" \nto revitalize the meridian and enhance the results of body circulation. \nIt improves body circulation and revitalize Qi and blood metabolism, \neliminates edema and enhances natural healing powers of body.", 800, 200);
    else if (choice == "S3") displayService("S3 : Makeup", "Our makeup services offer a variety of makeup styles. You can also \ncommunicate with our makeup artists to customize the style you want.", 300, 100);
    else if (choice == "V") {
        string viewcustomerID;
        clearScreen();
        displayLogo();
        cout << "\nEnter your Customer ID for view appointment: ";
        cin >> viewcustomerID;

        // Load and display booking details from bookings.txt
        ifstream bookingFile("bookings.txt");

        if (bookingFile) {
            string line;
            bool found = false;
            string customerID;

            // Find the booking details
            while (getline(bookingFile, line)) {
                size_t pos = line.find(',');
                if (pos != string::npos && line.substr(0, pos) == viewcustomerID) {
                    found = true;
                    cout << "\nBooking details\n";
                    cout << "----------------------------------\n";
                    cout << "Customer ID: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Customer Name: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Phone Number: 01" << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Email: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Service: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Day/Date: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Time: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    pos = line.find(',');
                    cout << "Expert: " << line.substr(0, pos) << endl;
                    line = line.substr(pos + 1);
                    cout << "Price: " << line << endl;
                    customerID = line.substr(0, pos);
                    break;
                }
            }

            if (!found) {
                cout << "Customer ID not found.\n";
            }

            bookingFile.close();
        }
        else {
            cout << "Error opening files for reading.\n";
        }
    }
    else if (choice == "M") {
        cout << "Returning to main menu..." << endl;
        returnToMainMenu = true; // Set the flag to return to the main menu
    }
    else {
        cout << "Invalid choice. Please enter S1, S2, S3, V, or M." << endl;
        displayServiceList(returnToMainMenu);
    }
}

string generateCustomerID() {
    int customerCounter = getNextCustomerID();
    return "C" + to_string(customerCounter);
}

string** allocateWeekSchedule() {
    string** weekSchedule = new string * [15];
    for (int i = 0; i < 15; ++i) weekSchedule[i] = new string[6];
    return weekSchedule;
}

void deallocateWeekSchedule(string** weekSchedule) {
    for (int i = 0; i < 15; ++i) delete[] weekSchedule[i];
    delete[] weekSchedule;
}

void loadScheduleFromFile(string** schedule, const string& filename) {
    ifstream infile(filename);
    if (!infile) { cerr << "Error opening file: " << filename << endl; return; }
    string line;
    int row = 0;
    while (getline(infile, line) && row < 15) {
        stringstream ss(line);
        for (int col = 0; col < 6; ++col) ss >> schedule[row][col];
        row++;
    }
    infile.close();
}

void saveScheduleToFile(string** schedule, const string& filename) {
    ofstream outfile(filename);
    if (!outfile) { cerr << "Error opening file: " << filename << endl; return; }
    for (int row = 0; row < 15; ++row) {
        for (int col = 0; col < 6; ++col) outfile << schedule[row][col] << (col < 5 ? " " : "");
        outfile << endl;
    }
    outfile.close();
}

void displaySlotAvailability(string*** schedules) {
    cout << "----------------------------------------------------" << endl;
    cout << "|             Slot Availability October             |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Week      | Mon   | Tue   | Wed   | Thu   | Fri   |" << endl;
    cout << "----------------------------------------------------" << endl;
    for (int week = 0; week < 5; ++week) {
        cout << "| Week " << setw(1) << (week + 1) << "    ";
        for (int day = 0; day < 5; ++day) {
            int availableSlots = 0;
            if ((week == 0 && day == 0) || (week == 4 && day == 4)) cout << "|  " << setw(5) << "-";
            else {
                for (int row = day * 3; row < (day * 3) + 3; ++row)
                    for (int col = 2; col < 6; ++col)
                        if (schedules[week][row][col] != "Booked") availableSlots++;
                cout << "| " << setw(6) << (availableSlots ? to_string(availableSlots) : "Full");
            }
        }
        cout << "|" << endl;
    }
    cout << "----------------------------------------------------" << endl;
}

void displaySchedule(string** weekSchedule, int selectedWeek) {
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|                          Treatment Schedule for Week" << selectedWeek << "                         |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "| Day/Date    Expert Name    10am-12pm      12pm-2pm      3pm-4pm       4pm-5pm |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    for (int row = 0; row < 15; ++row) {
        cout << setw(10) << weekSchedule[row][0] << "   "
            << setw(11) << weekSchedule[row][1] << "   ";
        for (int col = 2; col < 6; ++col) cout << setw(11) << weekSchedule[row][col] << "   ";
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
}

bool updateSchedule(string** weekSchedule, const string& day, const string& expert, int timeSlot) {
    for (int row = 0; row < 15; ++row) {
        if (weekSchedule[row][0] == day && weekSchedule[row][1] == expert) {
            if (weekSchedule[row][timeSlot + 2] == "Booked") {
                return false;  // Slot is already booked
            }
            weekSchedule[row][timeSlot + 2] = "Booked";
            return true;
        }
    }
    return false;  // Day or expert not found in schedule
}

pair<string, int> getServiceInfo(const string& service, char type) {
    if (service == "S1") return { type == 'T' ? "Facial Treatment" : "Facial Consultation", type == 'T' ? 500 : 150 };
    if (service == "S2") return { type == 'T' ? "Spa Treatment" : "Spa Consultation", type == 'T' ? 800 : 200 };
    if (service == "S3") return { type == 'T' ? "Makeup Treatment" : "Makeup Consultation", type == 'T' ? 300 : 100 };
    return { "Unknown Service", 0 };
}

bool isValidDayDate(const string& day, string** weekSchedule, int selectedWeek = 0) {
    if (selectedWeek == 1 && day == "Mon/30") { cout << "Expert not available on Week 1 Mon/30. Please select another day/date." << endl; return false; }
    if (selectedWeek == 5 && day == "Fri/1") { cout << "Expert not available on Week 5 Fri/1. Please select another day/date." << endl; return false; }
    for (int row = 0; row < 15; ++row) if (weekSchedule[row][0] == day) return true;
    cout << "Invalid day/date. Please select a valid day/date." << endl; return false;
}

string getValidDayDate(string** weekSchedule, int selectedWeek) {
    string day;
    do { cout << "Enter day/date (Tue/1): "; cin >> day; } while (!isValidDayDate(day, weekSchedule, selectedWeek));
    return day;
}

bool isValidTimeSlot(const string& timeInput, char type, int& timeSlot) {
    string upperTimeInput = timeInput;
    for (char& c : upperTimeInput) c = toupper(c);
    if (type == 'T' && (upperTimeInput == "10AM-12PM" || upperTimeInput == "12PM-2PM")) { timeSlot = (upperTimeInput == "10AM-12PM") ? 0 : 1; return true; }
    if (type == 'C' && (upperTimeInput == "3PM-4PM" || upperTimeInput == "4PM-5PM")) { timeSlot = (upperTimeInput == "3PM-4PM") ? 2 : 3; return true; }
    return false;
}

bool isValidExpert(const string& expert, const string experts[], int size) {
    for (int index = 0; index < size; ++index) if (experts[index] == expert) return true;
    return false;
}

bool isValidCustomerName(const string& name) {
    regex pattern("^[a-zA-Z\\s/]+$");
    return regex_match(name, pattern);
}

bool isValidPhoneNumber(const string& phoneNumber) {
    return phoneNumber.length() == 8 || phoneNumber.length() == 9;
}

bool isValidEmail(const string& email) {
    regex pattern("^[a-zA-Z0-9._%+-]{1,30}@(gmail|hotmail|yahoo)\\.com$");
    return regex_match(email, pattern);
}

bool validateMaybankCreditCard(const string& cardNumber) {
    // Check if the card number starts with '5' (Maybank cards usually start with 5)
    if (cardNumber.length() == 16 && all_of(cardNumber.begin(), cardNumber.end(), ::isdigit) && cardNumber[0] == '5') {
        return true;
    }
    cout << "Invalid Maybank credit card number. It must be 16 digits and start with '5'." << endl;
    return false;
}

void runCustomerModule() {
    bool returnToMainMenu = false;

    while (!returnToMainMenu) {
        displayServiceList(returnToMainMenu);
        if (returnToMainMenu) break;

        string choice;
        while (true) {
            cout << "\nView slot availability enter [B] \nBack to view other service enter [N]\nEnter your choice: ";
            cin >> choice;
            for (char& c : choice) c = toupper(c);
            if (choice == "B") {
                string*** schedules = new string * *[5];
                for (int weekIndex = 0; weekIndex < 5; ++weekIndex) {
                    schedules[weekIndex] = allocateWeekSchedule();
                    loadScheduleFromFile(schedules[weekIndex], "week" + to_string(weekIndex + 1) + "_schedule.txt");
                }
                displayLogo();
                displaySlotAvailability(schedules);
                int selectedWeek;
                do { cout << "Select a week (1-5): "; cin >> selectedWeek; } while (selectedWeek < 1 || selectedWeek > 5);
                clearScreen();
                displayLogo();
                displaySchedule(schedules[selectedWeek - 1], selectedWeek);
                string day, expert, service, customerName, phoneNumber, email;
                char type;
                int timeSlot;
                string experts[] = { "Alice", "Betty", "Candy" };
                int numExperts = 3;
                do { cout << "Select service (S1 for Facial, S2 for Spa, S3 for Makeup): "; cin >> service; for (char& c : service) c = toupper(c); } while (service != "S1" && service != "S2" && service != "S3");
                do { cout << "Enter T for Treatment or C for Consultation: "; cin >> type; type = toupper(type); } while (type != 'T' && type != 'C');
                day = getValidDayDate(schedules[selectedWeek - 1], selectedWeek);
                string timeInput;
                do {
                    cout << "Enter time slot (";
                    if (type == 'T') cout << "10am-12pm, 12pm-2pm";
                    else cout << "3pm-4pm, 4pm-5pm";
                    cout << "): ";
                    cin >> timeInput;
                } while (!isValidTimeSlot(timeInput, type, timeSlot));

                bool expertFound = false;
                do {
                    cout << "Select expert name (Alice, Betty, Candy): ";
                    cin >> expert;

                    if (isValidExpert(expert, experts, numExperts)) {
                        if (updateSchedule(schedules[selectedWeek - 1], day, expert, timeSlot)) {
                            expertFound = true;
                        }
                        else {
                            cout << "The selected expert is not available for this time slot. Please choose another expert." << endl;
                        }
                    }
                    else {
                        cout << "Invalid expert name. Please try again." << endl;
                    }

                    if (!expertFound) {
                        cout << "Would you like to try a different expert? (Y/N): ";
                        char retry;
                        cin >> retry;
                        retry = toupper(retry);
                        if (retry != 'Y') {
                            cout << "Booking cancelled. Returning to main menu." << endl;
                            for (int weekIndex = 0; weekIndex < 5; ++weekIndex) deallocateWeekSchedule(schedules[weekIndex]);
                            delete[] schedules;
                            return;
                        }
                    }
                } while (!expertFound);

                clearScreen();
                displayLogo();
                auto serviceInfo = getServiceInfo(service, type);
                string customerID = generateCustomerID();
                cout << "Customer details: " << endl;
                do {
                    cout << "Enter customer name: ";
                    cin.ignore();
                    getline(cin, customerName);
                    if (!isValidCustomerName(customerName)) {
                        cout << "Invalid name. Please enter a valid name (letters and spaces only)." << endl;
                    }
                } while (!isValidCustomerName(customerName));
                do {
                    cout << "Enter phone number: 01";
                    cin >> phoneNumber;
                    if (!isValidPhoneNumber(phoneNumber)) {
                        cout << "Invalid phone number. Please enter a valid phone number (8 or 9 digits)." << endl;
                    }
                } while (!isValidPhoneNumber(phoneNumber));
                do {
                    cout << "Enter email: ";
                    cin >> email;
                    if (!isValidEmail(email)) {
                        cout << "Invalid email. Please enter a valid email (must include @gmail.com / @hotmail.com / @yahoo.com)." << endl;
                    }
                } while (!isValidEmail(email));
                ofstream bookingFile("bookings.txt", ios::app);
                if (bookingFile) {
                    bookingFile << customerID << "," << customerName << "," << phoneNumber << "," << email << ","
                        << serviceInfo.first << "," << day << ",";
                    if (timeSlot == 0) bookingFile << "10am-12pm,";
                    else if (timeSlot == 1) bookingFile << "12pm-2pm,";
                    else if (timeSlot == 2) bookingFile << "3pm-4pm,";
                    else if (timeSlot == 3) bookingFile << "4pm-5pm,";
                    bookingFile << expert << "," << serviceInfo.second << endl;
                    bookingFile.close();
                }
                ofstream customerFile("customers.txt", ios::app);
                if (customerFile) {
                    customerFile << customerID << "," << customerName << "," << phoneNumber << "," << email << endl;
                    customerFile.close();
                }
                cout << "Booking Confirmation\n----------------------------------\n"
                    << "Customer ID: " << customerID << "\nCustomer Name: " << customerName
                    << "\nPhone Number: 01" << phoneNumber << "\nEmail: " << email
                    << "\nDetails of booking:\nService name: " << serviceInfo.first
                    << "\nAppointment day/date: " << day << "\nAppointment time: ";
                if (timeSlot == 0) cout << "10am-12pm" << endl;
                else if (timeSlot == 1) cout << "12pm-2pm" << endl;
                else if (timeSlot == 2) cout << "3pm-4pm" << endl;
                else if (timeSlot == 3) cout << "4pm-5pm" << endl;
                cout << "Expert name: " << expert << "\nTotal Charges RM: " << serviceInfo.second
                    << "\n----------------------------------" << endl;
                char confirm;
                do { cout << "Enter P to confirm booking or E to exit: "; cin >> confirm; confirm = toupper(confirm); } while (confirm != 'P' && confirm != 'E');
                if (confirm == 'P') {
                    // Credit card validation
                    string cardNumber;
                    bool validCard = false;
                    do {
                        cout << "\nPlease enter your Maybank credit card number for payment: ";
                        cin >> cardNumber;
                        if (validateMaybankCreditCard(cardNumber)) {
                            cout << "Credit card validated successfully.\n";
                            validCard = true;
                        }
                        else {
                            cout << "Invalid credit card number. Please try again.\n";
                        }
                    } while (!validCard);

                    cout << "Payment processed successfully!\n";
                    saveScheduleToFile(schedules[selectedWeek - 1], "week" + to_string(selectedWeek) + "_schedule.txt");
                    displaySchedule(schedules[selectedWeek - 1], selectedWeek);
                }
                else {
                    cout << "Booking cancelled." << endl;
                }
                for (int weekIndex = 0; weekIndex < 5; ++weekIndex) deallocateWeekSchedule(schedules[weekIndex]);
                delete[] schedules;
                break;
            }
            else if (choice == "N") {
                break;
            }
            else cout << "Invalid choice. Please enter B or N." << endl;
        }
    }
}

struct User {
    string username;
    string password;
};

struct Employee {
    string id;
    string name;
    string position;
    string contact;
    string bio;
};

string getCurrentDateTime() {
    time_t now = time(0);
    struct tm timeinfo;
    char buffer[80];

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif

    strftime(buffer, sizeof(buffer), "%H:%M [%d/%m/%Y]", &timeinfo);

    return string(buffer);
}

string getCurrentDate() {
    time_t now = time(0);
    struct tm timeinfo;
    char buf[80];

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif

    strftime(buf, sizeof(buf), "%d/%m/%Y", &timeinfo);
    return std::string(buf);
}

string displayMenu() {
    return "+-----------------------------+\n"
        "|  1. Login                   |\n"
        "|  2. Register                |\n"
        "|  3. Exit                    |\n"
        "+-----------------------------+\n";
}

bool isValidPassword(const string& password) {
    bool hasCapital = false;
    bool hasNumber = false;

    for (char ch : password) {
        if (isupper(ch)) {
            hasCapital = true;
        }
        if (isdigit(ch)) {
            hasNumber = true;
        }
    }

    return hasCapital && hasNumber;
}

bool registerUser(const string& username, const string& password) {
    if (!isValidPassword(password)) {
        if (!any_of(password.begin(), password.end(), ::isupper)) {
            cout << "Password must contain at least 1 capital letter!" << endl;
        }
        if (!any_of(password.begin(), password.end(), ::isdigit)) {
            cout << "Password must contain at least 1 number!" << endl;
        }
        return false;
    }

    ofstream file("credentials.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "Registration successful!" << endl;
        return true;
    }
    else {
        cout << "Unable to open file for writing." << endl;
        return false;
    }
}

bool loginUser(const string& username, const string& password) {
    ifstream file("credentials.txt");
    if (file.is_open()) {
        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword) {
            if (username == storedUsername && password == storedPassword) {
                cout << "Login successful!" << endl;
                return true;
            }
        }
        file.close();
        cout << "Invalid username or password." << endl;
        cout << "Reminder: Password requires at least 1 capital letter and 1 number." << endl;
    }
    else {
        cout << "Unable to open file for reading." << endl;
    }
    return false;
}

string displayAdminMenu() {
    return "-----------------------------------\n"
        "|          ADMIN MENU             |\n"
        "-----------------------------------\n"
        "| 1: View Schedule                |\n"
        "| 2: View Customer                |\n"
        "| 3: View Sales Report            |\n"
        "| 4: View Employees               |\n"
        "| 5: Check In                     |\n"
        "| 6: Check Out                    |\n"
        "| 7: View Attendance              |\n"
        "| 8: Logout                       |\n"
        "-----------------------------------\n";
}

string viewSchedule() {
    ifstream bookingFile("bookings.txt");
    if (!bookingFile.is_open()) {
        return "Error opening bookings.txt";
    }

    string line;
    bool isEmpty = true;
    cout << "All Bookings:\n";
    cout << "----------------------------------\n";
    while (getline(bookingFile, line)) {
        istringstream iss(line);
        string customerID, name, phone, email, service, day, time, expert, charges;

        if (getline(iss, customerID, ',') &&
            getline(iss, name, ',') &&
            getline(iss, phone, ',') &&
            getline(iss, email, ',') &&
            getline(iss, service, ',') &&
            getline(iss, day, ',') &&
            getline(iss, time, ',') &&
            getline(iss, expert, ',') &&
            getline(iss, charges)) {  // Note: removed the comma here

            cout << "Customer ID: " << customerID << "\n"
                << "Name: " << name << "\n"
                << "Service: " << service << "\n"
                << "Date: " << day << "\n"
                << "Time: " << time << "\n"
                << "Expert: " << expert << "\n"
                << "Charges: RM" << charges << "\n"
                << "----------------------------------\n";
            isEmpty = false;
        }
        else {
            cout << "Warning: Skipping malformed line in bookings file\n";
        }
    }
    bookingFile.close();

    if (isEmpty) {
        return "No bookings found.";
    }
    return "";
}

string viewCustomer() {
    ifstream customerFile("customers.txt");
    if (!customerFile.is_open()) {
        return "Error opening customers.txt";
    }

    string line;
    bool isEmpty = true;
    cout << "Customer Details:\n";
    cout << "----------------------------------\n";
    while (getline(customerFile, line)) {
        istringstream iss(line);
        string customerID, name, phone, email;
        getline(iss, customerID, ',');
        getline(iss, name, ',');
        getline(iss, phone, ',');
        getline(iss, email, ',');

        cout << "Customer ID: " << customerID << "\n"
            << "Name: " << name << "\n"
            << "Phone: 01" << phone << "\n"
            << "Email: " << email << "\n"
            << "----------------------------------\n";
        isEmpty = false;
    }
    customerFile.close();

    if (isEmpty) {
        return "No customer details found.";
    }
    return "";
}

string viewSalesReport() {
    ifstream bookingFile("bookings.txt");
    if (!bookingFile.is_open()) {
        return "Error opening bookings.txt";
    }

    int totalEarnings = 0;
    string line;

    cout << "\nSales Report:\n";
    cout << "----------------------------------\n";
    while (getline(bookingFile, line)) {
        istringstream iss(line);
        string customerID, name, phone, email, service, day, time, expert, charges;

        if (getline(iss, customerID, ',') &&
            getline(iss, name, ',') &&
            getline(iss, phone, ',') &&
            getline(iss, email, ',') &&
            getline(iss, service, ',') &&
            getline(iss, day, ',') &&
            getline(iss, time, ',') &&
            getline(iss, expert, ',') &&
            getline(iss, charges, ',')) {

            cout << "Customer: " << name << "\n"
                << "Service: " << service << "\n"
                << "Charges: RM" << charges << "\n"
                << "----------------------------------\n";

            try {
                totalEarnings += stoi(charges);
            }
            catch (const std::invalid_argument& e) {
                cout << "Warning: Invalid charge amount for " << name << ": " << charges << "\n";
            }
            catch (const std::out_of_range& e) {
                cout << "Warning: Charge amount out of range for " << name << ": " << charges << "\n";
            }
        }
        else {
            cout << "Warning: Skipping malformed line in bookings file\n";
        }
    }
    bookingFile.close();

    cout << "\nTotal Money Earned: RM " << totalEarnings << endl;
    return "";
}

string viewEmployeeDetails(const Employee& employee) {
    stringstream ss;
    ss << "--------------------------------------\n"
        << "|         EMPLOYEE DETAILS           |\n"
        << "--------------------------------------\n"
        << "| ID: " << employee.id << string(30 - employee.id.length(), ' ') << " |\n"
        << "| Name: " << employee.name << string(28 - employee.name.length(), ' ') << " |\n"
        << "| Position: " << employee.position << string(25 - employee.position.length(), ' ') << "|\n"
        << "| Contact: " << employee.contact << string(26 - employee.contact.length(), ' ') << "|\n"
        << "--------------------------------------\n"
        << "| Bio:                               |\n";

    // Wrap the bio text
    string bio = employee.bio;
    size_t lineWidth = 30;
    size_t pos = 0;
    while (pos < bio.length()) {
        size_t endPos = pos + lineWidth;
        if (endPos > bio.length()) {
            endPos = bio.length();
        }
        else {
            // Find the last space within the line width
            size_t lastSpace = bio.rfind(' ', endPos);
            if (lastSpace != string::npos && lastSpace > pos) {
                endPos = lastSpace;
            }
        }
        ss << "| " << bio.substr(pos, endPos - pos) << string(lineWidth - (endPos - pos), ' ') << "     |\n";
        pos = endPos;
        if (pos < bio.length() && bio[pos] == ' ') {
            pos++; // Skip the space at the beginning of the next line
        }
    }

    ss << "--------------------------------------\n";

    return ss.str();
}

string viewEmployees() {
    ifstream file("employees.txt");
    if (!file.is_open()) {
        return "Unable to open employees file.";
    }

    string employeeList = "Viewing Employees...\n"
        "-----------------------------------\n"
        "|         EMPLOYEE LIST           |\n"
        "-----------------------------------\n";

    Employee employee;
    int count = 0;
    while (getline(file, employee.id, ',') &&
        getline(file, employee.name, ',') &&
        getline(file, employee.position, ',') &&
        getline(file, employee.contact, ',') &&
        getline(file, employee.bio)) {
        count++;
        employeeList += "| " + to_string(count) + ". " + employee.name + string(27 - employee.name.length(), ' ') + "  |\n"
            "|    ID: " + employee.id + string(23 - employee.id.length(), ' ') + "  |\n"
            "|    Position: " + employee.position + string(19 - employee.position.length(), ' ') + "|\n"
            "-----------------------------------\n";
    }

    file.close();

    employeeList += "| " + to_string(count + 1) + ". Return to Main Menu          |\n"
        "-----------------------------------\n";

    cout << employeeList;

    int choice;
    cout << "Select an employee to view details (1-" << count << ") or return to main menu (" << count + 1 << "): ";
    cin >> choice;

    if (choice >= 1 && choice <= count) {
        file.open("employees.txt");
        for (int i = 1; i <= choice; i++) {
            getline(file, employee.id, ',');
            getline(file, employee.name, ',');
            getline(file, employee.position, ',');
            getline(file, employee.contact, ',');
            getline(file, employee.bio);
        }
        file.close();
        return viewEmployeeDetails(employee);
    }
    else if (choice == count + 1) {
        return "Returning to main menu...";
    }
    else {
        return "Invalid choice. Please select a valid option.";
    }
}

bool hasCheckedInToday(const string& id) {
    ifstream file("attendance.txt");
    string line;
    string currentDate = getCurrentDate();

    while (getline(file, line)) {
        stringstream ss(line);
        string storedId, name, position, checkInTime, checkOutTime;
        getline(ss, storedId, ',');
        getline(ss, name, ',');
        getline(ss, position, ',');
        getline(ss, checkInTime, ',');
        getline(ss, checkOutTime);

        if (storedId == id && checkInTime.find(currentDate) != string::npos && checkOutTime.empty()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

string checkIn() {
    string id;
    while (true) {
        cout << "Enter your employee ID (or 'M' to return to main menu): ";
        cin >> id;

        if (id == "M" || id == "m") {
            return "Returning to main menu...";
        }

        if (hasCheckedInToday(id)) {
            cout << "You have already checked in today and haven't checked out. Please check out first." << endl;
            continue;
        }

        ifstream employeeFile("employees.txt");
        if (!employeeFile.is_open()) {
            return "Unable to open employees file.";
        }

        Employee employee;
        bool found = false;
        while (getline(employeeFile, employee.id, ',') &&
            getline(employeeFile, employee.name, ',') &&
            getline(employeeFile, employee.position, ',') &&
            getline(employeeFile, employee.contact, ',') &&
            getline(employeeFile, employee.bio)) {
            if (employee.id == id) {
                found = true;
                break;
            }
        }
        employeeFile.close();

        if (!found) {
            cout << "Employee ID not found. Please try again or enter 'M' to return to main menu." << endl;
            continue;
        }

        string dateTime = getCurrentDateTime();

        ofstream file("attendance.txt", ios::app);
        if (file.is_open()) {
            file << employee.id << "," << employee.name << "," << employee.position << "," << dateTime << "," << endl;
            file.close();
            return "Check-in successful for " + employee.name + " at " + dateTime;
        }
        else {
            return "Unable to open file for writing.";
        }
    }
}

string checkOut() {
    string id;
    while (true) {
        cout << "Enter your employee ID (or 'M' to return to main menu): ";
        cin >> id;

        if (id == "M" || id == "m") {
            return "Returning to main menu...";
        }

        if (!hasCheckedInToday(id)) {
            cout << "You haven't checked in today. Please check in first." << endl;
            continue;
        }

        string dateTime = getCurrentDateTime();

        ifstream inFile("attendance.txt");
        ofstream outFile("temp.txt");

        if (inFile.is_open() && outFile.is_open()) {
            string line;
            bool found = false;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string storedId, name, position, checkInTime;
                getline(ss, storedId, ',');
                getline(ss, name, ',');
                getline(ss, position, ',');
                getline(ss, checkInTime, ',');

                if (storedId == id && line.back() == ',' && checkInTime.find(getCurrentDate()) != string::npos) {
                    outFile << line << dateTime << endl;
                    found = true;
                }
                else {
                    outFile << line << endl;
                }
            }
            inFile.close();
            outFile.close();

            if (found) {
                if (remove("attendance.txt") != 0) {
                    perror("Error deleting file");
                }
                if (rename("temp.txt", "attendance.txt") != 0) {
                    perror("Error renaming file");
                }
                return "Check-out successful at " + dateTime;
            }
            else {
                if (remove("temp.txt") != 0) {
                    perror("Error deleting temporary file");
                }
                cout << "No matching check-in found for today. Please try again or enter 'M' to return to main menu." << endl;
            }
        }
        else {
            return "Unable to open files.";
        }
    }
}

string viewAttendance() {
    ifstream file("attendance.txt");
    stringstream report;
    report << "Viewing Attendance...\n"
        << "------------------------------------------------------------------------------------\n"
        << "|                                  ATTENDANCE RECORD                               |\n"
        << "------------------------------------------------------------------------------------\n"
        << "| ID  | Name           | Position        | Check-in           | Check-out          |\n"
        << "------------------------------------------------------------------------------------\n";

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, position, checkIn, checkOut;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, position, ',');
            getline(ss, checkIn, ',');
            getline(ss, checkOut);

            report << "| " << setw(2) << left << id
                << " | " << setw(14) << left << name
                << " | " << setw(15) << left << position
                << " | " << setw(15) << left << checkIn
                << " | " << setw(15) << left << (checkOut.empty() ? "Not checked out" : checkOut) << " |\n";
            report << "------------------------------------------------------------------------------------\n";
        }
        file.close();
    }
    else {
        report << "Unable to open attendance file.\n";
    }

    return report.str();
}

void runStaffModule() {
    string choice;
    bool isLoggedIn = false;

    while (true) {
        if (!isLoggedIn) {
            clearScreen();
            displayLogo();
            cout << displayMenu() << endl;
            cout << "Select an option (1, 2, 3): ";
            cin >> choice;

            if (choice == "1") {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                isLoggedIn = loginUser(username, password);
            }
            else if (choice == "2") {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                registerUser(username, password);
            }
            else if (choice == "3") {
                cout << "Exiting program." << endl;
                return;
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        else {
            clearScreen();
            displayLogo();
            cout << displayAdminMenu() << endl;
            cout << "Select an option (1-8): ";
            cin >> choice;

            if (choice == "1") {
                cout << viewSchedule() << endl;
            }
            else if (choice == "2") {
                cout << viewCustomer() << endl;
            }
            else if (choice == "3") {
                cout << viewSalesReport() << endl;
            }
            else if (choice == "4") {
                cout << viewEmployees() << endl;
            }
            else if (choice == "5") {
                cout << checkIn() << endl;
            }
            else if (choice == "6") {
                cout << checkOut() << endl;
            }
            else if (choice == "7") {
                cout << viewAttendance() << endl;
            }
            else if (choice == "8") {
                cout << "Logging out..." << endl;
                isLoggedIn = false;
            }
            else {
                cout << "Invalid choice. Please select a valid option." << endl;
            }
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

int main() {
    int choice;

    auto displayMainMenu = []() {
        clearScreen();
        displayLogo();
        cout << "\nMain Menu\n";
        cout << "---------\n";
        cout << "1. About Us\n";
        cout << "2. Customer\n";
        cout << "3. Staff\n";
        cout << "4. Exit\n";
        cout << "\nEnter your choice (1-4): ";
        };

    do {
        displayMainMenu();

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4: ";
        }

        switch (choice) {
        case 1:
            displayAboutUs();
            break;
        case 2:
            runCustomerModule();
            break;
        case 3:
            runStaffModule();
            break;
        case 4:
            cout << "Thank you for using our system. Goodbye!\n";
            return 0;
        }

        cout << "\nPress Enter to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    } while (true);

    return 0;
}