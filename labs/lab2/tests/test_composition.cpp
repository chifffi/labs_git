#include "../src/rlefile2.hpp"
#include "../src/base32file2.hpp"
#include "../src/basefile.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Тест для композиции RleFile2 + Base32File2 со случайными данными
bool test_composition_random() {
    std::cout << "\nТест композиции RleFile2(Base32File2) со случайными данными \n" << std::endl;
    
    const size_t DATA_SIZE = 50000;
    unsigned char* original = new unsigned char[DATA_SIZE];
    
    srand(time(nullptr));
    for (size_t i = 0; i < DATA_SIZE; i++) {
        original[i] = rand() % 256;
    }
    
    // Запись: сначала кодируем в Base32, потом сжимаем RLE
    {
        RleFile2 f(new Base32File2(new BaseFile("data/test_composition_random.bin", "w")));
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
    
    // Чтение: сначала распаковываем RLE, потом декодируем Base32
    unsigned char* read_data = new unsigned char[DATA_SIZE];
    size_t total_read = 0;
    {
        RleFile2 reader(new Base32File2(new BaseFile("data/test_composition_random.bin", "r")));
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
    
    std::cout << (ok ? "Тест композиции RleFile2(Base32File2) пройден!" : " Тест композиции НЕ пройден!") << std::endl;
    return ok;
}

int main() {
    return test_composition_random() ? 0 : 1;
}