#include <iostream>
#include <cmath>

using namespace std;

// функция поиска корня
double Metod1(double x0, double x1, double eps, int& iter);

double fun(double x) {
    return x * x * x + 10 * x * x - 50;
}


double Metod1(double x0, double x1, double eps, int& iter) {

    double y0, y1, x2, de;

    // считаем значения функции в начале и конце
    y0 = fun(x0);
    y1 = fun(x1);

    iter = 0;

    // повторяем пока не достигнем точности
    do {

        // считаем новое приближение корня
        x2 = x1 - y1 * (x1 - x0) / (y1 - y0);

        de = fabs(x1 - x2);

        // сдвигаем точки
        x0 = x1;
        x1 = x2;

        y0 = y1;
        y1 = fun(x2);

        iter++;

    } while (de > eps);

    return x2;
}

int main() {

    double a, b;

    int mode;

    cout << "1 - Variant (auto a, b)\n";
    cout << "2 - Manual input a, b\n";
    cout << ": ";
    cin >> mode;

    if (mode == 1) {
        a = -12;
        b = 5;
    }
    else {
        cout << "Input a = ";
        cin >> a;

        cout << "Input b = ";
        cin >> b;
    }

    double x, h, eps, y;

    int nom = 0; // сколько корней нашли
    int iter; // сколько шагов

    cout << "Function: x^3 + 10*x^2 - 50" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    cout << "Input h = ";
    cin >> h;

    cout << "Input eps = ";
    cin >> eps;

    if (h <= 0 || eps <= 0) {
        cout << "Error: h and eps must be positive!" << endl;
        return 0;
    }

    if (h <= 10 * eps) {
        cout << "Error: h must be much greater than eps!" << endl;
        return 0;
    }

    cout << "\n------ Table ------" << endl;

    for (x = a; x <= b; x += h) {
        cout << "x = " << x << "   f(x) = " << fun(x) << endl;
    }

    cout << "\n------ Roots ------" << endl;

    for (x = a; x <= b; x += h) {

        if (fun(x) * fun(x + h) < 0) {

            nom++;

            // ищем точный корень
            y = Metod1(x, x + h, eps, iter);

            cout << nom << "-root = " << y
                << "   f(x) = " << fun(y)
                << "   iterations = " << iter << endl;
        }
    }

    if (nom == 0)
        cout << "No roots!" << endl;

    return 0;
}