#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

struct Figure {
    int id;
    double area;
};

vector<string> split(const string &s) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

double calculateArea(const vector<string>& tokens) {
    string type = tokens[0];
    if (type == "Rectangle") {
        double a = stod(tokens[3]);
        double b = stod(tokens[4]);
        return a * b;
    } else if (type == "Square") {
        double a = stod(tokens[3]);
        return a * a;
    } else if (type == "Diamond") {
        double a = stod(tokens[3]);
        double alpha = stod(tokens[4]);
        return a * a * sin(alpha * M_PI / 180);
    } else if (type == "Circle") {
        double r = stod(tokens[3]);
        return M_PI * r * r;
    }
    return 0.0;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line;
    vector<Figure> figures;
    int id = 1;

    while (getline(input, line)) {
        vector<string> tokens = split(line);
        if (!tokens.empty()) {
            double area = calculateArea(tokens);
            figures.push_back({id, area});
            id++;
        }
    }

    if (figures.empty()) {
        output << "No figures" << endl;
        return 0;
    }

    double maxArea = 0.0;
    for (const auto& figure : figures) {
        if (figure.area > maxArea) {
            maxArea = figure.area;
        }
    }

    vector<int> maxFigures;
    for (const auto& figure : figures) {
        if (figure.area == maxArea) {
            maxFigures.push_back(figure.id);
        }
    }

    sort(maxFigures.begin(), maxFigures.end());

    for (int num : maxFigures) {
        output << num << endl;
    }

    input.close();
    output.close();

    return 0;
}