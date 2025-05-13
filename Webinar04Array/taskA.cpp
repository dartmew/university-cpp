#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> ratings(N);
    for (int i = 0; i < N; ++i) {
        cin >> ratings[i];
    }

    vector<int> excellent;
    vector<int> failing;

    for (int rating : ratings) {
        if (rating >= 90) {
            excellent.push_back(rating);
        } else if (rating < 60) {
            failing.push_back(rating);
        }
    }

    if (excellent.empty() || failing.empty()) {
        cout << "Impossible" << endl;
        return 0;
    }

    sort(excellent.rbegin(), excellent.rend());
    int num_groups = min(3, (int)excellent.size());
    vector<vector<int>> groups(num_groups);

    int failing_count = failing.size();
    int students_per_group = failing_count / num_groups;
    int remainder = failing_count % num_groups;

    int current = 0;
    for (int i = 0; i < num_groups; ++i) {
        int group_size = students_per_group + (i < remainder ? 1 : 0);
        for (int j = 0; j < group_size; ++j) {
            groups[i].push_back(failing[current++]);
        }
    }

    for (int i = 0; i < num_groups; ++i) {
        if (!groups[i].empty()) {
            cout << excellent[i];
            for (int student : groups[i]) {
                cout << " " << student;
            }
            cout << endl;
        }
    }

    return 0;
}