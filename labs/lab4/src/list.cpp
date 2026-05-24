#include "list.hpp"
#include <cassert>  // для assert в operator[]

// Класс Node
// Конструктор по умолчанию нужен для фиктивных узлов (Head, Tail)
List::Node::Node(): m_data(), pPrev(nullptr), pNext(nullptr){}

// Конструктор с параметрми для реального узла 
// создаёт новый узел и вставляет его после узла prevNode
List::Node::Node(Node* prevNode, const Circle* pc)
    : m_data(*pc) // разыменовываем указатель и копируем данные из круга
    , pPrev(prevNode) // новый узел запоминает, какой узел является для него предыдущим
    , pNext(prevNode->pNext)  
    // смотрит, на какой узел указывал prevNode до этого (это nextNode)
    // новый узел запоминает этот узел как следующий
{
    prevNode->pNext = this;
    
    pNext->pPrev = this;
}

// Деструктор узла — удаляет себя из списка
// деструктор Node вызывается только для реальных узлов
// Изменяет соседей, чтобы они указывали друг на друга
List::Node::~Node() {
    if (pPrev) {
        pPrev->pNext = pNext;
    }
    if (pNext) {
        pNext->pPrev = pPrev;
    }
}

// Класс List
// Конструктор по умолчанию
// Создаёт пустой список с фиктивными узлами Head и Tail
List::List(): m_size(0), m_head(), m_tail(), m_cachedNode(nullptr), m_cachedIndex(0)
{
    // Связываем Head и Tail друг с другом
    m_head.pNext = &m_tail;
    m_tail.pPrev = &m_head;
}

void List::invalidateCache() {
    m_cachedNode = nullptr;
    m_cachedIndex = 0;
}

// Конструктор копирования
// Создаёт новый список, содержащий копии всех элементов other
List::List(const List& other): List()  // вызываем конструктор по умолчанию
{
    // Копируем все реальные узлы из other
    Node* current = other.m_head.pNext; // указатель на первый реальный узел списка other
    while (current != &other.m_tail) {
        pushBack(current->m_data);  // добавляем копию данных текущего узла в конец нового списка
        current = current->pNext; //перемещаем указатель current на следующий
    }
}

// Деструктор
List::~List() {
    clear();
}

// Оператор присваивания
List& List::operator=(const List& other) {
    // Защита от самоприсваивания
    if (this == &other) {
        return *this;
    }
    
    // Очищаем текущий список
    clear();
    
    // Копируем все реальные узлы из other
    Node* current = other.m_head.pNext;
    while (current != &other.m_tail) {
        pushBack(current->m_data);
        current = current->pNext; //перемещаем указатель current на следующий
    }
    
    return *this;
}

// Добавление в начало списка (после фиктивного Head)
void List::pushFront(const Circle& circle) {
    new Node(&m_head, &circle);  
    // new — выделяет память в куче для нового узла
    // Node(&m_head, &circle) — вызывает конструктор Node с двумя аргументами
    // &m_head - указ на предыдущ(фиктивный узел), & circle - указ на круг
    ++m_size;
    invalidateCache();
}

// Добавление в конец списка (перед фиктивным Tail)
void List::pushBack(const Circle& circle) {
    new Node(m_tail.pPrev, &circle);  
    // Node(m_tail.pPrev, &circle)) — вызывает конструктор Node с двумя аргументами
    // m_tail.pPrev - указ на последний реальный узел (или на m_head, если список пуст), & circle - указ на круг
    ++m_size;
    invalidateCache();
}

// Удаление первого элемента с заданным значением(центр и радиус)
bool List::removeFirst(const Circle& value) {
    Node* current = m_head.pNext;  // указ на первый реальный узел
    
    while (current != &m_tail) {
        Node* next = current->pNext;  // сохраняем указатель на следующий узел до того, как мы удалим текущий
        
        if (current->m_data == value) // используем оператор ==, который определен в Circle
        {
            delete current; 
            // delete вызывает деструктор объекта current (тип Node), который сам изменяет соседей
            // delete освобождает память, которую занимал узел
            --m_size;
            invalidateCache();
            return true;
        }
        current = next; //перемещаем указатель current на следующий узел next
    }
    return false;
}

