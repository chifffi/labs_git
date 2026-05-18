#ifndef NOTIFICATION_QUEUE_HPP
#define NOTIFICATION_QUEUE_HPP
#include "notification.hpp"

// Использовался кольцевой буфер 
// Кольцевой буфер — это массив фиксированного размера, который работает как очередь: когда мы доходим до конца массива, указатель заворачивается в начало.
// Эффективность: push O(1), pop O(1), нет сдвигов, просто двигаем указатели

// Предварительное объявление класса очереди (нужно для итератора)
class NotificationQueue;

// Класс итератора
class NotificationQueueIterator {
private:
    const NotificationQueue* container; // указатель на очередь
    int currentIndex; // текущий индекс в массиве
    int offset; // сколько элементов уже прошли
    
public:
    NotificationQueueIterator(const NotificationQueue* queue, int index, int startOffset);
    
    bool operator==(const NotificationQueueIterator& other) const;
    bool operator!=(const NotificationQueueIterator& other) const;
    NotificationQueueIterator& operator++();   // ++it
    NotificationQueueIterator operator++(int); // it++
    
    Notification& operator*();   // *it
    Notification* operator->();  // it->
};

// Класс очереди уведомлений
class NotificationQueue {
private:
    Notification* buffer; // указатель на массив уведомлений
    int capacity; // вместимость буфера
    int head; // указывает на первый элемент очереди (откуда забираем)
    int tail; // указывает на первое свободное место (куда кладём)
    int count; // количество элементов
    
    static const int INITIAL_CAPACITY = 4; // начальный размер
    static const int GROWTH_FACTOR = 2; // коэффициент роста
    
    // Вспомогательный метод для расширения буфера
    void resize();
    
public:
    NotificationQueue();
    ~NotificationQueue();
    
    // Добавление уведомления в конец очереди
    void push(const Notification& n);

    // Количество уведомлений в очереди
    int size() const;

    // Проверка, пуста ли очередь
    bool empty() const;

    // Удаление первого уведомления и возврат его
    Notification pop();
    
    // Дружественный класс — итератор имеет доступ к приватным полям
    friend class NotificationQueueIterator;
    
    // begin() — итератор на первый элемент
    NotificationQueueIterator begin() const;

    // end() — итератор на позицию после последнего
    NotificationQueueIterator end() const;
};

#endif