#include "base32file.hpp"
#include <iostream>
#include <cstring>

//констр по умолч через список иницилизации передаем конструктор для базового класса и тд
Base32File::Base32File() : BaseFile(), table(mytable), 
                           write_bits_buffer(0), write_bits_count(0),
                           read_bits_buffer(0), read_bits_count(0) {
    std::cout << "Base32File::Base32File()" << std::endl;
}

//констр с путем и режимом(tbl = mytable по умолч)
Base32File::Base32File(const char* path, const char* m, const char* tbl) 
    : BaseFile(path, m), table(tbl != nullptr ? tbl : mytable),
      write_bits_buffer(0), write_bits_count(0),
      read_bits_buffer(0), read_bits_count(0) {
    std::cout << "Base32File::Base32File(const char* path, const char* m, const char* tbl)" << std::endl;
}

//констр с готовым файлом(tbl = mytable по умолч)
Base32File::Base32File(FILE* f, const char* m, const char* tbl) 
    : BaseFile(f, m), table(tbl != nullptr ? tbl : mytable),
      write_bits_buffer(0), write_bits_count(0),
      read_bits_buffer(0), read_bits_count(0) { 
    std::cout << "Base32File::Base32File(FILE* f, const char* m, const char* tb)" << std::endl;
}

//деструктор
Base32File::~Base32File() {
    // Если есть недописанные биты (1-4 штуки)
    if (write_bits_count > 0) {
        // берем эти биты и дополняем нулями до 5 бит, получаем число от 0 до 31
        int value = (write_bits_buffer << (5 - write_bits_count)) & 0x1F;
        
        // Превращаем число в символ Base32
        char last = table[value];
        
        // Записываем этот последний символ в файл
        BaseFile::write_raw(&last, 1); //& тк write_raw ожидает указатель
    }
    std::cout << "Base32File::~Base32File()" << std::endl;
}

//метод размер после кодирования
int Base32File::encoded32_size(int raw_size) const {
    int total_bits = 8 * raw_size; //всего бит в строке
    if (total_bits % 5 == 0) {
        return total_bits / 5;
    }
    return total_bits / 5 + 1; //делим и округляем вверх
}

//метод размер после декодирования
int Base32File::decoded32_size(int encoded_size) const {
    return (encoded_size * 5) / 8; //деление с округ вниз на 8 (округляем вниз, так как неполный байт не учитывается)
}

//метод кодирования: берет входные байты (raw_data) и кодирует их в Base32 строку (dst)
//ссылки чтобы сохр после выхода из функции
//сырые байты, их размер, накопленные до этого биты, их размер,куда, текущая позиция в этой строке
int Base32File::encode32(const unsigned char* raw_data, int raw_size, unsigned int& buffer, int& bits, char* dst, int& dst_idx) const {
    if (raw_data == nullptr || raw_size < 0 || dst == nullptr) return 1; // 1 - ошибка
    
    for (int i = 0; i < raw_size; i+=1) // проходим по всем байтам
    {
        buffer = (buffer << 8) | raw_data[i];
        bits += 8;
        
        while (bits >= 5) {
            int bit5 = (buffer >> (bits - 5)) & 0x1F; //извлекаем старшие 5 бит
            dst[dst_idx++] = table[bit5];
            bits -= 5;
        }
    }

    return 0;
}

//метод декодироввния
int Base32File::decode32(const char* encoded_data, int encoded_size, char* dst) const {
    if (encoded_data == nullptr || dst == nullptr || encoded_size < 0) return 1; // 1- ошибка
    if (encoded_size == 0) return 0; //ничего не декодируем, 0 - прошло
    
    //buffer - накопленные биты, bits - кол-во бит в буфере, dst_idx - текущая позиция в dst
    unsigned int buffer = 0;
    int bits = 0;
    int dst_idx = 0;
    
    for (int i = 0; i < encoded_size; i++) //по всем кодированным байтам
    {
        char c = encoded_data[i]; //возможный элем таблицы
        int indextable = -1; //индекс элем в таблице
        for (int j = 0; j < 32; j++) {
            if (table[j] == c) {
                indextable = j;
                break;
            }
        }
        if (indextable == -1) return 2; // 2 - ошибка (недопустимый символ)
        
        buffer = (buffer << 5) | indextable; // Добавляем 5 бит в буфер
        bits += 5;
        
        while (bits >= 8) {
            dst[dst_idx++] = (buffer >> (bits - 8)) & 0xFF; // Берем старшие 8 бит
            bits -= 8;
        }
    }
    
    return 0;
}

// запись с кодрованием: принимает сырые байты, кодирует их в Base32 и записывает в файл
size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!is_open() || !can_write() || buf == nullptr || n_bytes == 0) return 0;
    
    const unsigned char* data = (const unsigned char*)buf;
    
    // Считаем, сколько символов получится
    int total_bits = n_bytes * 8 + write_bits_count; //n_bytes + остаток от прошлого раза
    int max_encoded = total_bits / 5;
    if (total_bits % 5 != 0) max_encoded++; //округл вверх
    
    char* encoded = new char[max_encoded + 1]; //+1 для /0
    
    unsigned int buffer = write_bits_buffer;
    int bits = write_bits_count;
    int enc_idx = 0;
    
    int result = encode32(data, (int)n_bytes, buffer, bits, encoded, enc_idx); //сырые байты, их размер, накопленные до этого биты, их размер,куда, текущая позиция в этой строке
    if (result != 0) //все не получилось закодировать
    {
        delete[] encoded;
        return 0;
    }
    
    // Сохраняем остаток для следующего вызова
    write_bits_buffer = buffer;
    write_bits_count = bits;
    
    BaseFile::write_raw(encoded, enc_idx);
    
    delete[] encoded;
    return n_bytes;
}

// чтение с декодированием:  читает Base32 строку из файла и декодирует её обратно в сырые байты
size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!is_open() || !can_read() || buf == nullptr || max_bytes == 0) return 0;
    
    char* output = (char*)buf; //куда будем писать расшифрованные байты
    size_t bytes_written = 0; // сколько байт уже расшифровали
    
    unsigned int buffer = read_bits_buffer; // остаток от прошлого
    int bits = read_bits_count; //кол-во бит в буфере
    
    while (bytes_written < max_bytes) {
        // Если в буфере есть байт — записываем его 
        if (bits >= 8) 
        {
            output[bytes_written++] = (buffer >> (bits - 8)) & 0xFF;
            bits -= 8;
            continue;
        }
        
        // читаем символ из файла
        char ch;
        if (BaseFile::read_raw(&ch, 1) == 0) {
            break;  // файл закончился
        }
        
        // Находим индекс символа в таблице
        int idx = -1;
        for (int j = 0; j < 32; j++) {
            if (table[j] == ch) {
                idx = j;
                break;
            }
        }
        if (idx == -1) return 0;
        
        // прибавляем 5 бит в буфер
        buffer = (buffer << 5) | idx;
        bits += 5;
    }
    
    // Сохраняем остаток для следующего чтения
    read_bits_buffer = buffer;
    read_bits_count = bits;
    
    return bytes_written;
}