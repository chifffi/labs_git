#ifndef NOTIFICATION_PRIORITY_QUEUE_HPP
#define NOTIFICATION_PRIORITY_QUEUE_HPP

#include "notification.hpp"

// Функция для приоритета
// Преобразует тип уведомления в число (чем больше, тем выше приоритет)
int getTypePriority(NotificationType type);

// Приоритетная очередь уведомлений на бинарной куче
class NotificationPriorityQueue {
private:
    Notification* heap; // массив кучи
    int capacity; // вместимость массива
    int size; // текущее количество элементов
    
    static const int INITIAL_CAPACITY = 4;
    static const int GROWTH_FACTOR = 2;
    
    // Сравнение двух уведомлений по приоритету
    // Возвращает true, если a имеет больший приоритет, чем b
    bool isGreater(const Notification& a, const Notification& b) const;
    
    // Всплытие элемента вверх
    void siftUp(int index);
    
    // Просеивание элемента вниз
    void siftDown(int index);
    
    // Расширение массива
    void resize();
    
public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();
    
    // Добавление уведомления
    void push(const Notification& n);
    
    // Количество элементов
    int getSize() const;
    
    // Проверка на пустоту
    bool empty() const;
    
    // Получение самого приоритетного (без удаления)
    Notification top() const;
    
    // Удаление самого приоритетного и возврат его
    Notification pop();
};

#endif