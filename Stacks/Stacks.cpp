#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Односвязный список: каждый элемент знает только следующий
struct Stack {
    int info; 
    Stack* next;
};


// p — текущая вершина стека
// in — добавляемое значение
Stack* InStack(Stack* p, int in) {

    Stack* t = new Stack;
    t->info = in;
    t->next = p;

    return t;
}


// Удаление из стека
Stack* OutStack(Stack* p, int* out) {

    if (!p) return NULL;

    Stack* t = p;
    *out = p->info;
    p = p->next; // сдвигаем вершину вниз

    delete t;

    return p;
}


// вывод идёт от низа к верху (из-за рекурсии)
string ViewRec(Stack* p) {

    if (!p) return "";

    return ViewRec(p->next) + to_string(p->info) + " ";
}


void Del_All(Stack** p) {

    Stack* t;

    while (*p) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

// Сортировка значений
void Sort_info(Stack* p) {

    Stack* t = NULL;
    Stack* t1;
    int r;

    if (!p || !p->next) return;

    do {
        for (t1 = p; t1->next != t; t1 = t1->next) {

            // если порядок нарушен — меняем значения местами
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        }

        t = t1; // сужаем область сортировки

    } while (p->next != t);
}


// Сортировка перестановкой узлов
void Sort_p(Stack** p) {

    Stack* t = NULL;
    Stack* t1;
    Stack* r;

    if (!*p || !(*p)->next || !(*p)->next->next) return;

    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next) {

            if (t1->next->info > t1->next->next->info) {

                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        }

        t = t1->next;

    } while ((*p)->next->next != t);
}


// ЗАДАЧА: удалить элементы между min и max
void Task(Stack** p, int& k) {

    k = 0;

    if (!*p || !(*p)->next) return;

    Stack* t = *p;
    Stack* min = *p;
    Stack* max = *p;

    int i = 0;
    int imin = 0;
    int imax = 0;

    // поиск min и max
    while (t) {

        if (t->info < min->info) {
            min = t;
            imin = i;
        }

        if (t->info > max->info) {
            max = t;
            imax = i;
        }

        t = t->next;
        i++;
    }

    if (abs(imin - imax) <= 1) return;

    Stack* l;
    Stack* r;

    // определяем границы
    if (imin < imax) {
        l = min;
        r = max;
    }
    else {
        l = max;
        r = min;
    }

    Stack* q = l->next;
    Stack* del;

    // удаляем элементы между min и max
    while (q != r) {
        del = q;
        q = q->next;
        delete del;
        k++;
    }

    // соединяем список обратно
    l->next = r;
}


int main() {

    Stack* top = NULL;

    int kod, n, i, in, x, k;
    bool created = false;

    while (true) {

        cout << "\nCreate - 1\nAdd - 2\nView - 3\nTask - 4\nSort_info - 5\nSort_p - 6\nDel - 7\nExit - 0\n: ";
        cin >> kod;

        if (!top && kod != 1 && kod != 0) {
            cout << ViewRec(top) << endl;
            cout << "Stack empty. Create first!" << endl;
            continue;
        }

        switch (kod) {

            // создание стека
        case 1:

            if (top) {
                cout << "Clear Memory!" << endl;
                break;
            }

            cout << "Input kol = ";
            cin >> n;

            for (i = 1; i <= n; i++) {
                cout << "Input element: ";
                cin >> in;
                top = InStack(top, in);
            }

            created = true;
            cout << "Create " << n << endl;
            break;


            // добавление в стек
        case 2:

            cout << "Input kol = ";
            cin >> n;

            for (i = 1; i <= n; i++) {
                cout << "Input element: ";
                cin >> in;
                top = InStack(top, in);
            }

            cout << "Add " << n << endl;
            break;


            // вывод стека
        case 3:

            if (!top) {
                cout << "Stack Pyst!" << endl;
                break;
            }

            cout << ViewRec(top) << endl;
            break;


            // задача
        case 4:

            if (!top) {
                cout << "Stack Pyst!" << endl;
                break;
            }

            cout << "Before:" << endl;
            cout << ViewRec(top) << endl;

            Task(&top, k);

            cout << "Deleted = " << k << endl;

            cout << "After:" << endl;
            cout << ViewRec(top) << endl;
            break;


            // сортировка значений
        case 5:

            if (!top) {
                cout << "Stack Pyst!" << endl;
                break;
            }

            Sort_info(top);
            cout << ViewRec(top) << endl;
            break;


            // сортировка узлов
        case 6:

            if (!top) {
                cout << "Stack Pyst!" << endl;
                break;
            }

            top = InStack(top, 0);
            Sort_p(&top);
            top = OutStack(top, &x);

            cout << ViewRec(top) << endl;
            break;


            // очистка памяти
        case 7:

            Del_All(&top);
            cout << "Memory Free!" << endl;
            break;


        case 0:

            if (top) Del_All(&top);
            return 0;
        }
    }
}