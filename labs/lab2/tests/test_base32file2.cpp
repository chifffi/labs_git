#include "../src/base32file2.hpp"
#include "../src/basefile.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Тест для Base32File2 (композиция) со случайными данными
bool test_base32file2_random() {
    std::cout << "\n Тест Base32File2 (композиция) со случайными данными \n" << std::endl;
    
    const size_t DATA_SIZE = 50000;
    unsigned char* original = new unsigned char[DATA_SIZE];
    
    srand(time(nullptr));
    for (size_t i = 0; i < DATA_SIZE; i++) {
        original[i] = rand() % 256;
    }
    
    // Запись
    {
        Base32File2 f(new BaseFile("data/test_base32file2_random.bin", "w"));
        size_t total_written = 0;
        for (size_t i = 0; i < DATA_SIZE; i += 256) {
            size_t chunk_size = (i + 256 < DATA_SIZE) ? 256 : (DATA_SIZE - i);
            total_written += f.write(original + i, chunk_size);
        }
        if (total_written != DATA_SIZE) {
            std::cout << "Ошибка: записано не все!" << std::endl;
            delete[] original;
            return false;
        }
        std::cout << "Записано " << total_written << " байт" << std::endl;
    }
    
    // Чтение
    unsigned char* read_data = new unsigned char[DATA_SIZE];
    size_t total_read = 0;
    {
        Base32File2 reader(new BaseFile("data/test_base32file2_random.bin", "r"));
        while (total_read < DATA_SIZE) {
            size_t chunk_size = (total_read + 256 < DATA_SIZE) ? 256 : (DATA_SIZE - total_read);
            total_read += reader.read(read_data + total_read, chunk_size);
        }
        std::cout << "Прочитано " << total_read << " байт" << std::endl;
    }
    
    // Сравнение
    bool ok = (total_read == DATA_SIZE);
    for (size_t i = 0; i < DATA_SIZE && ok; i++) {
        if (original[i] != read_data[i]) ok = false;
    }
    
    delete[] original;
    delete[] read_data;
    
    std::cout << (ok ? "Тест Base32File2 пройден!" : "Тест Base32File2 НЕ пройден!") << std::endl;
    return ok;
}

int main() {
    return test_base32file2_random() ? 0 : 1;
}