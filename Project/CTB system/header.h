#ifndef CINEMA_BOOKING_H
#define CINEMA_BOOKING_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

// ==================== CONSTANTS ====================
const int movieCount = 6;
const int seatRows = 60;
const int seatColumns = 60;
const int maxSeatsPerMovie = seatRows * seatColumns;
const int maxSeats = maxSeatsPerMovie;
const int maxQueue = maxSeats + 1;

const string movieOptions[movieCount] = {
    "End Games",
    "The Dog Stars",
    "The Odyssey",
    "Insidious: Out of the Further",
    "Spider-Man: Brand New Day",
    "Doomsday"
};

// ==================== PRICING (MYR) ====================
const double PRICE_INFANT  = 0.00;   // Infant (0-2 years)
const double PRICE_CHILD   = 12.00;  // Child (3-12 years)
const double PRICE_STUDENT = 15.00;  // Student (with valid ID)
const double PRICE_ADULT   = 20.00;  // Adult (13-59 years)
const double PRICE_OKU     = 10.00;  // OKU / Senior Citizen

const string AGE_CATEGORIES[5] = {
    "Infant (0-2 years)",
    "Child (3-12 years)",
    "Student (with valid ID)",
    "Adult (13-59 years)",
    "OKU / Senior Citizen"
};

// ==================== FILE NAMES ====================
const string BOOKINGS_FILE      = "bookings.txt";
const string CANCELLATIONS_FILE = "cancellations.txt";
const string ALL_RECORDS_FILE   = "all_records.txt";
const string TRANSACTION_LOG    = "transaction_log.txt";

// ==================== STRUCT ====================
struct customer
{
    string customerID;
    string customerName;
    string movieName;
    string seatNumber;
    string ageCategory;
    double ticketPrice;
};

// ==================== GLOBAL VARIABLES ====================
inline customer theaterSeats[maxSeats];
inline int movieOccupancy[movieCount] = {0, 0, 0, 0, 0, 0};
inline int seatCount = 0;

// ==================== FORWARD DECLARATIONS ====================
class Queue;
class CancellationStack;

// ==================== FUNCTION PROTOTYPES ====================
string getNonEmptyInput(const string& prompt);
int getMovieIndex(const string& movieName);
string chooseMovieOption();
bool IDexists(const string& id);
bool seatExists(const string& seatNumber);
bool seatExistsForMovie(const string& movieName, const string& seatNumber);
bool validSeat(const string& seatNumber);
string generateCustomerID();
void displayBooking(const customer& c);
void displaySeatLayout(const string& movieName = movieOptions[0]);
void displaySeatLayoutMulti(const string& movieName, const vector<string>& selectedSeats = {});
void cancelBooking(CancellationStack& stack);
void undoCancellation(CancellationStack& stack);
int linearSearch(const string& id, int& comparisons);
void sortByID();
int binarySearch(const string& id, int& comparisons);
void displayAllBookings();
void searchMenu();
string chooseAgeCategory();
double getPriceForCategory(const string& category);
void displayPriceList();
void mainMenu(Queue& queue, CancellationStack& stack);

// File handling prototypes
string getCurrentDateTime();
void logTransaction(const string& action, const customer& c);
void saveBookingsToFile();
void loadBookingsFromFile();
void saveCancellationsToFile(CancellationStack& stack);
void saveAllRecordsToFile(CancellationStack& stack);
void fileManagementMenu(CancellationStack& stack);

// ==================== QUEUE CLASS ====================
class Queue
{
private:
    customer customers[maxQueue];
    int front;
    int rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    { return (front == -1 && rear == -1); }

    bool isFull()
    { return (rear + 1) % maxQueue == front; }

    void enqueue(customer c)
    {
        if (isFull())
        { cout << "\nQueue is full. Cannot add more customers.\n"; return; }

        if (isEmpty())
        { front = rear = 0; }
        else
        { rear = (rear + 1) % maxQueue; }

        customers[rear] = c;
        cout << "\nCustomer added to the queue successfully.\n";
    }

    void dequeue()
    {
        if (isEmpty())
        { cout << "\nQueue is empty. No customers to serve.\n"; return; }

        cout << "\n\n------------ SERVING CUSTOMER ------------\n";
        cout << "Customer ID: "   << customers[front].customerID   << endl;
        cout << "Customer Name: " << customers[front].customerName << endl;
        cout << "Movie Name: "    << customers[front].movieName    << endl;
        cout << "Seat Number: "   << customers[front].seatNumber   << endl;
        cout << "Age Category: "  << customers[front].ageCategory  << endl;
        cout << "Price: MYR " << fixed << setprecision(2)
             << customers[front].ticketPrice << endl;

        if (front == rear)
        { front = rear = -1; }
        else
        { front = (front + 1) % maxQueue; }

        cout << "Customer has been served.\n";
    }

    void displayQueue()
    {
        if (isEmpty())
        { cout << "\nQueue is empty. No customers to display.\n"; return; }

        cout << "\n\n------------ CUSTOMERS IN QUEUE ------------\n";

        int i = front;
        int count = 1;

        while (true)
        {
            cout << "\nCustomer " << count << endl;
            cout << "Customer ID: "   << customers[i].customerID   << endl;
            cout << "Customer Name: " << customers[i].customerName << endl;
            cout << "Movie Name: "    << customers[i].movieName    << endl;
            cout << "Seat Number: "   << customers[i].seatNumber   << endl;
            cout << "Age Category: "  << customers[i].ageCategory  << endl;
            cout << "Price: MYR " << fixed << setprecision(2)
                 << customers[i].ticketPrice << endl;

            if (i == rear) { break; }
            i = (i + 1) % maxQueue;
            count++;
        }
        cout << "-----------------------------------------------\n";
    }

    void displayFront()
    {
        if (isEmpty())
        { cout << "\nQueue is empty.\n"; return; }

        cout << "\n\n---------- FRONT CUSTOMER ----------\n";
        displayBooking(customers[front]);
        cout << "--------------------------------------\n";
    }

