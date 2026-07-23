// Created by User on 8/5/2025.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//variable Declaration
int choice;

//Store User Data .a
typedef struct
{
    char booking_id[10];
    char name[50];
    char passport_id[20];
    int age;
    char date[20]; // DD/MM/YYYY
    char time[10]; // HH:MM
    char seat[10];
    int actives;// 0 as Unactive 1 as Active
    int pay_status;// 0 as Paid 1 as Unpaid
    char passenger_type[20];
    char payment_method[20];

} User_data;
User_data user;//user information

//Max Record of Bookings
#define max_bookings 180

//seats Variable Declaration & Settings
#define rows 30
#define cols 6

char seats[rows][cols];
char COLS[cols] = {'A', 'B', 'C', 'D', 'E', 'F'};//set Col[cols] {A,B,C,D,E,F}

User_data bookings[max_bookings];//Userdata[bookings] while bookings[180]
int bookingCount = 0;
int activeBooking = 0;

//-------------------------------------------------------------------------------------------------//

//Booking ID Generation
void generation_bookingID(char *id)
{
    int unique = 0;
    while (!unique) {//(!0)
        sprintf(id, "B%05d", rand() % 100000);//B12345
        unique = 1; // assume it's unique

        for (int i = 0; i < bookingCount; i++) {
            if (strcmp(bookings[i].booking_id, id) == 0) {// check for same ID
                unique = 0;
                break;
            }
        }
    }
}

//Seating Arrangement & Reservation
void reservation_defaultstatus() //Reset Seating status = O (available)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            seats[i][j] = 'O';
        }
    }
}

void resetFile() // open in write mode → clears file
{
    FILE *fp = fopen("bookings.txt", "w");
    if (fp != NULL)
    {
        fclose(fp);
    }
}

void seating_layout()
{
    printf("    "); //Display Rows 1-30
    for (int i = 1; i <= rows; i++)
    {
        printf(" %2d", i);
    }
    printf("\n"); // Next line

    for (int j = 0; j < cols; j++) //Display Cols A-F
    {
        printf(" %c |", COLS[j]);//print first letter A|
        for (int i = 0; i < rows; i++)
        {
            printf(" %2c", seats[i][j]);//print available seat
        }
        printf(" |\n");

        if (j == 2) //After reach the 3rd row
        {
            printf("    ");
            for (int k = 1; k <= rows; k++)
            {
                printf("---");//line
            }
            printf("\n");
        }
    }
}

// Convert seat letter to column index
int colIndex(char col)
{
    col = (char)toupper((unsigned char)col); //default to uppercase

    for (int i = 0; i < cols; i++)//1-6
    {
        if (COLS[i] == col)//(A-F) == (A-F)
            return i;//valid
    }
    return -1; //invalid input
}

void countSeats(int *available, int *occupied)//Count seat show Available & Occupied
{//Pointer------------^
    *available = 0;//set pointer
    *occupied = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (seats[i][j] == 'O')
                (*available)++;
            else
                (*occupied)++;
        }
    }
}

void pause_screen() {// let user have time to read
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar(); // wait for enter
}

