#include "files.h"
#include <iostream>

using namespace std;

void fileOpen(ifstream &read) {
    char filename[60] = {};
    cout << "\nEnter file name to open: ";
    cin >> filename;
    read.open(filename);

    if (!read) {
        throw EXCEPTION_CODE::openError;
    }
}

void fileCreate(ofstream& write) {
    char filename[60] = {};
    cout << "\nEnter file name to save: ";
    cin >> filename;
    write.open(filename);
    if (!write) {
        cout << "\nUnable to save to file." << endl;
        exit(0);
    }
}

void seeExceptions(EXCEPTION_CODE error) {
    switch (error) {
        case EXCEPTION_CODE::openError:
            cerr << "\n Błąd otwarcia pliku z dysku";
            break;
        case EXCEPTION_CODE::readError:
            cerr << "\n Błąd odczytu pliku";
            break;
        case EXCEPTION_CODE::lackOfMemory:
            cerr << "\n Problem z pamięcią";
            break;
    }
}