    void displayRear()
    {
        if (isEmpty())
        { cout << "\nQueue is empty.\n"; return; }

        cout << "\n\n---------- REAR CUSTOMER ----------\n";
        displayBooking(customers[rear]);
        cout << "-------------------------------------\n";
    }

    // ============ ENHANCED QUEUE MENU ============
    void queueMenu()
    {
        int choice;
        do
        {
            cout << "\n\n--------------- QUEUE MENU -------------\n";
            cout << "1. Add Customer(s) to Queue (Buy Tickets)\n";
            cout << "2. Serve Customer from Queue\n";
            cout << "3. Display All Customers in Queue\n";
            cout << "4. Display Customer at Front\n";
            cout << "5. Display Customer at Rear\n";
            cout << "6. Check Queue Status\n";
            cout << "7. Display Price List\n";
            cout << "0. Back to Main Menu\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
                case 1:
                {
                    if (seatCount >= maxSeats)
                    {
                        cout << "\nTheater is full. No more bookings available.\n";
                        break;
                    }

                    // -------- ASK HOW MANY TICKETS --------
                    int numTickets = 0;
                    while (true)
                    {
                        cout << "\nHow many tickets would you like to buy? (1-10): ";
                        string input;
                        getline(cin, input);
                        try
                        {
                            numTickets = stoi(input);
                            if (numTickets >= 1 && numTickets <= 10)
                                break;
                            cout << "Please enter a number between 1 and 10.\n";
                        }
                        catch (...)
                        {
                            cout << "Invalid input. Please enter a number.\n";
                        }
                    }

                    // -------- SELECT MOVIE --------
                    string selectedMovie = chooseMovieOption();
                    int movieIndex = getMovieIndex(selectedMovie);

                    if (movieOccupancy[movieIndex] + numTickets > maxSeatsPerMovie)
                    {
                        cout << "\nNot enough seats available for " << selectedMovie
                             << ". Only " << (maxSeatsPerMovie - movieOccupancy[movieIndex])
                             << " seats left.\n";
                        break;
                    }

                    // -------- COLLECT BOOKING DETAILS --------
                    vector<customer> newBookings;
                    vector<string> chosenSeats;
                    double totalCost = 0.0;

                    displaySeatLayoutMulti(selectedMovie);

                    for (int t = 1; t <= numTickets; t++)
                    {
                        cout << "\n========== TICKET " << t << " of " << numTickets << " ==========\n";

                        customer c;
                        c.customerID = generateCustomerID();
                        cout << "Generated Customer ID: " << c.customerID << endl;

                        c.customerName = getNonEmptyInput("Enter Customer Name: ");
                        c.movieName = selectedMovie;

                        c.ageCategory = chooseAgeCategory();
                        c.ticketPrice = getPriceForCategory(c.ageCategory);

                        displaySeatLayoutMulti(selectedMovie, chosenSeats);

                        do
                        {
                            c.seatNumber = getNonEmptyInput("Enter Seat Number: ");

                            for (char& ch : c.seatNumber)
                            { ch = toupper(ch); }

                            if (!validSeat(c.seatNumber))
                            {
                                cout << "\nInvalid seat number. Please enter a valid seat number.\n";
                                continue;
                            }

                            if (seatExistsForMovie(selectedMovie, c.seatNumber))
                            {
                                cout << "\nSeat number already occupied for this movie.\n";
                                cout << "Please enter a different seat number.\n";
                                continue;
                            }

                            bool duplicateInBatch = false;
                            for (const string& s : chosenSeats)
                            {
                                if (s == c.seatNumber)
                                { duplicateInBatch = true; break; }
                            }
                            if (duplicateInBatch)
                            {
                                cout << "\nSeat already selected in this booking. Choose another.\n";
                                continue;
                            }

                            break;
                        }
                        while (true);

                        chosenSeats.push_back(c.seatNumber);
                        newBookings.push_back(c);
                        totalCost += c.ticketPrice;

                        cout << "\nTicket " << t << " added:\n";
                        displayBooking(c);
                    }

                    // -------- BOOKING SUMMARY --------
                    cout << "\n\n========== BOOKING SUMMARY ==========\n";
                    cout << "Movie: " << selectedMovie << endl;
                    cout << "Number of Tickets: " << numTickets << endl;
                    cout << "------------------------------------\n";
                    for (int i = 0; i < (int)newBookings.size(); i++)
                    {
                        cout << "Ticket " << i + 1 << ":\n";
                        cout << "  Name: " << newBookings[i].customerName << endl;
                        cout << "  Seat: " << newBookings[i].seatNumber << endl;
                        cout << "  Category: " << newBookings[i].ageCategory << endl;
                        cout << "  Price: MYR " << fixed << setprecision(2)
                             << newBookings[i].ticketPrice << endl;
                    }
                    cout << "------------------------------------\n";
                    cout << "TOTAL COST: MYR " << fixed << setprecision(2) << totalCost << endl;
                    cout << "====================================\n";

                    cout << "\nConfirm booking? (Y/N): ";
                    string confirm;
                    getline(cin, confirm);
                    if (confirm != "Y" && confirm != "y")
                    {
                        cout << "\nBooking cancelled. No tickets were purchased.\n";
                        break;
                    }

                    // -------- COMMIT --------
                    for (customer& c : newBookings)
                    {
                        theaterSeats[seatCount] = c;
                        seatCount++;
                        movieOccupancy[movieIndex]++;
                        enqueue(c);
                        logTransaction("BOOKED", c);
                    }

                    cout << "\nAll " << numTickets << " booking(s) successfully added!\n";
                    break;
                }
                case 2: dequeue(); break;
                case 3: displayQueue(); break;
                case 4: displayFront(); break;
                case 5: displayRear(); break;
                case 6:
                    cout << "\n\n";
                    if (isEmpty())
                    { cout << "\nThe queue is EMPTY.\n"; }
                    else if (isFull())
                    { cout << "\nThe queue is FULL.\n"; }
                    else
                    { cout << "\nThe queue is neither empty nor full.\n"; }
                    break;
                case 7:
                    displayPriceList();
                    break;
                case 0:
                    cout << "\nReturning to main menu...\n"; break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);
    }
};

