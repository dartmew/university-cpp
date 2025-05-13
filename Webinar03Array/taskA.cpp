#include <iostream>
#include <climits> // Для использования INT_MAX
using namespace std;

int main() {
    int N;
    cin >> N; // Считываем количество дней

    // Выделяем динамическую память для температур
    int* temperatures = new int[2 * N];

    // Считываем температуры
    for (int i = 0; i < 2 * N; ++i) {
        cin >> temperatures[i];
    }

    // Находим день с наименьшей разницей температур
    int minDiff = INT_MAX; // Минимальная разница
    int minDay = 1;        // Номер дня с минимальной разницей (начинается с 1)

    for (int i = 0; i < N; ++i) {
        int dayTemp = temperatures[2 * i];     // Температура в полдень
        int nightTemp = temperatures[2 * i + 1]; // Температура в полночь
        int diff = dayTemp - nightTemp;   // Разница температур

        // Ищем минимальную разницу
        if (diff < minDiff) {
            minDiff = diff;
            minDay = i + 1; // Нумерация дней с 1
        }
    }

    // Считаем количество дневных температур выше нуля
    int positiveCount = 0;
    for (int i = 0; i < N; ++i) {
        if (temperatures[2 * i] > 0) {
            positiveCount++;
        }
    }


    // Выводим номер дня с минимальной разницей
    cout << minDay << endl;

    // Проверяем, есть ли положительные температуры
    if (positiveCount == 0) {
        cout << "No positive data" << endl;
    }
    else if (positiveCount == N) {
        cout << "All data are positive" << endl;
    }
    else {
        // Выводим положительные температуры через пробел
        for (int i = 0; i < N; ++i) {
            if (temperatures[2 * i] > 0) {
                cout << temperatures[2 * i];
                if (--positiveCount > 0) {
                    cout << " "; // Добавляем пробел, кроме последнего элемента
                }
            }
        }
        cout << endl;
    }

    // Освобождаем динамическую память
    delete[] temperatures;
}