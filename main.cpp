#include <iostream>
#include "relationship.h"
#include <windows.h>

using namespace std;


// Функция возвращает true, если выполняется условие (x < 3 & y < 3) || (x > 3 & y > 3) || (x == y)
bool f(const int &x, const int &y) {
    return (x < 3 & y < 3) || (x > 3 & y > 3) || (x == y);
}

// Функция всегда возвращает false
bool false_f(const int &x, const int &y) {
    return false;
}

// Функция всегда возвращает true
bool true_f(const int &x, const int &y) {
    return true;
}

// Функция печатает элементы вектора a в формате [x1, x2, ..., xn]
void print_vec(vector<int> &a) {
    cout << "[";
    for (auto x: a)
        cout << x << ", ";
    cout << "\b\b]" << endl;
}

// Функция проверяет, содержится ли элемент x в векторе a
bool elem_in_vec(vector<int> &a, const int &x) {
    for (const int y: a)
        if (y == x)
            return true;
    return false;
}

// Функция удаляет из вектора a все элементы, которые содержатся в векторе b
void diff_vector(vector<int> *a, vector<int> b) {
    vector<int> result = {};
    for (int x: *a) {
        if (!elem_in_vec(b, x)) {
            result.push_back(x);
        }
    }
    a->clear();
    for (const auto x: result) {
        a->push_back(x);
    }
}

// Функция проверяет, находятся ли элементы x и y в одной строке матрицы A
bool pair_in_same_row(const vector<vector<int>> &A, int x, int y) {
    for (auto row: A)
        if (elem_in_vec(row, x) && elem_in_vec(row, y))
            return true;
    return false;
}

// Функция возвращает класс эквивалентности для элемента x по отношению к матрице R
vector<int> get_equal_class(const vector<vector<int>> &R, const int &x, vector<int> &M) {
    vector<int> result = {};
    for (auto y: M)
        if (R[y - 1][x - 1])
            result.push_back(y);
    return result;
}

// Функция возвращает факторное множество по отношению к матрице R и множеству M
vector<vector<int>> get_factor_set(const vector<vector<int>> &R, const vector<int> &M) {
    vector<int> A = M;
    vector<vector<int>> S = {};
    while (!A.empty()) {
        int x = A[0];
        vector<int> equal_class_x = get_equal_class(R, x, A);
        S.push_back(equal_class_x);
        diff_vector(&A, equal_class_x);
    }
    return S;
}

// Функция возвращает матрицу отношений эквивалентности на основе факторного множества S и множества M
vector<vector<int>> get_equal_relationship(const vector<vector<int>> &S, const vector<int> &M) {
    vector<vector<int>> R = create_matrix_relationship(false_f);
    for (const int x: M)
        for (const int y: M)
            if (pair_in_same_row(S, x, y))
                R[x-1][y-1] = 1;
    return R;
}



int main() {
    SetConsoleOutputCP(CP_UTF8);

    const vector M = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    const vector<pair<int, int> > A_p = generate_relationship(f);
    print_relationship(A_p);

    const vector<vector<int>> A_m = create_matrix_relationship(f);
    print_matrix(A_m);

    const bool equivalence = is_relationship_reflexive(A_m, 1) && is_relationship_symmetrical(A_m, 1) && is_relationship_transitive(A_m, 1);

    if (equivalence) {
        cout << "Отношение имеет свойство эквивалентности" << endl;
        cout << endl;
    } else {
        cout << "Отношение не имеет свойство эквивалентности" << endl;
        cout << endl;
    }

    cout << "Разбиение Ф: " << endl;
    vector<vector<int> > factor_set = get_factor_set(A_m, M);

    for (auto elem: factor_set) {
        print_vec(elem);
    }

    cout << endl;

    return 0;
}