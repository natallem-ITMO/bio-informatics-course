#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>


std::vector<std::vector<int>> matr =
        {{4,  0,  -2, -1, -2, 0,  -2, -1, -1, -1, -1, -2, -1, -1, -1, 1,  0,  0,  -3, -2},
         {0,  9,  -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2},
         {-2, -3, 6,  2,  -3, -1, -1, -3, -1, -4, -3, 1,  -1, 0,  -2, 0,  -1, -3, -4, -3},
         {-1, -4, 2,  5,  -3, -2, 0,  -3, 1,  -3, -2, 0,  -1, 2,  0,  0,  -1, -2, -3, -2},
         {-2, -2, -3, -3, 6,  -3, -1, 0,  -3, 0,  0,  -3, -4, -3, -3, -2, -2, -1, 1,  3},
         {0,  -3, -1, -2, -3, 6,  -2, -4, -2, -4, -3, 0,  -2, -2, -2, 0,  -2, -3, -2, -3},
         {-2, -3, -1, 0,  -1, -2, 8,  -3, -1, -3, -2, 1,  -2, 0,  0,  -1, -2, -3, -2, 2},
         {-1, -1, -3, -3, 0,  -4, -3, 4,  -3, 2,  1,  -3, -3, -3, -3, -2, -1, 3,  -3, -1},
         {-1, -3, -1, 1,  -3, -2, -1, -3, 5,  -2, -1, 0,  -1, 1,  2,  0,  -1, -2, -3, -2},
         {-1, -1, -4, -3, 0,  -4, -3, 2,  -2, 4,  2,  -3, -3, -2, -2, -2, -1, 1,  -2, -1},
         {-1, -1, -3, -2, 0,  -3, -2, 1,  -1, 2,  5,  -2, -2, 0,  -1, -1, -1, 1,  -1, -1},
         {-2, -3, 1,  0,  -3, 0,  1,  -3, 0,  -3, -2, 6,  -2, 0,  0,  1,  0,  -3, -4, -2},
         {-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2, 7,  -1, -2, -1, -1, -2, -4, -3},
         {-1, -3, 0,  2,  -3, -2, 0,  -3, 1,  -2, 0,  0,  -1, 5,  1,  0,  -1, -2, -2, -1},
         {-1, -3, -2, 0,  -3, -2, 0,  -3, 2,  -2, -1, 0,  -2, 1,  5,  -1, -1, -3, -3, -2},
         {1,  -1, 0,  0,  -2, 0,  -1, -2, 0,  -2, -1, 1,  -1, 0,  -1, 4,  1,  -2, -3, -2},
         {0,  -1, -1, -1, -2, -2, -2, -1, -1, -1, -1, 0,  -1, -1, -1, 1,  5,  0,  -2, -2},
         {0,  -1, -3, -2, -1, -3, -3, 3,  -2, 1,  1,  -3, -2, -2, -3, -2, 0,  4,  -3, -1},
         {-3, -2, -4, -3, 1,  -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11, 2},
         {2,  -2, -3, -2, 3,  -3, 2,  -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1, 2,  7}};

std::unordered_map<char, int> get_pos_int() {
    std::unordered_map<char, int> res;
    std::vector<char> v = {'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V',
                           'W', 'Y'};
    for (int i = 0; i < v.size(); ++i) {
        res[v[i]] = i;
    }
    return res;
}

std::unordered_map<char, int> pos_int = get_pos_int();

int get_scoring_matrix_value(char a, char b) {
    auto &tt = pos_int;
    int posA = pos_int[a];
    int posB = pos_int[b];
    return matr[posA][posB];
}

