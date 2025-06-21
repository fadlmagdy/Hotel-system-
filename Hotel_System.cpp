// فضل الله مجدى عبدالوهاب 20246081
// يوسف محمد شاكر خطيب 20246136
// احمد محمد ضهاب عطيه 20246009
#include <iostream>
#include <string>
using namespace std;

const int ROOM_CHARGE = 100;
long long NumOfGuests;

bool Search(const string *guestNames, int count, const string guestName) {
    for (int i = 0; i < count; i++) {
        if (guestNames[i] == guestName) {
            return true;
        }
    }
    return false;
}
void PrintNamesAsUpperCase(const string *GuestNames, int count) {
    for (int i = 0; i < count; ++i) {
        for (char c : GuestNames[i])
            cout << (char)toupper(c);
        cout << endl;
    }
}
void PrintBills(int NumOfGuests, string *GuestNames, int *NumOfServices, int **Quantity, int **Price) {
    for (int i = 0; i < NumOfGuests; ++i) {
        int serviceTotal = 0;
        for (int j = 0; j < NumOfServices[i]; ++j) {
            serviceTotal += Quantity[i][j] * Price[i][j];
        }
        cout << GuestNames[i] << " -> $" << (ROOM_CHARGE + serviceTotal) << endl;
    }
}
void printFirstNames(const string *GuestNames, int count) {
    for (int i = 0; i < count; ++i) {
        int pos = GuestNames[i].find(' ');
        cout << (pos != string::npos ? GuestNames[i].substr(0, pos) : GuestNames[i]) << endl;
    }
}
void FilterByPrefix(const string *GuestNames, int count, const string prefix) {
    for (int i = 0; i < count; ++i) {
        bool match = true;
        for (size_t j = 0; j < prefix.size(); ++j) {
            if (toupper(GuestNames[i][j]) != toupper(prefix[j])) {
                match = false;
                break;
            }
        }
        if (match) cout << GuestNames[i] << endl;
    }
}
void GuestNameByService(int *NumOfServices, string **ServiceNames, string *GuestNames, int NumOfGuests, string Servicename) {
    for (int i = 0; i < NumOfGuests; ++i) {
        for (int j = 0; j < NumOfServices[i]; ++j) {
            if (ServiceNames[i][j] == Servicename) {
                cout << GuestNames[i] << endl;
                break;
            }
        }
    }
}



int main() {
    cout << "Enter number of guests:\n";
    cin >> NumOfGuests;
    cin.ignore();

    string *GuestNames = new string[NumOfGuests];
    int *NumOfServices = new int[NumOfGuests];
    string **ServiceNames = new string*[NumOfGuests];
    int **Quantity = new int*[NumOfGuests];
    int **Price = new int*[NumOfGuests];


    for (int i = 0; i < NumOfGuests; ++i) {
        cout << "Enter Guest " << i+1 << " Name: ";
        getline(cin, GuestNames[i]);

        cout << "How many services did this guest use? ";
        cin >> NumOfServices[i];
        cin.ignore();

        ServiceNames[i] = new string[NumOfServices[i]];
        Quantity[i] = new int[NumOfServices[i]];
        Price[i] = new int[NumOfServices[i]];

        for (int j = 0; j < NumOfServices[i]; ++j) {
            cout << "Enter name, quantity and price of service " << j+1 << ": ";
            cin >> ServiceNames[i][j] >> Quantity[i][j] >> Price[i][j];
        }
        cin.ignore();
    }

    cout << "===== HOTEL MENU =====\n"
            "1. Display Guests Bills\n"
            "2. Print Names to UPPERCASE\n"
            "3. Search Guest by Name\n"
            "4. Filter Guests by Prefix.\n"
            "5. Print Guest First Name\n"
            "6. Print Guest Names that use Specific Service\n"
            "7. Exit\n";
    char choice;
    cin >> choice;
    cin.ignore();
    switch (choice) {
        case '1' :
            PrintBills(NumOfGuests, GuestNames, NumOfServices, Quantity, Price);
            break;
        case '2':
            PrintNamesAsUpperCase(GuestNames, NumOfGuests);
            break;
        case '3':{
            string name;
            cout << "Enter Name that you want to search for: ";
            getline(cin, name);
            cout << (Search(GuestNames, NumOfGuests, name) ? "Found" : "Not Found") << endl;
            break;}
        case '4': {
            string prefix;
            cout << "Enter Prefix: ";
            getline(cin, prefix);
            FilterByPrefix(GuestNames, NumOfGuests, prefix);
            break;}
        case '5':
            printFirstNames(GuestNames, NumOfGuests);
            break;
        case '6': {
            string service;
            cout << "Enter Service Name: ";
            getline(cin, service);
            GuestNameByService(NumOfServices, ServiceNames, GuestNames, NumOfGuests, service);
            break;}
        case '7':
            break;
    }
    for (int i = 0; i < NumOfGuests; ++i) {
        delete[] ServiceNames[i];
        delete[] Quantity[i];
        delete[] Price[i];
    }
    delete[] ServiceNames;
    delete[] Quantity;
    delete[] Price;
    delete[] GuestNames;
    delete[] NumOfServices;


return 0;
}