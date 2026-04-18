#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

double f1(double x) {
    return sin(x);
}

double f2(double x) {
    return cos(x);
}

double f3(double x) {
    return sin(0.5 * x) - 0.5;
}

double fun1(double x) {
    double y1 = f1(x);
    double y2 = f2(x);
    return y2 - y1;  
}

double fun2(double x) {
    double y1 = f1(x);
    double y3 = f3(x);
    return y3 - y1; 
}

double simpson1(double a, double b, int n) {
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double sum = fun1(a) + fun1(b);

    for (int i = 1; i < n; i += 2) {
        double x = a + i * h;
        sum += 4 * fun1(x);
    }
    for (int i = 2; i < n; i += 2) {
        double x = a + i * h;
        sum += 2 * fun1(x);
    }
    return (h / 3) * sum;
}

double simpson2(double b, double c, int n) {
    if (n % 2 != 0) n++;
    double h = (c - b) / n;
    double sum = fun2(b) + fun2(c);

    for (int i = 1; i < n; i += 2) {
        double x = b + i * h;
        sum += 4 * fun2(x);
    }
    for (int i = 2; i < n; i += 2) {
        double x = b + i * h;
        sum += 2 * fun2(x);
    }
    return (h / 3) * sum;
}


double sum_res(double result1, double result2) {
    return result2 + result1;  
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a = 4.0;
    double b = 4.87;
    double c = 6.0;

    vector<int> n_values = { 1, 10, 20, 50, 100, 200, 500, 1000 };

    cout << "Таблица результатов:\n";
    cout << "n\tПлощадь\n";

    for (int n : n_values) {

        double result1 = simpson1(a, b, n);
        double result2 = simpson2(b, c, n);
        double area = sum_res(result1, result2);
        cout << n << "\t" << area << endl;
    }

    return 0;
}