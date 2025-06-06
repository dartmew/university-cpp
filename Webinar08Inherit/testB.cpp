#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    map<string, vector<string>> professorGroups;  // professor -> list of groups
    map<string, string> studentGroup;            // student -> group
    map<string, int> professorStudentCount;      // professor -> number of students

    string line;
    while (getline(input, line)) {
        vector<string> tokens = split(line, ';');
        if (tokens.empty()) continue;

        if (tokens[0].find("Professor") != string::npos) {
            // Professor record: Professor N;Subject;Group
            if (tokens.size() >= 3) {
                string professor = tokens[0];
                string group = tokens[2];
                professorGroups[professor].push_back(group);
            }
        } else if (tokens[0].find("Student") != string::npos) {
            // Student record: Student N;Group
            if (tokens.size() >= 2) {
                string student = tokens[0];
                string group = tokens[1];
                studentGroup[student] = group;
            }
        }
    }

    // Count students for each professor
    for (const auto &prof : professorGroups) {
        const string &professor = prof.first;
        const vector<string> &groups = prof.second;

        for (const auto &group : groups) {
            for (const auto &student : studentGroup) {
                if (student.second == group) {
                    professorStudentCount[professor]++;
                }
            }
        }
    }

    if (professorStudentCount.empty()) {
        output << "No professors" << endl;
        return 0;
    }

    // Find professor with maximum students
    int maxStudents = 0;
    vector<string> topProfessors;
    for (const auto &entry : professorStudentCount) {
        if (entry.second > maxStudents) {
            maxStudents = entry.second;
            topProfessors.clear();
            topProfessors.push_back(entry.first);
        } else if (entry.second == maxStudents) {
            topProfessors.push_back(entry.first);
        }
    }

    // Sort professors by their ID (assuming "Professor N" format)
    sort(topProfessors.begin(), topProfessors.end(), [](const string &a, const string &b) {
        int numA = stoi(a.substr(9));
        int numB = stoi(b.substr(9));
        return numA < numB;
    });

    // Output the result
    for (const string &prof : topProfessors) {
        output << prof << endl;
    }

    input.close();
    output.close();

    return 0;
}