#include<iostream>
#include<string.h>
#include<fstream>
#define MAX 100
using namespace std;

// Abstract base class for Room
class RoomBase {
public:
    virtual void addRoom(int rno) = 0;
    virtual void searchRoom(int rno) = 0;
    virtual void deleteRoom(int rno) = 0;
    virtual void displayRoom() = 0;
};

// Class Customer
class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

// Class Room
class Room : public RoomBase {
private:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

public:
    void addRoom(int rno) override;
    void searchRoom(int rno) override;
    void deleteRoom(int rno) override;
    void displayRoom() override;

    // Getter and setter methods
    int getRoomNumber() 
	{ return roomNumber; }
    int getStatus()
	 { return status; }
    void setStatus(int status) 
	{ this->status = status; }
    Customer& getCustomer() 
	{ return cust; }
    int getRent() 
	{ return rent; } // Added getter for rent
};

// Global Declarations
Room rooms[MAX];
int count = 0;

void Room::addRoom(int rno) {
		fstream f;
	f.open("E:AddedRooms_file.txt",ios::app);
if(f.is_open())
{

    roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> ac;
    cout << "\nType Comfort (S/N) : ";
    cin >> type;
    cout << "\nType Size (B/S) : ";
    cin >> stype;
    cout << "\nDaily Rent : ";
    cin >> rent;
    f <<ac<<"\t"<<type<<"\t"<<stype<<"\t"<<rent<<"\t"<<rno<<"\t"<<"\n";
    status = 0;

    cout << "\nRoom Added Successfully!";
    }
else
{
cout<<"File is not found";}
f.close();

}

void Room::searchRoom(int rno) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].getRoomNumber() == rno) {
            found = 1;
            cout << "Room Details\n";
            if (rooms[i].getStatus() == 1) {
                cout << "\nRoom is Reserved";
            } else {
                cout << "\nRoom is available";
            }
            rooms[i].displayRoom();
            break;
        }
    }
    if (!found) {
        cout << "\nRoom not found";
    }
}

void Room::displayRoom() {
    cout << "\nRoom Number: \t" << roomNumber;
    cout << "\nType AC/Non-AC (A/N): " << ac;
    cout << "\nType Comfort (S/N): " << type;
    cout << "\nType Size (B/S): " << stype;
    cout << "\nRent: " << rent;
}

void Room::deleteRoom(int rno) {
    // Implement deletion logic if needed
}

// Hotel management class
class HotelMgnt : public Room {
public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(char* pname);
    void checkOut(int roomNum);
    void guestSummaryReport();
};

void HotelMgnt::guestSummaryReport() {
    if (count == 0) {
        cout << "\n No Guest in Hotel !!";
    }
    for (int i = 0; i < count; i++) {
        if (rooms[i].getStatus() == 1) {
            cout << "\nCustomer First Name: " << rooms[i].getCustomer().name;
            cout << "\nRoom Number: " << rooms[i].getRoomNumber();
            cout << "\nAddress (only city): " << rooms[i].getCustomer().address;
            cout << "\nPhone: " << rooms[i].getCustomer().phone;
            cout << "\n---------------------------------------";
        }
    }
}

void HotelMgnt::checkIn() {
    int rno, found = 0;

    cout << "\nEnter Room number: ";
    cin >> rno;
    for (int i = 0; i < count; i++) {
        if (rooms[i].getRoomNumber() == rno) {
            found = 1;
            if (rooms[i].getStatus() == 1) {
                cout << "\nRoom is already Booked";
                return;
            }

            cout << "\nEnter booking id: ";
            cin >> rooms[i].getCustomer().booking_id;

            cout << "\nEnter Customer Name (First Name): ";
            cin >> rooms[i].getCustomer().name;

            cout << "\nEnter Address (only city): ";
            cin >> rooms[i].getCustomer().address;

            cout << "\nEnter Phone: ";
            cin >> rooms[i].getCustomer().phone;

            cout << "\nEnter From Date: ";
            cin >> rooms[i].getCustomer().from_date;

            cout << "\nEnter to Date: ";
            cin >> rooms[i].getCustomer().to_date;

            cout << "\nEnter Advance Payment: ";
            cin >> rooms[i].getCustomer().payment_advance;

            rooms[i].setStatus(1);

            cout << "\nCustomer Checked-in Successfully..";
            break;
        }
    }
    if (!found) {
        cout << "\nRoom not found";
    }
}

