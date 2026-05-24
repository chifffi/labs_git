#include "list.hpp"
#include <iostream>

int main() {
    List list;
    
    Circle c1(0, 0, 5);
    Circle c2(1, 1, 5);
    Circle c3(2, 2, 3);
    Circle c4(0, 0, 5);
    Circle c5(0, 0, 5);
    
    list.pushBack(c1);
    list.pushBack(c2);
    list.pushBack(c3);
    list.pushBack(c4);
    list.pushBack(c5);
    
    std::cout << "Исходный список:\n" << list;
    
    std::cout << "\nУдаление первого элемента (0,0,5)\n";
    list.removeFirst(c1);
    std::cout << "После удаления:\n" << list;
    
    std::cout << "\nУдаление всех элементов (0,0,5)\n";
    size_t removed = list.removeAll(c1);
    std::cout << "Удалено: " << removed << "\n";
    std::cout << "После удаления:\n" << list;
    
    std::cout << "\nУдаление несуществующего \n";
    if (!list.removeFirst(Circle(99,99,99))) {
        std::cout << "Не найден (правильно)\n";
    }
    
    return 0;
}