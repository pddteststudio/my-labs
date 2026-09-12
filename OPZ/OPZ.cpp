#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*
Добавление элемента в стек
p — текущая вершина стека
in — добавляемый символ
*/
struct Stack {
    char info;
    Stack* next;
};

Stack* InStack(Stack* p, char in) {
    Stack* t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

/*
Удаление элемента из стека
out — куда сохранить удалённый символ
*/
Stack* OutStack(Stack* p, char* out) {
    if (!p) return NULL;

    Stack* t = p;
    *out = t->info;
    p = p->next;
    delete t;

    return p;
}

// Приоритет операций
int Prior(char a) {
    if (a == '^') return 4;
    if (a == '*' || a == '/') return 3;
    if (a == '+' || a == '-') return 2;
    if (a == '(') return 1;
    return 0;
}

string Make_OPZ(string InStr, Stack*& top) {

    top = NULL;
    string OutStr;
    char ss, a;

    // идём по строке слева направо
    for (int i = 0; i < InStr.length(); i++) {

        ss = InStr[i];

        // если открывающая скобка -> в стек
        if (ss == '(')
            top = InStack(top, ss);

        // если закрывающая скобка
        else if (ss == ')') {

            // выталкиваем всё до (
            while (top && top->info != '(') {
                top = OutStack(top, &a);
                OutStr += a;
            }

            // удаляем (
            if (top)
                top = OutStack(top, &a);
        }

        // если переменная -> сразу в результат
        else if (ss >= 'a' && ss <= 'z')
            OutStr += ss;

        else if (ss == '+' || ss == '-' || ss == '*' || ss == '/' || ss == '^') {

            while (top && Prior(top->info) >= Prior(ss)) {
                top = OutStack(top, &a);
                OutStr += a;
            }

            // кладём текущую операцию
            top = InStack(top, ss);
        }
    }

    // выталкиваем остаток стека
    while (top) {
        top = OutStack(top, &a);
        OutStr += a;
    }

    return OutStr;
}

// Вычисление ОПЗ
double Rezult(string Str, double* mas, Stack*& top) {

    char ch, ch1, ch2;
    double op1, op2, rez = 0;

    char chr = 'z' + 1;

    top = NULL;

    for (int i = 0; i < Str.length(); i++) {

        ch = Str[i];

        // если не операция -> кладём в стек
        if (!(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'))
            top = InStack(top, ch);

        else {
            top = OutStack(top, &ch1);
            top = OutStack(top, &ch2);

            op1 = mas[(int)ch1];
            op2 = mas[(int)ch2];

            switch (ch) {
            case '+': rez = op2 + op1; break;
            case '-': rez = op2 - op1; break;
            case '*': rez = op2 * op1; break;
            case '/': rez = op2 / op1; break;
            case '^': rez = pow(op2, op1); break;
            }

            // сохраняем промежуточный результат
            mas[(int)chr] = rez;

            // кладём результат в стек
            top = InStack(top, chr);

            chr++;
        }
    }

    return rez;
}


void run(string expr, double* mas, Stack*& top) {

    cout << "Infix: " << expr << endl;

    // перевод в ОПЗ
    string opz = Make_OPZ(expr, top);

    cout << "OPZ: " << opz << endl;

    cout << "Result: " << Rezult(opz, mas, top) << endl;
}

int main() {

    Stack* top = NULL;
    double* mas = new double[256];

    int mode;

    while (true) {

        cout << "\n1 - Custom input\n2 - Variant\n0 - Exit\n: ";
        cin >> mode;

        if (mode == 0) {
            delete[] mas;
            return 0;
        }

        if (mode == 1) {

            string expr;

            cout << "Input Infix: ";
            cin >> expr;

            cout << "Input a b c d e: ";
            cin >> mas['a'] >> mas['b'] >> mas['c'] >> mas['d'] >> mas['e'];

            run(expr, mas, top);
        }

        if (mode == 2) {

            string expr = "(a+(b/c-d))*e";

            mas['a'] = 5.6;
            mas['b'] = 7.4;
            mas['c'] = 8.9;
            mas['d'] = 3.1;
            mas['e'] = 0.2;

            cout << "a = " << mas['a'] << endl;
            cout << "b = " << mas['b'] << endl;
            cout << "c = " << mas['c'] << endl;
            cout << "d = " << mas['d'] << endl;
            cout << "e = " << mas['e'] << endl;

            run(expr, mas, top);
        }
    }
}