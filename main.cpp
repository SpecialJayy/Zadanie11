#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <random>
#include <string>

#include "libs/exceptions.h"
#include "libs/files.h"

using namespace std;

class cTablica {
private:
    vector<int> data;
public:
    //domyślny konstruktor
    cTablica() {}

    void setData(vector<int>& newData) {
        data = newData;
    }

    vector<int> getData() {
        return data;
    }

    /**
     * @brief podstawowe sortowanie bąbelkowe
     * @param compares liczba porównań
     * @param swaps liczba przestawień
     */
    void bubbleSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        if (data.empty()) return;

        int n = data.size();
        // flaga optymalizacji
        bool swapped;

        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                compares++;
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                    swaps++;
                    // oznacz zamiane
                    swapped = true;
                }
            }
            // jesli bez zamian to przerwij
            if (!swapped) break;
        }
    }

    /**
    * @brief sortowanie bąbelkowe wahadłowe
     * @param compares liczba porównań
     * @param swaps liczba przestawień
     */
    void shakerSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        if (data.empty()) return;

        int start = 0;
        int end = data.size() - 1;
        // flaga startowa
        bool swapped = true;

        while (swapped && start < end) {
            // reset flagi przed przebiegiem
            swapped = false;

            // przebieg w prawo
            for (int i = start; i < end; i++) {
                compares++;
                if (data[i] > data[i + 1]) {
                    swap(data[i], data[i + 1]);
                    swaps++;
                    swapped = true;
                }
            }

            // czy bylo juz sort
            if (!swapped) break;

            end--;

            swapped = false;

            // przebieg w lewo
            for (int i = end - 1; i >= start; i--) {
                compares++;
                if (data[i] > data[i + 1]) {
                    swap(data[i], data[i + 1]);
                    swaps++;
                    swapped = true;
                }
            }
            start++;
        }
    }

    int lomutoSort(int low, int high, long long &compares, long long &swaps) {
        int middle = low + (high -low) / 2;
        swap(data[middle], data[high]);
        compares++;

        double pivot = data[high];

        // granica mniejszych
        int i = low - 1;

        // skanowanie tablicy
        for (int j = low; j <= high - 1; j++) {
            compares++;

            if (data[j] < pivot) {
                // przesun granice
                i++;
                swap(data[i], data[j]);
                swaps++;
            }
        }

        // wstaw pivot
        swap(data[i + 1], data[high]);
        swaps++;

        // zwracamy indeks
        return i + 1;
    }

    void lomutoSortInner(int low, int high, long long &compares, long long &swaps) {
        // warunek stopu
        if (low < high) {
            // podzial lomuto
            int p = lomutoSort(low, high, compares, swaps);

            // sortuj lewo
            lomutoSortInner(low, p - 1, compares, swaps);

            // sortuj prawo
            lomutoSortInner(p + 1, high, compares, swaps);
        }
    }

    void runLomutoSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;

        if (!data.empty()) {
            lomutoSortInner(0, data.size() - 1, compares, swaps);
        }
    }

    int hoareSort(int low, int high, long long &compares, long long &swaps) {
        // srodek tablicy
        int middle = low + (high -low) / 2;
        double pivot = data[middle];

        // lewy wskaznik
        int i = low - 1;

        // prawy wskaznik
        int j = high + 1;

        while (true) {
            // szukaj wiekszego po lewej
            do {
                i++;
                compares++;
            } while (data[i] < pivot);

            // szukaj mniejszego po prawej
            do {
                j--;
                compares++;
            } while (data[j] > pivot);

            if (i >= j) return j;

            // zamiana elementow
            swap(data[i], data[j]);
            swaps++;
        }
    }

    void hoareSortInner(int low, int high, long long &compares, long long &swaps) {
        if (low < high) {
            int p = hoareSort(low, high, compares, swaps);
            // sortuj lewo
            hoareSortInner(low, p, compares, swaps);
            // sortuj prawo
            hoareSortInner(p + 1, high, compares, swaps);
        }
    }

    void runHoareSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        if (!data.empty()) {
            hoareSortInner(0, data.size() - 1, compares, swaps);
        }
    }

    /**
     * @brief buduje kopiec w drzewie binarnym
     * @param n rozmiar kopca
     * @param i indeks korzenia
     * @param compares liczba porównań
     * @param swaps liczba przestawień
     */
    void heapSortInner(int n, int i, long long &compares, long long &swaps) {
        // zakładamy, że aktualny węzeł to maksimum
        int biggest = i;

        // indeksy dzieci ze wzoru na drzewo binarne
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // weryfikacja czy lewe dziecko nie wychodzi poza zakres kopca
        if (left < n) {
            compares++;
            // sprawdzenie czy dziecko jest większe od aktualnego największego węzła
            if (data[left] > data[biggest]) {
                biggest = left;
            }
        }

        // to samo dla prawej gałęzi
        if (right < n) {
            compares++;
            if (data[right] > data[biggest]) {
                biggest = right;
            }
        }

        // jeśli któreś dziecko było większe od rodzica
        if (biggest != i) {
            //zamieniamy je miejscami
            swap(data[i], data[biggest]);
            swaps++;
            // po zamianie rekurencyjnie sprawdzamy czy poddrzewo dalej jest kopcem
            heapSortInner(n, biggest, compares, swaps);
        }
    }

    /**
     * @brief sortowanie kopcowe (heap sort)
     * @param compares liczba porównań
     * @param swaps liczba przestawień
     */
    void heapSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        int n = data.size();


        //budowa początkowego kopca
        // start od najniższego poziomu węzłów posiadających dzieci
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapSortInner(n, i, compares, swaps);
        }

        // petla odcinająca posortowane już elementy z końca tablicy
        for (int i = n - 1; i > 0; i--) {
            // przeniesienie aktualnie największego elementu na ostatnią pozycję w tablicy
            swap(data[0], data[i]);
            swaps++;
            // przywrocenie wlasnosci kopca dla pozostalej nieposortowanej czesci
            heapSortInner(i, 0, compares, swaps);
        }
    }
};

