#include <bits/stdc++.h>
#define CONS 1000000007;

int substring_multiplier(std::string S) {
    // count the number of times each character appears in the string
    int n = S.length();
    std::vector<int> count(26, 0);
    for (int i = 0; i < n; i++) {
        count[S[i] - 'a']++;
    }

    // calculate the number of unique characters in the string
    int unique_chars = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            unique_chars++;
        }
    }

    return unique_chars;
}

int nof_occurrences(std::string K, std::string S, int N, int L) {
    std::vector<long long int> frequency(L + 1, 0);
    frequency[0] = 1;

    int multiplier = substring_multiplier(S);

    // iterate over the string K
    for (int i = 0; i < N; i++) {
        // if the current char is a '?'
        if (K[i] == '?') {
            // frequency[j] = frequency[j] * multiplier + aux[j - 1];
            for (int j = L; j > 0; j--) {
                frequency[j] = (frequency[j] * multiplier + frequency[j - 1]);
                frequency[j] %= CONS;
            }
            frequency[0] = (frequency[0] * multiplier) % CONS;
        } else {
            // search for each apperance of the current char in the string S
            for (int j = L - 1; j >= 0; j--) {
                if (K[i] == S[j]) {
                    // update the frequency vector
                    frequency[j + 1] = (frequency[j + 1] + frequency[j]) % CONS;
                }
            }
        }
    }

    // the last element of the frequency vector is the number of occurrences
    return frequency[L];
}

int main() {
    std::ifstream fin("crypto.in");
    std::ofstream fout("crypto.out");

    // N = length of the key K
    // L = length of the substring S
    int N, L;
    fin >> N >> L;

    // K = key
    // S = substring
    std::string K, S;
    fin >> K >> S;

    int result = nof_occurrences(K, S, N, L);
    std::cout << result << std::endl;
    fout << result << std::endl;

    fin.close();
    fout.close();

    return 0;
}
