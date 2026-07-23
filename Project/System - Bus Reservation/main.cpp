#include <iostream>
#include <vector> //for 2D vector
#include <string> //string handling
#include <iomanip> //for setw
#include <cctype> //for toupper
#include "Ticket.h" // Include the Ticket class header
//-------------------------------------------
#include <fstream> //file handling
#include <sstream> //for sscanf
#include <cstdlib> //for rand, srand
#include <ctime> //for time
//-------------------------------------------

using namespace std;

//variable declaration
int choice;

//Global seating arrangement
const int rows = 25;
const int cols = 3;
vector<vector<char>> seats; //2D vector seats
vector<char> COLS = {'A', 'B', 'C'}; // Seat columns

//Declare functions
void resetFile();
void mainmenu();
void choiceHandler();
void RDS();//reservation_defaultstatus
int colIndex(char col);
void countSeats(int &available, int &occupied);
void seating_arragement();
string ticketID();//ticket ID generation
void reservation();
void ticketGeneration();
void paymentProcess();
void printReceipt();
void cancelReservation();

void resetFile() {// open in write mode → clears file content
    ofstream file("reservations.txt", ios::trunc);//trunc(clear file),app(append),in(read file),out(write),ate(start at end)
    file.close();
}

void mainmenu() {//mainmenu display
    cout << "\nWelcome to the Bus Reservation System!" <<'\n';
    cout << "-------------- Main Menu --------------" << '\n';
    cout << "1. Seating Arrangement & Reservation" << '\n';
    cout << "2. Ticket Generation" << '\n';
    cout << "3. Payment Processing" << '\n';
    cout << "4. Receipt Printing" << '\n';
    cout << "5. Reservation Cancellation" << '\n';
    cout << "6. Exit" << '\n';
    cout << "---------------------------------------" << '\n';
}

void choiceHandler() {//handle user choice

    cout << "Enter your choice (1-6): ";
    cin >> choice;
    cout << '\n';

    switch (choice) {
        case 1:
            cout << "Seating Arrangement & Reservation selected." << '\n';reservation();
            break;
        case 2:
            cout << "Ticket Generation selected." << '\n';ticketGeneration();
            break;
        case 3:
            cout << "Payment Processing selected." << '\n';paymentProcess();
            break;
        case 4:
            cout << "Receipt Printing selected." << '\n';printReceipt();
            break;
        case 5:
            cout << "Reservation Cancellation selected." << '\n';cancelReservation();
            break;
        case 6:
            cout << "Exiting the system. Thank you!" << '\n';
            break;
        default:
            cout << "Invalid choice. Please select a number between 1 and 6." << '\n';
    }
}

void RDS(int rows, int cols) {//reset seating default status '75'
    seats.assign(rows, vector<char>(cols, 'O')); // assign 'O' to all seats (Vector <> Variable [help assign multiple values])
}

int colIndex(char col) {// Convert seat letter to column index                                  0 or 0+
    col = toupper(static_cast<unsigned char>(col)); // normalize to uppercase (convert char -> unsigned char -> toupper -> char)
    for (int i = 0; i < COLS.size(); i++) {
        if (COLS[i] == col) {
            return i;
        }
    }
    return -1; // Invalid column
}

void countSeats(int &available, int &occupied) {//count available & occupied seats
    available = 0;
    occupied = 0;
    for (int i = 0; i < seats.size(); i++) {
        for (int j = 0; j < seats[i].size(); j++) {
            if (seats[i][j] == 'O')
                available++;
            else
                occupied++;
        }
    }
}

void seating_arrangement() {
    cout << "\n----------- Bus Seating Layout -----------\n\n";

    int rows = seats.size();
    int cols = seats[0].size();

    // Print row numbers across the top
    cout << "    ";
    for (int i = 1; i <= rows; i++) {
        cout << setw(2) << i << " ";
    }
    cout << '\n';

    // Print each column (A, B, C) with seats
    for (int j = 0; j < COLS.size(); j++) {
        cout << " " << COLS[j] << "  ";
        for (int i = 0; i < rows; i++) {
            cout << " " << seats[i][j] << " ";
        }
        cout << '\n';
    }

    int available, occupied;
    countSeats(available, occupied);
    cout << "\nSeats available: " << available << "    Seats occupied: " << occupied << endl;
}

