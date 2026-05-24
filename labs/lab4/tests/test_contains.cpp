#include "list.hpp"
#include <iostream>

int main() {
    List list;
    Circle c1(1, 1, 1);
    Circle c2(2, 2, 2);
    Circle c3(3, 3, 3);
    
    list.pushBack(c1);
    list.pushBack(c2);
    
    std::cout << "Список: \n" << list;
    
    std::cout << "\nПоиск \n";
    std::cout << "Содержит " << c1 << "? " << (list.contains(c1) ? "Да" : "Нет") << "\n";
    std::cout << "Содержит " << c2 << "? " << (list.contains(c2) ? "Да" : "Нет") << "\n";
    std::cout << "Содержит " << c3 << "? " << (list.contains(c3) ? "Да" : "Нет") << "\n";
    
    std::cout << "\nПоиск в пустом списке \n";
    List emptyList;
    std::cout << "Содержит " << c1 << "? " << (emptyList.contains(c1) ? "Да" : "Нет") << "\n";
    
    return 0;
}