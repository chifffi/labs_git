#include "list.hpp"
#include <iostream>

int main() {
    List original;
    original.pushBack(Circle(1, 1, 1));
    original.pushBack(Circle(2, 2, 2));
    original.pushBack(Circle(3, 3, 3));
    
    std::cout << "Оригинал: \n" << original;
    
    std::cout << "\nКонструктор копирования \n";
    List copy(original);
    std::cout << "Копия: \n" << copy;
    
    std::cout << "\nОператор присваивания \n";
    List assigned;
    assigned.pushBack(Circle(99, 99, 99));
    assigned = original;
    std::cout << "После присваивания: \n" << assigned;
    
    return 0;
}