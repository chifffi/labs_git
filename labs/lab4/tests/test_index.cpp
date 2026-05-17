#include "list.hpp"
#include <iostream>

int main() {
    List list;
    
    for (int i = 1; i <= 5; i+=1) {
        list.pushBack(Circle(i, i, i));
    }
    
    std::cout << "Список:\n" << list;
    
    std::cout << "\nЧтение по индексу \n";
    for (size_t i = 0; i < list.size(); i+=1) {
        std::cout << "list[" << i << "] = " << list[i] << "\n";
    }
    
    std::cout << "\nИзменение по индексу \n";
    std::cout << "list[2] до: " << list[2] << "\n";
    list[2] = Circle(100, 100, 100);
    std::cout << "list[2] после: " << list[2] << "\n";
    
    return 0;
}