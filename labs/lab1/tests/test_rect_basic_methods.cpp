#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

//make build/test_rect_basic_methods.out
//./build/test_rect_basic_methods.out

int main() {
    std::cout << "Запуск тестов test_rect_basic_methods.out" << std::endl;
    
    //Конструктор по умолчанию
    {
        std::cout << "  Тест 1: Конструктор по умолчанию" << std::endl;
        Rect r;
        assert(r.get_left() == 0);
        assert(r.get_right() == 0);
        assert(r.get_top() == 0);
        assert(r.get_bottom() == 0);
    }
    
    //Конструктор с параметрами
    {
        std::cout << "  Тест 2: Конструктор с параметрами" << std::endl;
        Rect r(1, 2, 5, 3);
        assert(r.get_left() == 1);
        assert(r.get_right() == 2);
        assert(r.get_top() == 5);
        assert(r.get_bottom() == 3);
    }
    
    //Конструктор копирования
    {
        std::cout << "  Тест 3: Конструктор копирования" << std::endl;
        Rect r1(1, 8, 7, 2);
        Rect r2 = r1;
        assert(r2.get_left() == 1);
        assert(r2.get_right() == 8);
        assert(r2.get_top() == 7);
        assert(r2.get_bottom() == 2);
    }
    
    //Метод set_all
    {
        std::cout << "  Тест 4: Метод set_all" << std::endl;
        Rect r;
        r.set_all(5, 10, 30, 20);
        assert(r.get_left() == 5);
        assert(r.get_right() == 10);
        assert(r.get_top() == 30);
        assert(r.get_bottom() == 20);
    }
    
    
    //Проверка независимости копий
    {
        std::cout << "  Тест 5: Независимость копий" << std::endl;
        Rect r1(1, 2, 4, 3);
        Rect r2 = r1;
        r2.set_all(5, 6, 8, 7);
        
        assert(r1.get_left() == 1);
        assert(r1.get_right() == 2);
        assert(r1.get_top() == 4);
        assert(r1.get_bottom() == 3);
        
        assert(r2.get_left() == 5);
        assert(r2.get_right() == 6);
        assert(r2.get_top() == 8);
        assert(r2.get_bottom() == 7);
    }
    
    std::cout << "Все тесты пройдены успешно" << std::endl;
    return 0;
}