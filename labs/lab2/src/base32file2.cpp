#include "base32file2.hpp"
#include <iostream>
#include <cstring>

// конструктор
// target — указатель на то, куда писать
// table — таблица кодировки (ужее есть значение по умолчанию)
Base32File2::Base32File2(IFile* t, const char* tbl) : target(t), table(tbl), write_bits_buffer(0), write_bits_count(0), read_bits_buffer(0), read_bits_count(0) {
    std::cout << "Base32File2::Base32File2()" << std::endl;
}

// деструктор
Base32File2::~Base32File2() {
    // Если остались недописанные биты — дописываем
    if (write_bits_count > 0 && target != nullptr) 
    {
        int value = (write_bits_buffer << (5 - write_bits_count)) & 0x1F; // берем эти биты и дополняем нулями до 5 бит, получаем число от 0 до 31
        char last = table[value]; // Превращаем число в символ Base32
        target->write(&last, 1); // Записываем этот последний
    }
    delete target;  // освобождаем память целевого объекта
    std::cout << "Base32File2::~Base32File2()" << std::endl;
}

// методы интерфейса IFilе
bool Base32File2::can_read() const {
    return target != nullptr && target->can_read();
}

bool Base32File2::can_write() const {
    return target != nullptr && target->can_write();
}

// запись с кодрованием: принимает сырые байты, кодирует их в Base32 и записывает
size_t Base32File2::write(const void* buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr || n_bytes == 0) return 0;
    
    const unsigned char* data = (const unsigned char*)buf;
    
    // Сколько символов получится после кодирования
    int total_bits = n_bytes * 8 + write_bits_count;
    int max_encoded = total_bits / 5;
    if (total_bits % 5 != 0) max_encoded++;
    
    char* encoded = new char[max_encoded + 1];
    
    unsigned int buffer = write_bits_buffer;
    int bits = write_bits_count;
    int enc_idx = 0; //в конце должно = длине кодированного
    
    int result = encode32(data, (int)n_bytes, buffer, bits, encoded, enc_idx); //сырые байты, их размер, накопленные до этого биты, их размер,куда, текущая позиция в этой строке
    
    if (result != 0) {
        delete[] encoded;
        return 0;
    }
    
    // Сохраняем остаток для следующего вызова
    write_bits_buffer = buffer;
    write_bits_count = bits;
    
    // Пишем закодированные данные в target
    size_t written = target->write(encoded, enc_idx);
    
    delete[] encoded;
    return (written == (size_t)enc_idx) ? n_bytes : 0;
    // если записалось всё, то возвращаем n_bytes (оригинальные данные)
    // если записалось не всё, то возвращаем 0 (ошибка)
}

// чтение с декодированием:  читает Base32 строку и декодирует её обратно в сырые байты
size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr || max_bytes == 0) return 0;
    
    char* output = (char*)buf; //куда будем писать расшифрованные байты
    size_t bytes_written = 0; // сколько байт уже расшифровали
    
    unsigned int buffer = read_bits_buffer;
    int bits = read_bits_count;
    
    while (bytes_written < max_bytes) {
        // Если в буфере есть целый байт — выдаем
        if (bits >= 8) {
            output[bytes_written++] = (buffer >> (bits - 8)) & 0xFF;
            bits -= 8;
            continue;
        }
        
        // Читаем один символ из target
        char ch;
        if (target->read(&ch, 1) == 0) break; // target закончился
        
        // Находим индекс символа в таблице
        int idx = -1;
        for (int j = 0; j < 32; j++) {
            if (table[j] == ch) {
                idx = j;
                break;
            }
        }
        if (idx == -1) return 0;
        
        // Добавляем 5 бит в буфер
        buffer = (buffer << 5) | idx;
        bits += 5;
    }
    
    // Сохраняем остаток для следующего вызова
    read_bits_buffer = buffer;
    read_bits_count = bits;
    
    return bytes_written;
}
//размер кодировки
int Base32File2::encoded32_size(int raw_size) const {
    int total_bits = 8 * raw_size;
    if (total_bits % 5 == 0) return total_bits / 5;
    return total_bits / 5 + 1;
}

//размер декодировки
int Base32File2::decoded32_size(int encoded_size) const {
    return (encoded_size * 5) / 8;
}

//кодировка
//сырые байты, их размер, накопленные до этого биты, их размер,куда, текущая позиция в этой строке
int Base32File2::encode32(const unsigned char* raw_data, int raw_size, unsigned int& buffer, int& bits, char* dst, int& dst_idx) const {
    if (raw_data == nullptr || raw_size < 0 || dst == nullptr) return 1;
    
    for (int i = 0; i < raw_size; i++) {
        buffer = (buffer << 8) | raw_data[i];
        bits += 8;
        
        while (bits >= 5) {
            int value = (buffer >> (bits - 5)) & 0x1F;
            dst[dst_idx++] = table[value];
            bits -= 5;
        }
    }
    return 0;
}

//декодировка
int Base32File2::decode32(const char* encoded_data, int encoded_size, char* dst) const {
    if (encoded_data == nullptr || dst == nullptr || encoded_size < 0) return 1;
    if (encoded_size == 0) return 0;
    
    unsigned int buffer = 0;
    int bits = 0;
    int dst_idx = 0;
    
    for (int i = 0; i < encoded_size; i++) {
        char c = encoded_data[i];
        int idx = -1;
        for (int j = 0; j < 32; j++) {
            if (table[j] == c) {
                idx = j;
                break;
            }
        }
        if (idx == -1) return 2;
        
        buffer = (buffer << 5) | idx;
        bits += 5;
        
        while (bits >= 8) {
            dst[dst_idx++] = (buffer >> (bits - 8)) & 0xFF;
            bits -= 8;
        }
    }
    return 0;
}