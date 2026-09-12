#include <iostream>
using namespace std;

void In(int* a, int n);
void Out(const int* a, int n);
void Poisk(const int* a, int n, double& C, int* Y);

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: n <= 0\n";
        return 0;
    }

    int* a = new int[n];

    In(a, n);

    Out(a, n);

    double C = 0.0;
    int Y = 0;
    Poisk(a, n, C, &Y);

    cout << "\nC (average) = " << C << "\n";
    cout << "Y (count < average) = " << Y << "\n";

    delete[] a;

    return 0;
}

void In(int* a, int n) {
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void Out(const int* a, int n) {
    cout << "Array:\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
}

void Poisk(const int* a, int n, double& C, int* Y) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    C = sum / n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < C) count++;
    }
    *Y = count;
}