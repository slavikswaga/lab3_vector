#include "vector.hpp"
#include <iostream>
#include <vector>

int main(int, char**){
    Container<unsigned long> vec;
    std::cout << vec.empty() << "\n";
    std::cout << vec.capacity() << "\n";
    std::cout << vec.size() << "\n";
    
    vec.reserve(20);

    std::cout << vec.empty() << "\n";
    std::cout << vec.capacity() << "\n";
    std::cout << vec.size() << "\n";

    return 0;
}
