#include "boolarray.hpp"
#include <cstring>


int BoolArray::bytesCount() const {
    return (arr_size + 7) / 8; //округление вверх
}

bool BoolArray::getBit(int index) const {
    int byteIndex = index / 8; // в каком байте лежит нужный бит
    int bitOffset = index % 8; // позиция бита внутри байта
    return (data[byteIndex] >> bitOffset) & 1; // сдвигаем нужный бит в самую правую позицию и отсекаем всё, кроме младшего бита
}

void BoolArray::setBit(int index, bool value) {
    int byteIndex = index / 8; // в каком байте лежит нужный бит
    int bitOffset = index % 8; // позиция бита внутри байта
    if (value)
    {
        data[byteIndex] |= (1 << bitOffset); // value == true: data[byteIndex] |= (1 << bitOffset) — ставим 1 в нужную позицию
    } else {
        data[byteIndex] &= ~(1 << bitOffset); //value == false: data[byteIndex] &= ~(1 << bitOffset) — ставим 0 в нужную позицию
    }
}

// Конструктор
BitReference::BitReference(BoolArray& arr, int idx): array(arr), index(idx) {}

// Неявное преобразование в bool
BitReference::operator bool() const {
    return array.getBit(index);
}

// Оператор присваивания от bool
BitReference& BitReference::operator=(bool value) {
    array.setBit(index, value);
    return *this; //для цепочек
}

// Присваивание от другого BitReference
BitReference& BitReference::operator=(const BitReference& other) {
    array.setBit(index, other.array.getBit(other.index));
    return *this;
}

// Равенство 
bool BitReference::operator==(bool other) const {
    return array.getBit(index) == other;
}

// Неравенство
bool BitReference::operator!=(bool other) const {
    return array.getBit(index) != other;
}

// Логическое отрицание: возвращает противоположное значение бита
bool BitReference::operator!() const {
    return !array.getBit(index);
}

// Логическое и: возвращает true, если бит установлен И other == true
bool BitReference::operator&&(bool other) const {
    return array.getBit(index) && other;
}

// Логическое или: возвращает true, если бит установлен ИЛИ other == true
bool BitReference::operator||(bool other) const {
    return array.getBit(index) || other;
}

// Конструктор массив из size значений false
BoolArray::BoolArray(int size) : arr_size(size) {
    int bytes = bytesCount();
    data = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++) {
        data[i] = 0;
    }
}
 
// Конструктор массив из size значений defaultValue
BoolArray::BoolArray(int size, bool defaultValue) : arr_size(size) {
    int bytes = bytesCount();
    data = new unsigned char[bytes];
    
    if (defaultValue) // defaultValue == true: заполняем все байты 0xFF, в байте со страшим индексом обнуляем лишние биты
    {
        for (int i = 0; i < bytes; i++) {
            data[i] = 0xFF; // 11111111
        }
        int lastByteBits = size % 8;
        if (lastByteBits != 0) {
            data[bytes - 1] &= (1 << lastByteBits) - 1;
        }
    } else // просто заполняем нулями
    {
        for (int i = 0; i < bytes; i++) {
            data[i] = 0;
        }
    }
}

// Конструктор копирования
BoolArray::BoolArray(const BoolArray& other) : arr_size(other.arr_size) {
    int bytes = bytesCount();
    data = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++) {
        data[i] = other.data[i];
    }
}

// Деструктор
BoolArray::~BoolArray() {
    delete[] data;
}

// Оператор присваивания
BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        arr_size = other.arr_size;
        int bytes = bytesCount();
        data = new unsigned char[bytes];
        for (int i = 0; i < bytes; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Оператор индексирования
// Возвращает объект, который умеет и читать, и писать
BitReference BoolArray::operator[](int index) {
    return BitReference(*this, index);
}

// Константный оператор индексирования
// Возвращает bool (только чтение)
bool BoolArray::operator[](int index) const {
    return getBit(index);
}

// Размер
int BoolArray::size() const {
    return arr_size;
}

// Изменение размера
void BoolArray::resize(int newSize, bool defaultValue) {
    if (newSize == arr_size) return;
    
    // Сохраняем старые данные
    int oldSize = arr_size;
    unsigned char* oldData = data;
    int oldBytes = (oldSize + 7) / 8;
    
    arr_size = newSize;
    int newBytes = bytesCount();
    data = new unsigned char[newBytes];
    
    // Копируем старые данные (сколько помещается в новый массив)
    int copyBytes = (oldBytes < newBytes) ? oldBytes : newBytes;
    for (int i = 0; i < copyBytes; i++) {
        data[i] = oldData[i];
    }
    //Если массив стал больше — заполняем новые байты значением по умолчанию
    if (newSize > oldSize) {
        // Просто проходим по всем новым индексам и устанавливаем их
        for (int i = oldSize; i < newSize; i++) {
            setBit(i, defaultValue);
        }
    }
    
    delete[] oldData;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, const BoolArray& arr) {
    out << "[";
    for (int i = 0; i < arr.size(); i++) {
        //если не первый, выводим запятую и пробел, затем значение элемента
        if (i > 0) out << ", ";
        out << arr[i];
    }
    out << "]";
    return out;
}