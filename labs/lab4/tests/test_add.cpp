#include "list.hpp"
#include <iostream>

int main() {
    List list;
    
    std::cout << "Добавление в конец (pushBack):\n";
    list.pushBack(Circle(0, 0, 5));
    list.pushBack(Circle(1, 1, 3));
    list.pushBack(Circle(2, 2, 7));
    
    std::cout << "После pushBack:\n" << list;
    std::cout << "Размер: " << list.size() << "\n";
    
    std::cout << "\nДобавление в начало (pushFront):\n";
    list.pushFront(Circle(10, 10, 1));
    list.pushFront(Circle(20, 20, 2));
    
    std::cout << "После pushFront:\n" << list;
    std::cout << "Размер: " << list.size() << "\n";
    
    return 0;
}