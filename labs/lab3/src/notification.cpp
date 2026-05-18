#include "notification.hpp"

int Notification::nextSequence = 0;

//Конструктор по умолчанию
Notification::Notification() : type(SYSTEM_NORMAL), timestamp(0), sequence(nextSequence++) {
    data = {};  // обнуляем union
}

//Конструктор копирования
Notification::Notification(const Notification& other) : type(other.type), timestamp(other.timestamp), data(other.data), sequence(nextSequence++)  {}

// Деструктор
Notification::~Notification() {}

Notification& Notification::operator=(const Notification& other) {
    if (this != &other) {
        type = other.type;
        timestamp = other.timestamp;
        data = other.data;
        sequence = nextSequence++;
    }
    return *this;
}

// Методы создания
Notification Notification::createSystem(const char* msg, bool urgent, time_t time) {
    Notification n;
    n.type = urgent ? SYSTEM_URGENT : SYSTEM_NORMAL;
    n.timestamp = time;
    n.data.system.message = msg;
    return n;
}

Notification Notification::createInstant(const char* contact, const char* text, time_t time) {
    Notification n;
    n.type = INSTANT;
    n.timestamp = time;
    n.data.instant.contact = contact;
    n.data.instant.text = text;
    return n;
}

Notification Notification::createApp(const char* appName, const char* title, const char* text, time_t time) {
    Notification n;
    n.type = APP;
    n.timestamp = time;
    n.data.app.appName = appName;
    n.data.app.title = title;
    n.data.app.text = text;
    return n;
}

// Геттеры
const char* Notification::getSystemMessage() const {
    return data.system.message;
}

const char* Notification::getInstantContact() const {
    return data.instant.contact;
}

const char* Notification::getInstantText() const {
    return data.instant.text;
}

const char* Notification::getAppName() const {
    return data.app.appName;
}

const char* Notification::getAppTitle() const {
    return data.app.title;
}

const char* Notification::getAppText() const {
    return data.app.text;
}

// Печать одного уведомления
void Notification::print() const {
    std::cout << "[" << timestamp << "] ";
    
    switch (type) {
        case SYSTEM_NORMAL:
            std::cout << "[SYSTEM] (normal): " << data.system.message;
            break;
        case SYSTEM_URGENT:
            std::cout << "[SYSTEM] (urgent!!): " << data.system.message;
            break;
        case INSTANT:
            std::cout << "[INSTANT]: " << data.instant.contact << ": " << data.instant.text;
            break;
        case APP:
            std::cout << "[APP]: " << data.app.appName << " - " 
                      << data.app.title << ": " << data.app.text;
            break;
    }
    std::cout << std::endl;
}

// Подсчет в массиве указателей
int Notification::countByType (Notification* arr[], int size, NotificationType target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i]->getType() == target) {
            count++;
        }
    }
    return count;
}