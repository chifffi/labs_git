#include <cassert>
#include <iostream>
#include "../src/rect.hpp"


int main() {
    std::cout << "Запуск тестов test_bounding_rect.cpp" << std::endl;
    
    // Тест 1: Обычные прямоугольники
    {
        std::cout << "  Тест 1: Обычные прямоугольники" << std::endl;
        Rect r1(0, 10, 10, 0);
        Rect r2(5, 15, 15, 5);
        Rect r3 = bounding_rect(r1, r2);
        
        assert(r3.get_left() == 0);
        assert(r3.get_right() == 15);
        assert(r3.get_top() == 15);
        assert(r3.get_bottom() == 0);
    }
    
    // Тест 2: Непересекающиеся прямоугольники
    {
        std::cout << "  Тест 2: Непересекающиеся прямоугольники" << std::endl;
        Rect r1(0, 5, 5, 0);
        Rect r2(10, 15, 15, 10);
        Rect r3 = bounding_rect(r1, r2);
        
        assert(r3.get_left() == 0);
        assert(r3.get_right() == 15);
        assert(r3.get_top() == 15);
        assert(r3.get_bottom() == 0);
    }
    
    // Тест 3: Один прямоугольник внутри другого
    {
        std::cout << "  Тест 3: Один прямоугольник внутри другого" << std::endl;
        Rect r1(0, 20, 20, 0);
        Rect r2(5, 15, 15, 5);
        Rect r3 = bounding_rect(r1, r2);
        
        assert(r3.get_left() == 0);
        assert(r3.get_right() == 20);
        assert(r3.get_top() == 20);
        assert(r3.get_bottom() == 0);
    }
    
    // Тест 4: С отрицательными координатами
    {
        std::cout << "  Тест 4: С отрицательными координатами" << std::endl;
        Rect r1(-10, 0, 0, -10);
        Rect r2(0, 10, 10, 0);
        Rect r3 = bounding_rect(r1, r2);
        
        assert(r3.get_left() == -10);
        assert(r3.get_right() == 10);
        assert(r3.get_top() == 10);
        assert(r3.get_bottom() == -10);
    }
    
        // Тест 5: Пользователь перепутал всё
    {
        std::cout << "  Тест 5: Все координаты перепутаны" << std::endl;
        // Пользователь ввел (20, 10, 20, 30) вместо (10, 20, 30, 20)
        Rect r1(20, 10, 20, 30); //(10, 20, 30, 20)
        Rect r2(15, 5, 5, 15); //(5, 15, 15, 5)
        
        Rect r3 = bounding_rect(r1, r2);
        
        assert(r3.get_left() == 5);
        assert(r3.get_right() == 20);
        assert(r3.get_top() == 30);
        assert(r3.get_bottom() == 5);
    }

    std::cout << "Все тесты пройдены успешно" << std::endl;
    return 0;
}