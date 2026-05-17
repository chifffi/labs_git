#include "list.hpp"
#include <iostream>

int main() {
    List emptyList;
    
    std::cout << "Пустой список:\n";
    std::cout << "empty() = " << (emptyList.empty() ? "true" : "false") << "\n";
    std::cout << "size() = " << emptyList.size() << "\n";
    std::cout << "Вывод: " << emptyList;
    
    Circle testCircle(0, 0, 5); // не добавили в лист
    if (emptyList.removeFirst(testCircle)) {
        std::cout << "Удаление из пустого: получилось (неправильно)\n";
    } else {
        std::cout << "Удаление из пустого: не получилось (правильно)\n";
    }
    
    return 0;
}