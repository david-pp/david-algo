#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <vector>


// Brute-force substring search
// 时间复杂度：M*N
int search(const std::string &pat, const std::string &txt) {
    int N = txt.length();
    int M = pat.length();

    if (M > N) return N;

    for (int i = 0; i <= N - M; i++) {
        for (int j = 0; j < M; j++) {
            if (txt[i + j] != pat[j])
                break;

            if (j == M - 1) {
                return i;
            }
        }
    }

    return N;
}

void test() {
    std::cout << search("ABRA", "ABACADABRAC") << std::endl;
}

int main(int argc, char *argv[]) {
    test();
}