// Удаление всех элементов с заданным значением
size_t List::removeAll(const Circle& value) {
    size_t removed = 0; //кол-во удаленных
    Node* current = m_head.pNext; // указ на первый реальный узел
    
    while (current != &m_tail) {
        Node* next = current->pNext;  // сохраняем указатель на следующий узел до того, как мы удалим текущий
        
        if (current->m_data == value) // как в removeFirst
        {
            delete current;
            // delete вызывает деструктор объекта current (тип Node), который сам изменяет соседей
            // delete освобождает память, которую занимал узел
            ++removed;
            --m_size;
        }
        current = next;
    }
    
    if (removed > 0) {
        invalidateCache();
    }

    return removed;
}

// Удаление всех элементов
void List::clear() {
    Node* current = m_head.pNext; // указ на первый реальный узел
    
    while (current != &m_tail) {
        Node* next = current->pNext; // сохраняем указатель на следующий узел до того, как мы удалим текущий
        delete current;
        current = next;
    }
    
    // Восстанавливаем пустой список
    m_head.pNext = &m_tail;
    m_tail.pPrev = &m_head;
    m_size = 0;
    invalidateCache();
}

// оператор []
Circle& List::operator[](size_t index) {
    assert(index < m_size);  // проверка выхода за границы
    
    // Если кэш валиден и индекс совпадает, сложность O(1)
    if (m_cachedNode && index == m_cachedIndex) {
        return m_cachedNode->m_data;
    }
    
    // Если кэш валиден и индекс больше, идём вперед от кэша
    if (m_cachedNode && index > m_cachedIndex) {
        Node* current = m_cachedNode;
        for (size_t i = m_cachedIndex; i < index; ++i) {
            current = current->pNext;
        }
        m_cachedNode = current;
        m_cachedIndex = index;
        return current->m_data;
    }
    
    // Если кэш валиден и индекс меньше, идём назад от кэша
    if (m_cachedNode && index < m_cachedIndex) {
        Node* current = m_cachedNode;
        for (size_t i = m_cachedIndex; i > index; --i) {
            current = current->pPrev;
        }
        m_cachedNode = current;
        m_cachedIndex = index;
        return current->m_data;
    }
    
    // Кэш не валиден,  идём сначала
    Node* current = m_head.pNext;
    for (size_t i = 0; i < index; ++i) {
        current = current->pNext;
    }
    m_cachedNode = current;
    m_cachedIndex = index;
    return current->m_data;
}

// const версия оператора [] (для константных объектов List)
const Circle& List::operator[](size_t index) const {
    assert(index < m_size);  // проверка выхода за границы
    
    if (m_cachedNode && index == m_cachedIndex) {
        return m_cachedNode->m_data;
    }
    
    if (m_cachedNode && index > m_cachedIndex) {
        Node* current = m_cachedNode;
        for (size_t i = m_cachedIndex; i < index; ++i) {
            current = current->pNext;
        }
        m_cachedNode = current;
        m_cachedIndex = index;
        return current->m_data;
    }
    
    if (m_cachedNode && index < m_cachedIndex) {
        Node* current = m_cachedNode;
        for (size_t i = m_cachedIndex; i > index; --i) {
            current = current->pPrev;
        }
        m_cachedNode = current;
        m_cachedIndex = index;
        return current->m_data;
    }
    
    Node* current = m_head.pNext;
    for (size_t i = 0; i < index; ++i) {
        current = current->pNext;
    }
    m_cachedNode = current;
    m_cachedIndex = index;
    return current->m_data;
}

// Проверка на пустоту (нет реальных узлов)
bool List::empty() const {
    return m_head.pNext == &m_tail;
}

// Получение размера списка
size_t List::size() const {
    return m_size;
}


/*
Сортировка слиянием без учета фиктивных элементов
1. разделяем на две части
2. рекурсивно сортируем каждую из 2х частей
3. сливаем две отсортированные части

Сортировка слиянием имеет сложность O(n log n), потому что список рекурсивно делится пополам (log n уровней), 
а на каждом уровне выполняется слияние всех элементов (O(n) на уровень). 
Рекуррентное соотношение T(n) = 2T(n/2) + O(n) даёт решение O(n log n). 
Это быстрее пузырьковой сортировки, сортировки вставками, сортировки выбором O(n²)
*/


