#include "mystring.hpp"
#include <iostream>
#include <cstring>   // для strlen, strcpy

MyString::MyString() {
	mylen = 0;
    stroka = nullptr;


}

// объект выделяет память под копию этой строки
MyString::MyString(const char* str) {
    if (str == nullptr) {
        throw "передан нулевой указатель в конструктор!!";
    }
	mylen = strlen(str);
    stroka = new char[mylen + 1];  // +1 для '\0'
    std::cout << "CONSTRUCTOR (выделение памяти)" << std::endl;
    
    for (int i = 0; i <= mylen; i+=1)
    {
        stroka[i] = str[i];
    }

}

// конструктор копирования
MyString::MyString(const MyString &other) {
    if (other.stroka == nullptr) {
        mylen = 0;
        stroka = nullptr;  
        return;
    }
    mylen = other.mylen;
    stroka = new char[mylen + 1];
    std::cout << "COPY CONSTRUCTOR (выделение памяти)" << std::endl;
    for (int i = 0; i <= mylen; i++) {
        stroka[i] = other.stroka[i];
    }
}

MyString::~MyString() {
	if (stroka != nullptr) {
        delete[] stroka;
    }
}

// получение i-того элемента строки
char MyString::get(int i) const {
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
    if (str == nullptr) {
        // если передали nullptr - делаем строку пустой
        if (stroka != nullptr) {
            delete[] stroka;
        }
        mylen = 0;
        stroka = nullptr;
        return;
    }
    
    int new_len = strlen(str);
    
    if (stroka != nullptr && new_len <= mylen) 
    {
        // используем существующую память
        for (int i = 0; i <= new_len; i++) {
            stroka[i] = str[i];
        }
        mylen = new_len;
    } 
    else 
    {
        // нужно выделить новую память
        char* new_stroka = new char[new_len + 1];
        for (int i = 0; i <= new_len; i++) {
            new_stroka[i] = str[i];
        }
        
        if (stroka != nullptr) {
            delete[] stroka;
        }
        stroka = new_stroka;
        mylen = new_len;
    }
}


// вывод строки на консоль
void MyString::print() const{
    if (stroka == nullptr) { 
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < mylen; i++) {
        std::cout << stroka[i];
    }
    std::cout << std::endl;
}

// замена текущего содержимого строки на строку, считанную с консоли (неопределенного размера)
void MyString::read_line() {
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

int MyString::length_str() const {
    return mylen;
}
//оператор присванивания
//параметр: & чтобы не создавалась лишняя копия, const как гарантия что исходный объект не изменится
MyString& MyString::operator=(const MyString& other) {
    //Проверка на самоприсваивание (s1 = s1), без этого удалится память s1, потом будет ошибка при копировании из удаленной
    //this - указатель на на текущий объект. Он существует внутри каждого нестатического метода класса и указывает на тот объект, для которого был вызван метод
    if (this == &other) {
        return *this;  // ничего не делаем, возвращаем ссылку на себя
    }
    
    //Освобождаем старую память текущего объекта
    delete[] stroka;
    
    //Копируем данные из other
    mylen = other.mylen;
    
    if (other.stroka == nullptr) 
    {
        stroka = nullptr;
    } 
    else {
        stroka = new char[mylen + 1];
        std::cout << "COPY ASSIGNMENT (выделение памяти)" << std::endl;
        for (int i = 0; i <= mylen; i+=1) 
        {
            stroka[i] = other.stroka[i];
        }
    }
    
    // Возвращаем сам объект (разыменованный указатель) для цепочек присваиваний
    return *this;
}


// Оператор += для MyString
MyString& MyString::operator+=(const MyString& other) {
    int new_len = mylen + other.mylen;
    char* new_stroka = new char[new_len + 1];
    
    for (int i = 0; i < mylen; i++) {
        new_stroka[i] = stroka[i];  // если mylen=0, цикл не выполняется
    }
    
    for (int i = 0; i < other.mylen; i++) {
        new_stroka[mylen + i] = other.stroka[i];  //  если other.mylen=0, цикл не выполняется
    }
    
    new_stroka[new_len] = '\0';
    
    delete[] stroka;  // delete[] nullptr ничего не делает
    stroka = new_stroka;
    mylen = new_len;
    
    return *this;
}

// Оператор += для const char*
MyString& MyString::operator+=(const char* str) {
    // Проверка на nullptr
    if (str == nullptr) {
        throw "передан нулевой указатель в operator+= !";
    }
    
    // Если строка пустая
    if (str[0] == '\0') {
        return *this;
    }
    
    // временный объект MyString из str
    MyString temp(str);
    // Используем уже реализованный operator+=(const MyString&) для объекта *this с аргументом temp
    //*this - это текущий объект
    return *this += temp;
}

// Глобальный оператор + (MyString + MyString)
MyString operator+(const MyString& left, const MyString& right) {
    // Создаем копию левой строки (используем конструктор копирования)
    MyString result(left);
    
    // Добавляем правую строку с помощью operator+=(const MyString&)
    result += right;
    
    return result;
}

// Глобальный оператор + (MyString + const char*)
MyString operator+(const MyString& left, const char* right) {
    // Проверка на nullptr
    if (right == nullptr) {
        throw "передан нулевой указатель в operator+ !";
    }
    
    // Создаем копию левой строки (используем конструктор копирования)
    MyString result(left);
    
    // Добавляем правую строку operator+=(const char* str)
    result += right;
    
    return result;
}

// Глобальный оператор + (const char* + MyString)
MyString operator+(const char* left, const MyString& right) {
    // Проверка на nullptr
    if (left == nullptr) {
        throw "передан нулевой указатель в operator+ !";
    }
    
    // Создаем объект из левой строки (используем конструктор от const char*)
    MyString result(left);
    
    // Добавляем правую строку operator+=(const char* str)
    result += right;
    
    return result;
}

// Move-конструктор
MyString::MyString(MyString&& other) 
    : mylen(other.mylen), stroka(other.stroka) 
{
    other.mylen = 0;
    other.stroka = nullptr;
    std::cout << "MOVE CONSTRUCTOR (память НЕ выделяется)" << std::endl;
}

// Move-оператор присваивания
MyString& MyString::operator=(MyString&& other) {
    if (this != &other) 
    {
        delete[] stroka; //очищаем текущую строку
        mylen = other.mylen;
        stroka = other.stroka;
        other.mylen = 0;
        other.stroka = nullptr;
        std::cout << "MOVE ASSIGNMENT (память НЕ выделяется)" << std::endl;
    }
    return *this;
}

#include <cstring>  // для strcmp

// Сравнение MyString с MyString

bool MyString::operator==(const MyString& other) const {
    if (stroka == nullptr && other.stroka == nullptr) {
        return true; //обе пустые
    }
    if (stroka == nullptr || other.stroka == nullptr) {
        return false; // одна пустая а другая нет (обе пустые в предыдущем)
    }
    return strcmp(stroka, other.stroka) == 0; //обычная проверка
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other); // отрицание результата operator==
}

