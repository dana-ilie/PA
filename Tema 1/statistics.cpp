#include <bits/stdc++.h>

int max_solution(std::vector<int> v) {
    int max = v[0];

    for (int sol : v) {
        if (sol > max) {
            max = sol;
        }
    }

    return max;
}

int main() {
    std::ifstream fin("statistics.in");
    std::ofstream fout("statistics.out");

    int n;
    std::vector<std::string> words;
    std::vector<int> solutions;
    solutions.push_back(0);

    fin >> n;

    for (int i = 0; i < n; i++) {
        std::string s;
        fin >> s;
        words.push_back(s);
    }

    // for each letter of the alphabet (a-z)
    for (int i = 0; i < 26; i++) {
        int solution_nof_words = 0;
        int letter_dom_all_words = 0;
        std::vector<int> dom_less_than_zero;

        /*
        calculate the dominnance of the letter in each word 
        and store the words with dominnance < 0 in a vector
        dom = 2 * nof appearances of the letter in the word - len of the word
        */

        for (int j = 0; j < n; j++) {
            int app = std::count(words[j].begin(), words[j].end(), 'a' + i);
            int len = words[j].length();
            int dom = 2 * app - len;
            if (dom < 0) {
                dom_less_than_zero.push_back(dom);
            } else {
                letter_dom_all_words += dom;
            }
        }

        solution_nof_words = words.size() - dom_less_than_zero.size();

        // sort the vector of words with dominnance < 0
        std::sort(dom_less_than_zero.begin(), dom_less_than_zero.end());


        int size = dom_less_than_zero.size();
        while (size > 0 && letter_dom_all_words > 0) {
            // if the domminance of the word from the words with dominnace < 0
            // keeps the global dominnance of the letter > 0
            if (letter_dom_all_words + dom_less_than_zero[size - 1] > 0) {
                solution_nof_words++;
                letter_dom_all_words += dom_less_than_zero[size - 1];
            }
            size--;
        }

        solutions.push_back(solution_nof_words);
    }

    int max_len = max_solution(solutions);
    if (max_len == 0) {
        fout << -1 << std::endl;
    } else {
        fout << max_len << std::endl;
    }

    fin.close();
    fout.close();

    return 0;
}
