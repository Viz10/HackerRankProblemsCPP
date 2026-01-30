#include <iostream>
using namespace std;

///////////////////////////////////////////

template<int count, bool...digits>
struct reversed_binary_value_helper{};

template<int count, bool first>
struct reversed_binary_value_helper<count,first> {
    static int constexpr value = (!first) ? 0 : (1 << count);
};

template<int count, bool first, bool...digits>
struct reversed_binary_value_helper<count, first, digits...> {
    static int constexpr value = reversed_binary_value_helper<count + 1, digits...>::value + ((!first) ? 0 : (1 << count));
};

template<bool...digits>
int reversed_binary_value() {
    return reversed_binary_value_helper<0, digits...>::value;
}

///////////////////////////////////////////

template <int n, bool...digits>
struct CheckValues {
    static void check(int x, int y)
    {
        CheckValues<n - 1, 0, digits...>::check(x, y);
        CheckValues<n - 1, 1, digits...>::check(x, y);
    }
};

template <bool...digits>
struct CheckValues<0, digits...> {
    static void check(int x, int y)
    {
        int z = reversed_binary_value<digits...>();
        std::cout << (z + 64 * y == x);
    }
};

int main()
{
    int t; 
    std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int x, y;
        cin >> x >> y;
        CheckValues<6>::check(x, y);
        cout << "\n";
    }
}