// ==================== STACK NODE ====================
struct StackNode
{
    customer data;
    StackNode* next;
};

// ==================== CANCELLATION STACK ====================
class CancellationStack
{
private:
    StackNode* top;

public:
    CancellationStack()
    { top = nullptr; }

    ~CancellationStack()
    {
        while (top != nullptr)
        {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty()
    { return top == nullptr; }

    // NEW: read-only accessor for file saving
    StackNode* getTop() const { return top; }

    void push(customer c)
    {
        StackNode* newNode = new StackNode();
        newNode->data = c;
        newNode->next = top;
        top = newNode;
        cout << "\nCustomer added to cancellation stack.\n";
    }

    customer pop()
    {
        if (isEmpty())
        { cout << "\nStack is empty.\n"; return customer(); }

        StackNode* temp = top;
        customer c = top->data;
        top = top->next;
        delete temp;
        return c;
    }

    void peek()
    {
        if (isEmpty())
        { cout << "\nStack is empty. No cancellation to display.\n"; return; }

        cout << "\n\n--------- LATEST CANCELLATION -------\n";
        displayBooking(top->data);
        cout << "----------------------------------------\n";
    }

    customer peekData()
    {
        if (isEmpty())
        { cout << "\nStack is empty. No cancellation to display.\n"; return customer(); }
        return top->data;
    }

    void displayStack()
    {
        if (isEmpty())
        { cout << "\nStack is empty. No cancellation history.\n"; return; }

        cout << "\n\n------------ CANCELLATION HISTORY -----------\n";

        StackNode* current = top;
        int count = 1;

        while (current != nullptr)
        {
            cout << "\nCancellation " << count << endl;
            displayBooking(current->data);
            current = current->next;
            count++;
        }
        cout << "----------------------------------------\n";
    }

    void stackMenu()
    {
        int choice;
        do
        {
            cout << "\n\n---------- CANCELLATION STACK ----------\n";
            cout << "1. Cancel Ticket (with options)\n";
            cout << "2. Undo Latest Cancellation\n";
            cout << "3. Display Cancellation History\n";
            cout << "4. Peek Latest Cancellation\n";
            cout << "0. Back to Main Menu\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
                case 1: cancelBooking(*this); break;
                case 2: undoCancellation(*this); break;
                case 3: displayStack(); break;
                case 4: peek(); break;
                case 0:
                    cout << "\nReturning to main menu...\n"; break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);
    }
};

// ==================== HELPER FUNCTIONS ====================

inline string getNonEmptyInput(const string& prompt)
{
    string input;
    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        { cout << "Input cannot be empty. Please try again.\n"; }
    }
    while (input.empty());
    return input;
}

inline bool IDexists(const string& id)
{
    for (int i = 0; i < seatCount; i++)
    {
        if (theaterSeats[i].customerID == id)
        { return true; }
    }
    return false;
}

inline bool seatExists(const string& seatNumber)
{
    for (int i = 0; i < seatCount; i++)
    {
        if (theaterSeats[i].seatNumber == seatNumber)
        { return true; }
    }
    return false;
}

inline bool validSeat(const string& seatNumber)
{
    size_t separator = seatNumber.find('-');
    if (separator == string::npos || separator == 0 || separator == seatNumber.length() - 1)
    { return false; }

    if (seatNumber.find('-', separator + 1) != string::npos)
    { return false; }

    string rowStr = seatNumber.substr(0, separator);
    string columnStr = seatNumber.substr(separator + 1);

    if (!all_of(rowStr.begin(), rowStr.end(), [](unsigned char ch) { return isdigit(ch); }) ||
        !all_of(columnStr.begin(), columnStr.end(), [](unsigned char ch) { return isdigit(ch); }))
    { return false; }

    int row;
    int column;
    try
    {
        row = stoi(rowStr);
        column = stoi(columnStr);
    }
    catch (...)
    { return false; }

    if (row < 1 || row > seatRows || column < 1 || column > seatColumns)
    { return false; }

    if (seatNumber != to_string(row) + "-" + to_string(column))
    { return false; }

    return true;
}

inline int getMovieIndex(const string& movieName)
{
    for (int i = 0; i < movieCount; i++)
    {
        if (movieOptions[i] == movieName)
        { return i; }
    }
    return 0;
}

inline string chooseMovieOption()
{
    cout << "\nAvailable Movies (default: End Games):\n";
    for (int i = 0; i < movieCount; i++)
    {
        cout << i + 1 << ". " << movieOptions[i] << "\n";
    }

    cout << "Select movie [1-6] or press Enter for default: ";
    string input;
    getline(cin, input);

    if (input.empty())
    { return movieOptions[0]; }

    try
    {
        int choice = stoi(input);
        if (choice >= 1 && choice <= movieCount)
        { return movieOptions[choice - 1]; }
    }
    catch (...) {}

    cout << "Invalid movie choice. Defaulting to End Games.\n";
    return movieOptions[0];
}

inline bool seatExistsForMovie(const string& movieName, const string& seatNumber)
{
    for (int i = 0; i < seatCount; i++)
    {
        if (theaterSeats[i].movieName == movieName && theaterSeats[i].seatNumber == seatNumber)
        { return true; }
    }
    return false;
}

inline string generateCustomerID()
{
    static int nextID = 1;
    string id = "C";
    if (nextID < 10)
    { id += "000"; }
    else if (nextID < 100)
    { id += "00"; }
    else if (nextID < 1000)
    { id += "0"; }
    id += to_string(nextID);
    nextID++;
    return id;
}

inline void displaySeatLayout(const string& movieName)
{
    cout << "\n\n";
    cout << "----------------- Cinema Seat Layout -----------------\n";
    cout << "Movie: " << movieName << "\n\n";

    cout << setw(3) << " ";
    for (int column = 1; column <= seatColumns; ++column)
    { cout << setw(3) << column; }
    cout << endl;

    for (int row = 1; row <= seatRows; ++row)
    {
        cout << setw(3) << row;
        for (int column = 1; column <= seatColumns; ++column)
        {
            string seat = to_string(row) + "-" + to_string(column);
            cout << setw(3) << (seatExistsForMovie(movieName, seat) ? 'X' : 'O');
        }
        cout << endl;
    }

    cout << "\n";
    cout << "O = Available, X = Booked\n";
    cout << "Enter seats as row-column, for example: 1-1 or 60-60\n\n";
}

inline void displaySeatLayoutMulti(const string& movieName, const vector<string>& selectedSeats)
{
    cout << "\n\n";
    cout << "----------------- Cinema Seat Layout -----------------\n";
    cout << "Movie: " << movieName << "\n";
    if (!selectedSeats.empty())
    {
        cout << "Selected seats this booking: ";
        for (size_t i = 0; i < selectedSeats.size(); i++)
        {
            cout << selectedSeats[i];
            if (i + 1 < selectedSeats.size()) cout << ", ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << setw(3) << " ";
    for (int column = 1; column <= seatColumns; ++column)
    { cout << setw(3) << column; }
    cout << endl;

    for (int row = 1; row <= seatRows; ++row)
    {
        cout << setw(3) << row;
        for (int column = 1; column <= seatColumns; ++column)
        {
            string seat = to_string(row) + "-" + to_string(column);
            char symbol;
            if (seatExistsForMovie(movieName, seat))
                symbol = 'X';
            else
            {
                bool isSelected = false;
                for (const string& s : selectedSeats)
                {
                    if (s == seat) { isSelected = true; break; }
                }
                symbol = isSelected ? 'S' : 'O';
            }
            cout << setw(3) << symbol;
        }
        cout << endl;
    }

    cout << "\n";
    cout << "O = Available, X = Booked, S = Selected this booking\n";
    cout << "Enter seats as row-column, for example: 1-1 or 60-60\n\n";
}

inline void displayBooking(const customer& c)
{
    cout << "Customer ID: "   << c.customerID   << endl;
    cout << "Customer Name: " << c.customerName << endl;
    cout << "Movie Name: "    << c.movieName    << endl;
    cout << "Seat Number: "   << c.seatNumber   << endl;
    cout << "Age Category: "  << c.ageCategory  << endl;
    cout << "Price: MYR " << fixed << setprecision(2) << c.ticketPrice << endl;
}

inline void displayAllBookings()
{
    if (seatCount == 0)
    { cout << "\nNo bookings available.\n"; return; }

    cout << "\n\n---------- ALL BOOKINGS -----------\n";

    for (int i = 0; i < seatCount; i++)
    {
        cout << "\nBooking " << i + 1 << endl;
        displayBooking(theaterSeats[i]);
        cout << "----------------------------------\n";
    }
}

// ==================== PRICE / AGE HELPERS ====================

inline void displayPriceList()
{
    cout << "\n\n============ TICKET PRICE LIST (MYR) ============\n";
    cout << left << setw(35) << "Category" << setw(15) << "Price (MYR)" << endl;
    cout << "--------------------------------------------------\n";
    cout << left << setw(35) << "Infant (0-2 years)"      << setw(15) << fixed << setprecision(2) << PRICE_INFANT  << endl;
    cout << left << setw(35) << "Child (3-12 years)"      << setw(15) << PRICE_CHILD   << endl;
    cout << left << setw(35) << "Student (with valid ID)" << setw(15) << PRICE_STUDENT << endl;
    cout << left << setw(35) << "Adult (13-59 years)"     << setw(15) << PRICE_ADULT   << endl;
    cout << left << setw(35) << "OKU / Senior Citizen"    << setw(15) << PRICE_OKU     << endl;
    cout << "--------------------------------------------------\n";
    cout << "Note: Infants (0-2 years) enter free but still\n";
    cout << "require a seat reservation.\n";
    cout << "==================================================\n";
}

inline double getPriceForCategory(const string& category)
{
    if (category == AGE_CATEGORIES[0]) return PRICE_INFANT;
    if (category == AGE_CATEGORIES[1]) return PRICE_CHILD;
    if (category == AGE_CATEGORIES[2]) return PRICE_STUDENT;
    if (category == AGE_CATEGORIES[3]) return PRICE_ADULT;
    if (category == AGE_CATEGORIES[4]) return PRICE_OKU;
    return PRICE_ADULT;
}

inline string chooseAgeCategory()
{
    cout << "\n--- Select Age Category ---\n";
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". " << AGE_CATEGORIES[i]
             << "  (MYR " << fixed << setprecision(2)
             << getPriceForCategory(AGE_CATEGORIES[i]) << ")\n";
    }
    cout << "Enter choice [1-5]: ";

    string input;
    getline(cin, input);

    try
    {
        int choice = stoi(input);
        if (choice >= 1 && choice <= 5)
        { return AGE_CATEGORIES[choice - 1]; }
    }
    catch (...) {}

    cout << "Invalid choice. Defaulting to Adult.\n";
    return AGE_CATEGORIES[3];
}

// ==================== CANCEL / UNDO ====================

inline void cancelBooking(CancellationStack& stack)
{
    if (seatCount == 0)
    { cout << "\nNo bookings to cancel.\n"; return; }

    string id;
    cout << "\n\n---------- CANCEL BOOKING ----------\n";
    cout << "Enter Customer ID to cancel: ";
    getline(cin, id);

    for (char& ch : id) ch = toupper(ch);

    int index = -1;

    for (int i = 0; i < seatCount; i++)
    { if (theaterSeats[i].customerID == id) { index = i; break; } }

    if (index == -1)
    { cout << "\nCustomer ID not found.\n"; return; }

    cout << "\nBooking found:\n";
    displayBooking(theaterSeats[index]);

    // -------- CANCELLATION OPTIONS --------
    cout << "\n--- Cancellation Options ---\n";
    cout << "1. Confirm Cancel (remove booking completely)\n";
    cout << "2. Change Movie (keep customer, reselect movie + seat)\n";
    cout << "3. Change Seat  (keep same movie, reselect seat)\n";
    cout << "4. Change Both Movie and Seat\n";
    cout << "0. Abort (do nothing)\n";
    cout << "Enter choice: ";

    string optInput;
    getline(cin, optInput);
    int opt = -1;
    try { opt = stoi(optInput); } catch (...) { opt = -1; }

    if (opt == 0 || opt < 0 || opt > 4)
    {
        cout << "\nCancellation aborted. No changes made.\n";
        return;
    }

    // -------- OPTION 1: CONFIRM CANCEL --------
    if (opt == 1)
    {
        stack.push(theaterSeats[index]);
        logTransaction("CANCELLED", theaterSeats[index]);
        cout << "\nBooking Cancelled:\n";
        displayBooking(theaterSeats[index]);

        int movieIndex = getMovieIndex(theaterSeats[index].movieName);
        movieOccupancy[movieIndex]--;

        for (int i = index; i < seatCount - 1; i++)
        { theaterSeats[i] = theaterSeats[i + 1]; }

        seatCount--;
        cout << "\nBooking successfully cancelled.\n";
        return;
    }

    customer original = theaterSeats[index];
    string newMovie = original.movieName;
    string newSeat  = original.seatNumber;

    // -------- Choose new movie if needed --------
    if (opt == 2 || opt == 4)
    {
        cout << "\nCurrent movie: " << original.movieName << endl;
        newMovie = chooseMovieOption();
        int newMovieIdx = getMovieIndex(newMovie);

        if (newMovie != original.movieName)
        {
            if (movieOccupancy[newMovieIdx] >= maxSeatsPerMovie)
            {
                cout << "\n" << newMovie << " is full. Cannot change to this movie.\n";
                return;
            }
        }
        cout << "\nNew movie selected: " << newMovie << endl;
    }

    // -------- Choose new seat if needed --------
    if (opt == 3 || opt == 4)
    {
        for (int i = index; i < seatCount - 1; i++)
        { theaterSeats[i] = theaterSeats[i + 1]; }
        seatCount--;
        movieOccupancy[getMovieIndex(original.movieName)]--;

        displaySeatLayout(newMovie);

        string chosenSeat;
        bool seatOk = false;
        while (!seatOk)
        {
            cout << "Enter new Seat Number (or 0 to abort): ";
            getline(cin, chosenSeat);
            if (chosenSeat == "0")
            {
                theaterSeats[seatCount] = original;
                seatCount++;
                movieOccupancy[getMovieIndex(original.movieName)]++;
                cout << "\nChange aborted. Original booking restored.\n";
                return;
            }
            for (char& ch : chosenSeat) ch = toupper(ch);

            if (!validSeat(chosenSeat))
            { cout << "Invalid seat number. Try again.\n"; continue; }
            if (seatExistsForMovie(newMovie, chosenSeat))
            { cout << "Seat already occupied for " << newMovie << ". Try again.\n"; continue; }

            seatOk = true;
            newSeat = chosenSeat;
        }

        original.movieName = newMovie;
        original.seatNumber = newSeat;
        theaterSeats[seatCount] = original;
        seatCount++;
        movieOccupancy[getMovieIndex(newMovie)]++;
        logTransaction("MODIFIED", original);

        cout << "\n\nBooking updated successfully!\n";
        displayBooking(original);
        return;
    }

    // -------- OPTION 2 ONLY (change movie, keep seat) --------
    if (opt == 2)
    {
        for (int i = index; i < seatCount - 1; i++)
        { theaterSeats[i] = theaterSeats[i + 1]; }
        seatCount--;
        movieOccupancy[getMovieIndex(original.movieName)]--;

        if (seatExistsForMovie(newMovie, original.seatNumber))
        {
            cout << "\nSeat " << original.seatNumber << " is already taken for "
                 << newMovie << ".\n";
            cout << "Would you like to choose a different seat? (Y/N): ";
            string ans;
            getline(cin, ans);
            if (ans == "Y" || ans == "y")
            {
                displaySeatLayout(newMovie);
                string chosenSeat;
                bool seatOk = false;
                while (!seatOk)
                {
                    cout << "Enter new Seat Number: ";
                    getline(cin, chosenSeat);
                    for (char& ch : chosenSeat) ch = toupper(ch);
                    if (!validSeat(chosenSeat))
                    { cout << "Invalid seat number. Try again.\n"; continue; }
                    if (seatExistsForMovie(newMovie, chosenSeat))
                    { cout << "Seat occupied. Try again.\n"; continue; }
                    seatOk = true;
                    newSeat = chosenSeat;
                }
            }
            else
            {
                theaterSeats[seatCount] = original;
                seatCount++;
                movieOccupancy[getMovieIndex(original.movieName)]++;
                cout << "\nChange aborted. Original booking restored.\n";
                return;
            }
        }

        original.movieName = newMovie;
        original.seatNumber = newSeat;
        theaterSeats[seatCount] = original;
        seatCount++;
        movieOccupancy[getMovieIndex(newMovie)]++;
        logTransaction("MODIFIED", original);

        cout << "\n\nBooking updated successfully!\n";
        displayBooking(original);
        return;
    }
}

inline void undoCancellation(CancellationStack& stack)
{
    if (stack.isEmpty())
    { cout << "\nNo cancellations to undo.\n"; return; }

    customer c = stack.peekData();
    int movieIndex = getMovieIndex(c.movieName);

    if (movieOccupancy[movieIndex] >= maxSeatsPerMovie)
    { cout << "\n" << c.movieName << " is full. Cannot restore booking.\n"; return; }

    if (seatExistsForMovie(c.movieName, c.seatNumber))
    {
        cout << "\nCannot restore booking. Seat number "
             << c.seatNumber << " is already occupied for " << c.movieName << ".\n";
        return;
    }

    c = stack.pop();
    theaterSeats[seatCount] = c;
    seatCount++;
    movieOccupancy[getMovieIndex(c.movieName)]++;
    logTransaction("RESTORED", c);

    cout << "\n\n---------- UNDO CANCELLATION -----------\n";
    cout << "Booking successfully restored!\n\n";
    displayBooking(c);
    cout << "------------------------------------------\n";
}

// ==================== SEARCH ====================

inline int linearSearch(const string& id, int& comparisons)
{
    comparisons = 0;

    for (int i = 0; i < seatCount; i++)
    {
        comparisons++;
        if (theaterSeats[i].customerID == id) { return i; }
    }
    return -1;
}

inline void sortByID()
{
    for (int i = 0; i < seatCount - 1; i++)
    {
        for (int j = 0; j < seatCount - i - 1; j++)
        {
            if (theaterSeats[j].customerID > theaterSeats[j + 1].customerID)
            { swap(theaterSeats[j], theaterSeats[j + 1]); }
        }
    }
}

inline int binarySearch(const string& id, int& comparisons)
{
    comparisons = 0;
    sortByID();
    int left = 0;
    int right = seatCount - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        comparisons++;

        if (theaterSeats[mid].customerID == id) { return mid; }

        if (theaterSeats[mid].customerID < id) { left = mid + 1; }
        else { right = mid - 1; }
    }
    return -1;
}

inline void searchMenu()
{
    int choice;
    do
    {
        cout << "\n\n-------------- SEARCH MENU -------------\n";
        cout << "1. Linear Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Compare Search Algorithms\n";
        cout << "0. Back to Main Menu\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
            {
                if (seatCount == 0)
                { cout << "\nNo bookings available.\n"; break; }

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);
                for (char& ch : id) ch = toupper(ch);

                int comparisons;
                int result = linearSearch(id, comparisons);

                cout << "\n\n---------- LINEAR SEARCH RESULT ----------\n";

                if (result == -1)
                { cout << "Booking not found.\n"; }
                else
                { cout << "Booking found!\n\n"; displayBooking(theaterSeats[result]); }

                cout << "\nNumber of comparisons: " << comparisons << endl;
                cout << "Time Complexity: O(n)\n";
                cout << "------------------------------------------\n";
                break;
            }

            case 2:
            {
                if (seatCount == 0)
                { cout << "\nNo bookings available.\n"; break; }

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);
                for (char& ch : id) ch = toupper(ch);

                int comparisons;
                int result = binarySearch(id, comparisons);

                cout << "\n\n-------- BINARY SEARCH RESULT --------\n";

                if (result == -1)
                { cout << "Booking not found.\n"; }
                else
                { cout << "Booking found!\n\n"; displayBooking(theaterSeats[result]); }

                cout << "\nNumber of comparisons: " << comparisons << endl;
                cout << "Time Complexity: O(log n)\n";
                cout << "----------------------------------------\n";
                break;
            }

