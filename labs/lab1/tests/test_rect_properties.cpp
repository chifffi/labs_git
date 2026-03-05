#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Запуск тестов test_rect_properties.cpp" << std::endl;
    
    // Тест 1: get_width и get_height
    {
        std::cout << "  Тест 1: get_width и get_height" << std::endl;
        Rect r(10, 30, 50, 20);  
        assert(r.get_width() == 20);   
        assert(r.get_height() == 30);  
    }
    
    // Тест 2: get_square
    {
        std::cout << "  Тест 2: get_square" << std::endl;
        Rect r(0, 5, 10, 0);  
        assert(r.get_square() == 50);  
    }
    
    // Тест 3: set_width (левый угол не меняется)
    {
        std::cout << "  Тест 3: set_width" << std::endl;
        Rect r(10, 20, 50, 30); 
        r.set_width(25);
        assert(r.get_left() == 10);    // left не изменился
        assert(r.get_right() == 35);   // right = left + new_width = 10+25=35
        assert(r.get_width() == 25);
    }
    
    // Тест 4: set_height 
    {
        std::cout << "  Тест 4: set_height" << std::endl;
        Rect r(10, 20, 40, 30);  // top=40, bottom=30, height=10
        r.set_height(15);
        assert(r.get_top() == 45);  // top = bottom + 15
        assert(r.get_bottom() == 30); 
        assert(r.get_height() == 15);
    }
    
    
    // Тест 5: set_width с отрицательным значением (должен игнорироваться)
    {
        std::cout << "  Тест 5: set_width с отрицательным значением" << std::endl;
        Rect r(5, 10, 10, 5);
        int old_width = r.get_width();
        r.set_width(-5);
        assert(r.get_width() == old_width); // ширина не должна измениться
    }
    
    std::cout << "Все тесты пройдены успешно" << std::endl;
    return 0;
}