#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"
#include <iostream>  // для std::ostream и std::cerr

// Внедренный означает, что объект Point хранится прямо внутри Circle (нет отдельного выделения памяти, нет указателей)
// Обращение к полям - прямой доступ(через .), без лишних разыменований
// Когда Circle уничтожается, m_center уничтожается автоматически (внедрённые объекты живут и умирают вместе с родительским объектом)

class Circle {
private:
    Point m_center; // внедренный объект - центр круга
    double m_radius; // радиус круга

public:

    /* Конструктор с координатами центра и радиусом
        Если бы мы написали:
        Circle(double x, double y, double r) {
             m_center = Point(x, y);
             m_radius = r;
           }
        То было бы два вызова: конструктор по умолчанию + оператор присваивания
        А со списком инициализации  один вызов конструктора с параметрами
     */
    Circle(double x = 0.0, double y = 0.0, double r = 0.0);
    
    // Конструктор с готовым объектом Point. Тоже использует список инициализации
    // const слева от параметра - параметр не меняется
    Circle(const Point& center, double r);
    
    //default - явное указание компилятору сгенерировать стандартную реализацию конструктора копирования, оператора присваивания или деструктора
    Circle(const Circle&) = default; // конструктор копирования
    Circle& operator=(const Circle&) = default; // оператор присваивания
    ~Circle() = default; // деструктор
    

    // Геттеры
    // Возвращает копию центра, чтобы внешний код не мог изменить центр круга
    Point getCenter() const;
    
    // Возвращает копию радиуса
    double getRadius() const;
    
    
    // Сеттеры
    // Установка нового центра
    Circle& setCenter(const Point& center);
    
    // Установка радиуса с проверкой
    Circle& setRadius(double r);
    
    
    // Метод вычисления площади
    // const в конце - метод не меняет текущий объект
    double area() const;
    
    
    // Оператор сравнения
    // const в конце - метод не меняет текущий объект
    // const слева от параметра - параметр не меняется
    bool operator==(const Circle& other) const;
    
    
    // Дружественный оператор вывода
    // не может быть методом класса, потому что левый операнд должен быть std::ostream&, а не объектом нашего класса
    friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};

#endif