void arrangementreservation_exe() //execute 1. Seating Arrangement & Reservation
{
    char input[10];
    int row, available, occupied;
    char col;

    printf("\nLoading...\n Map Layout Display...\n\n");
    seating_layout();                 //print map
    countSeats(&available, &occupied); //count for seats

    while (1) //infinite loop
    {
        printf("Seats available:%2d    Seats occupied:%2d\n", available, occupied);
        printf("Enter seat (e.g. 12C) or Q to quit:\n");
        scanf("%9s", input);

        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) //Q to quit
        {
            printf("\n");
            break;
        }

        if (sscanf(input, "%d%c", &row, &col) == 2) //check two strings = 2 (__)
        {
            col = (char)toupper((unsigned char)col);//set uppercase
            int cindex = colIndex(col);
            if (row >= 1 && row <= rows && cindex != -1)//row is (1-30) (A-F)
            {
                if (seats[row - 1][cindex] == 'O')
                {
                    seats[row - 1][cindex] = 'X';//Taken

                    seating_layout();//layout reprint
                    countSeats(&available, &occupied); //count seats again
                    generation_bookingID(user.booking_id);//bookings id & active id
                    user.actives = 1;
                    snprintf(user.seat, sizeof(user.seat), "%d%c", row, col);//prevent overflow

                    bookings[bookingCount++] = user; // Save Info in array --- bookingsCount ADD +1 each time
                    FILE *fp = fopen("bookings.txt", "a");//open file
                    if (fp != NULL)
                    {
                        fprintf(fp, "%s|%s|%d|%s|%s|%d|%s|%s|%d\n",
                        user.booking_id, user.seat, user.actives,
                        "-", "-", 0, "-", "-", 0);
                        fclose(fp);
                    }

                    printf("\nSeats %d%c Booked Successfully!\n", row, col);
                    printf("Seats available:%2d    Seats occupied:%2d\n", available, occupied);
                    printf("Booking ID:%s\n", user.booking_id);

                    pause_screen();//react time
                    printf("\n");
                    break;
                }
                else
                {
                    printf("Seats %d%c is already Occupied!\n", row, col);
                }
            }
            else
            {
                printf("Invalid seat! Try again.\n");
            }
        }
        else
        {
            printf("Invalid format! Please use like 12C.\n");
        }
    }
}

//Available Ticket slot count
void count_bookings()
{
    if (activeBooking >= max_bookings)
    {
        printf("Maximum number of bookings reached.\n");
        pause_screen();
        return;
    }
}

//Ticket Generation
void ticket_generation()
{
    char booking_id[10];
    int found = 0;

    count_bookings();//prevent over 180
    printf("\n");

    printf("Enter Your Booking ID or Q to quit:");
    scanf("%9s", booking_id);

    if (strcmp(booking_id, "q") == 0 || strcmp(booking_id, "Q") == 0)
    {
        printf("\nReturning to Main Menu...\n");
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
        if (strcmp(bookings[i].booking_id, booking_id) == 0)//found match
        {
            if (bookings[i].actives == 0)
            {
                printf("\nYour ticket is cancelled.\n");
                printf("Returning to Main Menu...\n");
                return;
            }

            found = 1;//prom information
            activeBooking++;

            printf("\n");
            printf("Enter Your name:");
            getchar(); // eat previous scanf "/n"
            fgets(bookings[i].name, 50, stdin); //read with space
            bookings[i].name[strcspn(bookings[i].name, "\n")] = '\0'; //remove newline

            printf("Enter Your Passport/IC:");
            scanf("%19s", bookings[i].passport_id);

            char ageinput[10];
            int valid = 0;

            while (!valid) {
                printf("Enter Your age: ");
                scanf("%9s", ageinput);  // read as string

                valid = 1;//assume valid
                for (int j = 0; ageinput[j] != '\0'; j++) {
                    if (!isdigit((unsigned char)ageinput[j])) {//not int
                        valid = 0;
                        break;
                    }
                }

                if (valid) {
                    bookings[i].age = atoi(ageinput); // convert to integer
                    if (bookings[i].age >= 1) {
                        //valid age
                        break;
                    }
                } else {
                    printf("\nInvalid input. Numbers only!\n");//repeat
                }
            }


            printf("\nTime & Date Auto key-in...\n");
            //get current time
            time_t present = time(NULL);           //variable to hold current time
            struct tm *local = localtime(&present);//structure for local time format

            //format
            strftime(bookings[i].date, sizeof(bookings[i].date), "%d/%m/%Y", local);  // dd/mm/yyyy
            strftime(bookings[i].time, sizeof(bookings[i].time), "%H:%M:%S", local);  // HH:MM:SS

            bookings[i].actives = 1;
            bookings[i].pay_status = 0;//Pay Status set 0 (Haven't Paid)

            FILE *fp = fopen("bookings.txt", "a+");//add data in file
            if (fp != NULL)
            {
               fprintf(fp, "%s|%s|%d|%s|%s|%d|%s|%s|%d\n",
                    bookings[i].booking_id, bookings[i].seat, bookings[i].actives,
                    bookings[i].name, bookings[i].passport_id, bookings[i].age, bookings[i].date,
                    bookings[i].time, bookings[i].pay_status);
                fclose(fp);

                printf("\n------------Booking Status------------\n");
                printf("Booking ID   : %s\n", bookings[i].booking_id);
                printf("Name         : %s\n", bookings[i].name);
                printf("Passport/IC  : %s\n", bookings[i].passport_id);
                printf("Age          : %d\n", bookings[i].age);
                printf("Flight Date  : %s %s\n", bookings[i].date, bookings[i].time);
                printf("Seats        : %s\n", bookings[i].seat);
                printf("Pay Status   : %s\n", (bookings[i].pay_status == 1) ? "Paid" : "Unpaid");
                printf("Ticket Status: %s\n",(bookings[i].actives == 1) ? "Active" : "Cancel");
                printf("-------------------------------------\n");
                printf("\nPress Enter to continue...\n");
                getchar();
                getchar();
            }
            break;
        }
    }

    if (!found)//not found return error
    {
        printf("\nError...\nBooking ID %s not found or Invalid.\n", booking_id);
        pause_screen();
    }
}

