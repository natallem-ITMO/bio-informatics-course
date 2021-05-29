#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>

void gen(int k, std::unordered_map<char, std::unordered_set<char>> &rules, std::string &cur,
         std::unordered_set<std::string> &all_poss_sols) {
    if (cur.length() == k) {
        all_poss_sols.insert(cur);
    } else {
        if (cur.empty()) {
            for (auto &p : rules) {
                cur.push_back(p.first);
                gen(k, rules, cur, all_poss_sols);
            }
        } else {
            char last = cur.back();
            for (char t : rules[last]) {
                cur.push_back(t);
                gen(k, rules, cur, all_poss_sols);
            }
        }

    }
    cur.pop_back();
}

int distance(const std::string &a, const std::string &b) {
    int res = 0;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) {
            ++res;
        }
    }
    return res;
}

std::string
check_all(std::unordered_set<std::string> &all_poss_sols, std::vector<std::unordered_set<std::string>> &k_mers_dna) {
    std::string result;
    int cur_min = INT_MAX;

    for (const std::string &cur_pattern : all_poss_sols) {
        int sum = 0;
        for (std::unordered_set<std::string> &dna_i_set : k_mers_dna) {
            int cur_min = cur_pattern.length();
            for (const std::string &cur_dna_i : dna_i_set) {
                cur_min = std::min(distance(cur_dna_i, cur_pattern), cur_min);
                if (cur_min == 0) {
                    break;
                }
            }
            sum += cur_min;
        }
        if (sum < cur_min) {
            result = cur_pattern;
            cur_min = sum;
        }
    }
    return result;
}

int main() {
    std::ifstream input("..\\input\\ba2b.txt");
    int k;
    input >> k;
    std::vector<std::string> dnas;
    std::string cur_dna;
    std::vector<std::unordered_set<std::string>> k_mers_dna;
    std::unordered_map<std::string, int> counter;
    while (input >> cur_dna) {
        dnas.push_back(cur_dna);
        for (int i = 0; i < cur_dna.length() - 1; ++i) {
            ++counter[cur_dna.substr(i, 2)];
        }
        k_mers_dna.emplace_back();
        for (int i = 0; i + k <= cur_dna.length(); ++i) {
            k_mers_dna.back().insert(cur_dna.substr(i, k));
        }
    }
    std::unordered_set<std::string> all_poss_sols;
    std::unordered_map<char, std::unordered_set<char>> rules = {
            {'A', {'A', 'C', 'G', 'T'}},
            {'C', {'A', 'C', 'G', 'T'}},
            {'G', {'A', 'C', 'G', 'T'}},
            {'T', {'A', 'C', 'G', 'T'}},
    };
    std::string cur;
    gen(k, rules, cur, all_poss_sols);
    std::cout << check_all(all_poss_sols, k_mers_dna);
    return 0;
}
