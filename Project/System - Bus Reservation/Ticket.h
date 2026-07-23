#include <string>// string handling
#include <iostream>// input output
#include <fstream>//file handling
#include <ctime>//time.h>
#include <cstdlib>//for rand, srand

using namespace std;

class Ticket {
private:
    string ticketID;
    string seatCode;
    string passengerName;
    string passengerType;
    string scheduleDate;
    string scheduleTime;
    double price;
    string status;

    string generateTicketID() {
        srand(time(0) + rand());
        string id = "TC";
        for (int i = 0; i < 4; i++) id += to_string(rand() % 10);
        for (int i = 0; i < 4; i++) id += char('A' + rand() % 26);
        return id;
    }

    double calculatePrice(string type) {
        if (type == "Adult") return 50.0;
        if (type == "Child") return 25.0;
        if (type == "Senior") return 40.0;
        if (type == "Infant") return 15.0;
        return 0.0;
    }

public:
    Ticket(string seat = "-", string name = "-", string type = "-", 
           string date = "-", string time = "-", string stat = "Pending") {
        seatCode = seat;
        passengerName = name;
        passengerType = type;
        scheduleDate = date;
        scheduleTime = time;
        ticketID = generateTicketID();
        price = calculatePrice(type);
        status = stat;
    }

    string getTicketID() { return ticketID; }
    string getSeatCode() { return seatCode; }
    double getPrice() { return price; }

    void setPassengerName(string name) { passengerName = name; }
    void setPassengerType(string type) { passengerType = type; price = calculatePrice(type); }
    void setScheduleDate(string date) { scheduleDate = date; }
    void setScheduleTime(string time) { scheduleTime = time; }
    void setStatus(string stat) { status = stat; }

    void saveToFile() {
        ofstream file("reservations.txt", ios::app);
        if (file.is_open()) {
            file << ticketID << "|" << seatCode << "|" << status
                 << "|" << passengerName << "|" << passengerType
                 << "|" << scheduleDate << "|" << scheduleTime
                 << "|" << price << "\n";
            file.close();
        }
    }

    void printTicket() {
        cout << "\n===== Ticket Info =====\n";
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Passenger: " << passengerName << " (" << passengerType << ")\n";
        cout << "Seat: " << seatCode << endl;
        cout << "Schedule: " << scheduleDate << " " << scheduleTime << endl;
        cout << "Price: RM" << price << endl;
        cout << "Status: " << status << endl;
    }
};