// Разделение списка на две примерно равные части
// Возвращает указатель на узел начала второй половины
List::Node* List::split(Node* first) {
    if (!first || !first->pNext) // нет или один 
    {
        return nullptr;
    }
    
    Node* slow = first; //slow - указ, который двигается на 1 шаг
    Node* fast = first->pNext; // fast - указ, который двигается на 2 шага

    //когда fast достигнет конца списка, slow будет
    //при четном кол-ве: на конце первой части, части будут равны
    //при нечетном кол-ве: ровно в середине, первая часть будет на 1 больше
    
    while (fast && fast->pNext) //чтобы fast мог сделать 2 шага, нужно, чтобы существовал и текущий узел fast, и следующий за ним
    {
        slow = slow->pNext; //1 шаг
        fast = fast->pNext->pNext; // 2 шага
    }
    
    // slow указывает на последний узел первый половины
    // secondHalf указывает на первый узел второй половины
    Node* secondHalf = slow->pNext; //запоминаем узел после slow - начало второй половины

    slow->pNext = nullptr; //разрыв прямую связь в первой половине со второй
    secondHalf->pPrev = nullptr;// разрываем обратную связь во второй половине
    
    return secondHalf;
}

// Слияние двух отсортированных до этого списков в один отсортированный список
// Возвращает указатель на начало слитого списка
// left - указатель на начало первого отсортированного списка, right - указатель на начало второго
List::Node* List::merge(Node* left, Node* right) {
    Node dummy; // фиктивный узел (временная голова)
    Node* tail = &dummy; // указатель tail показывает на последний добавленный узел (пока начало dummy = конец)
    
    while (left && right) //пока оба списка не пусты добавляем по одному узлу
    {
        if (left->m_data.area() <= right->m_data.area()) // берем площадь меньшего
        {
            tail->pNext = left;
            //tail теперь знает своего следующего
            left->pPrev = tail;
            //left теперь знает своего предыдущего
            left = left->pNext;
            //Двигаем указатель в том списке, откуда взяли
        } 
        else // аналогично левому
        {
            tail->pNext = right;
            right->pPrev = tail;
            right = right->pNext; //двигаем указатель в том списке, откуда взяли
        }
        tail = tail->pNext; // перемещаем указатель tail на новый последний добавленный узел(конец)
    }
    
    // Когда один из списков закончился, добавляем оставшиеся элементы другого списка целиком
    // Узлы в остатке уже связаны между собой, поэтому достаточно прицепить первый узел остатка, и все остальные подтянутся за ним автоматически
    
    // Добавляем остатки левого списка
    if (left) {
        tail->pNext = left; // прицепляем весь оставшийся список
        left->pPrev = tail;
    }
    // Добавляем остатки правого списка
    if (right) {
        tail->pNext = right;
        right->pPrev = tail;
    }
    
    // Возвращаем начало (следующий за фиктивным узлом)
    Node* result = dummy.pNext; //указатель на первый реальный узел
    if (result) {
        result->pPrev = nullptr; //Обнуляем обратную связь у первого узла (у него нет предыдущего)
    }
    return result;
}

// Рекурсивная сортировка слиянием
// Возвращает указатель на начало отсортированного списка

/*T(n) = 2 * T(n/2) + O(n)
Время сортировки списка из n элементов равно:
    Времени сортировки левой половины (n/2 элементов) +
    Времени сортировки правой половины (n/2 элементов) +
    Линейное время на разделение и слияние
Hешается методом подстановки:
После k шагов получаем T(n) = 2^k * T(n/2^k) + k * n
Базовый случай T(1) = 1 даёт k = log n
Подставляя, получаем T(n) = n + n log n, что даёт O(n log n)
*/

List::Node* List::mergeSort(Node* first) {
    // Базовый случай для остановки рекурсии: пустой список или один элемент
    if (!first || !first->pNext) {
        return first;
    }
    
    // Разделяем список на две половины
    // secondHalf - указатель на начало второй половины
    Node* secondHalf = split(first); // O(n)
    
    // Рекурсивно сортируем каждую половину
    Node* left = mergeSort(first); // T(n/2)
    Node* right = mergeSort(secondHalf); // T(n/2)
    
    // Сливаем отсортированные половины
    // возвращает указатель на начало слитого списка
    return merge(left, right); // O(n)
}

