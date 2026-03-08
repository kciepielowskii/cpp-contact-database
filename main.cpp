#include <iostream>
using namespace std;

struct Contact {
    char firstName[20];
    char surname[20];
    long int telephoneNumber;
};

struct ContactDatabase {
    int currentNumberOfContacts;
    int maximumNumberOfContacts;
    Contact *registration;
};

int addRegistration(ContactDatabase *databasePointer, const Contact *registrationPointer) {
    if (databasePointer->currentNumberOfContacts == databasePointer->maximumNumberOfContacts) {
        int new_size = databasePointer->maximumNumberOfContacts + 10;
        auto *new_list = new Contact[new_size];

        for (int i = 0; i < databasePointer->currentNumberOfContacts; i++) {
            new_list[i] = databasePointer->registration[i];
        }
        delete[] databasePointer->registration;
        databasePointer->maximumNumberOfContacts = new_size;
        databasePointer->registration = new_list;
    }
    databasePointer->registration[databasePointer->currentNumberOfContacts] = *registrationPointer;
    databasePointer->currentNumberOfContacts++;
    return 0;
}

int deleteRegistration(ContactDatabase *databasePointer, int index) {
    if (index < 0 || index >= databasePointer->currentNumberOfContacts) {
        cout << "Index is out of range.\n";
        return -1;
    }
    for (int i = index; i < databasePointer->currentNumberOfContacts - 1; i++) {
        databasePointer->registration[i] = databasePointer->registration[i + 1];
    }
    databasePointer->currentNumberOfContacts--;
    return 0;
}

void writeDownAList(const ContactDatabase *databasePointer) {
    if (databasePointer->currentNumberOfContacts == 0) {
        cout << "\n[!] The contact list is empty." << endl;
        return;
    }

    cout << "\n--- CONTACT DATABASE (" << databasePointer->currentNumberOfContacts << ") ---" << endl;

    for (int i = 0; i < databasePointer->currentNumberOfContacts; i++) {
        const auto &contact = databasePointer->registration[i];

        cout << "Index: " << i << endl;
        cout << "Name:  " << contact.firstName << " " << contact.surname << endl;
        cout << "Phone: " << contact.telephoneNumber << endl;
        cout << "-------------------------------" << endl;
    }
}

int main() {
    ContactDatabase database = {};
    database.currentNumberOfContacts = 0;
    database.maximumNumberOfContacts = 10;
    database.registration = new Contact[database.maximumNumberOfContacts];

    Contact contactList[] = {
        {"Jack", "Smith", 657120387},
        {"Olivier", "Johnson", 457239100},
        {"Noah", "Lee", 859128472},
    };

    for (const auto &contact : contactList) {
        addRegistration(&database, &contact);
    }

    writeDownAList(&database);

    deleteRegistration(&database, 2);

    writeDownAList(&database);

    delete[] database.registration;

    return 0;
}