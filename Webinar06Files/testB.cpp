#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y'; // Y — гласная!
}

bool starts_with_upper_consonant(const string& word) {
    if (word.empty()) return false;
    char first = word[0];
    return isupper(first) && !is_vowel(first); // Y не считается согласной!
}

void process_word(const string& word, vector<string>& target_words, map<char, int>& letter_counts) {
    if (word.empty()) return;
    
    // Проверяем, начинается ли слово с заглавной согласной
    if (starts_with_upper_consonant(word)) {
        target_words.push_back(word);
        
        // Считаем все буквы в слове (без учёта регистра)
        for (char c : word) {
            if (isalpha(c)) {
                char upper_c = toupper(c);
                letter_counts[upper_c]++;
            }
        }
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line;
    vector<string> target_words;
    map<char, int> letter_counts;

    while (getline(input, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // Удаляем знаки препинания в начале и конце слова
            while (!word.empty() && !isalpha(word.front())) {
                word.erase(word.begin());
            }
            while (!word.empty() && !isalpha(word.back())) {
                word.pop_back();
            }
            
            if (!word.empty()) {
                process_word(word, target_words, letter_counts);
            }
        }
    }

    if (target_words.empty()) {
        output << "No words" << endl;
        return 0;
    }

    output << target_words.size() << endl;

    // Сортируем буквы по частоте и алфавиту
    vector<pair<char, int>> letters(letter_counts.begin(), letter_counts.end());
    sort(letters.begin(), letters.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second; // Сначала более частые
        } else {
            return a.first < b.first;   // Затем по алфавиту
        }
    });

    // Выводим топ-3 буквы
    for (int i = 0; i < min(3, (int)letters.size()); ++i) {
        if (i > 0) output << " ";
        output << letters[i].first;
    }
    output << endl;

    input.close();
    output.close();

    return 0;
}