            case 3:
            {
                if (seatCount == 0)
                { cout << "\nNo bookings available.\n"; break; }

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);
                for (char& ch : id) ch = toupper(ch);

                int linearComparisons;
                int linearResult = linearSearch(id, linearComparisons);

                int binaryComparisons;
                int binaryResult = binarySearch(id, binaryComparisons);

                cout << "\n\n--------SEARCH ALGORITHM COMPARISON--------\n";
                cout << "\nLinear Search\n";
                cout << "Result: ";
                if (linearResult != -1) { cout << "Booking Found"; }
                else { cout << "Booking Not Found"; }
                cout << endl;
                cout << "Comparisons: " << linearComparisons << endl;
                cout << "Time Complexity: O(n)\n";
                cout << "\nBinary Search\n";
                cout << "Result: ";
                if (binaryResult != -1) { cout << "Booking Found"; }
                else { cout << "Booking Not Found"; }
                cout << endl;
                cout << "Comparisons: " << binaryComparisons << endl;
                cout << "Time Complexity: O(log n)\n";
                cout << "\n-------------------------------------------\n";

                if (binaryComparisons < linearComparisons)
                { cout << "Binary Search used fewer comparisons.\n"; }
                else if (linearComparisons < binaryComparisons)
                { cout << "Linear Search used fewer comparisons.\n"; }
                else { cout << "Both used the same number of comparisons.\n"; }

