#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N, M;
    input >> N >> M;

    vector<bool> zero_rows(N, true);
    vector<double> column_sums(M, 0.0);

    int current_row;
    while (true) {
        input >> current_row;
        if (current_row == -1) {
            break;
        }

        zero_rows[current_row] = false;
        int num_elements;
        input >> num_elements;

        for (int i = 0; i < num_elements; ++i) {
            double value;
            int column;
            input >> value >> column;
            column_sums[column] += value;
        }
    }

    // Находим нулевые строки
    bool first = true;
    for (int i = 0; i < N; ++i) {
        if (zero_rows[i]) {
            if (!first) {
                output << " ";
            }
            output << i;
            first = false;
        }
    }
    output << endl;

    // Находим столбец с максимальной суммой
    double max_sum = -1.0;
    int max_column = 0;
    for (int j = 0; j < M; ++j) {
        if (column_sums[j] > max_sum) {
            max_sum = column_sums[j];
            max_column = j;
        }
    }
    output << max_column << endl;

    input.close();
    output.close();

    return 0;
}