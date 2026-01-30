#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
    int n{}, m{};
public:
    vector<vector<int>> a;
    Matrix() = default;
    Matrix(int n,int m) : n{n},m{m} {}

    Matrix operator+(const Matrix& other) {
        Matrix result;
        std::for_each(std::cbegin(a), std::cend(a), [&result, &other, i = 0](const auto& vec) mutable {
            vector<int> aux(vec.size(), 0);
            std::transform(std::cbegin(vec), std::cend(vec),
                std::cbegin(other.a[i++]), std::begin(aux),
                [](int a, int b) { return a + b; });
            result.a.emplace_back(aux);
            });
        return result;
    }

};


int main() {

    int cases, k;
    cin >> cases;

    for (k = 0; k < cases; k++) {

        Matrix x,y,result;
        int n, m, i, j;
        cin >> n >> m;

        for (i = 0; i < n; i++) {

            vector<int> b;
            int num;

            for (j = 0; j < m; j++) {
                cin >> num;
                b.emplace_back(num);
            }
            x.a.emplace_back(b);
        }
        for (i = 0; i < n; i++) {
            vector<int> b;
            int num;
            for (j = 0; j < m; j++) {
                cin >> num;
                b.emplace_back(num);
            }
            y.a.emplace_back(b);
        }
        result = x + y;
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                cout << result.a[i][j] << " ";
            }
            cout << "\n";
        
        }
    }
    return 0;
}
