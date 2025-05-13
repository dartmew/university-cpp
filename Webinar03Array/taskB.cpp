#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Функция для проверки високосного года
bool isLeapYear(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400 == 0);
}

// Функция для получения количества дней в месяце
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeapYear(year) ? 29 : 28;
        default: return 0;
    }
}

// Функция для добавления дней к дате
void addDays(int &day, int &month, int &year, int daysToAdd) {
    for (int i = 0; i < daysToAdd; ++i) {
        day++;
        if (day > daysInMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
}

// Функция для форматирования даты в строку dd.mm.yyyy
string formatDate(int day, int month, int year) {
    stringstream ss;
    ss << setw(2) << setfill('0') << day << ".";
    ss << setw(2) << setfill('0') << month << ".";
    ss << year;
    return ss.str();
}

int main() {
    int day, month, year;
    char dot;
    cin >> day >> month >> year;

    int N;
    cin >> N;

    vector<double> rates(N);
    for (int i = 0; i < N; ++i) {
        cin >> rates[i];
    }

    // Находим индекс первого максимального элемента
    double maxRate = *max_element(rates.begin(), rates.end());
    int maxIndex = find(rates.begin(), rates.end(), maxRate) - rates.begin();

    // Вычисляем дату максимального курса
    int resultDay = day, resultMonth = month, resultYear = year;
    addDays(resultDay, resultMonth, resultYear, maxIndex);
    string dateStr = formatDate(resultDay, resultMonth, resultYear);

    // Подсчитываем количество дней роста до максимального курса
    int growthDays = 0;
    if (maxIndex == 0) {
        growthDays = 1;
    } else {
        int count = 1;
        for (int i = 1; i <= maxIndex; ++i) {
            if (rates[i] > rates[i-1]) {
                count++;
            } else {
                count = 1;
            }
        }
        growthDays = count - 1;
    }

    cout << dateStr << " " << growthDays << endl;

    return 0;
}