#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Запуск тестов test_rect_operations.cpp" << std::endl;
    
        // Тест 1: move с одним параметром (только по X)
    {
        std::cout << "  Тест 1: move с одним параметром" << std::endl;
        Rect r(10, 20, 40, 30);
        r.move(7);  // сдвиг на 7 по X, Y не меняется
        assert(r.get_left() == 17);   // 10+7=17
        assert(r.get_right() == 27);  // 20+7=27
        assert(r.get_top() == 40);    // не изменилось
        assert(r.get_bottom() == 30); // не изменилось
    }

    // Тест 2: move с двумя параметрами
    {
        std::cout << "  Тест 2: move с двумя параметрами" << std::endl;
        Rect r(10, 20, 40, 30);
        r.move(5, 3);  // сдвиг на 5 по X, на 3 по Y
        assert(r.get_left() == 15);   // 10+5=15
        assert(r.get_right() == 25);  // 20+5=25
        assert(r.get_top() == 43);    
        assert(r.get_bottom() == 33); 
    }
    
    
    // Тест 3: inflate с одним параметром
    {
        std::cout << "  Тест 3: inflate с одним параметром" << std::endl;
        Rect r(10, 20, 40, 30);
        r.inflate(2);  // расширить на 2 во все стороны
        assert(r.get_left() == 8);    // 10-2=8
        assert(r.get_right() == 22);  // 20+2=22
        assert(r.get_top() == 42);    
        assert(r.get_bottom() == 28); 
    }
    
    // Тест 4: inflate с двумя параметрами
    {
        std::cout << "  Тест 4: inflate с двумя параметрами" << std::endl;
        Rect r(10, 20, 40, 30);
        r.inflate(3, 4);  // по горизонтали на 3, по вертикали на 4
        assert(r.get_left() == 7);    // 10-3=7
        assert(r.get_right() == 23);  // 20+3=23
        assert(r.get_top() == 44);   
        assert(r.get_bottom() == 26); 
    }
    
    // Тест 5: inflate с четырьмя параметрами
    {
        std::cout << "  Тест 5: inflate с четырьмя параметрами" << std::endl;
        Rect r(10, 20, 40, 30);
        r.inflate(1, 2, 5, 4);  // разные стороны
        assert(r.get_left() == 9);    // 10-1=9
        assert(r.get_right() == 22);  // 20+2=22
        assert(r.get_top() == 45);   
        assert(r.get_bottom() == 26); 
    }
    
    std::cout << "Все тесты пройдены успешно" << std::endl;
    return 0;
}