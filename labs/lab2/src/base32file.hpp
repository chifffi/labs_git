#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP

#include "basefile.hpp"

const char mytable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"; //таблица по умолч (32 символа)

class Base32File : public BaseFile {
private:
    const char* table;

    unsigned int write_bits_buffer;  // буфер для остатка битов при записи
    int write_bits_count; // сколько бит в буфере при записи

    unsigned int read_bits_buffer;   // буфер для остатка битов при чтении
    int read_bits_count; //сколько бит в буфере при чтении
    
    int encoded32_size(int raw_size) const; //размер после кодирования
    int decoded32_size(int encoded_size) const; //размер после декодироания
    
    int encode32(const unsigned char* raw_data, int raw_size, unsigned int& buffer, int& bits, char* dst, int& dst_idx) const; //кодирует
    int decode32(const char* encoded_data, int encoded_size, char* dst) const; //декодирует
    
public:
    Base32File(); //по умолч
    Base32File(const char* path, const char* mode, const char* tbl = mytable);
    Base32File(FILE* f, const char* mode = "r", const char* tbl = mytable);
    
    ~Base32File();
    
    // переопределение write и read
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif