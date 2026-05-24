#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
private:
    double m_x; // координата х
    double m_y; // координата у

public:
    Point(double x = 0.0, double y = 0.0); // конструктор с параметрами по умолчанию

    //default - явное указание компилятору сгенерировать стандартную реализацию конструктора копирования, оператора присваивания или деструктора
    Point(const Point&) = default; // конструктор копирования
    Point& operator=(const Point&) = default; // оператор присваивания
    ~Point() = default; // деструктор
    
    // Геттеры
    double getX() const;
    double getY() const;

    // Сеттеры
    Point& setX(double x);
    Point& setY(double y);
    
    // Оператор сравнения
    // const в конце - метод не меняет текущий объект
    // const слева от параметра - параметр не меняется
    bool operator==(const Point& other) const;

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif