#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Student {
public:
    string name;
    double average;

    Student(const string& name, const vector<int>& grades) : name(name) {
        double sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        average = sum / grades.size();
    }
};

class Employee {
public:
    string name;
    int salary;

    Employee(const string& name, int salary) : name(name), salary(salary) {}
};

class Player {
public:
    string name;
    int points;

    Player(const string& name, int points) : name(name), points(points) {}
};

template <typename T, typename Compare>
T findBest(const vector<T>& items, Compare comp) {
    if (items.empty()) {
        throw runtime_error("No items found");
    }
    return *max_element(items.begin(), items.end(), comp);
}

vector<string> split(const string& s) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    vector<Student> students;
    vector<Employee> employees;
    vector<Player> players;

    string line;
    while (getline(input, line)) {
        vector<string> tokens = split(line);
        if (tokens.empty()) continue;

        if (tokens[0].find("Student_") != string::npos) {
            vector<int> grades;
            for (size_t i = 1; i < tokens.size(); ++i) {
                grades.push_back(stoi(tokens[i]));
            }
            students.emplace_back(tokens[0], grades);
        } else if (tokens[0].find("Employee_") != string::npos) {
            int salary = stoi(tokens.back());
            employees.emplace_back(tokens[0], salary);
        } else if (tokens[0].find("Player_") != string::npos) {
            int points = stoi(tokens.back());
            players.emplace_back(tokens[0], points);
        }
    }

    try {
        auto bestStudent = findBest(students, [](const Student& a, const Student& b) {
            return a.average < b.average;
        });
        output << bestStudent.name << endl;
    } catch (const runtime_error& e) {
        output << "No students" << endl;
    }

    try {
        auto bestEmployee = findBest(employees, [](const Employee& a, const Employee& b) {
            return a.salary < b.salary;
        });
        output << bestEmployee.name << endl;
    } catch (const runtime_error& e) {
        output << "No employees" << endl;
    }

    try {
        auto bestPlayer = findBest(players, [](const Player& a, const Player& b) {
            return a.points < b.points;
        });
        output << bestPlayer.name << endl;
    } catch (const runtime_error& e) {
        output << "No players" << endl;
    }

    input.close();
    output.close();

    return 0;
}