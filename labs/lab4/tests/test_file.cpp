#include "list.hpp"
#include <iostream>

int main() {
    List list;
    list.pushBack(Circle(1.5, 2.5, 3.0));
    list.pushBack(Circle(4.0, 5.0, 6.0));
    list.pushBack(Circle(7.5, 8.5, 9.0));
    
    std::cout << "Исходный список: \n" << list;
    
    const char* filename = "test_circles.txt";
    
    std::cout << "\nСохранение в файл \n";
    list.saveToFile(filename);
    
    std::cout << "\nЗагрузка из файла \n";
    List newList;
    newList.loadFromFile(filename);
    std::cout << "Загруженный список:\n" << newList;
    
    return 0;
}