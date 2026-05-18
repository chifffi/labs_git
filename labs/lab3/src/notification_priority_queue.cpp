#include "notification_priority_queue.hpp"

// Приоритеты:
// Правила от самого приоритетного к наименее:
// 1. SYSTEM_URGENT актуальнее всго остального
// 2. Чем раньше время, тем выше приоритет
// 3. При одинаковом времени: INSTANT > SYSTEM_NORMAL > APP
// 4. При одинаковом типе и времени: кто раньше добавлен, тот актуальнее (определяется индексом, но в куче не хранится порядок добавления)

// Функция для приоритета
int getTypePriority(NotificationType type) {
    switch (type) {
        case INSTANT:       return 3;  // мгновенные сообщения самые важные
        case SYSTEM_NORMAL: return 2;  // обычные системные средние
        case APP:           return 1;  // уведомления от приложений наименее важные
        case SYSTEM_URGENT: return 4;
        default:            return 0;
    }
}

bool NotificationPriorityQueue::isGreater(const Notification& a, const Notification& b) const {
    
    // SYSTEM_URGENT всегда важнее любого другого
    if (a.getType() == SYSTEM_URGENT && b.getType() != SYSTEM_URGENT) {
        return true;   // a важнее
    }
    if (a.getType() != SYSTEM_URGENT && b.getType() == SYSTEM_URGENT) {
        return false;  // b важнее
    }
    
    // Оба SYSTEM_URGENT или оба не SYSTEM_URGENT
    //  сравниваем по времени
    if (a.getTimestamp() != b.getTimestamp()) {
        return a.getTimestamp() < b.getTimestamp();  // меньше время, значит важнее
    }
    
    // одинаковое время, значит сравниваем по типу
    // INSTANT > SYSTEM_NORMAL > APP
    
    int priorityA = getTypePriority(a.getType());
    int priorityB = getTypePriority(b.getType());
    
    if (priorityA != priorityB) {
        return priorityA > priorityB;
    }
    
    //  одинаковый тип и время, значит актуальнее тот, что раньше добавлен в кучу
    return a.getSequence() < b.getSequence();
}

// Всплытие элемента вверх
void NotificationPriorityQueue::siftUp(int index) {
    // Пока не дошли до корня (индекс > 0)
    while (index > 0) {
        // Индекс родителя: (текущий индекс - 1) / 2
        int parent = (index - 1) / 2;
        // Если текущий элемент приоритетнее родителя — меняем их местами
        if (isGreater(heap[index], heap[parent])) {
            std::swap(heap[index], heap[parent]);
            index = parent; // поднимаемся выше и продолжаем
        } else {
            break;
        }
    }
}

// Просеивание элемента вниз
// Опускает элемент с индексом index вниз по куче, пока он не займёт правильное место
void NotificationPriorityQueue::siftDown(int index) {
    while (true) {
        // Индексы левого и правого детей
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index; // предполагаем, что текущий элемент — самый приоритетный
        
        // Если левый ребёнок существует и он приоритетнее текущего
        if (left < size && isGreater(heap[left], heap[largest])) {
            largest = left;
        }
        // Если правый ребёнок существует и он приоритетнее текущего
        if (right < size && isGreater(heap[right], heap[largest])) {
            largest = right;
        }
        
        // Если текущий элемент оказался самым приоритетным, останавливаемся
        if (largest == index) {
            break;
        }
        
        // Меняем местами с самым приоритетным ребёнком
        std::swap(heap[index], heap[largest]);
        // Опускаемся вниз и продолжаем
        index = largest;
    }
}

// Расширение массива
void NotificationPriorityQueue::resize() {
    // Новый размер в 2 раза больше старого
    int newCapacity = capacity * GROWTH_FACTOR;
    Notification* newHeap = new Notification[newCapacity];
    
    // Копируем все существующие элементы
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

// Конструктор
NotificationPriorityQueue::NotificationPriorityQueue() : capacity(INITIAL_CAPACITY), size(0) {
    heap = new Notification[capacity];
}

// Деструктор
NotificationPriorityQueue::~NotificationPriorityQueue() {
    delete[] heap;
}

// Добавление уведомления
// Сложность: O(log n) из-за siftUp (siftUp поднимается по дереву высотой log n)
void NotificationPriorityQueue::push(const Notification& n) {
    // Если массив заполнен — расширяем
    if (size == capacity) {
        resize();
    }
    
    // Добавляем новый элемент в конец
    heap[size] = n;
    // Поднимаем его на правильное место
    siftUp(size);
    // Увеличиваем счётчик элементов
    size++;
}

// Количество элементов
int NotificationPriorityQueue::getSize() const {
    return size;
}

// Проверка на пустоту
bool NotificationPriorityQueue::empty() const {
    return size == 0;
}

// Получение самого приоритетного (без удаления)
// Сложность: O(1) — просто берём элемент по индексу 0
Notification NotificationPriorityQueue::top() const {
    if (size == 0) {
        throw "Priority queue is empty!";
    }
    return heap[0];
}

// Удаление самого приоритетного и возврат его
// Сложность: O(log n) из-за siftDown (siftDown опускается по дереву высотой log n)
Notification NotificationPriorityQueue::pop() {
    if (size == 0) {
        throw "Priority queue is empty!";
    }
    
    // Запоминаем самый приоритетный элемент (корень)
    Notification result = heap[0];
    size--;
    
    // Если остались элементы, перемещаем последний в корень и просеиваем вниз
    // Так эффективнее вместо сдвтгов всех элементов O(n)
    if (size > 0) {
        heap[0] = heap[size];
        siftDown(0);
    }
    
    return result;
}
