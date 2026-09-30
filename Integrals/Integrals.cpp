#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Func {
    double A, B, C, D;
};

double fun(double x, Func f) {
    return f.A * x * x * x + f.B * x * x + f.C * x + f.D;
}

double Simpson(double a, double b, int n, Func f) {
    double h = (b - a) / n; // шаг разбиения
    double s = 0; // сумма интеграла

    double x = a; // текущая точка

    for (int i = 1; i <= n; i++) {

        double x1 = x + h / 2;
        double x2 = x + h;

        double f0 = fun(x, f);
        double f1 = fun(x1, f);
        double f2 = fun(x2, f);

        // формула Симпсона
        s += f0 + 4 * f1 + f2;

        x = x2;
    }

    return s * h / 6;
}

Func getVariant() {
    Func f;

    f.A = 1;
    f.B = 10;
    f.C = 0;
    f.D = 0;

    cout << "Function: x^3 + 10x^2\n";

    return f;
}

int main() {
    double a, b;

    int choice;
    int n; // начальное разбиение
    int n1; // разбиение для уточнения точности
    double eps;

    cout << "1 - Variant function (default a, b)\n";
    cout << "2 - Custom a, b input\n";
    cin >> choice;

    Func f = getVariant();

    if (choice == 1) {
        a = -8;
        b = 2;
    }
    else {
        cout << "Input a b: ";
        cin >> a >> b;
    }

    cout << "a = " << a << "\nb = " << b << endl;

    cout << "Input n: ";
    cin >> n;

    cout << "Input eps: ";
    cin >> eps;

    cout << "\n--- Simpson ---\n";

    // вычисление интеграла при заданном n
    double I1 = Simpson(a, b, n, f);

    cout << "Integral (n=" << n << ") = "
        << fixed << setprecision(10) << I1 << endl;

    cout << "\n--- Accuracy ---\n";

    // стартовое разбиение для проверки точности
    n1 = 2;
    I1 = Simpson(a, b, n1, f);

    double I2;
    double error;

    // итерационное уточнение результата
    do {
        n1 *= 2; // увеличиваем разбиение

        I2 = Simpson(a, b, n1, f);

        // разница между двумя приближениями
        error = fabs(I2 - I1);

        I1 = I2;

    } while (error > eps);

    cout << "Integral = " << fixed << setprecision(10) << I1 << endl;
    cout << "n = " << n1 << endl;

    return 0;
}