class cSortTablicy {
private:
    cTablica obj;
public:
    void keyboardInput(vector<int> &baseData) {
        int n;
        cout << "Podaj liczbę elementów tablicy: ";
        if (!(cin >> n)) {
            cin.clear();
            cin.ignore();
            throw WrongDataException("Błąd: niepoprawny format danych");
        }

        if (n <= 0) {
            throw ArraySizeException("Błąd: niepoprawny rozmiar");
        }

        vector<int> temp(n);
        cout << "Podaj elementy:" << endl;
        for (int i = 0; i < n; i++) {
            if (!(cin >> temp[i])) {
                cin.clear();
                cin.ignore();
                throw WrongDataException("Błąd: niepoprawny format danych");
            }
        }
        baseData = temp;
    }

    vector<int> generateData(int length, int type) {
        vector<int> v(length);

        random_device rd;

        mt19937 mt(rd());

        uniform_int_distribution<int> dis(-100000, 100000);

        //rózne warianty tablic
        switch (type) {
            //losowe
            case 1:
                for (int i = 0; i < length; i++) {
                    v[i] = dis(mt);
                }
                break;
            //posortowane rosnąco
            case 2:
                for (int i = 0; i < length; i++) {
                    v[i] = i;
                }
                break;
            //posortowane malejąco
            case 3:
                for (int i = 0; i < length; i++) {
                    v[i] = length - i;
                }
                break;
            //tablica posortowana w 90%
            case 4:
                for (int i = 0; i < length; i++) {
                    v[i] = i;
                }
                //używamy 5% długości tablicy co daje 10% swapów
                for (int i = 0; i < length * 0.05; i++) {
                    int idx1 = rand() % length;
                    int idx2 = rand() % length;
                    swap(v[idx1], v[idx2]);
                }
                break;
        }
        return v;
    }

    void generateOutputFiles(bool keyboard, vector<int> &baseData) {
        ofstream file;
        fileCreate(file);

        file << left << setw(25) << "Nazwa metody"
             << setw(18) << "Długość tablicy"
             << setw(35) << "Rodzaj tablicy"
             << setw(20) << "Liczba porównań"
             << setw(20) << "Liczba przestawień" << endl;
        file << string(118, '-') << endl;

        int lengths[] = {100, 1000, 1000000};
        int types[] = {1, 2, 3, 4};
        string typesNames[] = {"Losowe", "Posortowane rosnąco", "Posortowane malejąco", "Częściowo posortowane (90%)"};
        string sorts[] = {"Bubble Sort", "Shaker Sort", "Quick Sort (Lomuto)", "Quick Sort (Hoare)", "Heap Sort"};

        for (int l : lengths) {
            for (int t : types) {
                if (!keyboard) {
                    baseData = generateData(l, t);
                }

                for (string& s : sorts) {
                    obj.setData(baseData);
                    long long compares = 0;
                    long long swaps = 0;

                    if (s == "Bubble Sort") {
                        obj.bubbleSort(compares, swaps);
                    } else if (s == "Shaker Sort") {
                        obj.shakerSort(compares, swaps);
                    } else if (s == "Quick Sort (Lomuto)") {
                        obj.runLomutoSort(compares, swaps);
                    } else if (s == "Quick Sort (Hoare)") {
                        obj.runHoareSort(compares, swaps);
                    } else if (s == "Heap Sort") {
                        obj.heapSort(compares, swaps);
                    }

                    file << left << setw(25) << s
                         << setw(18) << l
                         << setw(35) << typesNames[t - 1]
                         << setw(20) << compares
                         << setw(20) << swaps << endl;
                }
                file << string(118, '-') << endl;
            }
        }
        cout << "Tabela zapisana" << endl;
        file.close();
    }
};

int main() {

    cSortTablicy c;
    int choice = 0;

    while (choice != 3) {
        cout << "1. Wprowadź dane z klawiatury" << endl;
        cout << "2. Wygeneruj dane" << endl;
        cout << "3. Wyjdź" << endl;
        cout << "Twój wybór: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "Błąd, spróbuj ponownie" << endl;
            continue;
        }

        try {
            vector<int> baseData;
            switch (choice) {
                case 1:
                    c.keyboardInput(baseData);
                    c.generateOutputFiles(true, baseData);
                    break;
                case 2:
                    c.generateOutputFiles(false, baseData);
                    break;
                case 3:
                    break;
                default:
                    cout << "Wybierz poprawna opcje" << endl;
            }
        } catch (exception& e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}
