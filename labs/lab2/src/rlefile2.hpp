#ifndef RLEFILE2_HPP
#define RLEFILE2_HPP

#include <cstddef>      // для size_t
#include "ifile.hpp" 

class RleFile2 : public IFile {
private:
    //target это указатель на любой объект, реализующий интерфейс IFile(BaseFile, Base32File2 или RleFile2)
    IFile* target;  // куда писать сжатые данные
    
    unsigned char write_buffer[256]; // буфер для накопления данных при записи(перед сжатием)
    int write_buffer_size; // сколько байт в буфере при записи
    unsigned char read_buffer[256]; // буфер с распакованными данными
    int read_buffer_size; // сколько байт в буфере при чтении
    int read_buffer_pos; // позиция в буфере чтения

    size_t rle_encode(const unsigned char* src, size_t src_len, unsigned char* dst); //сжатие
    size_t rle_decode(const unsigned char* src, size_t src_len, unsigned char* dst); //распаковка
    
public:
    // Конструктор: принимает целевой IFile (куда писать сжатые данные)
    RleFile2(IFile* target);
    
    ~RleFile2();
    
    // Методы интерфейса IFile
    bool can_read() const;
    bool can_write() const;
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif