#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int maxSeats = 120;
const int maxQueue = 300;

struct customer//Default construct
{
    string customerID;
    string customerName;
    string movieName;
    string seatNumber;
};

customer theaterSeats[maxSeats];//Global bookings Array

int seatCount = 0;

//Functions
string getNonEmptyInput(const string& prompt);
bool IDexists(const string& id);
void displayBooking(const customer& c);
void cancelBooking(class CancellationStack& stack);
void undoCancellation(class CancellationStack& stack);
int linearSearch(const string& id, int& comparisons);
void sortByID();
int binarySearch(const string& id, int& comparisons);
void displayAllBookings();
void addBooking();
void searchMenu();

class Queue
{
private:

    customer customers[maxQueue];
    int front;
    int rear;

public:

    // Constructor
    Queue()
    {
        front = -1;
        rear = -1;
    }

    // Check whether queue is empty
    bool isEmpty()
    {return (front == -1 && rear == -1);}

    // Check whether queue is full
    bool isFull()
    {return (rear + 1) % maxQueue == front;}

    void enqueue(customer c)
    {
        if (isFull())
        {cout << "\nQueue is full. Cannot add more customers.\n";return;}

        if (isEmpty())
        {front = rear = 0;}
        
        else
        {rear = (rear + 1) % maxQueue;}

        customers[rear] = c;
        cout << "\nCustomer added to the queue successfully.\n";
    }

    void dequeue()
    {
        if (isEmpty())
        {cout << "\nQueue is empty. No customers to serve.\n";return;}

        cout << "\n------------ SERVING CUSTOMER ------------\n";
        cout << "Customer ID: "
             << customers[front].customerID << endl;
        cout << "Customer Name: "
             << customers[front].customerName << endl;
        cout << "Movie Name: "
             << customers[front].movieName << endl;
        cout << "Seat Number: "
             << customers[front].seatNumber << endl;

        if (front == rear)
        {front = rear = -1;}
        
        else
        {front = (front + 1) % maxQueue;}

        cout << "Customer has been served.\n";
    }

    void displayQueue()
    {
        if (isEmpty())
        {cout << "\nQueue is empty. No customers to display.\n";return;}
        
        cout << "\n------------ CUSTOMERS IN QUEUE ------------\n";

        int i = front;
        int count = 1;

        while (true)
        {
            cout << "\nCustomer " << count << endl;
            cout << "Customer ID: "<< customers[i].customerID << endl;
            cout << "Customer Name: "<< customers[i].customerName << endl;
            cout << "Movie Name: "<< customers[i].movieName << endl;
            cout << "Seat Number: "<< customers[i].seatNumber << endl;

            if (i == rear){break;}
            i = (i + 1) % maxQueue;
            count++;
        }
        cout << "-----------------------------------------------\n";
    }

    void displayFront()
    {
        if (isEmpty())
        {cout << "\nQueue is empty.\n";return;}

        cout << "\n---------- FRONT CUSTOMER ----------\n";
        displayBooking(customers[front]);
        cout << "--------------------------------------\n";
    }

    void displayRear()
    {
        if (isEmpty())
        {cout << "\nQueue is empty.\n";return;}

        cout << "\n---------- REAR CUSTOMER ----------\n";
        displayBooking(customers[rear]);
        cout << "-------------------------------------\n";
    }

    void queueMenu()
    {
        int choice;
        do
        {
            cout << "--------------- QUEUE MENU -------------\n";
            cout << "1. Add Customer to Queue\n";
            cout << "2. Serve Customer from Queue\n";
            cout << "3. Display All Customers in Queue\n";
            cout << "4. Display Customer at Front\n";
            cout << "5. Display Customer at Rear\n";
            cout << "6. Check Queue Status\n";
            cout << "0. Back to Main Menu\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
                case 1:
                {
                    customer c;
                    c.customerID = getNonEmptyInput("Enter Customer ID: ");
                    c.customerName = getNonEmptyInput("Enter Customer Name: ");
                    c.movieName = getNonEmptyInput("Enter Movie Name: ");
                    c.seatNumber = getNonEmptyInput("Enter Seat Number: ");

                    if (IDexists(c.customerID))
                    {
                        cout << "\nCustomer ID already exists.\n";
                        cout << "Please enter a different ID.\n";
                    }
                    else{enqueue(c);}
                    
                    break;
                }
                case 2:
                    dequeue();break;
                case 3:
                    displayQueue();break;
                case 4:
                    displayFront();break;
                case 5:
                    displayRear();break;
                case 6:
                    if (isEmpty())
                    {cout << "\nThe queue is EMPTY.\n";}
                    
                    else if (isFull())
                    {cout << "\nThe queue is FULL.\n";}
                    
                    else
                    {cout << "\nThe queue is neither empty nor full.\n";}
                    
                    break;
                case 0:
                    cout << "\nReturning to main menu...\n";break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);
    }
};

struct StackNode
{
    customer data;
    StackNode* next;
};

class CancellationStack
{
private:

    StackNode* top;

public:

    // Constructor
    CancellationStack()
    {top = nullptr;}

    // Destructor
    ~CancellationStack()
    {
        while (top != nullptr)
        {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Check whether stack is empty
    bool isEmpty()
    {return top == nullptr;}

    void push(customer c)
    {
        StackNode* newNode =new StackNode();
        newNode->data = c;
        newNode->next = top;
        top = newNode;
        cout << "\nCustomer added to cancellation stack.\n";
    }

    customer pop()
    {
        if (isEmpty())
        {cout << "\nStack is empty.\n";return customer();}

        StackNode* temp = top;
        customer c = top->data;
        top = top->next;
        delete temp;
        return c;
    }

    void peek()
    {
        if (isEmpty())
        {cout << "\nStack is empty. No cancellation to display.\n";return;}

        cout << "\n--------- LATEST CANCELLATION -------\n";
        displayBooking(top->data);
        cout << "----------------------------------------\n";
    }

    void displayStack()
    {
        if (isEmpty())
        {cout << "\nStack is empty. No cancellation history.\n";return;}

        cout << "\n------------ CANCELLATION HISTORY -----------\n";

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
            cout << "---------- CANCELLATION STACK ----------\n";
            cout << "1. Display Cancellation History\n";
            cout << "2. Undo Latest Cancellation\n";
            cout << "3. Peek Latest Cancellation\n";
            cout << "0. Back to Main Menu\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
                case 1:
                    displayStack();break;
                case 2:
                    undoCancellation(*this);break;
                case 3:
                    peek();break;
                case 0:
                    cout << "\nReturning to main menu...\n";break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);
    }
};

string getNonEmptyInput(const string& prompt)
{
    string input;
    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {cout << "Input cannot be empty. Please try again.\n";}
    }
    while (input.empty());
    return input;
}

bool IDexists(const string& id)
{
    for (int i = 0; i < seatCount; i++)
    {
        if (theaterSeats[i].customerID == id)
        {return true;}
    }
    return false;
}

void displayBooking(const customer& c)
{
    cout << "Customer ID: "<< c.customerID << endl;
    cout << "Customer Name: "<< c.customerName << endl;
    cout << "Movie Name: "<< c.movieName << endl;
    cout << "Seat Number: "<< c.seatNumber << endl;
}

void addBooking()
{
    if (seatCount >= maxSeats)
    {cout << "\nTheater is full. No more bookings available.\n";return;}

    customer c;

    cout << "\n========== ADD BOOKING ==========\n";

    do
    {
        c.customerID = getNonEmptyInput("Enter Customer ID: ");

        if (IDexists(c.customerID))
        {
            cout << "\nCustomer ID already exists.\n";
            cout << "Please enter another ID.\n";
        }
    }
    while (IDexists(c.customerID));
    
    c.customerName = getNonEmptyInput("Enter Customer Name: ");
    c.movieName = getNonEmptyInput("Enter Movie Name: ");
    c.seatNumber = getNonEmptyInput("Enter Seat Number: ");
    theaterSeats[seatCount] = c;
    seatCount++;
    cout << "\nBooking successfully added!\n";
    displayBooking(c);
}

void displayAllBookings()
{
    if (seatCount == 0)
    {cout << "\nNo bookings available.\n";return;}

    cout << "\n---------- ALL BOOKINGS -----------\n";

    for (int i = 0; i < seatCount; i++)
    {
        cout << "\nBooking " << i + 1 << endl;
        displayBooking(theaterSeats[i]);
        cout << "----------------------------------\n";
    }
}

void cancelBooking(CancellationStack& stack)
{
    if (seatCount == 0)
    {cout << "\nNo bookings to cancel.\n";return;}

    string id;
    cout << "\n---------- CANCEL BOOKING ----------\n";
    cout << "Enter Customer ID to cancel: ";
    getline(cin, id);
    int index = -1;

    // Find customer
    for (int i = 0; i < seatCount; i++)
    {if (theaterSeats[i].customerID == id){index = i;break;}}

    // Customer not found
    if (index == -1)
    {cout << "\nCustomer ID not found.\n";return;}

    // Push cancelled customer onto stack
    stack.push(theaterSeats[index]);
    cout << "\nBooking Cancelled:\n";
    displayBooking(theaterSeats[index]);

    for (int i = index; i < seatCount - 1; i++)
    {theaterSeats[i] = theaterSeats[i + 1];}
    
    seatCount--;
    cout << "\nBooking successfully cancelled.\n";
}

void undoCancellation(CancellationStack& stack)
{
    if (stack.isEmpty())
    {
        cout << "\nNo cancellations to undo.\n";
        return;
    }


    if (seatCount >= maxSeats)
    {
        cout << "\nTheater is full. Cannot restore booking.\n";
        return;
    }

    // Pop latest cancellation
    customer c = stack.pop();

    // Check duplicate ID
    if (IDexists(c.customerID))
    {
        cout << "\nCannot restore booking.\n";
        cout << "Customer ID already exists.\n";
        return;
    }

    // Add customer back
    theaterSeats[seatCount] = c;

    seatCount++;
    cout << "\n---------- UNDO CANCELLATION -----------\n";
    cout << "Booking successfully restored!\n\n";
    displayBooking(c);
    cout << "------------------------------------------\n";
}

int linearSearch(
    const string& id ,int& comparisons)
{
    comparisons = 0;

    for (int i = 0; i < seatCount; i++)
    {
        comparisons++;
        if (theaterSeats[i].customerID == id){return i;}
    }
    return -1;
}

void sortByID()
{
    for (int i = 0; i < seatCount - 1; i++)
    {
        for (int j = 0; j < seatCount - i - 1; j++)
        {
            if (theaterSeats[j].customerID >theaterSeats[j + 1].customerID)
            { swap(theaterSeats[j], theaterSeats[j + 1]);}
        }
    }
}

int binarySearch(const string& id ,int& comparisons)
{
    comparisons = 0;

    // Sort before binary search
    sortByID();
    int left = 0;
    int right = seatCount - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        comparisons++;

        if (theaterSeats[mid].customerID == id){return mid;}

        if (theaterSeats[mid].customerID < id){left = mid + 1;}
        
        else{right = mid - 1;}
    }
    return -1;
}

void searchMenu()
{
    int choice;
    do
    {
        cout << "-------------- SEARCH MENU -------------\n";
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
                {cout << "\nNo bookings available.\n";break;}

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);

                int comparisons;
                int result =linearSearch(id, comparisons);

                cout << "\n---------- LINEAR SEARCH RESULT ----------\n";

                if (result == -1)
                {cout << "Booking not found.\n";}
                
                else
                {cout << "Booking found!\n\n";
                displayBooking(theaterSeats[result]);}

                cout << "\nNumber of comparisons: "<< comparisons << endl;
                cout << "Time Complexity: O(n)\n";

                cout << "------------------------------------------\n";
                break;
            }

            case 2:
            {
                if (seatCount == 0)
                {cout << "\nNo bookings available.\n";break;}

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);

                int comparisons;
                int result = binarySearch(id, comparisons);

                cout << "\n-------- BINARY SEARCH RESULT --------\n";

                if (result == -1)
                {cout << "Booking not found.\n";}
                
                else
                {cout << "Booking found!\n\n";
                displayBooking(theaterSeats[result]);}

                cout << "\nNumber of comparisons: "<< comparisons << endl;
                cout << "Time Complexity: O(log n)\n";
                cout << "----------------------------------------\n";
                break;
            }

            case 3:
            {
                if (seatCount == 0)
                {cout << "\nNo bookings available.\n";break;}

                string id;
                cout << "\nEnter Customer ID to search: ";
                getline(cin, id);

                // Linear Search
                int linearComparisons;
                int linearResult = linearSearch(id,linearComparisons);

                // Binary Search
                int binaryComparisons;
                int binaryResult = binarySearch(id,binaryComparisons);

                cout << "--------SEARCH ALGORITHM COMPARISON--------\n";
                cout << "\nLinear Search\n";

                cout << "Result: ";
                if (linearResult != -1){cout << "Booking Found";}
                else{cout << "Booking Not Found";}
                
                cout << endl;

                cout << "Comparisons: "<< linearComparisons << endl;
                cout << "Time Complexity: O(n)\n";
                cout << "\nBinary Search\n";
                cout << "Result: ";

                if (binaryResult != -1) {cout << "Booking Found";}
                else{cout << "Booking Not Found";}
                
                cout << endl;

                cout << "Comparisons: "
                     << binaryComparisons << endl;

                cout << "Time Complexity: O(log n)\n";

                cout << "\n-------------------------------------------\n";

                if (binaryComparisons < linearComparisons)
                {cout << "Binary Search used fewer comparisons.\n";}
                
                    else if (linearComparisons < binaryComparisons)
                    {cout << "Linear Search used fewer comparisons.\n";}
                
                else{cout << "Both used the same number of comparisons.\n";}

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

void mainMenu(
    Queue& queue,
    CancellationStack& stack)
{
    int choice;
    do{
        cout << "\n\n";
        cout << "--------CINEMA TICKET BOOKING SYSTEM--------\n";
        cout << "1. Customer Queue\n";
        cout << "2. Add Booking\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Cancellation Stack\n";
        cout << "5. Undo Latest Cancellation\n";
        cout << "6. Display All Bookings\n";
        cout << "7. Search Booking\n";
        cout << "0. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice){
            case 1:
                queue.queueMenu();
                break;
            case 2:
                addBooking();
                break;
            case 3:
                cancelBooking(stack);
                break;
            case 4:
                stack.stackMenu();
                break;
            case 5:
                undoCancellation(stack);
                break;
            case 6:
                displayAllBookings();
                break;
            case 7:
                searchMenu();
                break;
            case 0:
                cout << "\nThank you for using the Cinema "
                     << "Ticket Booking System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice != 0);
}