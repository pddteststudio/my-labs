#include <iostream>
#include <cmath>

using namespace std;

struct Spis2 {
    int info;
    Spis2* prev;
    Spis2* next;
};

// Создание первого элемента списка
void Create_Spis2(Spis2*& b, int in) {
    b = new Spis2;

    b->info = in;
    b->next = NULL;
    b->prev = NULL;
}

// Добавление элемента в начало или конец списка
void Add_Spis2(int kod, Spis2*& b, Spis2*& e, int in) {

    Spis2* t = new Spis2;  // создаём новый узел
    t->info = in;

    // добавление в начало
    if (kod == 0) {
        t->prev = NULL; // у нового первого нет предыдущего
        t->next = b; // он ссылается на старый первый
        b->prev = t;
        b = t;
    }

    // добавление в конец
    else {
        t->next = NULL; // у последнего нет следующего
        t->prev = e;
        e->next = t;
        e = t;
    }
}

// Вывод списка слева направо
void View_Spis2(Spis2* t) {
    while (t) {
        cout << t->info << " ";
        t = t->next;
    }
    cout << endl;
}

void Del_All(Spis2*& b) {
    Spis2* t;

    while (b) {
        t = b;
        b = b->next;
        delete t;
    }
}

// удалить элементы между минимальным и максимальным
void Task(Spis2*& b, Spis2*& e, int& k) {

    k = 0;

    if (!b || !b->next) return;

    Spis2* min = b;
    Spis2* max = b;
    Spis2* cur = b; // текущий указатель

    int i = 0; // индекс текущего элемента
    int imin = 0;
    int imax = 0;

    // поиск min и max
    while (cur) {

        if (cur->info < min->info) {
            min = cur;
            imin = i;
        }

        if (cur->info > max->info) {
            max = cur;
            imax = i;
        }

        cur = cur->next;
        i++;
    }

    if (abs(imin - imax) <= 1) return;

    Spis2* l; // левая граница
    Spis2* r; // правая граница

    // определяем порядок
    if (imin < imax) {
        l = min;
        r = max;
    }
    else {
        l = max;
        r = min;
    }

    Spis2* q = l->next; // начинаем удаление после l
    Spis2* del;

    // удаляем всё между l и r
    while (q && q != r) {
        del = q;
        q = q->next;
        delete del;
        k++;
    }

    // соединяем список обратно
    l->next = r;
    r->prev = l;
}

int main() {

    Spis2* pbeg = NULL;
    Spis2* pend = NULL;

    int kod, kod1, n, i, k, in;

    while (true) {

        cout << "\nCreate - 1\nAdd - 2\nView - 3\nTask - 4\nDel - 5\nExit - 0\n: ";
        cin >> kod;

        switch (kod) {

            // создание
        case 1:

            if (pbeg) {
                cout << "Clear Memory!" << endl;
                break;
            }

            cout << "Input kol = ";
            cin >> n;

            cout << "Input element: ";
            cin >> in;

            Create_Spis2(pbeg, in);
            pend = pbeg;

            for (i = 2; i <= n; i++) {
                cout << "Input element: ";
                cin >> in;
                Add_Spis2(1, pbeg, pend, in);
            }
            break;

            // добавление
        case 2:

            if (!pbeg) {
                cout << "Create List!" << endl;
                break;
            }

            cout << "Add Begin - 0, Add End - 1 : ";
            cin >> kod1;

            cout << "Input element: ";
            cin >> in;

            Add_Spis2(kod1, pbeg, pend, in);
            cout << "Added\n";
            break;

            // вывод
        case 3:

            if (!pbeg) {
                cout << "List Empty!" << endl;
                break;
            }

            View_Spis2(pbeg);
            break;

            // задача
        case 4:

            if (!pbeg) {
                cout << "List Empty!" << endl;
                break;
            }

            View_Spis2(pbeg);
            Task(pbeg, pend, k);
            cout << "Deleted = " << k << endl;
            View_Spis2(pbeg);
            break;

            // очистка памяти
        case 5:

            Del_All(pbeg);
            pend = NULL;
            cout << "Memory Free!" << endl;
            break;

        case 0:

            if (pbeg) Del_All(pbeg);
            return 0;
        }
    }
}