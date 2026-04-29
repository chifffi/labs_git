#include "../src/basefile.hpp"
#include <iostream>
#include <cstring>

//конструктор по умолчанию
BaseFile::BaseFile() : file(nullptr) {
    mode[0] = '\0';
    std::cout << "BaseFile::BaseFile()" << std::endl;
}

//констуктор с параметрами (открывает файл по пути)
BaseFile::BaseFile(const char* path, const char* m) : file(nullptr) {
    // проверка
    if (path == nullptr || m == nullptr) 
    {
        mode[0] = '\0'; 
        return; // file остался nullptr 
    }
    // если проверка прошла - сохр режим
    int len = strlen(m);
    if (len > 3) len = 3;  // защита от слишком длинных режимов
    strncpy(mode, m, len);
    mode[len] = '\0';
    
    file = fopen(path, m); //если файл существует — перезаписывает, если файла нет — создает
    std::cout << "BaseFile::BaseFile(const char* path, const char* m)" << std::endl;
}

//конструктор с параметрами (принимает готовый FILE*)
BaseFile::BaseFile(FILE* f, const char* m) : file(f) {
    if (m != nullptr) 
    {
        int len = strlen(m);
        if (len > 3) len = 3;
        strncpy(mode, m, len);
        mode[len] = '\0';
    } 
    std::cout << "BaseFile::BaseFile(FILE* f, const char* m)" << std::endl;
}

//деструктор
BaseFile::~BaseFile() {
    if (file != nullptr) //fclose(nullptr) может привести к падению программы
    {
        fclose(file);
    }
    std::cout << "BaseFile::~BaseFile()" << std::endl;
}

//метод: открыт ли файл (true если не nullptr)
bool BaseFile::is_open() const {
    return file != nullptr;
}

//метод: можно ли читать 
bool BaseFile::can_read() const {
    if (file == nullptr) return false;
    
    for (int i = 0; mode[i] != '\0'; i+=1) 
    {
        if (mode[i] == 'r') return true;
    }
    return false;
}

//метод: можно ли писать
bool BaseFile::can_write() const {
    if (file == nullptr) return false;
    
    for (int i = 0; mode[i] != '\0'; i+=1) 
    {
        if (mode[i] == 'w' || mode[i] == 'a') return true;
    }
    return false;
}

//метод записи (fwrite и fread в C автоматически продолжают запись/чтение с текущей позиции в файле.)
size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (file == nullptr) return 0;
    return fwrite(buf, 1, n_bytes, file); //откуда, размер 1 эл, макс кол эл, куда
}

//метод чтения (fwrite и fread в C автоматически продолжают запись/чтение с текущей позиции в файле.)
size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (file == nullptr) return 0;
    return fread(buf, 1, max_bytes, file); //куда, размер 1 эл, макс кол эл, откуда
}

//возвращает текущую позицию в файле (количество байт от начала)
long BaseFile::tell() const {
    if (file == nullptr) return -1;
    return ftell(file);
}

//устанавливает сдвиг, true, если операция успешна
bool BaseFile::seek(long offset) {
    if (file == nullptr) return false;
    return fseek(file, offset, SEEK_SET) == 0; //в каком файле, на сколько, откуда идет смещение
}

// методы read и write
size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}