#ifndef BOOLARRAY_HPP
#define BOOLARRAY_HPP

#include <iostream>

// Предварительное объявление класса BoolArray (нужно для BitReference)
class BoolArray;

// класс для для доступа к отдельному биту
// позволяет arr[5] = true и bool x = arr[5] работать как с обычным массивом.
class BitReference {
private:
    BoolArray& array; // ссылка на объект BoolArray, к которому относится этот бит
    int index; //индекс бита в массиве
    
public:
    // Конструктор
    BitReference(BoolArray& arr, int idx);
    
    // Неявное преобразование в bool
    operator bool() const;
    
    // Оператор присваивания от bool
    BitReference& operator=(bool value);
    
    // Присваивание от другого BitReference
    BitReference& operator=(const BitReference& other);
    
    /* TODO: можно ли без них?
        операторы ==, !=, !, &&, || в классе BitReference не обязательны, 
        потому что встроенные операторы C++ для типа bool уже существуют.
        operator bool() обеспечивает неявное преобразование BitReference в bool, 
        после чего все логические операции и сравнения выполняются встроенными операторами

        удаление операторов ==, !=, !, &&, || из класса BitReference будет работать на любом стандартном компиляторе, 
        потому что это поведение описано в стандарте C++

        стандарт C++ определяет, что:
        1. неявное преобразование пользовательского типа (через operator bool()) применяется везде, где ожидается bool
        2. встроенные операторы &&, ||, !, ==, != для типа bool существуют в языке всегда
        3. компилятор обязан выполнить неявное преобразование, если нет точного совпадения типов
    */

    // Сравнение с bool
    //bool operator==(bool other) const;
    //bool operator!=(bool other) const;
    // Логические операторы
    //bool operator!() const;
    //bool operator&&(bool other) const;
    //bool operator||(bool other) const;
};

class BoolArray {
private:
    unsigned char* data; // указатель на массив байтов (Каждый байт хранит 8 бит - логических значений)
    int arr_size; // количество логических элементов
    
    int bytesCount() const;  // сколько нужно байт для хранения arr_size бит
    bool getBit(int index) const; // Получить бит по индексу
    void setBit(int index, bool value); // Установить бит по индексу
    
public:
    // Конструкторы
    BoolArray(int size);  // массив из size значений false
    BoolArray(int size, bool defaultValue);  // массив из size значений defaultValue
    BoolArray(const BoolArray& other); // конструктор копирования
    
    // Деструктор
    ~BoolArray();
    
    // Оператор присваивания
    BoolArray& operator=(const BoolArray& other);
    
    // Операторы индексирования
    BitReference operator[](int index); //когда объект не константный, возвращаем BitReference для записи и чтения
    bool operator[](int index) const; // для константных объектов, только читать, потому что константный объект нельзя менять
    
    // Размер массива
    int size() const;
    
    // Изменение размера
    // Если newSize больше, то новые элементы заполняются defaultValue
    // Если newSize меньше, то лишние элементы отбрасываются
    void resize(int newSize, bool defaultValue = false);
    
    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& out, const BoolArray& arr);

    // Дружественный класс для доступа к приватным полям
    friend class BitReference;
};

#endif