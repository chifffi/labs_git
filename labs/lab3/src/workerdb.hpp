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
    friend class WorkerDb;
};

// Хеш-таблица — это структура данных, которая хранит пары «ключ - значение» и позволяет быстро найти значение по ключу
// Нужна для эффективного поиска. В отличие от массива (где индекс — число) или списка (структура данных, где каждый элемент хранит указатель на следующий, элементы могут быть разбросаны по памяти.), 
// хеш-таблица находит элемент по ключу за O(1) в среднем
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
        //С флагом deleted мы не останавливаемся, а продолжаем поиск, когда видим на пути удаленную ячейку
        
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

    /* TODO: линейная ли сложность будет при поиске несуществующего элемента? будем ли мы проходить по каждому элементу до конца?
        Цикл в findIndex() продолжается только пока встречаются ячейки, которые когда=то были заняты (occupied == true)
        Как только мы доходим до ячейки, которая никогда не была занята (occupied == false), цикл останавливается
    
        В хеш-таблицах с линейным пробированием среднее число проверок для неуспешного поиска (ключа нет) примерно равно 1 + коэффициент загрузки^2
        где коэффициент загрузки = size / capacity
        В моей реализации коэффициент загрузки  <= LOAD_FACTOR (0.75), потому что при достижении 75% вызывается rehash(), увеличивающий capacity в 2 раза
    
        Для коэффициента загрузки = 0.75 среднее число проверок = 1 + (0.75)^2 = 1 + 0.5625 = 1.5625
        Это значит, что в среднем нужно проверить всего 1-2 ячейки, независимо от того, сколько всего элементов хранится в таблице
    
        Если в таблице много удалённых элементов (deleted = true, occupied = true), 
        то цепочка проверок может стать длиннее, потому что удалённые ячейки имеют occupied = true и не останавливают цикл
        Однако при rehash() удалённые элементы не переносятся в новую таблицу,
        таким образом, при каждой перестройке таблица очищается, и длинные цепочки удалённых элементов исчезают

        Можно ли обойти всю таблицу: теоретически да, если size == capacity (таблица полностью заполнена)
        В этом случае все ячейки имеют occupied == true, и поиск может пройти по всем ячейкам, вернувшись в начало
        Но в моей реализации этого никогда не будет, потому что rehash() срабатывает раньше, чем произойдет полное заполение (увеличивает capacity и сбрасывет коэффициент загрузки)
    */

    // Оператор [] возвращает ссылку на WorkerData
    // Если ключа нет, то создаёт новую запись с пустыми данными
    WorkerData& operator[](const MyString& key);
    
    // Количество элементов
    int getSize() const { return size; }

    // Дружественный класс итератора
    friend class WorkerDbIterator;

    // Удаление по ключу (фамилии)
    // Не удаляем физически, только помечаем. При поиске пропускаем deleted ячейки
    void remove(const MyString& key);
    
    // Удаление по итератору
    // Не удаляем физически, только помечаем. При поиске пропускаем deleted ячейки
    void erase(const WorkerDbIterator& pos);
    
    // Поиск
    WorkerDbIterator find(const MyString& surname) const;

    // Методы begin() и end()
    WorkerDbIterator begin() const; // итератор на начало
    WorkerDbIterator end() const; // итератор на конец
    

};

// Функции для работы с WorkerDb
void print_db(const WorkerDb& db);
double get_avg_age(const WorkerDb& db);

#endif