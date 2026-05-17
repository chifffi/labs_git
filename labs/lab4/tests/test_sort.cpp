#include "list.hpp"
#include <iostream>

int main() {
    List list;
    
    list.pushBack(Circle(0, 0, 10));
    list.pushBack(Circle(0, 0, 1));
    list.pushBack(Circle(0, 0, 5));
    list.pushBack(Circle(0, 0, 3));
    list.pushBack(Circle(0, 0, 7));
    list.pushBack(Circle(0, 0, 2));
    list.pushBack(Circle(0, 0, 8));
    
    std::cout << "До сортировки:\n" << list;
    
    list.sortByArea();
    
    std::cout << "\nПосле сортировки: \n" << list;
    
    return 0;
}