void HotelMgnt::getAvailRoom() {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].getStatus() == 0) {
            rooms[i].displayRoom();
            cout << "\n\nPress enter for next room";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nAll rooms are reserved";
    }
}

void HotelMgnt::searchCustomer(char* pname) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].getStatus() == 1 && strcmp(rooms[i].getCustomer().name, pname) == 0) {
            cout << "\nCustomer Name: " << rooms[i].getCustomer().name;
            cout << "\nRoom Number: " << rooms[i].getRoomNumber();

            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nPerson not found.\n";
    }
}

void HotelMgnt::checkOut(int roomNum) {
    int found = 0, days;
    float billAmount = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].getStatus() == 1 && rooms[i].getRoomNumber() == roomNum) {
            found = 1;
            cout << "\nEnter Number of Days:\t";
            cin >> days;
            billAmount = days * rooms[i].getRent();

            cout << "\n\t######## CheckOut Details ########\n";
            cout << "\nCustomer Name : " << rooms[i].getCustomer().name;
            cout << "\nRoom Number : " << rooms[i].getRoomNumber();
            cout << "\nAddress : " << rooms[i].getCustomer().address;
            cout << "\nPhone : " << rooms[i].getCustomer().phone;
            cout << "\nTotal Amount Due : " << billAmount << " /";
            cout << "\nAdvance Paid: " << rooms[i].getCustomer().payment_advance << " /";
            cout << "\n*** Total Payable: " << billAmount - rooms[i].getCustomer().payment_advance << "/ only";

            rooms[i].setStatus(0);
            break;
        }
    }
    if (!found) {
        cout << "\nRoom not found";
    }
}

void manageRooms() {
    Room room;
    int opt, rno, flag = 0;

    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
        case 1:
            cout << "\nEnter Room Number: ";
            cin >> rno;
            for (int i = 0; i < count; i++) {
                if (rooms[i].getRoomNumber() == rno) {
                    flag = 1;
                }
            }
            if (flag == 1) {
                cout << "\nRoom Number is Present.\nPlease enter unique Number";
                flag = 0;
            } else {
                rooms[count].addRoom(rno);
                count++;
            }
            break;
        case 2:
            cout << "\nEnter room number: ";
            cin >> rno;
            room.searchRoom(rno);
            break;
        case 3:
            // nothing to do
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 3);
}

int main() {
    HotelMgnt hm;
    int opt, rno;
    char pname[100];

    do {
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Customer";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
        case 1:
            manageRooms();
            break;
        case 2:
            if (count == 0) {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            } else {
                hm.checkIn();
            }
            break;
        case 3:
            if (count == 0) {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            } else {
                hm.getAvailRoom();
            }
            break;
        case 4:
            if (count == 0) {
                cout << "\nRooms are not available.\nPlease add the rooms first.";
            } else {
                cout << "Enter Customer Name: ";
                cin >> pname;
                hm.searchCustomer(pname);
            }
            break;
        case 5:
            if (count == 0) {
                cout << "\nRooms are not available.\nPlease add the rooms first.";
            } else {
                cout << "Enter Room Number : ";
                cin >> rno;
                hm.checkOut(rno);
            }
            break;
        case 6:
            hm.guestSummaryReport();
            break;
        case 7:
            cout << "\nTHANK YOU! FOR USING SOFTWARE\n";
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 7);

    return 0;
}

