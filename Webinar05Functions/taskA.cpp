#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int countDivisors(int num) {
    if (num == 1) return 1;
    int count = 2; // 1 and num itself
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            if (i * i == num) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

void findMaxWithMaxDivisors(int N, int &M, int &maxDivisors) {
    M = 1;
    maxDivisors = 1;
    for (int i = 2; i <= N; ++i) {
        int divisors = countDivisors(i);
        if (divisors > maxDivisors || (divisors == maxDivisors && i > M)) {
            maxDivisors = divisors;
            M = i;
        }
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N;
    input >> N;

    int M, maxDivisors;
    findMaxWithMaxDivisors(N, M, maxDivisors);

    output << M << "\n" << maxDivisors << endl;

    input.close();
    output.close();
    return 0;
}