// Публичный метод сортировки
void List::sortByArea() {
    if (m_size < 2) return;  // пустой список или 1 элемент, сортировать нечего
    
    // Отсоединяем реальные узлы от фиктивных Head и Tail
    Node* firstNode = m_head.pNext; 
    if (firstNode == &m_tail) return;  // пустой список
    
    Node* lastNode = m_tail.pPrev;
    
    // Разрываем связь с фиктивными элементами
    firstNode->pPrev = nullptr;
    lastNode->pNext = nullptr;
    
    // Вызываем рекурсивную сортировку на чистом списке
    Node* sortedHead = mergeSort(firstNode);
    
    // Находим последний узел в отсортированном списке
    Node* sortedTail = sortedHead;
    while (sortedTail->pNext) {
        sortedTail = sortedTail->pNext;
    }
    
    // Подключаем отсортированный список обратно к фиктивным элементам
    m_head.pNext = sortedHead;
    sortedHead->pPrev = &m_head;
    
    sortedTail->pNext = &m_tail;
    m_tail.pPrev = sortedTail;

    invalidateCache();
}


// Проверка наличия элемента в списке по данным 
bool List::contains(const Circle& value) const {
    Node* current = m_head.pNext; // указ на первый реальный узел
    while (current != &m_tail) {
        if (current->m_data == value) {
            return true;
        }
        current = current->pNext; // перемещаем указатель current на следующий узел
    }
    return false;
}

// Дружественный оператор вывода
std::ostream& operator<<(std::ostream& os, const List& list) {
    if (list.empty()) {
        os << "List is empty\n";
        return os; // Возвращает ссылку на поток, чтобы можно было писать цепочки
    }
    
    os << "List of " << list.m_size << " circles:\n";
    
    const List::Node* current = list.m_head.pNext; // Указатель на первый реальный узел списка (константный тк не можем изменять данные узла: current->m_data, current->pNext и тд)
    int index = 1; //Счётчик элементов для нумерации при выводе
    while (current != &list.m_tail) {
        os << "  " << index++ << ": " << current->m_data << "\n";
        current = current->pNext; // перемещаем указатель current на следующий узел
    }
    return os; // Возвращает ссылку на поток, чтобы можно было писать цепочки
}


// Сохранение(запись) списка в файл
// Формат: каждая строка "x y радиус", сама функция ничего не возвращает, принимает как параметр имя файла
void List::saveToFile(const char* filename) const {
    std::ofstream fout(filename);
    // std::ofstream - тип объекта - выходной файловый поток
    // fout	- имя объекта
    // (filename) - передаём имя файла в конструктор, если файла нет — создаётся, если файл есть — его содержимое стирается и перезаписывается
    if (!fout) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для записи\n";
        return; // файл не создаётся, список не сохраняется
    }
    
    Node* current = m_head.pNext; // Указатель на первый реальный узел списка
    while (current != &m_tail) {
        fout << current->m_data.getCenter().getX() << " "
             << current->m_data.getCenter().getY() << " "
             << current->m_data.getRadius() << "\n";
        current = current->pNext; // перемещаем указатель current на следующий узел
    }
    
    fout.close();
    std::cout << "Сохранено " << m_size << " кругов в файл " << filename << "\n";
}

// Загрузка(чтение) списка из файла
// Формат: каждая строка "x y радиус"
void List::loadFromFile(const char* filename) {
    std::ifstream fin(filename);
    // std::ifstream - тип объекта - входной файловый поток
    // fin	- имя объекта
    // (filename) - передаём имя файла в конструктор, если файла нет - ошибка
    if (!fin) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для чтения\n";
        return;
    }
    
    clear();  // очищаем текущий список
    
    double x, y, r;
    while (fin >> x >> y >> r) 
    // читает первое число из файла, сохраняет в x
    // читает второе число из файла, сохраняет в y
    // читает третье число из файла, сохраняет в r
    // возвращает ссылку на fin (fin можно преобразовать в bool, если true - продолжаем, если false - ошибка или конец файла )
    {
        pushBack(Circle(x, y, r)); // создаем новый круг с прочитанными координатами и радиусом, и добавляем его в конец списка
    }
    
    fin.close();
    std::cout << "Загружено " << m_size << " кругов из файла " << filename << "\n";
}