bool MyString::operator<(const MyString& other) const {
    if (stroka == nullptr && other.stroka == nullptr) {
        return false;
    }
    if (stroka == nullptr) {
        return true;   // "" < "что-то"
    }
    if (other.stroka == nullptr) {
        return false;  // "что-то" < "", значит false
    }
    return strcmp(stroka, other.stroka) < 0; //обычная проверка
}

bool MyString::operator<=(const MyString& other) const {
    return (*this < other) || (*this == other); //используем результат operator< или operator==
}

bool MyString::operator>(const MyString& other) const {
    return !(*this <= other); //отрицание результата operator<=
}

bool MyString::operator>=(const MyString& other) const {
    return !(*this < other); // отрицание результата operator<
}

// Сравнение MyString с const char* 

bool MyString::operator==(const char* str) const {
    if (stroka == nullptr && str == nullptr) {
        return true;
    }
    if (stroka == nullptr || str == nullptr) {
        return false;
    }
    return strcmp(stroka, str) == 0;
}

bool MyString::operator!=(const char* str) const {
    return !(*this == str);
}

bool MyString::operator<(const char* str) const {
    if (stroka == nullptr && str == nullptr) {
        return false;
    }
    if (stroka == nullptr) {
        return true;   // "" < "что-то"
    }
    if (str == nullptr) {
        return false;  // "что-то" < nullptr? false
    }
    return strcmp(stroka, str) < 0;
}

bool MyString::operator<=(const char* str) const {
    return (*this < str) || (*this == str);
}

bool MyString::operator>(const char* str) const {
    return !(*this <= str);
}

bool MyString::operator>=(const char* str) const {
    return !(*this < str);
}

// Сравнение const char* с MyString (дружественные функции) 

bool operator==(const char* str, const MyString& s) {
    return s == str;  // просто вызываем метод
}

bool operator!=(const char* str, const MyString& s) {
    return !(s == str);
}

bool operator<(const char* str, const MyString& s) {
    return s > str;   // "ab" < s2  <=>  s2 > "ab"
}

bool operator<=(const char* str, const MyString& s) {
    return s >= str;
}

bool operator>(const char* str, const MyString& s) {
    return s < str;
}

bool operator>=(const char* str, const MyString& s) {
    return s <= str;
}

// Оператор индексирования (неконстантный)
char& MyString::operator[](int index) {
    // Проверка на пустую строку
    if (stroka == nullptr) {
        throw "строка пустая!";
    }
    // Проверка границ
    if (index < 0 || index >= mylen) {
        throw "индекс выходит за границы строки!";
    }
    return stroka[index];
}

// Константный оператор индексирования (для константных объектов)
const char& MyString::operator[](int index) const {
    // Проверка на пустую строку
    if (stroka == nullptr) {
        throw "строка пустая!";
    }
    // Проверка границ
    if (index < 0 || index >= mylen) {
        throw "индекс выходит за границы строки!";
    }
    return stroka[index];
}

// Оператор вывода (<<)
std::ostream& operator<<(std::ostream& out, const MyString& str) {
    // std::ostream - это тип для выходных потоков (куда можно записывать данные)
    // Если строка nullptr, выводим пустую строку
    if (str.stroka == nullptr) {
        return out;  // ничего не выводим, просто возвращаем поток
    }
    
    // Выводим все символы строки
    for (int i = 0; i < str.mylen; i++) {
        out << str.stroka[i];
    }
    
    return out;  // возвращаем поток для цепочек операций
}

// Оператор ввода (>>) для консольного ввода
std::istream& operator>>(std::istream& in, MyString& str) {
    //std::istream - это тип для входных потоков (откуда можно читать данные)
    //Параметр in получает ссылку на std::cin, а метод read_line() внутренне использует std::cin для чтения строки
    //связь между in и read_line() устанавливается через глобальный объект std::cin
    //Возврат in обеспечивает поддержку цепочек ввода.

    str.read_line();
    return in;
}