string generateTicketID() {
    // Load all existing IDs from file
    ifstream file("reservations.txt");
    vector<string> existingIDs;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string ticketID;
        getline(ss, ticketID, '|'); // first field is ID
        existingIDs.push_back(ticketID);
    }
    file.close();

    string id;
    bool unique = false;

    while (!unique) {
        // Generate random ID
        srand(time(0) + rand());
        id = "TC";
        for (int i = 0; i < 4; i++) id += to_string(rand() % 10);
        for (int i = 0; i < 4; i++) id += char('A' + rand() % 26);

        // Check uniqueness
        unique = true;
        for (auto &existing : existingIDs) {//auto - automatically deduce type
            if (existing == id) {
                unique = false;
                break;
            }
        }
    }
    return id;
}

void reservation() {
    string input;
    seating_arrangement();

    while (true) {
        cout << "\nEnter seat (e.g., C12) or Q to quit: ";
        cin >> input;

        if (input == "Q" || input == "q") {
            cout << "\nReturning to Main Menu...\n";
            break;
        }

        if (input.size() < 2) {//minimum 2 characters
            cout << "Invalid format! Please use like C12.\n";
            continue;
        }

        char colLetter = toupper(input[0]);//first character uppercase
        string rowPart = input.substr(1);//take from index 1 to end

        if (colLetter != 'A' && colLetter != 'B' && colLetter != 'C') {
            cout << "Invalid seat! Must start with A, B, or C.\n";
            continue;
        }

        for (char ch : rowPart) {//check all characters in rowPart are digits
            if (!isdigit(ch)) {
                cout << "Invalid seat number! Must be digits.\n";
                rowPart = "";
                break;
            }
        }
        if (rowPart == "") continue;

        int rowNumber = stoi(rowPart);//convert string to int
        if (rowNumber < 1 || rowNumber > seats.size()) {
            cout << "Invalid seat number! Must be between 1 and " << seats.size() << ".\n";
            continue;
        }

        int colIndex = (colLetter == 'A') ? 0 : (colLetter == 'B') ? 1 : 2;//switch A-C -> 1-3
        int rowIndex = rowNumber - 1;

        if (seats[rowIndex][colIndex] == 'O') {
            seats[rowIndex][colIndex] = 'X';
            string seatCode = string(1, colLetter) + rowPart;//"C"+"12"
            Ticket ticket(seatCode); // only seat, rest defaults
            cout << "\nSeat " << ticket.getSeatCode() << " booked successfully!\n";
            cout << "Generated ID: " << ticket.getTicketID() << '\n';
            ticket.saveToFile(); // saves with placeholders
            break;
        } else {
            cout << "Seat " << colLetter << rowNumber << " is already occupied!\n";
        }
    }
}

void ticketGeneration() {
    string id;
    cout << "Enter your Ticket ID: ";
    cin >> id;

    ifstream file("reservations.txt");// read file
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        // Split line by '|'
        stringstream ss(line);
        string ticketID, seatCode, status, name, type, date, time, price;
        getline(ss, ticketID, '|');
        getline(ss, seatCode, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, price, '|');

        if (ticketID == id) { // EXACT match required
            found = true;
            cout << "\nTicket found. Please enter details:\n";

            cout << "Passenger Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Passenger Type (Adult/Child/Senior/Infant): ";
            cin >> type;
            cout << "Schedule Date (DD/MM/YYYY): ";
            cin >> date;
            cout << "Schedule Time (HH:MM): ";
            cin >> time;

            double newPrice = 50.0; // default
            if (type == "Adult") newPrice = 50.0;
            else if (type == "Child") newPrice = 25.0;
            else if (type == "Senior") newPrice = 40.0;
            else if (type == "Infant") newPrice = 15.0;
            stringstream price;
            price << fixed << setprecision(2) << newPrice;//format price to 2 decimal places
            string priceText = price.str();

            // Build updated line
            line = ticketID + "|" + seatCode + "|Reserved|" + name + "|" + type + "|" + date + "|" + time + "|" + priceText;
        }
        lines.push_back(line);//store all lines
    }
    file.close();

    if (!found) {
        cout << "Error: Ticket ID not found. You must enter the exact ID.\n";
        return;
    }

    // Rewrite file with updated info
    ofstream out("reservations.txt", ios::trunc);
    for (auto &l : lines) out << l << "\n";
    out.close();

    cout << "Ticket updated successfully!\n";
}

