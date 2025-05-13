#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool matchesMask(const vector<int>& row, const string& mask) {
    for (size_t i = 0; i < row.size(); ++i) {
        char c = mask[i];
        int num = row[i];
        if (c == '+') {
            if (num <= 0) return false;
        } else if (c == '-') {
            if (num >= 0) return false;
        } else if (c == '.') {
            if (num != 0) return false;
        } else if (c == '*') {
            continue;
        } else {
            return false; // некорректный символ в маске
        }
    }
    return true;
}

int main() {
    int N, M;
    cin >> N >> M;
    cin.ignore(); // пропускаем перевод строки после чисел
    
    string mask;
    getline(cin, mask);
    
    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    int count = 0;
    for (const auto& row : matrix) {
        if (matchesMask(row, mask)) {
            count++;
        }
    }
    
    if (count == 0) {
        cout << "No lines with mask" << endl;
    } else {
        cout << count << endl;
    }
    
    return 0;
}