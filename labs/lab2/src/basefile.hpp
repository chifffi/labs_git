#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio>  // для FILE*, fopen, fclose и тд
#include <cstddef> // для size_t
#include "ifile.hpp"

class BaseFile : public IFile { //наследуем от IFile
    FILE* file;  // указатель на открытый файл
    char mode[4]; // режим открытия, максимум 3 символа + '\0'
    //r, w, a, r+, w+, a+, wb+, rb+, ab+
    
public:
    BaseFile(); // конструктор по умолчанию
    BaseFile(const char* path, const char* m);  // открывает файл по пути
    BaseFile(FILE* f, const char* m = "r"); // принимает готовый FILE*
    
    virtual ~BaseFile();
    
    // методы для проверки
    //const - метод не изменит ни одно поле класса, только его можно вызывать для const объектов
    bool is_open() const; //true, если файл успешно открыт
    bool can_read() const; //true, если из файла можно считать данные
    bool can_write() const; //true, если в файл можно записать данные
    
    // методы чтения/записи
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    
    // методы для позиционирования
    long tell() const; //возвращает текущий сдвиг файла
    bool seek(long offset); //устанавливает сдвиг, true, если операция успешна
    
    // методы read и write
    virtual  size_t write(const void* buf, size_t n_bytes);
    virtual  size_t read(void* buf, size_t max_bytes);
};

#endif