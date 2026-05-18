#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include "mystring.hpp"
#include <ctime>
#include <iostream>

// Типы уведомлений
enum NotificationType {
    SYSTEM_NORMAL, //0, Системное обычное
    SYSTEM_URGENT, //1, Системное срочное
    INSTANT, //2, Мгновенное
    APP //3, от приложения
};

// Класс уведомления
class Notification {
private:
    NotificationType type;
    time_t timestamp;
    int sequence;  // порядковый номер уведомления для приоритетов

    static int nextSequence;  // глобальный счётчик для всех уведомлений
    
    union NotificationData {
        struct {
            const char* message;
        } system;
        
        struct {
            const char* contact;
            const char* text;
        } instant;
        
        struct {
            const char* appName;
            const char* title;
            const char* text;
        } app;
        
        // Конструктор для union (обнуляем)
        NotificationData() {}
        
        // Деструктор (пустой, т.к. указатели не нужно удалять)
        ~NotificationData() {}
    } data;
    
public:
    // Конструкторы
    Notification();
    Notification(const Notification& other);
    ~Notification();
    Notification& operator=(const Notification& other);
    
    // Методы создания
    // static тк такие методы вызываются от имени класса, а не от объекта
    // Это позволяет создавать объекты без предварительного существующего экземпляра
    static Notification createSystem(const char* msg, bool urgent, time_t time);
    static Notification createInstant(const char* contact, const char* text, time_t time);
    static Notification createApp(const char* appName, const char* title, const char* text, time_t time);
    
    // Геттеры
    NotificationType getType() const { return type; }
    time_t getTimestamp() const { return timestamp; }
    int getSequence() const { return sequence; } 
    
    // Методы для доступа к данным
    const char* getSystemMessage() const;
    const char* getInstantContact() const;
    const char*getInstantText() const;
    const char* getAppName() const;
    const char* getAppTitle() const;
    const char* getAppText() const;
    
    // Вывод одного уведомления
    void print() const;
    
    // Подсчёт уведомлений по типу
    static int countByType(Notification* arr[], int size, NotificationType target);
};

#endif