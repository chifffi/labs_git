#include "mystring.hpp"
#include <cstring>   // для strlen, strcpy

MyString::MyString() {
    // TODO: убрать выделение память
    // TODO: обработать везде nullptr
	mylen = 0;
    stroka = nullptr;


}

// объект выделяет память под копию этой строки
MyString::MyString(const char* str) {
    // TODO: обработать nullptr и тут тоже
    if (str == nullptr) {
        throw "передан нулевой указатель в конструктор!!";
    }
	mylen = strlen(str);
    stroka = new char[mylen + 1];  // +1 для '\0'
    
    for (int i = 0; i <= mylen; i+=1)
    {
        stroka[i] = str[i];
    }

}

// конструктор копирования
MyString::MyString(const MyString &other) {
    if (other.stroka == nullptr) {
        throw "строка пустая!!";
    }
	mylen = other.mylen;
    stroka = new char[mylen + 1]; // +1 для '\0'
    
    for (int i = 0; i <= mylen; i+=1) 
    {
        stroka[i] = other.stroka[i];
    }
}

MyString::~MyString() {
	if (stroka != nullptr) {
        delete[] stroka;
    }
}

// получение i-того элемента строки
char MyString::get(int i) {
    if (stroka == nullptr) {
        throw "строка пустая!!";
    }
	if (i < 0 || i >= mylen) 
	{
        std::cout<<"индекс выходит за границы!!: получение i-того элемента строки"<<std::endl;
        return '\0';  // нулевой символ при ошибке
    }
    return stroka[i];
}

// установка i-того элемента строки
void MyString::set(int i, char c){
    if (stroka == nullptr) {
        throw "строка пустая!!";
    }
	if (i >= 0 && i < mylen) 
	{
        stroka[i] = c;
    }
    else {
    	std::cout<<"индекс выходит за границы!!: установка i-того элемента строки"<<std::endl;
    }
}

// замена текущего содержимого на новое
void MyString::set_new_string(const char* str) {
    if (stroka == nullptr) {
        throw "строка пустая!!";
    }
    if (str == nullptr) 
    {
	    std::cout << "передан нулевой указатель!!" << std::endl;
	    return; 
    }
	int new_len = strlen(str);
    
    //если новая строка короче или равна текущей, просто копируем
    if (new_len <= mylen) 
    {
        for (int i = 0; i <= new_len; i+=1) 
        {
            stroka[i] = str[i];
        }
        mylen = new_len;
    } 
    else {
        // выделяем новую память
        char* new_stroka = new char[new_len + 1];
        
        // копируем новую строку
        for (int i = 0; i <= new_len; i+=1) 
        {
            new_stroka[i] = str[i];
        }
        
        // oсвобождаем старую память и присваиваем новые значения
        delete[] stroka;
        stroka = new_stroka;
        mylen = new_len;
    }
}

// вывод строки на консоль
void MyString::print() {
    if (stroka == nullptr) {
        throw "строка пустая!!";
    }
	if (stroka != nullptr) {
		for (int i = 0; i < mylen; i+=1) 
		{
	    	std::cout << stroka[i];  //каждый символ до '\0'
		}
		std::cout << std::endl;
	}
}

// замена текущего содержимого строки на строку, считанную с консоли (неопределенного размера)
void MyString::read_line() {
    std::cout<<"Введите строку: "<<std::endl;
    int bufsize = 20; // начальный размер
    char* string = new char[bufsize];
    char c;
    int position = 0;

    while (std::cin.get(c)) //пока не прошли весь поток с консоли
    {
        if (c == '\n') // если enter
        {
            break;
        }
        
        string[position] = c;
        position++;
        
        // Проверяем, не кончается ли место
        if (position >= bufsize - 1) //-1 для '\0'
        {
            // удваиваем буфер
            int newbufsize = bufsize * 2;
            char* newbuf = new char[newbufsize];
            
            // копируем все символы
            for (int x = 0; x < position; x+=1) 
            {
                newbuf[x] = string[x];
            }
            
            delete[] string;
            string = newbuf;
            bufsize = newbufsize;
        }
    }
    
    // Добавляем завершающий ноль
    string[position] = '\0';
    
    delete[] stroka;  // освобождаем старую память
    stroka = string; // присваиваем новое значение
    mylen = position; // сохраняем длину
}

int MyString::length_str() {
    return mylen;
}