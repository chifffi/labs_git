#ifndef RLEFILE_HPP
#define RLEFILE_HPP

#include "basefile.hpp"

//256 тк это удобное число для работы с байтами(2^8), достаточно большой буфер для хорошего сжатия

class RleFile : public BaseFile {
private:
    unsigned char write_buffer[256]; // буфер для накопления данных при записи(перед сжатием)
    int write_buffer_size; // сколько байт в буфере при записи
    
    unsigned char read_buffer[256]; // буфер с распакованными данными
    int read_buffer_size; // сколько байт в буфере при чтении
    int read_buffer_pos; // позиция в буфере чтения

    size_t rle_encode(const unsigned char* src, size_t src_len, unsigned char* dst); //сжатие
    size_t rle_decode(const unsigned char* src, size_t src_len, unsigned char* dst); //распаковка
    
public:
    RleFile();
    RleFile(const char* path, const char* mode);
    RleFile(FILE* f, const char* mode = "r");

    ~RleFile();
    
    // переопределение write и read
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif