#include "vector.hpp"


int main(int, char**){
    Vector<unsigned int> vec;
    std::cout << "Заполнение вектора через push_back\n";
    for(int i = 10; i >= 0; --i){
        vec.push_back((unsigned int)i);
        std::cout << "size = " << vec.size() << " cap = " << vec.capacity() << "\n";
    }
    std::cout << "Содержимое вектора (вывод через метод at)\n";
    for(int i = 0; i < vec.size(); ++i){
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (вывод через оператор [])\n";
    for(int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (вывод через range-based for loop)\n";
    for(auto value : vec){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (вывод через итераторы)\n";
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (вывод через константные итераторы)\n";
    for(auto it = vec.cbegin(); it != vec.cend(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (вывод и увеличение значения через итераторы)\n";
    for(auto it = vec.begin(); it != vec.end(); ++it){
        (*it)++;
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Вставка в середину вектора с помощью метода insert\n";
    vec.insert(5, 99ul);
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (удаление элемента с помощью erase())\n";
    vec.erase(5);
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Содержимое вектора (удаление элемента с помощью pop_back())\n";
    std::cout << vec.pop_back() << std::endl;
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Применение метода std::sort\n";
    std::sort(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Применение метода std::find\n";
    auto it =  std::find(vec.begin(), vec.end(), 7);
    if(it != vec.end()){
        std::cout << "Индекс искомого элемента - " << it - vec.begin() << std::endl;
    }
    
    std::cout << "Применение метода std::reverse\n";
    std::reverse(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
