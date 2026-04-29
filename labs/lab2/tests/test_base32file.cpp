#include "../src/base32file.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Тест для Base32File со случайными данными
bool test_base32file_random() {
    std::cout << "\n Тест Base32File со случайными данными \n" << std::endl;
    
    const size_t DATA_SIZE = 50000;  // 50000 байт
    unsigned char* original = new unsigned char[DATA_SIZE];
    
    srand(time(nullptr));
    for (size_t i = 0; i < DATA_SIZE; i++) {
        original[i] = rand() % 256;
    }
    
    
    // Запись
    {
        Base32File f("data/test_base32_random.b32", "w");
        size_t total_written = 0;
        
        for (size_t i = 0; i < DATA_SIZE; i += 256) {
            size_t chunk_size = (i + 256 < DATA_SIZE) ? 256 : (DATA_SIZE - i);
            size_t written = f.write(original + i, chunk_size);
            total_written += written;
        }
        
        std::cout << "Записано " << total_written << " байт" << std::endl;
        if (total_written != DATA_SIZE) {
            std::cout << "Ошибка: записано не все!" << std::endl;
            delete[] original;
            return false;
        }
    }
    
    // Чтение
    unsigned char* read_data = new unsigned char[DATA_SIZE];
    size_t total_read = 0;
    
    {
        Base32File f("data/test_base32_random.b32", "r");
        
        while (total_read < DATA_SIZE) {
            size_t chunk_size = (total_read + 256 < DATA_SIZE) ? 256 : (DATA_SIZE - total_read);
            size_t read = f.read(read_data + total_read, chunk_size);
            if (read == 0) break;
            total_read += read;
        }
        
        std::cout << "Прочитано " << total_read << " байт" << std::endl;
    }
    
    // Сравнение
    bool ok = true;
    if (total_read != DATA_SIZE) {
        std::cout << "Размер не совпадает!" << std::endl;
        ok = false;
    } else {
        for (size_t i = 0; i < DATA_SIZE; i++) {
            if (original[i] != read_data[i]) {
                std::cout << "Ошибка на позиции " << i << std::endl;
                ok = false;
                break;
            }
        }
    }
    
    if (ok) {
        std::cout << "Тест Base32File со случайными данными пройден!" << std::endl;
    }
    
    delete[] original;
    delete[] read_data;
    
    return ok;
}

int main() {
    return test_base32file_random() ? 0 : 1;
}