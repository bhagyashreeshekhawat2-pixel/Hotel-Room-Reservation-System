/*
cd C:\Users\Bhagyashree\Desktop\cprogproject
gcc hotelroomreservation.c -o hotelroomreservation
.\hotelroomreservation.exe
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOTAL_ROOMS 10

//information for one room
struct room
{
    int roomNo;
    char roomType[20];
    int price;

    int booked;
    int checkedIn;

    char customerName[50];
    char phone[15];
    int days;

};



//FUNCTIONS PROTOTYPE


//hotel
struct room hotel[TOTAL_ROOMS];

//create and prpare room data
void initializeRooms();

//show room types
void showRoomTypes();

//print room information
void displayRooms();

//booking of room
void bookRoom();

//show available rooms
void checkAvailability();

//cancel the reservation
void cancelReservation();

//check - in the room when customer arrive
void checkIn();

//check - out the customer and make the room available again
void checkOut();

//Display details of booked rooms
void displayBookingDetails();

//save the records to .txt file
void saveRecords();

//load previously stored data
void loadRecords();







int menu()
{
    int choice;

    printf("\n=======WELCOME=======\n");
    printf("1.Display Rooms\n");
    printf("2.Book Room\n");
    printf("3.Check Availability\n");
    printf("4.Cancel Reservation\n");
    printf("5.Check In\n");
    printf("6.Check Out\n");
    printf("7.Display Booking Details\n");
    printf("8.Exit\n");
    

    printf("Enter your choice:");
    scanf("%d",&choice);

    return choice;
}






int main(){
        int choice;

        

        initializeRooms();

        

        //load previously saved data
        loadRecords();

        
        

        while(1)
        {
            choice=menu();

            switch(choice)
            {
                case 1:
                displayRooms();
                break;

            case 2:
                bookRoom();
                break;

            case 3:
                checkAvailability();
                break;

            case 4:
                cancelReservation();
                break;

            case 5:
                checkIn();
                break;

            case 6:
                checkOut();
                break;

            case 7:
                displayBookingDetails();
                break;

            case 8:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        
            }
        }
}


//initialize hotel information
void initializeRooms(){
    for(int i=0;i<TOTAL_ROOMS;i++){
        hotel[i].roomNo=101+i;
        hotel[i].booked=0;
        hotel[i].checkedIn=0;
        hotel[i].days=0;

    
        strcpy(hotel[i].customerName,"");
        strcpy(hotel[i].phone,"");

        if(i>=0 && i<=2)
        {
            strcpy(hotel[i].roomType,"Standard");
            hotel[i].price=3000;
        }
        else if(i>=3 && i<=5)
        {
            strcpy(hotel[i].roomType,"Deluxe");
            hotel[i].price=5500;
        }
        else if(i>=6 && i<=8)
        {
            strcpy(hotel[i].roomType,"Suite");
            hotel[i].price=7500;
        }
        else
        {
            strcpy(hotel[i].roomType,"VIP_Suite");
            hotel[i].price=10500;
        }
    }
}




//Display hotel room info
void displayRooms()
{
    int i;

    printf("\n---------------------------------------------------------------\n");
    printf("Room No   \tType\t    \tPrice    \tStatus\n");     //prints the table heading
    printf("---------------------------------------------------------------\n");

    for(i=0;i<TOTAL_ROOMS;i++){
        printf("%-8d\t",hotel[i].roomNo);
        printf("%-15s\t",hotel[i].roomType);
        printf("%-8d\t",hotel[i].price);

        if(hotel[i].booked==0)
        {
            printf("AVAILABLE!");
        }
        else {
            printf("BOOKED!");
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------\n");
}


//displat types of room - within bookRoom() function
void showRoomTypes(){
    printf("\n========ROOM TYPES=========\n");
    printf("1. Standard   -   3000/night\n");
    printf("2. Deluxe     -   5500/night\n");
    printf("3. Suite      -   7500/night\n");
    printf("4. VIP_Suite  -   10500/night\n");

}


//Room booking
void bookRoom()
{
   int choice;

   printf("=====BOOK ROOM=====");
    
   //show available room category
   showRoomTypes();

   //room choice by customer
   printf("Enter your choice:");
   scanf("%d",&choice);

   //check what the customer selected 
    if (choice==1)
    {
        printf("\nYou have selected STANDARD room.\n");
    }
    else  if (choice==2)
    {
        printf("\nYou have selected DELUXE room.\n");
    }
    else  if (choice==3)
    {
        printf("\nYou have selected SUITE room.\n");
    }
    else  if (choice==4)
    {
        printf("\nYou have selected VIP SUITE room.\n");
    }
    else
    {
        printf("INVALID CHOICE.\n");
        return;
    }




    //storing customer selected room type in selectedType variable

    char selectedType[20];

    if(choice==1)
    {
        strcpy(selectedType,"Standard");
    }

    else if(choice==2)
    {
        strcpy(selectedType,"Deluxe");
    }

    else if(choice==3)
    {
        strcpy(selectedType,"Suite");
    }

    else if(choice==4)
    {
        strcpy(selectedType,"VIP_Suite");
    }

    else
    {
       printf("INVALID INPUT!!\n");
       return;
    }


    //now room finding process 
    int roomfound=-1;       //not found yet so -1 when finded it will assign that value

    for(int i=0;i < TOTAL_ROOMS;i++)
    {
        if(strcmp(hotel[i].roomType,selectedType)==0 &&
            hotel[i].booked==0)
            {
                roomfound=i;
                break;
            }
    }


    if(roomfound==-1)
    {
        printf("\n Sorry! No %s rooms are available .\n",selectedType);
        return;
    }
   
    printf("\nRoom Found!\n");
    printf("Room Number : %d\n", hotel[roomfound].roomNo);
    printf("Room Type   : %s\n", hotel[roomfound].roomType);
    printf("Price       : %d\n", hotel[roomfound].price);

   



        printf("\nEnter customer name(without space):\n");
        scanf("%s",hotel[roomfound].customerName);

        printf("\nEnter phone no.:\n");
        scanf("%s",hotel[roomfound].phone);

        printf("\nEnter No. of days:\n");
        scanf("%d",&hotel[roomfound].days);

        hotel[roomfound].booked=1;


        //Bill calculation
        int totalBill;

        totalBill=hotel[roomfound].price * hotel[roomfound].days;


        saveRecords();                  //save data



        printf("\n=============================\n");
        printf("Booking successful!!\n");
        printf("1.Room No.    : %d\n",hotel[roomfound].roomNo);
        printf("2.Customer    : %s\n",hotel[roomfound].customerName);
        printf("3.Phone       : %s\n",hotel[roomfound].phone);
        printf("4.Days        : %d\n",hotel[roomfound].days);
        printf("Total Bill    : %d\n",totalBill);
        printf("\n=============================\n");

        }
        

//check availability = diplay available brooms only
void checkAvailability()
{
    int found=0;


    printf("\n=========AVAILABLE ROOMS==========\n");
    printf("--------------------------------------\n");
    printf("%-10s %-15s %-10s\n", "Room No.", "Type", "Price");                                      //Room no.\t\tType\t\tPrice
    printf("--------------------------------------\n");

    for(int i=0;i < TOTAL_ROOMS;i++)
    {
        if(hotel[i].booked==0)
        {
            printf("%-10d  %-15s  %-8d\n",
            hotel[i].roomNo,
            hotel[i].roomType,
            hotel[i].price);

        found = 1;
            
        }
        
    }

     if ( found == 0)
        {
            printf("\n No rooms are available.\n");
        }


}



//Cancel the reservation
void cancelReservation()
{
    int roomNo;
    int found = 0;

    printf("\n===== CANCEL RESERVATION =====\n");

    printf("Enter Room No.( 101 - 110) :");
    scanf("%d",&roomNo);

     for(int i = 0; i < TOTAL_ROOMS; i++)
     {
        if(hotel[i].roomNo == roomNo)
        {
            found = 1;

            if(hotel[i].booked == 1)
            {

            
            hotel[i].booked = 0;
            hotel[i].checkedIn = 0;
            hotel[i].days = 0;

            strcpy(hotel[i].customerName,"");
            strcpy(hotel[i].phone,"");

            
            saveRecords();                      //save record in .txt file

            printf("\nReservation Cancelled Successfully!\n");

            }

            else {
                printf("\nThis room is not booked yet!!");
                }

             break;
     }
}
    if (found == 0)
    {
        printf("\nInvalid Room Number!\n");
    }

}


//check - in the room when customer arrive
void checkIn()
{
    int roomNo;
    int found = 0;

    printf("\n===== CHECK IN =====\n");

    printf("Enter Room Number (101 - 110): ");
    scanf("%d", &roomNo);

    for(int i=0;i < TOTAL_ROOMS;i++)
    {
        if(hotel[i].roomNo == roomNo)
        {
            found = 1;

            if(hotel[i].booked==0)
            {
                printf("\nRoom is not booked yet!!\n");
            }

            else if (hotel[i].checkedIn==1)
            {
                 printf("\nCustomer has already checked In!!\n");
            }

            else
            {
                hotel[i].checkedIn=1;


                saveRecords();                  //save data

                 printf("\nChecked In Successful\n");
                 printf("Room No.   :%d\n",hotel[i].roomNo);
                 printf("Customer   :%s\n",hotel[i].customerName);

            }
            break;
        }
    }
        if ( found == 0)
        {
            printf("\nINVALID ROOM NO> !!\n");
        }
}


//check out the customer and make room available again
void checkOut()
{
    int roomNo;
    int found = 0;

    printf("\n========CHECK-OUT=========\n");
    printf("\nEnter room no. (101 - 110)\n");
    scanf("%d",&roomNo);

    for(int i=0;i < TOTAL_ROOMS;i++)
    {
        if(hotel[i].roomNo == roomNo)
        {
            found = 1;
            
            if(hotel[i].booked==0)
            {
                printf("\nRoom has been not booked yet!!\n");
            }

            else if (hotel[i].checkedIn==0)
            {
                printf("\nThe customer has not been checked-In yet!!\n");
            }

            else
            {
                printf("\n======== BILL DETAILS ============\n)");
                printf("Customer name   :%s\n",hotel[i].customerName);
                printf("Room No.        :%d\n",hotel[i].roomNo);
                printf("TOTAL BILL      :%d\n",hotel[i].days * hotel[i].price);

                //making room available again by removing data
                hotel[i].booked = 0;
                hotel[i].checkedIn = 0;
                hotel[i].days = 0;

                strcpy(hotel[i].customerName,"");
                strcpy(hotel[i].phone,"");


                saveRecords();                            //save data

                
                printf("\nCheck out successful!!\n");
                printf("\nRoom is now available!!\n");


            }
            break;
        }
    }

        if (found == 0)
        {
            printf("\nINVALID ROOM !!\n");
        }
    
}


//Display details of booked rooms
void displayBookingDetails()
{
    int roomNo;
    int found = 0;

    printf("\n===== BOOKING DETAILS =====\n");

    printf("Enter Room Number (101-110): ");
    scanf("%d", &roomNo);

    for(int i=0;i < TOTAL_ROOMS;i++)
    {
        if(hotel[i].roomNo == roomNo)
        {
            found = 1;

            if(hotel[i].booked==0)
            {
                printf("\nThis room is not booked.\n");
            }

            else
            {
                printf("\n ========= BOOKING DETAILS =========\n");
                printf("Room No.        :%d\n",hotel[i].roomNo);
                printf("Room Type       :%s\n",hotel[i].roomType);
                printf("Customer Name   :%s\n",hotel[i].customerName);
                printf("Phone No.       :%s\n",hotel[i].phone);
                printf("Days            :%d\n",hotel[i].days);
                printf("Price/night     :%d\n",hotel[i].price);


                if(hotel[i].checkedIn==1)
                    printf("\nStatus        :Checked-In\n");

                else
                    printf("\nStatus        :Booked(not checked-In)\n");
                

            }
            break;
        }
    }

    if(found == 0)
    {
        printf("\nINVALID ROOM NO.\n");
    }

}


//save the records to .txt file 2 forms
//Beautiful in - hotelrecords.txt (tabular format - good display)
//for load recors - hoteldata.txt ( one detail in one line - for sync with the format of loadrecords())

void saveRecords()
{
    FILE *fp1, *fp2;

    //Beautiful report file
    fp1 = fopen("hotelrecords.txt", "w");

    //Program data file
    fp2 = fopen("hoteldata.txt", "w");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("File cannot be opened!!\n");
        return;
    }

    fprintf(fp1,"=========================================\n");
    fprintf(fp1,"      HOTEL RESERVATION RECORDS\n");
    fprintf(fp1,"=========================================\n\n");

    for(int i=0; i<TOTAL_ROOMS; i++)
    {
        // ---------- Beautiful Report ----------

        fprintf(fp1,"Room No.        : %d\n",hotel[i].roomNo);
        fprintf(fp1,"Room Type       : %s\n",hotel[i].roomType);
        fprintf(fp1,"Price           : %d\n",hotel[i].price);
        fprintf(fp1,"Booked          : %d\n",hotel[i].booked);
        fprintf(fp1,"Checked In      : %d\n",hotel[i].checkedIn);
        fprintf(fp1,"Customer Name   : %s\n",hotel[i].customerName);
        fprintf(fp1,"Phone           : %s\n",hotel[i].phone);
        fprintf(fp1,"Days            : %d\n",hotel[i].days);
        fprintf(fp1,"----------------------------\n");


        // ---------- Program Data ----------

       if(hotel[i].booked==0)
{
    fprintf(fp2,"%d %s %d %d %d NONE NONE %d\n",
            hotel[i].roomNo,
            hotel[i].roomType,
            hotel[i].price,
            hotel[i].booked,
            hotel[i].checkedIn,
            hotel[i].days);
}
else
{
    fprintf(fp2,"%d %s %d %d %d %s %s %d\n",
            hotel[i].roomNo,
            hotel[i].roomType,
            hotel[i].price,
            hotel[i].booked,
            hotel[i].checkedIn,
            hotel[i].customerName,
            hotel[i].phone,
            hotel[i].days);
}

    fclose(fp1);
    fclose(fp2);

    printf("\nRecords Saved Successfully!\n");
}



//Load previously saved data
    
void loadRecords()
{

    printf("loadRecords() function called.\n");

    FILE *fp;

    fp = fopen("hoteldata.txt","r");

    if(fp == NULL)
    {
        
        return;
    }

    

    for(int i=0;i<TOTAL_ROOMS;i++)
    {
        fscanf(fp,"%d %s %d %d %d %s %s %d",
               &hotel[i].roomNo,
               hotel[i].roomType,
               &hotel[i].price,
               &hotel[i].booked,
               &hotel[i].checkedIn,
               hotel[i].customerName,
               hotel[i].phone,
               &hotel[i].days);

               //%d - integer(& required)
               //%s - string(& not required)
    }

    fclose(fp);
}