                cout << "\nAdvantages:\n";
                cout << "\nLinear Search:\n";
                cout << "- Simple to implement.\n";
                cout << "- Does not require sorted data.\n";
                cout << "- Suitable for small or unsorted data.\n";
                cout << "\nBinary Search:\n";
                cout << "- Faster for large sorted data.\n";
                cout << "- Uses O(log n) time.\n";
                cout << "- Requires sorted data.\n";
                cout << "\nDisadvantages:\n";
                cout << "\nLinear Search:\n";
                cout << "- Can require many comparisons.\n";
                cout << "- O(n) time complexity.\n";
                cout << "\nBinary Search:\n";
                cout << "- Requires sorted data.\n";
                cout << "- Sorting may take additional time.\n";
                cout << "--------------------------------------------\n";
                break;
            }
            case 0:
                cout << "\nReturning to main menu...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice != 0);
}

// ==================== FILE HANDLING ====================

inline string getCurrentDateTime()
{
    time_t now = time(0);
    char buf[80];
    struct tm tstruct;
    #ifdef _WIN32
        localtime_s(&tstruct, &now);
    #else
        tstruct = *localtime(&now);
    #endif
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return string(buf);
}

inline void logTransaction(const string& action, const customer& c)
{
    ofstream log(TRANSACTION_LOG, ios::app);
    if (!log.is_open()) return;

    log << getCurrentDateTime() << " | "
        << action << " | "
        << c.customerID << " | "
        << c.customerName << " | "
        << c.movieName << " | "
        << c.seatNumber << " | "
        << c.ageCategory << " | "
        << fixed << setprecision(2) << c.ticketPrice
        << "\n";
    log.close();
}

