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
    
    char get(int i) const; // получение i-того элемента строки
    void set(int i, char c); // установка i-того элемента строки
    
    void set_new_string(const char* str); // замена текущего содержимого на новое
    void print() const; // вывод строки на консоль
    void read_line(); // замена текущего содержимого строки на строку, считанную с консоли (неопределенного размера)
    int length_str() const;
    const char* get_Str() const { return stroka ? stroka : ""; };


    // Оператор присваивания
    //в параметре: & чтобы не создавалась лишняя копия other, const как гарантия что исходный объект other не изменится
    MyString& operator=(const MyString& other);

    // Операторы += 
    //изменяют сам объект поэтому выход MyString&
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);
    
    // дружественные функции для операторов +
    // создают новый объект поэтому без ссылки
    // третья точно должна быть глобальной из-за первого параметра(не объект класса), остальные глобальные для симметрии
    friend MyString operator+(const MyString& left, const MyString& right);
    friend MyString operator+(const MyString& left, const char* right);
    friend MyString operator+(const char* left, const MyString& right);

    
    //Move-семантика
    //Данные не копируются, а просто "крадутся" – забирается указатель на память. После move-операции исходный объект становится пустым.
    MyString(MyString&& other);  // move-конструктор
    MyString& operator=(MyString&& other); // move-оператор
    
    //операторы сравнения строк
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator>=(const MyString& other) const;

    // Операторы сравнения с const char*
    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;
    bool operator<(const char* str) const;
    bool operator<=(const char* str) const;
    bool operator>(const char* str) const;
    bool operator>=(const char* str) const;

    // Дружественные функции для сравнения const char* с MyString
    friend bool operator==(const char* str, const MyString& s);
    friend bool operator!=(const char* str, const MyString& s);
    friend bool operator<(const char* str, const MyString& s);
    friend bool operator<=(const char* str, const MyString& s);
    friend bool operator>(const char* str, const MyString& s);
    friend bool operator>=(const char* str, const MyString& s);

    // Оператор индексирования (доступ на запись и чтение)
    char& operator[](int index);
    // Константный оператор индексирования для константных объектов (только чтение)
    const char& operator[](int index) const;

    // Дружественные функции для операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
    friend std::istream& operator>>(std::istream& in, MyString& str);
    
};



#endif