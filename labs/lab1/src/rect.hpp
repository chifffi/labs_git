#ifndef RECT_HPP
#define RECT_HPP

#include <iostream>

class Rect {

/*int left_coord;
int right_coord;
int top_coord;
int bottom_coord;
*/
int coodr_x;  // x координата левого нижнего угла
int coodr_y;  // y координата левого нижнего угла
int width;    
int height;   

public:
    int get_left();
    int get_right();
    int get_top();
    int get_bottom();
    

    Rect(int cl, int cr, int ct, int cb);  //конструктор с параметрами
    Rect();  //конструктор по умолчанию
    ~Rect(); //деструктор
    Rect(const Rect &old); //конструктор копирования, параметр - константная ссылка на старый объект

    void set_all(int left, int right, int top, int bottom);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int x, int y = 0); //y по умолчанию 0, но можно задать другое значение

    int get_width();
    int get_height();
    int get_square();

    void set_width(int new_width);
    void set_height(int new_height);

};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);

#endif