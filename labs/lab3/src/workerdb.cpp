#include "workerdb.hpp"
#include <cstring>

const double WorkerDb::LOAD_FACTOR = 0.75;

// Класс итератора
// Конструктор (запоминает таблицу (container = db) и стартовую непустую позицию)
WorkerDbIterator::WorkerDbIterator(const WorkerDb* db, int startIndex)
    : container(db), currentIndex(startIndex) {
    // Пропускаем пустые и удалённые ячейки
    while (currentIndex < container->capacity && (!container->table[currentIndex].occupied || container->table[currentIndex].deleted)) {
        currentIndex++;
    }
}

// Сравнение индексов
bool WorkerDbIterator::operator==(const WorkerDbIterator& other) const {
    return currentIndex == other.currentIndex;
}
bool WorkerDbIterator::operator!=(const WorkerDbIterator& other) const {
    return !(*this == other);
}

// Префиксный ++ (перемещает итератор к следующему активному элементу)
WorkerDbIterator& WorkerDbIterator::operator++() {
    currentIndex++; // переходим к следующей ячейке
    while (currentIndex < container->capacity && (!container->table[currentIndex].occupied || container->table[currentIndex].deleted))
    {
        currentIndex++; // пропускаем пустые и удалённые
    }
    return *this; //для цепочек
}

// Постфиксный ++ (возвращает старый итератор, потом сдвигается)
WorkerDbIterator WorkerDbIterator::operator++(int) {
    WorkerDbIterator temp = *this; // запоминаем текущее состояние
    ++(*this); // вызываем префиксный ++
    return temp; // возвращаем старое состояние
}

// Разыменование (возвращает ссылку на данные (WorkerData) текущего сотрудника)
WorkerData& WorkerDbIterator::operator*() {
    return container->table[currentIndex].value;
}

// Возвращает указатель на данные
WorkerData* WorkerDbIterator::operator->() {
    return &(container->table[currentIndex].value);
}

// Получение ключа (возвращает фамилию (ключ) текущего сотрудника)
const MyString& WorkerDbIterator::key() const {
    return container->table[currentIndex].key;
}



// Основной класс

//Хеш-функция
//возвращает целое число (индекс от 0 до capacity-1)
int WorkerDb::hash(const MyString& key) const {
    const char* str = key.get_Str();
    int len = key.length_str();
    unsigned int h = 0; //переменная для хеш-значения, беззнаковое чтобы правильно работало с остатками
    
    for (int i = 0; i < len; i++) //по каждому символу строки
    {
        h = (h * 31 + static_cast<unsigned char>(str[i])) % capacity;
        //умножаем текущее хеш-значение на 31 
        //31 тк простое, нечетное, не слишком большое число, значит будет давать лучшее распределение при хешировании
        //преобразуем символ в unsigned char (от 0 до 255), чтобы работать с кодом символа как с неотрицательным числом
        //добавляем код текущего символа (так каждый символ влияет на хеш, коллизий будет меньше)
        //берём остаток от деления на размер таблицы, чтобы индекс был в пределах массива
    }
    return h;
}

//Поиск индекса (с учетом пометки об удалении)
int WorkerDb::findIndex(const MyString& key) const {
    int index = hash(key);
    int startIndex = index;
    
    // Пока ячейка когда-либо была занята
    // Если ячейка помечена deleted, всё равно occupied = true
    while (table[index].occupied) {
        // Если не удалена и ключ совпадает, то нашли
        if (!table[index].deleted && table[index].key == key) {
            return index;
        }
        // Иначе коллизия, идём дальше
        index = (index + 1) % capacity; //% capacity чтобы не выйти за пределы
        
        // Если обошли всю таблицу и не нашли, выходим
        if (index == startIndex) break;
    }
    // Вернём индекс свободной ячейки или удалённой, его можно использовать для вставки нового элемент
    return index;
}

//Перестройка таблицы (rehash)
void WorkerDb::rehash() {
    int oldCapacity = capacity;
    Entry* oldTable = table;
    
    // Увеличиваем размер в 2 раза
    capacity = oldCapacity * 2;
    table = new Entry[capacity];
    size = 0;
    
    // Переносим только активные (не удалённые) элементы
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].occupied && !oldTable[i].deleted) {
            int newIndex = findIndex(oldTable[i].key);
            table[newIndex].key = std::move(oldTable[i].key);
            table[newIndex].value = std::move(oldTable[i].value);
            table[newIndex].occupied = true;
            table[newIndex].deleted = false;
            size++;
        }
    }
    
    delete[] oldTable;
}

//Конструктор
WorkerDb::WorkerDb() {
    capacity = INITIAL_CAPACITY;
    table = new Entry[capacity];
    size = 0;
}

// Деструктор
WorkerDb::~WorkerDb() {
    delete[] table;
}

//Оператор []
WorkerData& WorkerDb::operator[](const MyString& key) {
    int index = findIndex(key);
    
    // Если ячейка свободна или помечена как удалённая — создаём новую запись
    if (!table[index].occupied || table[index].deleted) {
        table[index].key = key;
        table[index].occupied = true;
        table[index].deleted = false;
        size++;
        
        // Проверяем, не пора ли расширить таблицу
        if (static_cast<double>(size) / capacity >= LOAD_FACTOR) {
            rehash();
            index = findIndex(key);  // после расширения индекс мог измениться
        }
    }
    
    // Возвращаем ссылку на данные (можно читать и изменять)
    return table[index].value;
}

// begin() (итератор, который начинает с индекса 0 и сам находит первый активный элемент)
WorkerDbIterator WorkerDb::begin() const {
    return WorkerDbIterator(this, 0);
}

// end() (итератор, который указывает на позицию capacity (за пределами массива))
WorkerDbIterator WorkerDb::end() const {
    return WorkerDbIterator(this, capacity);
}

// Печать базы данных работников
void print_db(const WorkerDb& db) {
    for (auto it = db.begin(); it != db.end(); ++it) {
        std::cout << it.key() << "\n";
        std::cout << "  Name:       " << it->name << "\n";
        std::cout << "  Age:        " << it->age << "\n";
        std::cout << "  Experience: " << it->experience << " years\n";
        std::cout << "\n";
    }
}

// Подсчет среднего возраста сотрудников
double get_avg_age(const WorkerDb& db) {
    if (db.getSize() == 0) {
        return 0.0;  // нет сотрудников, средний возраст 0
    }
    
    int totalAge = 0;
    int count = 0;
    
    for (auto it = db.begin(); it != db.end(); ++it) {
        totalAge += it->age;
        count++;
    }
    
    return static_cast<double>(totalAge) / count;
}