inline void saveBookingsToFile()
{
    ofstream out(BOOKINGS_FILE);
    if (!out.is_open())
    {
        cout << "\nError: Could not open " << BOOKINGS_FILE << " for writing.\n";
        return;
    }

    out << "=============================================================\n";
    out << "           CINEMA TICKET BOOKING SYSTEM - BOOKINGS\n";
    out << "Generated: " << getCurrentDateTime() << "\n";
    out << "Total Bookings: " << seatCount << "\n";
    out << "=============================================================\n\n";

    out << left
        << setw(8)  << "ID"
        << setw(20) << "Name"
        << setw(32) << "Movie"
        << setw(10) << "Seat"
        << setw(28) << "Age Category"
        << setw(12) << "Price(MYR)"
        << "\n";
    out << string(110, '-') << "\n";

    double grandTotal = 0.0;
    for (int i = 0; i < seatCount; i++)
    {
        const customer& c = theaterSeats[i];
        out << left
            << setw(8)  << c.customerID
            << setw(20) << c.customerName
            << setw(32) << c.movieName
            << setw(10) << c.seatNumber
            << setw(28) << c.ageCategory
            << setw(12) << fixed << setprecision(2) << c.ticketPrice
            << "\n";
        grandTotal += c.ticketPrice;
    }

    out << string(110, '-') << "\n";
    out << "TOTAL REVENUE (active bookings): MYR "
        << fixed << setprecision(2) << grandTotal << "\n";

    out << "\n\n--- BOOKINGS PER MOVIE ---\n";
    for (int i = 0; i < movieCount; i++)
    {
        out << left << setw(35) << movieOptions[i]
            << ": " << movieOccupancy[i] << " seats booked\n";
    }

    out.close();
    cout << "\nBookings successfully saved to \"" << BOOKINGS_FILE << "\".\n";
}

