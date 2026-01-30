#include <iostream>
#include <vector>
#include <memory>
#include <print>
#include <ranges>
#include <algorithm>
#include <expected>
#include <list>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

struct Workshops {
    int start_time;
    int duration;
    int end_time() const { return start_time + duration; }
    Workshops(int start_time,int duration) : start_time(start_time) , duration(duration){}
};


struct Available_Workshops {
    int size{};
    std::vector <Workshops> workshops;

    Available_Workshops() = default;

    Available_Workshops(int n) : size{ n } { workshops.reserve(n); }
    void print_elements() {
        for (auto [start_time, duration] : workshops) { std::println("{},{},{}", start_time, duration, start_time + duration); }
    }
};

enum class error{invalid_size};

template <std::ranges::range Container1, std::ranges::range Container2>
std::expected<Available_Workshops,error> initialize(const Container1& start_times, const Container2& durations)
    requires requires {start_times.size(); durations.size(); }
{
    
    if (start_times.size() != durations.size()) 
        return std::unexpected(error::invalid_size);

    Available_Workshops rez(start_times.size());

    auto first1 = start_times.begin();
    auto first2 = durations.begin();
    for (; first1 != start_times.end(); ++first1, ++first2) {
        rez.workshops.emplace_back(*first1, *first2);
    }

    return rez;
}

int CalculateMaxWorkshops(Available_Workshops& data) {
    if (data.size == 0) return 0;
    
    std::sort(std::begin(data.workshops), std::end(data.workshops), [](const Workshops& a, const Workshops& b) {
        return a.end_time() < b.end_time(); });

    int cnt = 1;
    int current_end_time = data.workshops[0].end_time();

    std::for_each(std::next(std::begin(data.workshops)), std::end(data.workshops), [&cnt,&current_end_time](const Workshops& current) {
        if (current.start_time >= current_end_time) {
            cnt++, current_end_time = current.end_time();
        }
    });
    /// Workshop can be selected if it starts after or when the previous one ends
     
    return cnt;
}

/*
6
1 3 0 5 5 8
1 1 6 2 4 1


8 
1 3 0 5 8 5 6 9
2 4 6 7 9 9 8 10

*/

int main(int argc, char* argv[]) {
     // number of workshops
    
    std::array start_time{ 1 ,3 ,0 ,5 ,5 ,8 };
    std::list duration{ 1 ,1 ,6 ,2 ,4 ,1 };
   
    auto ptr=initialize(start_time, duration);
    if (ptr) {
        cout << CalculateMaxWorkshops(*ptr) << "\n";
  	  (*ptr).print_elements();
    }
    else if(ptr.error() == error::invalid_size) {
        std::println("sizes must be equal!");

    }
    else {
        std::println("unexpected error!");
    }
    
  
    return 0;
}