//Reservation Cancellation
void cancellation()
{
    char col, cancellation_ID[10];
    int row, found = 0;

    printf("\nWelcome to Reservation Cancellation Program.\n");
    printf("Enter Your Booking ID or Q to quit:");
    scanf("%9s", cancellation_ID);

    if (strcmp(cancellation_ID, "q") == 0 || strcmp(cancellation_ID, "Q") == 0)//quit
    {
        printf("\nReturning to Main Menu...\n");
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].actives == 0)//if already cancel
        {
            printf("\nYour ticket is cancelled.\n");
            printf("Returning to Main Menu...\n");
            return;
        }

        if (strcmp(bookings[i].booking_id, cancellation_ID) == 0 && bookings[i].actives == 1)//found match & active
        {
            found = 1;
            bookings[i].actives = 0;//set unactive
            activeBooking--;

            if (sscanf(bookings[i].seat, "%d%c", &row, &col) == 2)//check file
            {
                int cindex = colIndex(col);
                if (cindex != -1)
                {
                    seats[row - 1][cindex] = 'O';//release seat
                    printf("\n------------Booking Status------------\n");
                    printf("Booking ID   : %s\n", bookings[i].booking_id);
                    printf("Name         : %s\n", bookings[i].name);
                    printf("Passport/IC  : %s\n", bookings[i].passport_id);
                    printf("Age          : %d\n", bookings[i].age);
                    printf("Flight Date  : %s %s\n", bookings[i].date, bookings[i].time);
                    printf("Seats        : %s\n", bookings[i].seat);
                    printf("Ticket Status: %s\n",(bookings[i].actives == 1) ? "Active" : "Cancel");//if 1 active 0 cancel
                    printf("-------------------------------------\n");
                }
            }

            printf("\nBooking %s Cancelled Successfully", cancellation_ID);

            FILE *fp = fopen("bookings.txt", "r+");//rewrite information
            if (fp != NULL)
            {
                for (int j = 0; j < bookingCount; j++)
                {
                    fprintf(fp, "%s|%s|%d|%s|%s|%d|%s|%s|%d\n",
                    bookings[j].booking_id, bookings[j].seat, bookings[j].actives,
                    bookings[j].name, bookings[j].passport_id, bookings[j].age, bookings[j].date,
                    bookings[j].time, bookings[j].pay_status);
                }
                fclose(fp);
            }
            break;
        }
    }

    if (!found)
    {
        printf("\nError...\nBooking ID %s not found, Invalid.\n", cancellation_ID);
    }
    pause_screen();
}
//Payment Processing
void payment_process()
{
    char booking_id[10];
    int found = 0,pay_method;
    double payment = 0;

    count_bookings();//count available
    printf("\n");

    printf("Enter Your Booking ID or Q to quit:");
    scanf("%9s", booking_id);

    if (strcmp(booking_id, "q") == 0 || strcmp(booking_id, "Q") == 0)//quit
    {
        printf("\nReturning to Main Menu...\n");
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
        if (strcmp(bookings[i].booking_id, booking_id) == 0)//matches
        {
            if (bookings[i].actives == 0)//cancel
            {
                printf("\nYour ticket is cancelled.\n");
                printf("Returning to Main Menu...\n");
                return;
            }
            if (bookings[i].name[0] == '\0' || bookings[i].passport_id[0] == '\0')//no info
            {
                printf("\nYou Haven't Register your information or information are missing.\n");
                printf("Returning to Main Menu...\n");
                return;
            }

            printf("==================== Ticket =================\n");
            printf(" Passenger Type |   Age Group   |   Price(MYR)\n");
            printf("     Adult      |     18-59     |      200    \n");
            printf("     Senior     |      60+      |      160    \n");
            printf("     Child      |      2-17     |      180    \n");
            printf("     Infant     | Below 2 years |       20    \n");
            printf("=============================================\n\n");

            if (bookings[i].age >= 18 && bookings[i].age <= 59)
            {
                strcpy(bookings[i].passenger_type, "Adult");
                payment = 200;
            }
            else if (bookings[i].age >= 60)
            {
                strcpy(bookings[i].passenger_type, "Senior");
                payment = 160;
            }
            else if (bookings[i].age >= 2 && bookings[i].age <= 17)
            {
                strcpy(bookings[i].passenger_type, "Child");
                payment = 180;
            }
            else
            {
                strcpy(bookings[i].passenger_type, "Infant");
                payment = 20;
            }

            printf("\n---------------------------------------------\n");
            printf("Booking ID   : %s\n", bookings[i].booking_id);
            printf("Ticket Status: %s\n",(bookings[i].actives == 1) ? "Active" : "Cancel");
            printf("Name         : %s\n", bookings[i].name);
            printf("Seat         : %s\n", bookings[i].seat);
            printf("Passenger    : %s\n", bookings[i].passenger_type);
            printf("Flight Date  : %s %s\n", bookings[i].date, bookings[i].time);
            printf("---------------------------------------------\n");
            printf("Outstanding Amount: MYR%.2f\n",payment);
            printf("Online Payment (FPX) [1] / Cashier Payment [2] / Cards Payment [3] / Exit [4]\n");
            printf("Select Payment Method:");
            scanf("%d", &pay_method);
            printf("\n");
            switch (pay_method)
            {
            case 1:printf("You Selected Online Banking...\nPayment Success Total Fees: %.2f...\n",payment);
                 strcpy(bookings[i].payment_method, "Online Banking");break;
            case 2:printf("You Selected Cashier Payment...\nPayment Success Total Fees: %.2f...\n",payment);
                strcpy(bookings[i].payment_method, "Cashier");break;
            case 3:printf("You Selected Credit/Debit Payment...\nPayment Success Total Fees: %.2f...\n",payment);
                strcpy(bookings[i].payment_method, "Card");break;
            case 4:printf("Exiting...\n"); return;
            default: while (pay_method <= 0 || pay_method >= 5)// repeat until user input 1-4 number
            {
                printf("\nError... Invalid Payment Method.\n");//wrong selection
                printf("Select Payment Method:");
                scanf("%d", &pay_method);
            }
            }
            if (pay_method >= 1 && pay_method <= 3)//paid
            {
                bookings[i].pay_status = 1;// set pay status as (Paid)
            }
            printf("\nReturning to Main Menu...\n");

            found = 1;
            break;
        }
    }
    if (found)
    {
        FILE *fp = fopen("bookings.txt", "r+");//add passenger type & method
        if (fp == NULL)
        {
            printf("Error opening bookings.txt for writing.\n");
            return;
        }

        for (int j = 0; j < bookingCount; j++)
        {
            fprintf(fp, "%s|%s|%d|%s|%s|%d|%s|%s|%d|%s|%s\n",
                    bookings[j].booking_id,
                    bookings[j].seat,
                    bookings[j].actives,
                    bookings[j].name,
                    bookings[j].passport_id,
                    bookings[j].age,
                    bookings[j].date,
                    bookings[j].time,
                    bookings[j].pay_status,
                    bookings[j].passenger_type,
                    bookings[j].payment_method);
        }
        fclose(fp);
    }

    if (!found)
    {
        printf("\nError...\nBooking ID %s not found or Invalid.\n", booking_id);
        pause_screen();
    }
}
//Receipt Printing
void Receipt_Printing()
{
    char Receipt_ID[10];
    int found = 0;

    printf("\nWelcome to Receipt Printing Program.\n");
    printf("Enter Your Booking ID or Q to quit:");
    scanf("%9s", Receipt_ID);

    if (strcmp(Receipt_ID, "q") == 0 || strcmp(Receipt_ID, "Q") == 0)
    {
        printf("\nReturning to Main Menu...\n");
        return;
    }

    FILE *fp = fopen("bookings.txt", "r");//read file
    if (fp == NULL)//nothing = error
    {
        printf("Error: Could not open bookings.txt\n");
        return;
    }

    //temp variables to read file
    char booking_id[10], seat[10], name[50], passport_id[20];
    char date[20], time_str[20], passenger_type[20], payment_method[20];
    int actives, age, pay_status;

    while (fscanf(fp, "%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%[^|]|%[^|\n]\n",//read till '|'
                  booking_id, seat, &actives,
                  name, passport_id, &age,
                  date, time_str, &pay_status,
                  passenger_type, payment_method) == 11)
    {
        if (strcmp(booking_id, Receipt_ID) == 0)
        {
            found = 1;

            if (actives == 0)//cancel no print
            {
                printf("\nYour ticket is cancelled.\n");
                fclose(fp);
                return;
            }
            else if (pay_status == 0)//haven't paid
            {
                printf("\nYour ticket hasn't been paid yet.\n");
                fclose(fp);
                return;
            }

            // print receipt
            printf("\n====================================\n");
            printf("       AIRLINE PAYMENT RECEIPT      \n");
            printf("====================================\n");
            printf("Booking ID   : %s\n", booking_id);
            printf("Passport/IC  : %s\n", passport_id);
            printf("Name         : %s\n", name);
            printf("Age          : %d\n", age);
            printf("Passenger    : %s\n", passenger_type);
            printf("Flight Date  : %s %s\n", date, time_str);
            printf("Seat         : %s\n", seat);
            printf("--------------------------------------\n");
            printf("Pay Status   : %s\n", (pay_status == 1) ? "Paid" : "Unpaid");
            printf("Payment Mode : %s\n", payment_method);
            printf("Ticket Status: %s\n", (actives == 1) ? "Active" : "Cancel");
            printf("====================================\n");
            printf("    THANK YOU FOR FLYING WITH US!   \n");
            printf("====================================\n");
            break;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\nError...\nBooking ID %s not found, Invalid.\n", Receipt_ID);
    }
    pause_screen();
}


//mainmenu display
void mainmenu()
{
    printf("-------------Main menu-------------\n");
    printf("1.  Seating Arrangement & Reservation\n");
    printf("2.  Ticket Generation\n");
    printf("3.  Reservation Cancellation\n");
    printf("4.  Payment Processing\n");
    printf("5.  Receipt Printing\n");
    printf("6.  Exit\n");
    printf("-----------------------------------\n");

    printf("Enter your choice (1-6): ");
    scanf("%d", &choice);

    switch (choice){
    case 1:arrangementreservation_exe();break;
    case 2:ticket_generation();break;
    case 3:cancellation();break;
    case 4:payment_process();break;
    case 5:Receipt_Printing();break;;
    case 6:
        printf("\nThanks for choosing QIU Airline...\n");
        printf("Exiting...\n");
        break;
    default:printf("\nInvalid choice\n");}//accept (1-6 only)

}
int main()
{
    reservation_defaultstatus();//map set default all 'O'
    srand(time(0));//random function generate id

    resetFile();//each time open the file --> reset if stop function put (//resetFile;)
    do
    {
        mainmenu();//menu
    } while (choice != 6);//exit when choice = 6

    return 0;
}