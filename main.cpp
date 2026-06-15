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

    //CZY MA BYC TEN SWAPPED BREAK?? chyba nie..

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
        int middle = low + (high -low) / 2;
        swap(data[middle], data[high]);
        compares++;

        double pivot = data[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            compares++;
            if (data[j] < pivot) {
                i++;
                swap(data[i], data[j]);
                swaps++;
            }
        }
        swap(data[i + 1], data[high]);
        swaps++;
        return i + 1;
    }

    void lomutoSortInner(int low, int high, long long &compares, long long &swaps) {
        if (low < high) {
            int p = lomutoSort(low, high, compares, swaps);
            lomutoSortInner(low, p - 1, compares, swaps);
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
        int middle = low + (high -low) / 2;
        double pivot = data[middle];
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do {
                i++;
                compares++;
            } while (data[i] < pivot);

            do {
                j--;
                compares++;
            } while (data[j] > pivot);

            if (i >= j) return j;

            swap(data[i], data[j]);
            swaps++;
        }
    }

    void hoareSortInner(int low, int high, long long &compares, long long &swaps) {
        if (low < high) {
            int p = hoareSort(low, high, compares, swaps);
            hoareSortInner(low, p, compares, swaps);
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
        int biggest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n) {
            compares++;
            if (data[left] > data[biggest]) {
                biggest = left;
            }
        }

        if (right < n) {
            compares++;
            if (data[right] > data[biggest]) {
                biggest = right;
            }
        }

        if (biggest != i) {
            swap(data[i], data[biggest]);
            swaps++;
            heapSortInner(n, biggest, compares, swaps);
        }
    }

    void heapSort(long long &compares, long long &swaps) {
        compares = 0;
        swaps = 0;
        int n = data.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapSortInner(n, i, compares, swaps);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(data[0], data[i]);
            swaps++;
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
        cout << "Podaj liczbę elementów tablicy: ";
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
