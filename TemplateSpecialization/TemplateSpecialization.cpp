
#include <iostream>
#include <print>

using std::cin;
using std::cout;
using std::string;
using std::endl;


auto add(auto&& a, auto&& b) {
    return a + b;
}

template<typename T, typename U>
concept addable = requires (T t, U u) {
    { t + u } -> std::convertible_to<std::common_type_t<T,U>>;
};

template<typename T>
class AddElements {
    T element;
public:
    AddElements(const T& element): element(element){}
    
    template <typename U> requires addable<T,U>
    auto add(const U & other) { return element + other; }
  
};

template<typename Type>
AddElements(Type t) -> AddElements<Type>;

template<> /// full specialization of the class
class AddElements<string> {
    string element;
public:
    AddElements(const string& element) : element(element) {}
    string& concatenate(const string& other) { return element = element + other; }
};

int main() {
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++) {
        string type;
        cin >> type;
        if (type == "float") {
            double element1, element2;
            cin >> element1 >> element2;
            AddElements myfloat(element1);
            cout << myfloat.add(element2) << endl;
        }
        else if (type == "int") {
            int element1, element2;
            cin >> element1 >> element2;
            AddElements myint(element1);
            cout << myint.add(element2) << endl;
        }
        else if (type == "string") {
            string element1, element2;
            cin >> element1 >> element2;
            AddElements mystring(element1);
            cout << mystring.concatenate(element2) << endl;
        }
    }
    return 0;
}