inline void loadBookingsFromFile()
{
    ifstream in(BOOKINGS_FILE);
    if (!in.is_open())
    {
        cout << "\nNo saved file found (" << BOOKINGS_FILE << ").\n";
        return;
    }

    seatCount = 0;
    for (int i = 0; i < movieCount; i++) movieOccupancy[i] = 0;

    string line;
    bool inTable = false;
    int loaded = 0;

    while (getline(in, line))
    {
        if (line.find("-----") != string::npos && !inTable)
        {
            inTable = true;
            continue;
        }
        if (inTable && line.find("-----") != string::npos)
            break;
        if (!inTable) continue;
        if (line.empty()) continue;

        if (line.size() < 8 + 20 + 32 + 10 + 28) continue;

        customer c;
        string priceStr;

        c.customerID   = line.substr(0, 8);
        c.customerName = line.substr(8, 20);
        c.movieName    = line.substr(28, 32);
        c.seatNumber   = line.substr(60, 10);
        c.ageCategory  = line.substr(70, 28);
        priceStr       = line.substr(98);

        auto trim = [](string& s) {
            size_t start = s.find_first_not_of(" \t");
            size_t end   = s.find_last_not_of(" \t");
            if (start == string::npos) { s = ""; return; }
            s = s.substr(start, end - start + 1);
        };
        trim(c.customerID);
        trim(c.customerName);
        trim(c.movieName);
        trim(c.seatNumber);
        trim(c.ageCategory);
        trim(priceStr);

        try { c.ticketPrice = stod(priceStr); }
        catch (...) { c.ticketPrice = 0.0; }

        if (c.customerID.empty()) continue;

        if (seatCount < maxSeats)
        {
            theaterSeats[seatCount] = c;
            seatCount++;
            int mi = getMovieIndex(c.movieName);
            movieOccupancy[mi]++;
            loaded++;
        }
    }

    in.close();

    if (loaded > 0)
        cout << "\nLoaded " << loaded << " booking(s) from \"" << BOOKINGS_FILE << "\".\n";
    else
        cout << "\nNo valid records found in \"" << BOOKINGS_FILE << "\".\n";
}

inline void saveCancellationsToFile(CancellationStack& stack)
{
    ofstream out(CANCELLATIONS_FILE);
    if (!out.is_open())
    {
        cout << "\nError: Could not open " << CANCELLATIONS_FILE << " for writing.\n";
        return;
    }

    out << "=============================================================\n";
    out << "        CINEMA TICKET BOOKING SYSTEM - CANCELLATIONS\n";
    out << "Generated: " << getCurrentDateTime() << "\n";
    out << "=============================================================\n\n";

    StackNode* current = stack.getTop();
    int count = 1;
    double totalLost = 0.0;

    if (current == nullptr)
    {
        out << "(No cancellations recorded)\n";
    }
    else
    {
        out << left
            << setw(6)  << "No."
            << setw(8)  << "ID"
            << setw(20) << "Name"
            << setw(32) << "Movie"
            << setw(10) << "Seat"
            << setw(28) << "Age Category"
            << setw(12) << "Price(MYR)"
            << "\n";
        out << string(116, '-') << "\n";

        while (current != nullptr)
        {
            const customer& c = current->data;
            out << left
                << setw(6)  << count
                << setw(8)  << c.customerID
                << setw(20) << c.customerName
                << setw(32) << c.movieName
                << setw(10) << c.seatNumber
                << setw(28) << c.ageCategory
                << setw(12) << fixed << setprecision(2) << c.ticketPrice
                << "\n";
            totalLost += c.ticketPrice;
            current = current->next;
            count++;
        }
        out << string(116, '-') << "\n";
        out << "TOTAL CANCELLED VALUE: MYR " << fixed << setprecision(2) << totalLost << "\n";
        out << "Total Cancellations: " << count - 1 << "\n";
    }

    out.close();
    cout << "\nCancellation history saved to \"" << CANCELLATIONS_FILE << "\".\n";
}

