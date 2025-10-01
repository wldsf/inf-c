// дзшка 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    float x;
    cout << "Введите число: ";
    cin >> x;
    float y;
    cout << "Введите число: ";
    cin >> y;
    const float r = 1.0 / (cos(pow(y, 1/3.0)));
    const float s = (sqrt(abs(x))) / log(y);
    cout << "R = " << r <<endl;
    cout << "S = " << s << endl;
    cout << "C = " << max(r,s) << endl;
    system("pause"); 
    return 0;
}

