#include "notification_queue.hpp"

// Итератор
// Конструктор
NotificationQueueIterator::NotificationQueueIterator(const NotificationQueue* queue, int index, int startOffset): container(queue), currentIndex(index), offset(startOffset) {}

// Сравнение индексов
bool NotificationQueueIterator::operator==(const NotificationQueueIterator& other) const {
    return offset == other.offset;
}
bool NotificationQueueIterator::operator!=(const NotificationQueueIterator& other) const {
    return !(*this == other);
}

// Префиксный ++ (перемещает итератор на следующий элемент)
NotificationQueueIterator& NotificationQueueIterator::operator++() {
    offset++;
    // Переход к следующему индексу с учётом заворачивания
    currentIndex = (currentIndex + 1) % container->capacity;
    return *this;
}

// Постфиксный ++ (возвращает старое значение, увеличивает себя)
NotificationQueueIterator NotificationQueueIterator::operator++(int) {
    NotificationQueueIterator temp = *this;
    ++(*this); //вызывает префиксный ++, который учитывает заворачивание
    return temp;
}

// Разыменование
Notification& NotificationQueueIterator::operator*() {
    // Доступ к приватному полю buffer через дружбу
    // const_cast убирает const
    return const_cast<Notification&>(container->buffer[currentIndex]);
}

// Возвращает указатель на уведомление
Notification* NotificationQueueIterator::operator->() {
    return const_cast<Notification*>(&(container->buffer[currentIndex]));
}

// Класс очереди уведомлений
// Конструктор
// выделяем память сразу, чтобы был готов к использованию после конструктора
NotificationQueue::NotificationQueue() : capacity(INITIAL_CAPACITY), head(0), tail(0), count(0) {
    buffer = new Notification[capacity];
}

// Деструктор
NotificationQueue::~NotificationQueue() {
    delete[] buffer;
}

// Вспомогательный метод для расширения буфера
void NotificationQueue::resize() {
    int newCapacity = capacity * GROWTH_FACTOR;
    Notification* newBuffer = new Notification[newCapacity];
    
    for (int i = 0; i < count; i++) {
        newBuffer[i] = buffer[(head + i) % capacity];
        // (head + i) % capacity: вычисляет индекс в старом массиве с учётом заворачивания
        // Копирует элементы по порядку (без зазоров)
    }
    
    delete[] buffer;
    buffer = newBuffer;
    head = 0; // первый элемент теперь в начале
    tail = count; // свободное место после последнего элемента
    capacity = newCapacity; // новыйразмер
}

// Добавление уведомления в конец очереди
void NotificationQueue::push(const Notification& n) {
    if (count == capacity) {
        resize(); // расширяем, если заполнено
    }
    
    buffer[tail] = n; // кладём в ячейку tail
    tail = (tail + 1) % capacity; // двигаем tail (с учетом заворачивания)
    count++;
}

// Количество уведомлений в очереди
int NotificationQueue::size() const {
    return count;
}

// Проверка, пуста ли очередь
bool NotificationQueue::empty() const {
    return count == 0;
}

// Удаление первого уведомления и возврат его
// Элемент копируется, потом удаляется из очереди. 
// head двигается, элемент в массиве остаётся, но на него больше не указывает head
Notification NotificationQueue::pop() {
    if (count == 0) {
        throw "Queue is empty!";
    }
    
    Notification result = buffer[head]; // забираем первый элемент
    head = (head + 1) % capacity; // двигаем head (с учетом заворачивания)
    count--;
    return result;
}

// begin() — итератор на первый элемент buffer[head]
NotificationQueueIterator NotificationQueue::begin() const {
    // начинаем с head, первый элемент имеет offset 0
    return NotificationQueueIterator(this, head, 0);
}

// end() — итератор на позицию после последнего
NotificationQueueIterator NotificationQueue::end() const 
{
    // end — это позиция после последнего (offset = count)
    // currentIndex не важен, так как сравнение идёт по offset
    return NotificationQueueIterator(this, head, count);
}