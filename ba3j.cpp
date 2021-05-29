#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <stack>

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

int dista(const std::string &a, const std::string &b) {
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
                cur_min = std::min(dista(cur_dna_i, cur_pattern), cur_min);
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

std::string read_concat(const std::string &first, const std::string &second) {
    return first + '|' + second;
}

std::vector<std::string> find_start(std::unordered_map<std::string, std::vector<std::string>> &edges,
                                    std::unordered_set<std::string> &all_nodes) {

    std::vector<std::string> res;
    std::unordered_set<std::string> have_input;
    for (auto &t : edges) {
        for (auto &k : t.second) {
            have_input.insert(k);
        }
    }
    for (auto &k : all_nodes) {
        if (have_input.find(k) != have_input.end()) {
            continue;
        }
        res.push_back(k);
    }
    return res;
}

std::vector<std::string>
find_path(std::string &start, std::unordered_map <std::string, std::vector<std::string>> &edges) {
    std::vector<std::string> res;
    std::stack<std::string> st;
    st.push(start);
    while (!st.empty()){
        std::string el = st.top();
        if (edges[el].empty()){
            res.push_back(el);
            st.pop();
        } else {
            st.push(edges[el].back());
            edges[el].pop_back();
        }
    }
    return res;
}

int main() {
    std::ifstream input("..\\input\\ba3j.txt");
    std::unordered_map<std::string, std::vector<std::string>> edges;
    std::unordered_set<std::string> all_nodes;
    int k, d;
    input >> k >> d;
    std::string str;
    int num = 0;
    while (input >> str) {
        ++num;
        std::string first = str.substr(0, k);
        std::string second = str.substr(k + 1, k);
        std::string node_start = read_concat(first.substr(0, k - 1), second.substr(0, k - 1));
        std::string node_end = read_concat(first.substr(1, k - 1), second.substr(1, k - 1));
        edges[node_start].push_back(node_end);
        all_nodes.insert(node_start);
        all_nodes.insert(node_end);
    }
    std::vector<std::string> start = find_start(edges, all_nodes);
    assert(start.size() == 1);
    std::vector<std::string> path = find_path(start[0], edges);
    std::string result;
    std::string result2;
    result += path.back().substr(0, k-1);
    result2 += path.back().substr(k, k-1);
    for (int i = path.size() - 2; i >= 0; --i){
        result += path[i][k-2];
        result2 += path[i].back();
    }
    std::string fin_res;
    int len = num + 2 * k + d - 1;
    int second_start = len - result2.length();
    fin_res = result.substr(0, second_start);
    fin_res += result2;
    std::ofstream output("..\\output\\ba3j.txt");
    output << fin_res;
    return 0;
}
