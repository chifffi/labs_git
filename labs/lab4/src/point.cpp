#include "point.hpp"

// Конструктор
Point::Point(double x, double y) : m_x(x), m_y(y) {}


// Геттеры
double Point::getX() const {
    return m_x;
}

double Point::getY() const {
    return m_y;
}

// Сеттеры возвращают ссылку для цепочек вызовов
Point& Point::setX(double x) {
    m_x = x;
    return *this;
}

Point& Point::setY(double y) {
    m_y = y;
    return *this;
}

// Оператор сравнения
// const в конце - метод не меняет текущий объект
// const слева от параметра - параметр не меняется
bool Point::operator==(const Point& other) const {
    return m_x == other.m_x && m_y == other.m_y;
}

// Оператор вывода
// const слева от параметра - параметр не меняется
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.m_x << ", " << p.m_y << ")";
    return os;
}