#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <random>
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



};

int main() {

    return 0;
}
