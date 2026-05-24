#include "circle.hpp"
#include <cmath>
const double p = M_PI; // макрос из 1 семетра

// Конструктор с координатами центра и радиусом по умолчанию
Circle::Circle(double x, double y, double r): m_center(x, y), m_radius(r >= 0 ? r : 0)
{
    if (r < 0) {
        std::cerr << "Предупреждение: отрицательный радиус (" << r << ") заменён на 0\n";
    }
}

// Конструктор с готовым объектом Point
Circle::Circle(const Point& center, double r)
    : m_center(center) // копируем центр (вызов конструктора копирования Point)
    , m_radius(r >= 0 ? r : 0)
{
    if (r < 0) {
        std::cerr << "Предупреждение: отрицательный радиус (" << r << ") заменён на 0\n";
    }
}

// Геттеры
// Возвращает копию центра
Point Circle::getCenter() const {
    return m_center;
}

// Возвращает копию радиуса
double Circle::getRadius() const {
    return m_radius;
}

// Сеттеры
// Установка нового центра
// Возвращает ссылку на текущий объект (*this) для цепочек вызовов
Circle& Circle::setCenter(const Point& center) {
    m_center = center; // копируем новый центр
    return *this; // возвращаем ссылку на себя
}

// Установка радиуса с проверкой
Circle& Circle::setRadius(double r) {
    if (r >= 0) {  // радиус не может быть отрицательным
        m_radius = r;
    } 
    // Если радиус отрицательный, оставляем старый
    else {
        std::cerr << "Предупреждение: попытка установить отрицательный радиус (" << r << ") проигнорирована\n";
    }
    return *this;
}


// Вычисление площади круга
double Circle::area() const {
    return p * m_radius * m_radius; 
}

// Оператор сравнения двух кругов
// Сравнивает по центру и радиусу
bool Circle::operator==(const Circle& other) const {
    return m_center == other.m_center && m_radius == other.m_radius;
}

// Дружественный оператор вывода в поток
std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << "center= " << c.m_center << ", r=" << c.m_radius << ", area=" << c.area();
    return os;
}