#include "list.hpp"
#include <iostream>

int main() {
    List list;
    
    for (int i = 1; i <= 5; i+=1) {
        list.pushBack(Circle(i, i, i));
    }
    
    std::cout << "До очистки, размер: " << list.size() << "\n";
    std::cout << list;
    
    std::cout << "\nОчистка \n";
    list.clear();
    
    std::cout << "После очистки, размер: " << list.size() << "\n";
    std::cout << "empty() = " << (list.empty() ? "true" : "false") << "\n";
    std::cout << "Вывод: " << list;
    
    std::cout << "\nДобавление после очистки \n";
    list.pushBack(Circle(42, 52, 62));
    std::cout << list;
    
    return 0;
}