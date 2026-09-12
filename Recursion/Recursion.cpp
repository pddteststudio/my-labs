#include <iostream>
using namespace std;

void In(int* a, int n) {
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) cin >> a[i];
}

void Out(const int* a, int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 == n ? '\n' : ' ');
}

double AvgIter(const int* a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

double AvgRec(const int* a, int n, int i = 0) {
    if (i == n) return 0;
    return (a[i] + AvgRec(a, n, i + 1));
}

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

    double c1 = AvgIter(a, n);
    double c2 = AvgRec(a, n) / n;

    cout << "Average (no recursion) = " << c1 << "\n";
    cout << "Average (recursion)    = " << c2 << "\n";

    delete[] a;
    return 0;
}