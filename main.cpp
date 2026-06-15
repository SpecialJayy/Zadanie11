#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <random>
#include <string>
#include "libs/files.h"

using namespace std;

class cTablica {
private:
    vector<int> data;
public:
    cTablica() {}

    void setData(vector<int>& newData) {
        data = newData;
    }

    vector<int> getData() {
        return data;
    }

    void bubbleSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        if (data.empty()) return;

        int n = data.size();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                compares++;
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                    swaps++;
                }
            }
        }

    }

    void shakerSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        if (data.empty()) return;

        int start = 0;
        int end = data.size() - 1;

        while (start < end) {
            for (int i = start; i < end; i++) {
                compares++;
                if (data[i] > data[i + 1]) {
                    swap(data[i], data[i + 1]);
                    swaps++;
                }
            }
            end--;

            for (int i = end - 1; i >= start; i--) {
                compares++;
                if (data[i] > data[i + 1]) {
                    swap(data[i], data[i + 1]);
                    swaps++;
                }
            }
            start++;
        }
    }

    int lomutoSort(int low, int high, long long &compares, long long &swaps) {
        // pivot na koncu
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

    void heapSortInner(int n, int i, long long &compares, long long &swaps) {
        // zakladamy ze aktualny wezel to maksimum
        int biggest = i;

        // indeksy dzieci ze wzoru na drzewo binarne
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // weryfikacja czy lewe dziecko nie wychodzi poza zakres kopca
        if (left < n) {
            compares++;
            // sprawdzenie czy dziecko zaburza wlasnosc max-heap
            if (data[left] > data[biggest]) {
                // aktualizacja kandydata na szczyt
                biggest = left;
            }
        }

        // to samo dla prawej galezi
        if (right < n) {
            compares++;
            if (data[right] > data[biggest]) {
                biggest = right;
            }
        }

        // jesli znalezlismy wieksze dziecko niz ojciec
        if (biggest != i) {
            // wpychamy mniejszy element nizej
            swap(data[i], data[biggest]);
            swaps++;
            // rekurencyjna naprawa zepsutego poddrzewa, zeby znowu byl to max-heap
            heapSortInner(n, biggest, compares, swaps);
        }
    }

    void heapSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        int n = data.size();

        // start od najnizszego poziomu wezlow posiadajacych dzieci
        for (int i = n / 2 - 1; i >= 0; i--) {
            // przeksztalcenie surowej tablicy w strukture kopca
            heapSortInner(n, i, compares, swaps);
        }

        // petla odcinajaca posortowane juz elementy z konca tablicy
        for (int i = n - 1; i > 0; i--) {
            // eksmisja aktualnego najwiekszego elementu na ostateczna pozycje
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
    void keyboardInput() {
        int n;
        cout << "Podaj liczbę elementow tablicy: ";
        if (!(cin >> n)) {
            cin.clear();
            cin.ignore();
            throw "blad";
        }

        if (n <= 0) {
            throw "blad";
        }

        vector<int> temp(n);
        cout << "Podaj elementy:" << endl;
        for (int i = 0; i < n; i++) {
            if (!(cin >> temp[i])) {
                cin.clear();
                cin.ignore();
                throw "blad";
            }
        }
        obj.setData(temp);
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
            case 2:
                for (int i = 0; i < length; i++) {
                    v[i] = i;
                }
                break;
            case 3:
                for (int i = 0; i < length; i++) {
                    v[i] = length - i;
                }
                break;
            case 4:
                for (int i = 0; i < length; i++) {
                    v[i] = i;
                }
                for (int i = 0; i < length * 0.05; i++) {
                    int idx1 = rand() % length;
                    int idx2 = rand() % length;
                    swap(v[idx1], v[idx2]);
                }
                break;
        }
        return v;
    }

    void generateOutputFiles() {
        ofstream file;
        fileCreate(file);

        file << left << setw(25) << "Nazwa metody"
             << setw(18) << "Długosc tablicy"
             << setw(35) << "Rodzaj tablicy"
             << setw(20) << "Liczba porownan"
             << setw(20) << "Liczba przestawien" << endl;
        file << string(118, '-') << endl;

        int lengths[] = {100, 1000, 10000};
        int types[] = {1, 2, 3, 4};
        string typesNames[] = {"Losowe", "Posortowane rosnąco", "Posortowane malejąco", "Czesciowo posortowane (90%)"};
        string sorts[] = {"Bubble Sort", "Shaker Sort", "Quick Sort (Lomuto)", "Quick Sort (Hoare)", "Heap Sort"};

        for (int l : lengths) {
            for (int t : types) {
                vector<int> baseData = generateData(l, t);

                for (string& s : sorts) {

                    if ((s == "Bubble Sort" || s == "Shaker Sort") && l == 1000000) {
                        file << left << setw(25) << s
                             << setw(18) << l
                             << setw(35) << typesNames[t - 1]
                             << setw(20) << "Pominieto (O(N^2))"
                             << setw(20) << "Pominieto (O(N^2))" << endl;
                        continue;
                    }

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
        file << endl << "WNIOSKI:" << endl;
        file << "1." << endl;
        file << "2." << endl;
        file << "3." << endl;
        cout << "Tabela i wnioski zapisane" << endl;
        file.close();
    }
};

int main() {

    cSortTablicy c;
    int choice = 0;

    while (choice != 3) {
        cout << "1. Wprowadz dane z klawiatury" << endl;
        cout << "2. Wygeneruj dane" << endl;
        cout << "3. Wyjdz" << endl;
        cout << "Twoj wybor: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "Bład, sprobuj ponownie" << endl;
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    c.keyboardInput();
                    break;
                case 2:
                    c.generateOutputFiles();
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
