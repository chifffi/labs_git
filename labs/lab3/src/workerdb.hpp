#ifndef WORKERDB_HPP
#define WORKERDB_HPP

#include "mystring.hpp"
#include <iostream>

// Структура с информацией о работнике
// struct, потому что это простой контейнер данных
// Все поля public для прямого доступа: db["Ivanov"].name = "Ivan"
struct WorkerData {
    MyString name; 
    int age; 
    int experience;  // опыт работы в годах (целое число, полных лет)
    
    // Конструктор по умолчанию
    WorkerData() : name(""), age(0), experience(0) {}
    
    // Конструктор для создания WorkerData из MyString
    WorkerData(const MyString& n, int a, int exp) : name(n), age(a), experience(exp) {}
    
    // Конструктор для создания WorkerData из char*
    WorkerData(const char* n, int a, int exp) : name(MyString(n)), age(a), experience(exp) {}
};

// Предварительное неполное объявление класса (нужно для итератора)
class WorkerDb;

// Класс итератора
class WorkerDbIterator {
private:
    const WorkerDb* container; // указатель на таблицу
    int currentIndex; // текущий индекс в таблице
    
public:
    WorkerDbIterator(const WorkerDb* db, int startIndex);
    
    bool operator==(const WorkerDbIterator& other) const;
    bool operator!=(const WorkerDbIterator& other) const;
    WorkerDbIterator& operator++();  // ++it
    WorkerDbIterator operator++(int); // it++
    
    WorkerData& operator*(); // *it
    WorkerData* operator->(); // it->
    const MyString& key() const; // it.key()
};

// Хеш-таблица — это структура данных, которая хранит пары «ключ - значение» и позволяет быстро найти значение по ключу
// Нужна для эффективного поиска. В отличие от массива (где индекс — число) или списка (где поиск O(n)), хеш-таблица находит элемент по ключу за O(1) в среднем
// 1. Хеш-функция превращает ключ (строку-фамилию) в число-индекс
// 2. Данные кладутся в массив по этому индексу
// 3. При поиске снова вычисляется индекс — и данные находятся сразу
// Коллизии - когда два ключа дают одинаковый индекс. Решение линейным пробированием - идём к следующей свободной ячейке

// Класс ассоциативного массива WorkerDb (хеш-таблица)
class WorkerDb {
private:
    // Внутренняя структура для хранения элемента хеш-таблицы
    struct Entry {
        MyString key; // фамилия сотрудника (ключ)
        WorkerData value; // данные сотрудника
        bool occupied; // true — ячейка занята
        bool deleted;  // true — элемент помечен удаленным
        
        // Конструктор Entry: создаём пустую ячейку
        Entry() : key(""), occupied(false), deleted(false) {}
    };
    Entry* table;  // указатель на динамический массив
    int capacity;  // вместимость таблицы
    int size;   // количество реально хранящихся элементов
    
    // static const делает константу общей для всех объектов и защищённой от изменений, храня её внутри класса
    static const int INITIAL_CAPACITY = 16; // начальный размер
    static const double LOAD_FACTOR;  // коэффициент загрузки, при его достижении расширяем таблицу, =0.75 в cpp
    
    // Хеш-функция: превращает ключ в индекс
    int hash(const MyString& key) const;
    
    // Поиск индекса для ключа с учётом коллизий
    int findIndex(const MyString& key) const;
    
    // Перестройка таблицы при переполнении
    void rehash();
    
public:
    WorkerDb(); // конструктор
    ~WorkerDb(); // деструктор
    
    // Оператор [] возвращает ссылку на WorkerData
    // Если ключа нет, то создаёт новую запись с пустыми данными
    WorkerData& operator[](const MyString& key);
    
    // Количество элементов
    int getSize() const { return size; }

    // Дружественный класс итератора
    friend class WorkerDbIterator;

    // Методы begin() и end()
    WorkerDbIterator begin() const; // итератор на начало
    WorkerDbIterator end() const; // итератор на конец
    

};

// Функции для работы с WorkerDb
void print_db(const WorkerDb& db);
double get_avg_age(const WorkerDb& db);

#endif