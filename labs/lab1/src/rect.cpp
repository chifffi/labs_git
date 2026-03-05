#include "rect.hpp"
/*
int minn(int x, int y) { 
    if (x<=y)
        return x;
    return y;
}

int maxx(int x, int y) { 
    if (x>=y)
        return x;
    return y;
}

int Rect::get_left() {
    return left_coord;
}

int Rect::get_right() {
    return right_coord;
}

int Rect::get_top() {
    return top_coord;
}

int Rect::get_bottom() {
    return bottom_coord;
}

// Конструктор с параметрами
Rect::Rect(int cl, int cr, int ct, int cb) {
    set_all(cl, cr, ct, cb);
    std::cout << "Вызван конструктор с параметрами!! " << this << std::endl;
}

// Конструктор по умолчанию
Rect::Rect() {
    left_coord = 0;
    right_coord = 0;
    top_coord = 0;
    bottom_coord = 0;
    std::cout << "Вызван конструктор по умолчанию!! " << this << std::endl;
}

// Деструктор
Rect::~Rect() {
    std::cout << "Вызван деструктор!! " << this << std::endl;
}

// Конструктор копирования
Rect::Rect(const Rect &old) {
    left_coord = old.left_coord;
    right_coord = old.right_coord;
    top_coord = old.top_coord;
    bottom_coord = old.bottom_coord;
    std::cout << "Вызван конструктор копирования!! " << this << std::endl;
}

//Установка значений
void Rect::set_all(int left, int right, int top, int bottom)
{
	left_coord = minn(left, right);
    right_coord = maxx(left, right);
    top_coord = maxx(top, bottom);
    bottom_coord = minn(top, bottom);
}

//От центра на amount
void Rect::inflate(int amount) {
	left_coord -= amount;
    right_coord += amount;
    top_coord += amount;
    bottom_coord -= amount;

}

//По горизонтал на dw, по вертикали на dh
void Rect::inflate(int dw, int dh) {
	left_coord -= dw;
    right_coord += dw;
    top_coord += dh;
    bottom_coord -= dh;
}

//Каждая на определенное значение
void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
	left_coord -= d_left;
    right_coord += d_right;
    top_coord += d_top;
    bottom_coord -= d_bottom;
}

//Перемещение по осям, у по умолч 0
void Rect::move(int x, int y) {
	left_coord += x;
    right_coord += x;
    top_coord += y;
    bottom_coord += y;
}

//возврат наим прямоугольника, в котором находятся `r1` и `r2`
Rect bounding_rect(Rect r1, Rect r2) {
	int new_left = minn(r1.get_left(), r2.get_left());
	int new_right = maxx(r1.get_right(), r2.get_right());
	int new_top = maxx(r1.get_top(), r2.get_top());
	int new_bottom = minn(r1.get_bottom(), r2.get_bottom());
	Rect new_rect(new_left, new_right, new_top, new_bottom);
	return new_rect;

}

//печать прямоугольника
void print_rect(Rect &r) {
	int left = r.get_left();
    int right = r.get_right();
    int top = r.get_top();
    int bottom = r.get_bottom();
    
    for (int y = bottom; y <= top; y++) 
    {
        for (int x = left; x <= right; x++) 
        {
            if (y == top or y == bottom or x == left or x == right) 
            {
            		std::cout << "#";
            }
            else 
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;  // переход на новую строку
    }
}

//возврат ширины
int Rect::get_width() {
    return right_coord - left_coord;;
}

////возврат высоты
int Rect::get_height() {
    return top_coord - bottom_coord;
}

//возврат площади
int Rect::get_square() {
    return get_width() * get_height();
}

//установка ширины
void Rect::set_width(int new_width) {
    if (new_width <= 0) 
    {
        std::cout << "ширина должна быть положительной" << std::endl;
        return;
    }
    right_coord = left_coord + new_width;

}

//установка высоты
void Rect::set_height(int new_height) {
    if (new_height <= 0) 
    {
        std::cout << "высота должна быть положительной" << std::endl;
        return;
    }
    top_coord = bottom_coord + new_height;
}
*/

int minn(int x, int y) { 
    if (x<=y)
        return x;
    return y;
}

int maxx(int x, int y) { 
    if (x>=y)
        return x;
    return y;
}


//возврат координат границ
int Rect::get_left() {
    return coodr_x;
}

int Rect::get_right() {
    return coodr_x + width;
}

int Rect::get_top() {
    return coodr_y + height;
}

int Rect::get_bottom() {
    return coodr_y;
}

//конструктор с параметрами
Rect::Rect(int cl, int cr, int ct, int cb) {
    set_all(cl, cr, ct, cb);
    std::cout << "Вызван конструктор с параметрами!! " << this << std::endl;
}

//конструктор по умолчанию
Rect::Rect() {
    coodr_x = 0;
    coodr_y = 0;
    width = 0;
    height = 0;
    std::cout << "Вызван конструктор по умолчанию!! " << this << std::endl;
}

//деструктор
Rect::~Rect() {
    std::cout << "Вызван деструктор!! " << this << std::endl;
}

//конструктор копирования
Rect::Rect(const Rect &old) {
    coodr_x = old.coodr_x;
    coodr_y = old.coodr_y;
    width = old.width;
    height = old.height;
    std::cout << "Вызван конструктор копирования!! " << this << std::endl;
}

//установка значений
void Rect::set_all(int left, int right, int top, int bottom) {
    int left_coord = minn(left, right);
    int right_coord = maxx(left, right);
    int top_coord = maxx(top, bottom);
    int bottom_coord = minn(top, bottom);
    
    coodr_x = left_coord;
    coodr_y = bottom_coord;
    width = right_coord - left_coord;
    height = top_coord - bottom_coord;
}

//от центра на amount
void Rect::inflate(int amount) {
    coodr_x -= amount;
    coodr_y -= amount;
    width += 2 * amount;
    height += 2 * amount;
}

//по горизонтали на dw, по вертикали на dh
void Rect::inflate(int dw, int dh) {
    coodr_x -= dw;
    coodr_y -= dh;
    width += 2 * dw;
    height += 2 * dh;
}

//каждая на определенное значение
void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    coodr_x -= d_left;
    coodr_y -= d_bottom;
    width += d_left + d_right;
    height += d_bottom + d_top;
}

//перемещение по осям
void Rect::move(int dx, int dy) {
    coodr_x += dx;
    coodr_y += dy;
}

//возврат наим прямоугольника, в котором находятся `r1` и `r2`
Rect bounding_rect(Rect r1, Rect r2) {
    int new_left = minn(r1.get_left(), r2.get_left());
    int new_right = maxx(r1.get_right(), r2.get_right());
    int new_top = maxx(r1.get_top(), r2.get_top());
    int new_bottom = minn(r1.get_bottom(), r2.get_bottom());
    Rect new_rect(new_left, new_right, new_top, new_bottom);
    return new_rect;

}

//печать прямоугольника
void print_rect(Rect &r) {
    int left = r.get_left();
    int right = r.get_right();
    int top = r.get_top();
    int bottom = r.get_bottom();
    
    for (int y = bottom; y <= top; y+=1) 
    {
        for (int x = left; x <= right; x+=1) 
        {
            if (y == bottom || y == top || x == left || x == right) 
            {
                std::cout << "#";
            } 
            else 
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

//возврат ширины
int Rect::get_width() {
    return width;
}

//возврат высоты
int Rect::get_height() {
    return height;
}

//возврат площади
int Rect::get_square() {
    return width * height;
}

//установка ширины
void Rect::set_width(int new_width) {
    if (new_width <= 0) {
        std::cout << "ширина должна быть положительной" << std::endl;
        return;
    }
    width = new_width;
}

// Установка высоты
void Rect::set_height(int new_height) {
    if (new_height <= 0) {
        std::cout << "высота должна быть положительной" << std::endl;
        return;
    }
    height = new_height; 
}