inline void saveAllRecordsToFile(CancellationStack& stack)
{
    ofstream out(ALL_RECORDS_FILE);
    if (!out.is_open())
    {
        cout << "\nError: Could not open " << ALL_RECORDS_FILE << " for writing.\n";
        return;
    }

    out << "=============================================================\n";
    out << "          CINEMA TICKET BOOKING SYSTEM - FULL REPORT\n";
    out << "Generated: " << getCurrentDateTime() << "\n";
    out << "=============================================================\n\n";

    // SECTION 1: ACTIVE
    out << "SECTION 1: ACTIVE BOOKINGS (" << seatCount << ")\n";
    out << string(116, '-') << "\n";
    out << left
        << setw(8)  << "ID"
        << setw(20) << "Name"
        << setw(32) << "Movie"
        << setw(10) << "Seat"
        << setw(28) << "Age Category"
        << setw(12) << "Price(MYR)"
        << "\n";
    out << string(116, '-') << "\n";

    double activeTotal = 0.0;
    for (int i = 0; i < seatCount; i++)
    {
        const customer& c = theaterSeats[i];
        out << left
            << setw(8)  << c.customerID
            << setw(20) << c.customerName
            << setw(32) << c.movieName
            << setw(10) << c.seatNumber
            << setw(28) << c.ageCategory
            << setw(12) << fixed << setprecision(2) << c.ticketPrice
            << "\n";
        activeTotal += c.ticketPrice;
    }
    out << string(116, '-') << "\n";
    out << "Subtotal: MYR " << fixed << setprecision(2) << activeTotal << "\n\n\n";

    // SECTION 2: CANCELLATIONS
    out << "SECTION 2: CANCELLATION HISTORY\n";
    out << string(116, '-') << "\n";

    StackNode* current = stack.getTop();
    int cancelCount = 0;
    double cancelTotal = 0.0;

    if (current == nullptr)
    {
        out << "(No cancellations recorded)\n";
    }
    else
    {
        out << left
            << setw(6)  << "No."
            << setw(8)  << "ID"
            << setw(20) << "Name"
            << setw(32) << "Movie"
            << setw(10) << "Seat"
            << setw(28) << "Age Category"
            << setw(12) << "Price(MYR)"
            << "\n";
        out << string(116, '-') << "\n";

        while (current != nullptr)
        {
            const customer& c = current->data;
            cancelCount++;
            out << left
                << setw(6)  << cancelCount
                << setw(8)  << c.customerID
                << setw(20) << c.customerName
                << setw(32) << c.movieName
                << setw(10) << c.seatNumber
                << setw(28) << c.ageCategory
                << setw(12) << fixed << setprecision(2) << c.ticketPrice
                << "\n";
            cancelTotal += c.ticketPrice;
            current = current->next;
        }
        out << string(116, '-') << "\n";
    }
    out << "Subtotal (cancelled): MYR " << fixed << setprecision(2) << cancelTotal << "\n\n\n";

    // SECTION 3: OCCUPANCY
    out << "SECTION 3: OCCUPANCY PER MOVIE\n";
    out << string(60, '-') << "\n";
    for (int i = 0; i < movieCount; i++)
    {
        out << left << setw(35) << movieOptions[i]
            << ": " << setw(6) << movieOccupancy[i]
            << "/ " << maxSeatsPerMovie << " seats\n";
    }

    // SECTION 4: SUMMARY
    out << "\n\nSECTION 4: SUMMARY\n";
    out << string(60, '-') << "\n";
    out << "Active Bookings   : " << seatCount << "\n";
    out << "Cancellations     : " << cancelCount << "\n";
    out << "Active Revenue    : MYR " << fixed << setprecision(2) << activeTotal << "\n";
    out << "Cancelled Value   : MYR " << fixed << setprecision(2) << cancelTotal << "\n";
    out << "Total Transactions: " << (seatCount + cancelCount) << "\n";

    out << "\n=============================================================\n";
    out << "                    END OF REPORT\n";
    out << "=============================================================\n";

    out.close();
    cout << "\nFull report saved to \"" << ALL_RECORDS_FILE << "\".\n";
}

inline void fileManagementMenu(CancellationStack& stack)
{
    int choice;
    do
    {
        cout << "\n\n------------- FILE MANAGEMENT -------------\n";
        cout << "1. Save Active Bookings to File\n";
        cout << "2. Load Bookings from File\n";
        cout << "3. Save Cancellation History to File\n";
        cout << "4. Save Full Report (All Records)\n";
        cout << "5. View Transaction Log\n";
        cout << "0. Back to Main Menu\n";
        cout << "-------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                saveBookingsToFile();
                break;
            case 2:
            {
                cout << "\nWARNING: Loading will replace all current bookings.\n";
                cout << "Continue? (Y/N): ";
                string ans;
                getline(cin, ans);
                if (ans == "Y" || ans == "y")
                    loadBookingsFromFile();
                else
                    cout << "\nLoad cancelled.\n";
                break;
            }
            case 3:
                saveCancellationsToFile(stack);
                break;
            case 4:
                saveAllRecordsToFile(stack);
                break;
            case 5:
            {
                ifstream in(TRANSACTION_LOG);
                if (!in.is_open())
                {
                    cout << "\nNo transaction log found.\n";
                    break;
                }
                cout << "\n\n--------- TRANSACTION LOG ---------\n";
                string line;
                while (getline(in, line))
                    cout << line << "\n";
                cout << "-----------------------------------\n";
                in.close();
                break;
            }
            case 0:
                cout << "\nReturning to main menu...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice != 0);
}

// ==================== MAIN MENU ====================

inline void mainMenu(Queue& queue, CancellationStack& stack)
{
    int choice;
    do {
        cout << "\n\n";
        cout << "--------CINEMA TICKET BOOKING SYSTEM--------\n";
        cout << "1. Queue (Book / Serve Tickets)\n";
        cout << "2. Stack (Cancel / Modify Tickets)\n";
        cout << "3. Display All Bookings\n";
        cout << "4. Search Bookings\n";
        cout << "5. Display Price List\n";
        cout << "6. File Management (Save / Load)\n";
        cout << "0. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: queue.queueMenu(); break;
            case 2: stack.stackMenu(); break;
            case 3: displayAllBookings(); break;
            case 4: searchMenu(); break;
            case 5: displayPriceList(); break;
            case 6: fileManagementMenu(stack); break;
            case 0:
                cout << "\nSaving data before exit...\n";
                saveBookingsToFile();
                saveCancellationsToFile(stack);
                cout << "\nThank you for using the Cinema "
                     << "Ticket Booking System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice != 0);
}

#endif // CINEMA_BOOKING_H