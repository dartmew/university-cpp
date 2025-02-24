#include <iostream>
#include <vector>
#include <cmath> // Для функции abs

int main() {
    int N;
    std::cin >> N;

    std::vector<int> dayTemps(N);
    std::vector<int> nightTemps(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> dayTemps[i] >> nightTemps[i];
    }

    // Найти день с наименьшей разницей температур
    int minDiff = std::abs(dayTemps[0] - nightTemps[0]);
    int minDiffDay = 1;

    for (int i = 1; i < N; ++i) {
        int diff = std::abs(dayTemps[i] - nightTemps[i]);
        if (diff < minDiff) {
            minDiff = diff;
            minDiffDay = i + 2; // Номер дня начинается с 1
        }
    }

    std::cout << minDiffDay << std::endl;

    // Выделить дневные температуры выше нуля
    std::vector<int> positiveTemps;
    for (int temp : dayTemps) {
        if (temp > 0) {
            positiveTemps.push_back(temp);
        }
    }

    if (positiveTemps.empty()) {
        std::cout << "No positive data" << std::endl;
    } else if (positiveTemps.size() == N) {
        std::cout << "All data are positive" << std::endl;
    } else {
        for (size_t i = 0; i < positiveTemps.size(); ++i) {
            std::cout << positiveTemps[i];
            if (i < positiveTemps.size() - 1) {
                std::cout << " "; // Пробел между числами
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
