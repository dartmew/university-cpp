#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

struct Country {
    string name;
    string region;
    long long population;
    long long area;
    double gdp;
    double literacy;
};

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

    string line;
    map<string, int> regionTotalCountries;
    map<string, int> regionHighLiteracyCountries;

    // Пропускаем заголовок
    getline(input, line);

    while (getline(input, line)) {
        vector<string> tokens = split(line, ';');
        if (tokens.size() >= 6) {
            string region = tokens[1];
            double literacy = stod(tokens[5]);

            regionTotalCountries[region]++;
            if (literacy > 90.0) {
                regionHighLiteracyCountries[region]++;
            }
        }
    }

    map<string, double> regionLiteracyRatio;
    for (const auto &entry : regionTotalCountries) {
        string region = entry.first;
        int total = entry.second;
        int highLiteracy = regionHighLiteracyCountries[region];
        double ratio = (double)highLiteracy / total;
        regionLiteracyRatio[region] = ratio;
    }

    if (regionLiteracyRatio.empty()) {
        output << "No regions" << endl;
        return 0;
    }

    double maxRatio = 0.0;
    for (const auto &entry : regionLiteracyRatio) {
        if (entry.second > maxRatio) {
            maxRatio = entry.second;
        }
    }

    vector<string> bestRegions;
    for (const auto &entry : regionLiteracyRatio) {
        if (entry.second == maxRatio) {
            bestRegions.push_back(entry.first);
        }
    }

    sort(bestRegions.begin(), bestRegions.end());

    for (const string &region : bestRegions) {
        output << region << endl;
    }

    input.close();
    output.close();

    return 0;
}