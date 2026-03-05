#include "textwrapper.hpp"
#include <iostream>

// Конструктор
TextWrapper::TextWrapper(const MyString& t, int width) 
    : text(t), //вызывается конструктор копирования,  text создается сразу с t
      maxwidth(width),
      arr_end(nullptr),
      arr_start(nullptr),
      linecount(0),
      arr_wrapped(nullptr) {
}

// Деструктор
TextWrapper::~TextWrapper() {
    delete[] arr_end;
    delete[] arr_start;
    
    if (arr_wrapped != nullptr) 
    {
        for (int i = 0; i < linecount; i+=1) 
        {
            delete[] arr_wrapped[i];
        }
        delete[] arr_wrapped;
    }
}

bool TextWrapper::is_space(char c) {
    return c == ' '; //равны true, нет false
}

bool TextWrapper::is_end(int pos, int totallen) {
    return pos >= totallen; //вышло или на конце true, внутри false
}

// Поиск пробела справа налево
int TextWrapper::space_before(int start, int end, char* mytext) {
    for (int k = end; k >= start; k-=1) 
    {
        if (is_space(mytext[k])) 
        {
            return k;
        }
    }
    return -1; // пробел не найден
}

// Пропуск пробелов в начале строки
void TextWrapper::skip_spaces(int& pos, int totallen, char* mytext) {
    while (pos < totallen && is_space(mytext[pos])) 
    {
        pos+=1;
    }
}

// Копирование части строки с start по end включительно
void TextWrapper::copy_part(char* neww, char* old, int start, int end) {
    int len = end - start + 1;

    if (len > maxwidth) 
    {
        len = maxwidth;  // обрезаем до допустимой длины
    }

    for (int i = 0; i < len; i+=1) 
    {
        neww[i] = old[start + i];
    }
    neww[len] = '\0';
}

// разбиение текста на строки
void TextWrapper::wrap_text() {
    int totallen = text.length_str();
    
    char* buf = new char[totallen + 1];
    for (int i = 0; i < totallen; i++) {
        buf[i] = text.get(i);
    }
    buf[totallen] = '\0';
    
    linecount = 0;
    arr_end = new int[10000];
    
    // массив для хранения начал строк
    arr_start = new int[10000];
    
    for (int i = 0; i < totallen;) {
        arr_start[linecount] = i;  // запоминаем начало без пробелов
        
        int end = i + maxwidth - 1;
        
        if (end >= totallen) 
        {
            end = totallen - 1;
        } 

        else 
        {
            int space = space_before(i, end, buf);
            if (space != -1) 
            {
                end = space;
            }
        }

        int tek_len = end - i + 1;
        if (tek_len > maxwidth) {
            end = i + maxwidth - 1;
        }
        
        arr_end[linecount] = end;
        linecount++;
        
        i = end + 1;
        skip_spaces(i, totallen, buf); 
    }
    
    arr_wrapped = new char*[linecount];
    for (int i = 0; i < linecount; i+=1) 
    {
        arr_wrapped[i] = new char[maxwidth + 1];
    }
    
    for (int i = 0; i < linecount; i+=1) 
    {
        int start = arr_start[i];
        int end = arr_end[i];
        copy_part(arr_wrapped[i], buf, start, end);
    }
    
    delete[] buf;
}

// вывод
void TextWrapper::print_wrapped() {
    if (arr_wrapped == nullptr) {
        wrap_text();
    }
    
    std::cout << " ________________________________________" << std::endl;
    
    // Печатаем каждую строку с выравниванием по центру если надо
    for (int i = 0; i < linecount; i+=1) 
    {
        // длина текущей строки
        int str_len = 0;
        while (arr_wrapped[i][str_len] != '\0') 
        {
            str_len+=1;
        }
        
        std::cout << '|';
        // центрируем если меньше макс длины
        if (str_len < maxwidth) 
        {
            int left = (maxwidth - str_len) / 2;
            int right = maxwidth - left - str_len;
            
            // пробелы слева
            for (int k = 0; k < left; k+=1) 
            {
                std::cout << ' ';
            }
            // строка
            std::cout << arr_wrapped[i];
            // пробелы справа
            for (int k = 0; k < right; k+=1) 
            {
                std::cout << ' ';
            }
        } 
        //просто печатаем если макс длина
        else 
        {
            std::cout << arr_wrapped[i]; 
        }
        
        std::cout << '|' << std::endl;
    }
    
    std::cout << " ________________________________________ " << std::endl;
    std::cout << "     \\" << std::endl;
    std::cout << "      \\" << std::endl;
    std::cout << "        /\\_/\\   (" << std::endl;
    std::cout << "       ( ^.^ ) _)" << std::endl;
    std::cout << "         \\\"/  (" << std::endl;
    std::cout << "       ( | | )" << std::endl;
    std::cout << "      (__d b__)" << std::endl;

    // std::cout << " ________________________________________ \n"
    //              "     \\ \n"
    //              "      \\ \n"
    //              "        /\\_/\\   (\n" << std::endl;
    // std::cout << "       ( ^.^ ) _)" << std::endl;
    // std::cout << "         \\\"/  (" << std::endl;
    // std::cout << "       ( | | )" << std::endl;
    // std::cout << "      (__d b__)" << std::endl;
}