void paymentProcess() {
    string id;
    cout << "Enter your Ticket ID for payment: ";
    cin >> id;

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open reservations file.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string ticketID, seatCode, status, name, type, date, time, price;

        getline(ss, ticketID, '|');
        getline(ss, seatCode, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, price, '|');

        if (ticketID == id) { // exact match required
            found = true;

            cout << "\n===== Payment Processing =====\n";
            cout << "Ticket ID   : " << ticketID << endl;
            cout << "Passenger   : " << name << " (" << type << ")\n";
            cout << "Seat        : " << seatCode << endl;
            cout << "Schedule    : " << date << " " << time << endl;
            cout << "Price       : RM" << price << endl;
            cout << "Status      : " << status << endl;

            if (status == "Paid") {
                cout << "This ticket has already been paid.\n";
            } else if (status == "Reserved") {
                char confirm;
                cout << "Confirm payment? (Y/N): ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    status = "Paid";
                    cout << "Payment successful! Ticket marked as Paid.\n";
                } else{
                    cout << "Payment cancelled.\n";
                }
            } else {
                cout << "Ticket status not valid for payment.\n";
            }

            // Update line with new status
            line = ticketID + "|" + seatCode + "|" + status + "|" + name + "|" + type + "|" + date + "|" + time + "|" + price;
        }
        lines.push_back(line);
    }
    file.close();

    if (!found) {
        cout << "Error: Ticket ID not found. You must enter the exact ID.\n";
        return;
    }

    // Rewrite file with updated info
    ofstream out("reservations.txt", ios::trunc);
    for (auto &l : lines) out << l << "\n";
    out.close();
}

void printReceipt() {
    string id;
    cout << "Enter your Ticket ID to print receipt: ";
    cin >> id;

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open reservations file.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string ticketID, seatCode, status, name, type, date, time, price;

        getline(ss, ticketID, '|');
        getline(ss, seatCode, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, price, '|');

        if (ticketID == id) { // exact match required
            found = true;

            if (status != "Paid") {
                cout << "Error: Ticket is not paid yet. Please complete payment before printing receipt.\n";
                break;
            }

            cout << "\n=========== Receipt ===========\n";
            cout << "Ticket ID   : " << ticketID << endl;
            cout << "Passenger   : " << name << " (" << type << ")\n";
            cout << "Seat        : " << seatCode << endl;
            cout << "Schedule    : " << date << " " << time << endl;
            cout << "Price       : RM" << price << endl;
            cout << "Status      : " << status << endl;
            cout << "=================================\n";
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Error: Ticket ID not found. You must enter the exact ID.\n";
    }
}

void cancelReservation() {
    string id;
    cout << "Enter your Ticket ID to cancel reservation: ";
    cin >> id;

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open reservations file.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string ticketID, seatCode, status, name, type, date, time, price;

        getline(ss, ticketID, '|');
        getline(ss, seatCode, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, price, '|');

        if (ticketID == id) { // exact match required
            found = true;

            cout << "\n===== Cancellation =====\n";
            cout << "Ticket ID   : " << ticketID << endl;
            cout << "Passenger   : " << name << " (" << type << ")\n";
            cout << "Seat        : " << seatCode << endl;
            cout << "Schedule    : " << date << " " << time << endl;
            cout << "Price       : RM" << price << endl;
            cout << "Status      : " << status << endl;

            if (status == "Cancelled") {
                cout << "This reservation has already been cancelled.\n";
            } else if (status == "Pending") {
                cout << "This ticket is still pending and cannot be cancelled.\n";
            } else if (status == "Reserved" || status == "Paid") {
                char confirm;
                cout << "Confirm cancellation? (Y/N): ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    status = "Cancelled";
                    cout << "Reservation cancelled successfully!\n";

                    // Free the seat in seating layout
                    char colLetter = seatCode[0];
                    int rowNumber = stoi(seatCode.substr(1));
                    int colIndex = (colLetter == 'A') ? 0 : (colLetter == 'B') ? 1 : 2;
                    int rowIndex = rowNumber - 1;
                    seats[rowIndex][colIndex] = 'O';
                } else {
                    cout << "Cancellation aborted.\n";
                }
            } else {
                cout << "Invalid ticket status for cancellation.\n";
            }

            // Update line with new status
            line = ticketID + "|" + seatCode + "|" + status + "|" + name + "|" + type + "|" + date + "|" + time + "|" + price;
        }
        lines.push_back(line);
    }
    file.close();

    if (!found) {
        cout << "Error: Ticket ID not found. You must enter the exact ID.\n";
        return;
    }

    // Rewrite file with updated info
    ofstream out("reservations.txt", ios::trunc);
    for (auto &l : lines) out << l << "\n";
    out.close();
}

int main() {

    resetFile();//clear previous ticket file
    RDS(rows, cols);//map set default all 'O'

    do{
    mainmenu();
    choiceHandler();
    }while (choice != 6);//exit when choice = 6

    return 0;
}