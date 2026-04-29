#include "rlefile.hpp"
#include <iostream>
#include <cstring>

//по умолч
RleFile::RleFile() : BaseFile(), write_buffer_size(0), read_buffer_size(0), read_buffer_pos(0) {
    std::cout << "RleFile::RleFile()" << std::endl;
}

//путь, режим
RleFile::RleFile(const char* path, const char* m) 
    : BaseFile(path, m), write_buffer_size(0), read_buffer_size(0), read_buffer_pos(0) {
    std::cout << "RleFile::RleFile(const char*, const char*)" << std::endl;
}

//готовый файл
RleFile::RleFile(FILE* f, const char* m) 
    : BaseFile(f, m), write_buffer_size(0), read_buffer_size(0), read_buffer_pos(0) {
    std::cout << "RleFile::RleFile(FILE*, const char*)" << std::endl;
}
//деструктор
RleFile::~RleFile() {
    //есть ли недозаписанные данные
    if (write_buffer_size > 0) {
        //сжимаем остаток
        unsigned char compressed[512];
        size_t comp_size = rle_encode(write_buffer, write_buffer_size, compressed);
        if (comp_size > 0) //если сжатие прошло успешно
        {
            // Записываем размер получивсегося блока (2 байта) чтобы при чтении знать, где границы сжатых блоков
            unsigned char size_buf[2];
            size_buf[0] = (comp_size >> 8) & 0xFF; //старший байт
            size_buf[1] = comp_size & 0xFF; //младший байт
            BaseFile::write_raw(size_buf, 2); //запись размера блока
            
            // Записываем сжатые данные
            BaseFile::write_raw(compressed, comp_size);
        }
    }
    std::cout << "RleFile::~RleFile()" << std::endl;
}

//RLE сжатие
//формат:количество повторов, символ
//входные данные(указ на массив байтов), их размер(байты), выходной буфер для сжатия
size_t RleFile::rle_encode(const unsigned char* src, size_t src_len, unsigned char* dst) {
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

//RLE распаковка
//входные данные(указатель на сжатые данные), размер сжатых, буфер для распаковки
size_t RleFile::rle_decode(const unsigned char* src, size_t src_len, unsigned char* dst) {
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

//Запись со сжатием
//[[старший байт][младший байт]] [сжатые данные]
//указ на входные данные, сколько байт нужно записать
size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!is_open() || !can_write() || buf == nullptr || n_bytes == 0) return 0;
    
    const unsigned char* data = (const unsigned char*)buf; //вход данные, unsigned char чтобы работать с байтами
    size_t total_written = 0; //кол-во записанных ориг байт
    
    for (size_t i = 0; i < n_bytes; i+=1) 
    {
        // Добавляем байт в буфер
        write_buffer[write_buffer_size++] = data[i]; //записываем байт на позицию, следующую после записанных ДО этого байт
        
        // Если буфер заполнен или это последний байт — сжимаем и пишем
        if (write_buffer_size >= 256 || i == n_bytes - 1) 
        {
            //временный буфер для сжатия данных(512 для худшего случ если все байты разные, каждая группа по [1, символ] - 2 байта)
            unsigned char compressed[512]; 
            //Размер сжатых данных
            size_t comp_size = rle_encode(write_buffer, write_buffer_size, compressed);
            
            if (comp_size > 0) {

                // Записываем размер получивсегося блока (2 байта) чтобы при чтении знать, где границы блоков
                unsigned char size_buf[2];
                size_buf[0] = (comp_size >> 8) & 0xFF;  // старший байт
                size_buf[1] = comp_size & 0xFF;  // младший байт
                BaseFile::write_raw(size_buf, 2); //пишем размер

                BaseFile::write_raw(compressed, comp_size); //Записываем сжатые данные в файл
                total_written += write_buffer_size; //Увеличиваем счетчик оригинальных байт
            }
            
            write_buffer_size = 0; //буфер готов к приему следующих данных
        }
    }
    
    return total_written; //возвращ кол-во оригинальных байт, которые удалось записать 
}

//Чтение с распаковкой
//указ на данные, которые нужно прочитать, кол-во байт, которое готовы принять
size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!is_open() || !can_read() || buf == nullptr || max_bytes == 0) return 0;
    
    unsigned char* output = (unsigned char*)buf; //куда будем писать распакованные байты, приводим к unsigned char* (чтобы работать с байтами)
    size_t bytes_written = 0; // сколько байт уже отдали
    
    while (bytes_written < max_bytes) {
        // Если в буфере чтения есть невыданные расппакованные данные — берем оттуда
        if (read_buffer_pos < read_buffer_size) {
            output[bytes_written++] = read_buffer[read_buffer_pos++];
            continue;
        }
        
        //читам размер след блока
        unsigned char size_buf[2];
        size_t read_size_bytes = BaseFile::read_raw(size_buf, 2);
        if (read_size_bytes != 2) {
            break;  // файл закончился
        }
        
        // Восстанавливаем размер сжатого блока
        size_t comp_size = (size_buf[0] << 8) | size_buf[1];
        if (comp_size == 0 || comp_size > 512) {
            break;  // ошибка
        }

        // Читаем ровно comp_size байт сжатых данных
        unsigned char compressed[512]; //временный буфер для сжатых данных из файла(В худшем случае 256 оригинальных байт дают 512 сжатых - все разные)
        size_t read_size = BaseFile::read_raw(compressed, comp_size); //сколько байт сжатых данных реально прочиталось
        if (read_size == 0) break;  // файл закончился
        
        // распаковка
        // TODO: в тестах сгенерируйте длинные серии
        //       int size = rand() % 100 + 40;
        //       char data = rand() % 32 + 'A';
        //       for (int i = 0; i < size; ++i) buf[pos++] = data;
        read_buffer_size = rle_decode(compressed, read_size, read_buffer); //сколько байт получилось после распаковки
        read_buffer_pos = 0; //ставм на позицию на 0 для след итерации
    }
    
    
    return bytes_written; // возвращ количество байт, реально прочитанных и распакованных
}