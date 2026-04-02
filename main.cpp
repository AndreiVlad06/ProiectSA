#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int *original = nullptr;
int *a = nullptr;
string tipLista = "";

void BubbleSort(int n, int arr[]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void InsertionSort(int n, int arr[]) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void SelectionSort(int n, int arr[]) {
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void ShellSort(int n, int arr[]) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void Merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSortHelper(int arr[], int l, int r) {
    if(l >= r) return;
    int m = l + (r - l) / 2;
    MergeSortHelper(arr, l, m);
    MergeSortHelper(arr, m + 1, r);
    Merge(arr, l, m, r);
}

void MergeSort(int n, int arr[]) {
    if(n > 0) MergeSortHelper(arr, 0, n - 1);
}

int Partition(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void QuickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSortHelper(arr, low, pi - 1);
        QuickSortHelper(arr, pi + 1, high);
    }
}

void QuickSort(int n, int arr[]) {
    if(n > 0) QuickSortHelper(arr, 0, n - 1);
}

void PopuleazaLista(int n, int tip) {
    if(tip == 1) tipLista = "Random";
    else if(tip == 2) tipLista = "Sortata";
    else if(tip == 3) tipLista = "Invers Sortata";
    else if(tip == 4) tipLista = "Aproape Sortata";
    else if(tip == 5) tipLista = "Plata";

    for(int i = 0; i < n; i++) {
        if(tip == 1) original[i] = rand();
        else if(tip == 2) original[i] = i;
        else if(tip == 3) original[i] = n - i;
        else if(tip == 4) original[i] = i;
        else if(tip == 5) original[i] = rand() % 10;
    }

    if(tip == 4) {
        int swaps = n * 0.05;
        if(swaps == 0) swaps = 1;
        for(int i = 0; i < swaps; i++) {
            swap(original[rand() % n], original[rand() % n]);
        }
    }
}

void GenereazaLista(int &n) {
    int tip;
    cout << "Introduceti numarul de elemente: ";
    cin >> n;

    while (cin.fail() || n <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input invalid. Introduceti un numar valid de elemente: ";
        cin >> n;
    }

    if (original) delete[] original;
    if (a) delete[] a;

    original = new int[n];
    a = new int[n];

    cout << endl << "Alege tipul de lista dorit:" << endl;
    cout << "1. Random\n2. Sortata\n3. Invers sortata\n4. Aproape sortata\n5. Plata (duplicate)\nOptiune: ";
    cin >> tip;

    while (cin.fail() || tip < 1 || tip > 5) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input invalid. Alegeti o optiune intre 1 si 5: ";
        cin >> tip;
    }

    PopuleazaLista(n, tip);
}

void RunAndMeasure(void (*SortFunc)(int, int[]), string name, int n) {
    for(int i = 0; i < n; i++) a[i] = original[i];

    auto start = high_resolution_clock::now();
    SortFunc(n, a);
    auto end = high_resolution_clock::now();

    duration<double, std::milli> diff = end - start;

    cout << left << setw(18) << name << " : " << fixed << setprecision(6) << diff.count() << " ms\n";

    ofstream fout("output.txt", ios::app);
    fout << name << " | N = " << n << " | Tip: " << tipLista << " | Timp: " << fixed << setprecision(6) << diff.count() << " ms | Sir initial: ";

    for(int i = 0; i < n; i++) {
        fout << original[i] << (i == n - 1 ? "" : ",");
    }
    fout << "\n";
    fout.close();
}

int main() {
    srand(time(0));
    int metoda;
    int n = 0;

    GenereazaLista(n);

    cout << "\nAu fost generate " << n << " numere.\n";

    bool ruleaza = true;
    while(ruleaza) {
        cout << "Alege metoda de sortare dorita:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Shell Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Toate Metodele Simultan\n";
        cout << "8. Testare cazuri generale (Automatizat)\n";
        cout << "9. Goleste fisierul de rezultate (output.txt)\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";

        cin >> metoda;

        while (cin.fail() || metoda < 0 || metoda > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input invalid. Alegeti o optiune intre 0 si 9: ";
            cin >> metoda;
        }

        cout << endl;

        switch(metoda) {
            case 1:
                RunAndMeasure(BubbleSort, "Bubble Sort", n);
                ruleaza = false;
                break;
            case 2:
                RunAndMeasure(InsertionSort, "Insertion Sort", n);
                ruleaza = false;
                break;
            case 3:
                RunAndMeasure(SelectionSort, "Selection Sort", n);
                ruleaza = false;
                break;
            case 4:
                RunAndMeasure(ShellSort, "Shell Sort", n);
                ruleaza = false;
                break;
            case 5:
                RunAndMeasure(MergeSort, "Merge Sort", n);
                ruleaza = false;
                break;
            case 6:
                RunAndMeasure(QuickSort, "Quick Sort", n);
                ruleaza = false;
                break;
            case 7:
                RunAndMeasure(BubbleSort, "Bubble Sort", n);
                RunAndMeasure(InsertionSort, "Insertion Sort", n);
                RunAndMeasure(SelectionSort, "Selection Sort", n);
                RunAndMeasure(ShellSort, "Shell Sort", n);
                RunAndMeasure(MergeSort, "Merge Sort", n);
                RunAndMeasure(QuickSort, "Quick Sort", n);
                ruleaza = false;
                break;
            case 8:
                {
                    ofstream fout("output.txt", ios::trunc);
                    fout.close();

                    cout << "Incepem testarea automata...\n\n";
                    int current_n = n;
                    if (current_n < 10) current_n = 10;

                    while (true) {
                        delete[] original;
                        delete[] a;
                        original = new int[current_n];
                        a = new int[current_n];

                        for(int current_tip = 1; current_tip <= 5; current_tip++) {
                            PopuleazaLista(current_n, current_tip);
                            cout << "--- N = " << current_n << " | " << tipLista << " ---\n";
                            RunAndMeasure(BubbleSort, "Bubble Sort", current_n);
                            RunAndMeasure(InsertionSort, "Insertion Sort", current_n);
                            RunAndMeasure(SelectionSort, "Selection Sort", current_n);
                            RunAndMeasure(ShellSort, "Shell Sort", current_n);
                            RunAndMeasure(MergeSort, "Merge Sort", current_n);
                            RunAndMeasure(QuickSort, "Quick Sort", current_n);
                            cout << "\n";
                        }

                        if (current_n == 10) break;
                        current_n /= 10;
                        if (current_n < 10) current_n = 10;
                    }
                    ruleaza = false;
                }
                break;
            case 9:
                {
                    ofstream fout("output.txt", ios::trunc);
                    fout.close();
                    cout << "Fisierul output.txt a fost golit.\n";
                }
                break;
            case 0:
                ruleaza = false;
                break;
        }
    }

    if (original) delete[] original;
    if (a) delete[] a;

    if (metoda != 0 && metoda != 9) cout << "Datele complete (inclusiv sirurile nesortate) sunt in output.txt\n";

    return 0;
}
