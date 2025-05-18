#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

bool isBigCountry(const Country &country) {
    return country.area > 3000000 || country.population >= 25000000;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line;
    vector<Country> countries;

    // Пропускаем заголовок
    getline(input, line);

    while (getline(input, line)) {
        vector<string> tokens = split(line, ';');
        if (tokens.size() >= 6) {
            Country country;
            country.name = tokens[0];
            country.region = tokens[1];
            country.population = stoll(tokens[2]);
            country.area = stoll(tokens[3]);
            country.gdp = stod(tokens[4]);
            country.literacy = stod(tokens[5]);
            countries.push_back(country);
        }
    }

    vector<string> bigCountries;
    for (const auto &country : countries) {
        if (isBigCountry(country)) {
            bigCountries.push_back(country.name);
        }
    }

    sort(bigCountries.begin(), bigCountries.end());

    for (const auto &country : bigCountries) {
        output << country << endl;
    }

    input.close();
    output.close();

    return 0;
}