void show_matrix(std::vector<std::vector<int>> &v, const std::string &d = "") {
    std::cout << d << "\n";
    for (auto &t : v) {
        for (int i : t) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

void reverseStr(std::string &str) {
    int n = str.length();

    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        std::swap(str[i], str[n - i - 1]);
}

void solve(const std::string &X, const std::string &Y) {
    int gap_opening_penalty = -11;
    int gap_extension_penalty = -1;
    int xlen = X.length() + 1;
    int ylen = Y.length() + 1;
    std::vector<std::vector<int>> I(ylen, std::vector<int>(xlen, 0));
    std::vector<std::vector<int>> Iw(ylen, std::vector<int>(xlen, 0));
    std::vector<std::vector<int>> D(ylen, std::vector<int>(xlen, 0));
    std::vector<std::vector<int>> Dw(ylen, std::vector<int>(xlen, 0));
    std::vector<std::vector<int>> M(ylen, std::vector<int>(xlen, 0));
    std::vector<std::vector<int>> Mw(ylen, std::vector<int>(xlen, 0));
    for (int i = 0; i < xlen; ++i) {
        if (i == 0) {
            continue;
        }
        I[0][i] = INT_MIN;
        Iw[0][i] = -1;
        D[0][i] = (i == 1) ? gap_opening_penalty : D[0][i - 1] + gap_extension_penalty;
        Dw[0][i] = 0;
        M[0][i] = std::max(I[0][i], D[0][i]);
        Mw[0][i] = (I[0][i] > D[0][i]) ? 1 : 0;
    }
    for (int i = 0; i < ylen; ++i) {
        if (i == 0) {
            continue;
        }
        D[i][0] = INT_MIN;
        Dw[i][0] = -1;
        I[i][0] = (i == 1) ? gap_opening_penalty : I[i - 1][0] + gap_extension_penalty;
        Iw[i][0] = 0;
        M[i][0] = std::max(I[i][0], D[i][0]);
        Mw[i][0] = (I[i][0] > D[i][0]) ? 1 : 0;
    }
//    show_matrix(D, "D");
//    show_matrix(I, "I");
//    show_matrix(M, "M");
    for (int i = 1; i < ylen; ++i) {
        for (int j = 1; j < xlen; ++j) {
            int first = (I[i - 1][j] == INT_MIN) ? INT_MIN : I[i - 1][j] + gap_extension_penalty;
            int second = M[i - 1][j] + gap_opening_penalty;
            if (first >= second) {
                I[i][j] = first;
                Iw[i][j] = 0;
            } else {
                I[i][j] = second;
                Iw[i][j] = 1;
            }
            first = (D[i][j - 1] == INT_MIN) ? INT_MIN : D[i][j - 1] + gap_extension_penalty;
            second = M[i][j - 1] + gap_opening_penalty;
            if (first >= second) {
                D[i][j] = first;
                Dw[i][j] = 0;
            } else {
                D[i][j] = second;
                Dw[i][j] = 1;
            }
            int third = M[i - 1][j - 1] + get_scoring_matrix_value(Y[i - 1], X[j - 1]);
            first = D[i][j];
            second = I[i][j];
            if (first >= second && first >= third) {
                M[i][j] = first;
                Mw[i][j] = 0;
            } else if (second >= first && second >= third) {
                M[i][j] = second;
                Mw[i][j] = 1;
            } else {
                M[i][j] = third;
                Mw[i][j] = 2;
            }
        }
    }
/*    show_matrix(M, "M");
    show_matrix(Mw, "Mw");
    show_matrix(I, "I");
    show_matrix(Iw, "Iw");
    show_matrix(D, "D");
    show_matrix(Dw, "Dw");*/
    std::cout.flush();
    std::string Xn;
    std::string Yn;
    int i = ylen - 1;
    int j = xlen - 1;
    bool isM = true;
    bool isD = false;
    bool isI = false;
    while (i != 0 && j != 0) {
        int k = M[i][j];
        if (isM) {
            if (Mw[i][j] == 2) {
                Xn += X[j - 1];
                Yn += Y[i - 1];
                --i;
                --j;
            } else {
                isM = false;
                if (Mw[i][j] == 1) {
                    isI = true;
                } else {
                    isD = true;
                }
            }
        } else if (isI) {
            Yn += Y[i - 1];
            Xn += '-';
            if (Iw[i][j] == 1) {
                isM = true;
                isI = false;
            }
            --i;
        } else {
            Xn += X[j - 1];
            Yn += '-';
            if (Dw[i][j] == 1) {
                isM = true;
                isD = false;
            }
            --j;
        }
    }
    reverseStr(Xn);
    reverseStr(Yn);
    std::cout << M[ylen - 1][xlen - 1] << "\n" << Xn << "\n" << Yn << "\n";
}

int main() {
    solve("RFTMKYCRHYNFMDRPHSHYQVIIWAYKLFILGWRWFQDVHCWCDHGPVICLVPMLLQPHTHAIYLGNKCLNEGPQEMFRRHGQKPL",
          "RFTHTPNRKYCRHYNFMDRPDSHYQVIIWAYKLFILGPPDKSARWDVCWCDHVVMRLVPMNQPHHDTANKCLNEGPQEMFRRVRSHVLHGWQKPL");
    return 0;
}
