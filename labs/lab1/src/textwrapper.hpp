#ifndef TEXTWRAPPER_HPP
#define TEXTWRAPPER_HPP

#include "mystring.hpp"

class TextWrapper {
private:
    MyString text; // исходный текст
    int maxwidth;  // максимальная ширина строки = 40 по задаче
    int* arr_end; // массив позиций концов строк
    int* arr_start; //массив начала строк без пробелов
    int linecount; // количество строк
    char** arr_wrapped; // массив строк для вывода
    
public:

    bool is_space(char c);
    bool is_end(int pos, int totallen);
    int space_before(int start, int end, char* mytext); // поиск пробела справа налево
    void skip_spaces(int& pos, int totallen, char* mytext); // пропуск пробелов в начале строки
    void copy_part(char* neww, char* old, int start, int end); // копирование части строки с start по end включительно
    TextWrapper(const MyString& text, int width);
    ~TextWrapper();
    void wrap_text(); // разбиение текста на строки
    void print_wrapped(); // вывод
};

#endif