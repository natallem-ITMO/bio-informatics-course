#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include "circular_suffix_array.h"

void find_appears(std::string &word, const std::string &text, circular_suffix_array &suff_array,
                              std::unordered_map<size_t, std::unordered_map<char, size_t>> &O,
                              std::unordered_map<char, size_t> &C, std::vector<int> & res) {
    int Rl = 0;
    int Rh = O.size() - 2;
    for (int i = word.size() - 1; i >= 0; --i) {
       char cur_char = word[i];
       if (C.find(cur_char) == C.end()){
           return;
       }
       Rl = C[cur_char] + O[Rl - 1 + 1][cur_char];
       Rh = C[cur_char] + O[Rh + 1][cur_char] - 1;
       if (Rl > Rh){
           return;
       }
    }
    for (int i = Rl; i <= Rh; ++i){
        res.push_back(suff_array[i]);
    }
}

int to_BW(int i, size_t len) {
    return (i == 0) ? len - 1 : i - 1;
}

int main() {
    std::ifstream input("..\\input\\ba9h.txt");
    std::string text;
    input >> text;
    text += '$';
    std::vector<uint8_t> tt;
    for (char c : text) {
        tt.push_back(c);
    }
    circular_suffix_array suffix_array(tt);
    std::unordered_map<char, size_t> C;
    char prev_cur = '.';
    for (int i = 0; i < suffix_array.size(); ++i) {
        char cur = text[suffix_array[i]];
        if (cur != prev_cur) {
            C[cur] = i;
        }
        prev_cur = cur;
    }
    std::unordered_map<size_t, std::unordered_map<char, size_t>> O;
    for (int i = 0; i < text.length() + 1; i++) {
        for (auto &t : C) {
            O[i][t.first] = 0;
        }
    }
    for (int i = 0; i < suffix_array.size(); ++i) {
        int cur_index = suffix_array[i];
        int prev_index = to_BW(cur_index, text.length());
        for (auto &t : C) {
            O[i + 1][t.first] = O[i][t.first];
        }
        ++O[i + 1][text[prev_index]];
    }
    std::string cur_word;
    std::vector<int> res;
    while (input >> cur_word) {
        find_appears(cur_word, text, suffix_array, O, C, res);
    }
    std::sort(res.begin(), res.end());
    for (auto t : res){
        std::cout << t << " ";
    }
    return 0;
}
