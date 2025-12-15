#include <iostream>
#include <locale>

int cravnenie(const int arr[], int size, int t) {
    if (size < 0) {
        std::cout << "Ошибка: отрицательный размер массива" << size << std::endl;
        return 0;
    }

    if (size == 0) {
        return 0;  // Пустой массив
    }

    if (arr == nullptr) {
        std::cout << "Ошибка: передан нулевой указатель на массив" << std::endl;
        return 0;
    }
    int count = 0; // Инициализация суммы
    for (int i = 0; i < size; i++) {
        if (arr[i] > t) {
            count += 1;
        }
    }
    return count;
}

void mincount(const int* arrA, const int* arrB, int size, int t) {
    int countA = 0, countB = 0;

    if (size < 0) {
        std::cout << "Ошибка: отрицательный размер массивов" << size << std::endl;
        return;
    }

    if (size == 0) {
        std::cout << "Массивы пусты. Оба имеют 0 элементов больше " << t << std::endl;
        return;
    }

    if (arrA == nullptr || arrB == nullptr) {
        std::cout << "Ошибка: один из массивов не инициализирован" << std::endl;
        return;
    }

    // Вычисляем количество элементов > t для каждого массива
    countA = cravnenie(arrA, size, t);
    countB = cravnenie(arrB, size, t);

    // Сравниваем суммы и выводим массив с наибольшей суммой
    if (countA < countB) {
        std::cout << "Массив A имеет наименьшее количество: " << countA << std::endl;
        std::cout << "Элементы массива A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
        std::cout << "Элементы массива B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
    }
    else {
        std::cout << "Массив B имеет наименьшее количество: " << countB << std::endl;
        std::cout << "Элементы массива B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
        std::cout << "Элементы массива A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main() {

    setlocale(LC_ALL, "Russian");

    int N; // Размер массивов

    // Ввод размера массивов
    std::cout << "Введите размер массивов (N): ";
    std::cin >> N;

    //ввод числа для сравнения
    int t;
    std::cout << "Введите число для сравнения: ";
    std::cin >> t;

    int* A = new int[N]; // Динамическое выделение памяти для массива A
    int* B = new int[N]; // Динамическое выделение памяти для массива B

    if (A == nullptr || B == nullptr) {
        std::cout << "ошибка: Не удалось создать массивы!" << std::endl;
        return 0; 
    }
    // Ввод массивов
    std::cout << "Введите " << N << " элементов для массива A:" << std::endl;
    for (int i = 0; i < N; i++) {
        while (true) {
            std::cin >> A[i];

            if (std::cin.fail()) {
                std::cout << "ошибка! Введите целое число!" << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n') {
                }
            }
            else {
                break;
            }
        }
    }
    std::cout << "Введите " << N << " элементов для массива B:" << std::endl;
    for (int i = 0; i < N; i++) {
        while (true) {
            std::cin >> B[i];

            if (std::cin.fail()) {
                std::cout << "ошибка! Введите целое число!" << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n') {
                }
            }
            else {
                break;
            }
        }
    }
    // Поиск массива с наибольшей суммой
    mincount(A, B, N, t);

    // Освобождение выделенной памяти
    delete[] A;
    delete[] B;

    return 0;
}