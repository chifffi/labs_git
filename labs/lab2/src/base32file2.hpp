// Использование объектом другого объекта в качестве поля называется *композицией*.
#ifndef BASE32FILE2_HPP
#define BASE32FILE2_HPP

#include <cstddef>
#include "ifile.hpp"

class Base32File2 : public IFile  {
private:
    //target это указатель на любой объект, реализующий интерфейс IFile(BaseFile, Base32File2 или RleFile2)
    IFile* target;  // куда писать закодированные данные

    const char* table; //указ на таблицу
    unsigned int write_bits_buffer;  // буфер для остатка битов при записи
    int write_bits_count; // сколько бит в буфере при записи
    unsigned int read_bits_buffer;   // буфер для остатка битов при чтении
    int read_bits_count; //сколько бит в буфере при чтении
    
    int encoded32_size(int raw_size) const; //размер после кодирования
    int decoded32_size(int encoded_size) const; //размер после декодироания
    int encode32(const unsigned char* raw_data, int raw_size, unsigned int& buffer, int& bits, char* dst, int& dst_idx) const; //кодирует
    int decode32(const char* encoded_data, int encoded_size, char* dst) const; //декодирует
    
public:
    // Конструктор принимает целевой IFile (куда писать)
    // Второй параметр имеет значение по умолчанию
    Base32File2(IFile* target, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    
    ~Base32File2();
    
    //переопределение чисто виртуальных методов
    bool can_read() const;
    bool can_write() const;
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif