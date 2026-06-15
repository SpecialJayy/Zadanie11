#ifndef DWA_FILES_H
#define DWA_FILES_H

#include <fstream>

using namespace std;

enum class EXCEPTION_CODE {
    openError,
    readError,
    lackOfMemory,
};

/**
 * @brief pobiera od użytkownika ścieżkę do pliku i go otwiera
 * @param read referencja do strumienia wejściowego
 */
void fileOpen(ifstream& read);

/**
 * @brief pobiera od użytkownika nazwę pliku i go tworzy
 * @param write referencja do strumienia wyjściowego
 */
void fileCreate(ofstream& write);


//obsługa wyjątków
void seeExceptions(EXCEPTION_CODE error);

#endif //DWA_FILES_H