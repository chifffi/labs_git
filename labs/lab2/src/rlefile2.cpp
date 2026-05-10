#include "rlefile2.hpp"
#include <iostream>
#include <cstring>

//констркутор 
RleFile2::RleFile2(IFile* t) : target(t), write_buffer_size(0), read_buffer_size(0), read_buffer_pos(0) {
    std::cout << "RleFile2::RleFile2()" << std::endl;
}

//деструктор
RleFile2::~RleFile2() {
    // Записываем остаток при закрытии
    if (write_buffer_size > 0 && target != nullptr) {
        unsigned char compressed[512];
        size_t comp_size = rle_encode(write_buffer, write_buffer_size, compressed);
        if (comp_size > 0) {
            // Записываем размер блока (2 байта)
            unsigned char size_buf[2];
            size_buf[0] = (comp_size >> 8) & 0xFF;
            size_buf[1] = comp_size & 0xFF;
            target->write(size_buf, 2);

            // Записываем сжатые данные
            target->write(compressed, comp_size);
        }
    }
    delete target;  // освобождаем память целевого объекта
    std::cout << "RleFile2::~RleFile2()" << std::endl;
}

//методы интерфейса

//RleFile2 может читать если target существует и сам может читать/писать
bool RleFile2::can_read() const {
    return target != nullptr && target->can_read();
}

bool RleFile2::can_write() const {
    return target != nullptr && target->can_write();
}

//запись со сжатием
size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (!can_write() || buf == nullptr || n_bytes == 0) return 0;
    
    const unsigned char* data = (const unsigned char*)buf;
    size_t total_written = 0;
    
    for (size_t i = 0; i < n_bytes; i++) {
        // Добавляем байт в буфер
        write_buffer[write_buffer_size++] = data[i];
        
        // Если буфер заполнен или это последний байт — сжимаем и пишем
        if (write_buffer_size >= 256 || i == n_bytes - 1) {
            unsigned char compressed[512];
            size_t comp_size = rle_encode(write_buffer, write_buffer_size, compressed);
            
            if (comp_size > 0) {
                // Записываем размер блока (2 байта)
                unsigned char size_buf[2];
                size_buf[0] = (comp_size >> 8) & 0xFF;
                size_buf[1] = comp_size & 0xFF;
                target->write(size_buf, 2);
                
                // Записываем сжатые данные
                target->write(compressed, comp_size);
                total_written += write_buffer_size;
            }
            
            write_buffer_size = 0; // очищаем буфер
        }
    }
    
    return total_written;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    if (!can_read() || buf == nullptr || max_bytes == 0) return 0;
    
    unsigned char* output = (unsigned char*)buf;
    size_t bytes_written = 0;
    
    while (bytes_written < max_bytes) {
        // Если в буфере чтения есть данные — выдаем
        if (read_buffer_pos < read_buffer_size) {
            output[bytes_written++] = read_buffer[read_buffer_pos++];
            continue;
        }
        
        // Читаем размер следующего блока (2 байта)
        unsigned char size_buf[2];
        if (target->read(size_buf, 2) != 2) break;
        
        // Восстанавливаем размер сжатого блока
        size_t comp_size = (size_buf[0] << 8) | size_buf[1];
        if (comp_size == 0 || comp_size > 512) break;
        
        // Читаем сжатые данные из target
        unsigned char compressed[512];
        if (target->read(compressed, comp_size) != comp_size) break;
        
        // Распаковываем в read_buffer
        read_buffer_size = rle_decode(compressed, comp_size, read_buffer);
        read_buffer_pos = 0;
    }
    
    return bytes_written;
}


//сжатие
size_t RleFile2::rle_encode(const unsigned char* src, size_t src_len, unsigned char* dst) {
    if (src_len == 0) return 0; // нет данных, нечего сжимать
    
    size_t dst_idx = 0; // индекс куда будем писать
    size_t i = 0; // индекс откуда читаем
    
    while (i < src_len) //по всем данным
    {
        unsigned char tek = src[i]; // текущий символ
        size_t count = 1; //кол-во этого символа, 1 тк уже есть
        
        // считаем повторения (максимум 255 тк задали массив 256)
        //все соблюд: пока меньше размера входных, пока такой же символ, пока не превысили лимит 255(потом преобраз в unsigned char)
        while (((i + count) < src_len) && (src[i + count] == tek) && (count < 255)) {
            count+=1;
        }
        
        // запись: [количество] [символ]
        dst[dst_idx++] = (unsigned char)count;
        dst[dst_idx++] = tek;
        
        i += count; //переходим к следющему символу
    }
    
    return dst_idx; //вернули кол-во байт, записанных в буфер для сжатия
}

//распаковка
size_t RleFile2::rle_decode(const unsigned char* src, size_t src_len, unsigned char* dst) {
    size_t dst_idx = 0; //индекс куда пишем
    size_t i = 0; //индекс откуда читаем
    
    while (i + 1 < src_len) //пока есть хотя бы 2 байта "число - символ"
    {
        unsigned char count = src[i]; //кол-во символа
        unsigned char symbol = src[i + 1]; //сам символ
        
        for (int j = 0; j < count; j++) {
            dst[dst_idx++] = symbol; //записываем смивол count раз в буфер
        }
        
        i += 2; //переход к след паре "число - символ"
    }
    
    return dst_idx; //вернули кол-во байт, записанных в буфер для распаковки
}