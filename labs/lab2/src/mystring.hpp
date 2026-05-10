#ifndef MYSTRING_HPP
#define MYSTRING_HPP

#include <iostream>

class MyString {

    int mylen; // длина без '\0'
    char* stroka; 
    
public:
    MyString(); // по умолчанию пустая
    MyString(const char* str); // объект выделяет память под копию этой строки
    MyString(const MyString &other); // конструктор копирования
    
    ~MyString();
    
    char get(int i); // получение i-того элемента строки
    void set(int i, char c); // установка i-того элемента строки
    
    void set_new_string(const char* str); // замена текущего содержимого на новое
    void print(); // вывод строки на консоль
    void read_line(); // замена текущего содержимого строки на строку, считанную с консоли (неопределенного размера)
    int length_str();
    
};


#endif