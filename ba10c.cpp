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

void reverseStr(std::string &str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        std::swap(str[i], str[n - i - 1]);
}

int main() {
    std::ifstream input("..\\input\\ba10c.txt");
    std::string str;
    input >> str;
    std::string cur;
    input >> cur >> cur;
    std::vector<char> alphabet;
    while (cur.length() == 1) {
        alphabet.push_back(cur[0]);
        input >> cur;
    }
    std::vector<char> conditions;
    input >> cur;
    while (cur.length() == 1) {
        conditions.push_back(cur[0]);
        input >> cur;
    }
    std::unordered_map<char, std::unordered_map<char, double>> transitions;
    double possibility;
    for (auto &t : conditions) {
        input >> cur;
    }
    for (auto &t : conditions) {
        input >> cur;
        for (auto &k : conditions) {
            input >> possibility;
            transitions[t][k] = possibility;
        }
    }
    input >> cur;
    std::unordered_map<char, std::unordered_map<char, double>> emission;
    for (auto &t : alphabet) {
        input >> cur;
    }
    for (auto &t : conditions) {
        input >> cur;
        for (auto &k : alphabet) {
            input >> possibility;
            emission[t][k] = possibility;
        }
    }
    std::vector<std::vector<double>> matrix(str.length(), std::vector<double>(conditions.size()));
    std::vector<std::vector<int>> matrix_way(str.length(), std::vector<int>(conditions.size(), -1));
    char ch = str[0];
    for (int i = 0; i < conditions.size(); ++i) {
        matrix[0][i] = emission[conditions[i]][ch];
    }

    for (int str_index = 1; str_index < str.length(); ++str_index) {
        char cur_char = str[str_index];
        for (int cur_condition = 0; cur_condition < conditions.size(); ++cur_condition) {
            double maxx = 0;
            int way = -1;
            double cur_emission = emission[conditions[cur_condition]][cur_char];
            for (int prev_condition = 0; prev_condition < conditions.size(); ++prev_condition) {
                double a = matrix[str_index-1][prev_condition] * transitions[conditions[prev_condition]][conditions[cur_condition]];
                if (maxx < a){
                    way =  prev_condition;
                    maxx = a;
                }
            }
            matrix[str_index][cur_condition] = maxx * cur_emission;
            matrix_way[str_index][cur_condition] = way;
        }
    }
    int biggest_index = -1;
    double biggest = 0;
    for (int i = 0; i < conditions.size(); i++){
        if (biggest < matrix.back()[i]){
            biggest = matrix.back()[i];
            biggest_index = i;
        }
    }
    std::string result;
    result += conditions[biggest_index];
    int cur_index = matrix_way.back()[biggest_index];
    int cur_level = str.length() - 2;
    while (cur_index != -1){
        result += conditions[cur_index];
        cur_index = matrix_way[cur_level--][cur_index];
    }
    reverseStr(result);
    std::cout << result;
    return 0;
}
