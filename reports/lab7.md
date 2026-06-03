# Лабораторная работа №7. Развертывание на целевой машине

## Ход работы

## 1. Создание виртуальной машины

### 1.1. Используемая виртуальная машина
Для подготовки целевой машины использовалась **виртуальная машина, созданная в лабораторной работе №4**. Её параметры:

| Параметр | Значение |
|----------|----------|
| Платформа | Oracle VirtualBox 7.2.8 |
| Дистрибутив | Lubuntu 24.04 LTS (в соответствии с вариантом 5) |
| Оперативная память | 2048 МБ |
| Процессоры | 2 |
| Жёсткий диск | 25 ГБ |
| Сетевой режим | NAT |

### 1.2. Отключение графической среды

Поскольку лабораторная работа №7 не требует графического интерфейса (достаточно консольного доступа), было выполнено переключение на текстовую консоль без отключения графики полностью

**Способ переключения:** комбинация клавиш `Ctrl + Alt + F3`

После нажатия этой комбинации система переключилась на текстовую консоль, где появилось приглашение ввода логина. Графическая оболочка при этом продолжает работать в фоне на `Ctrl + Alt + F2`, но не используется в работе

### 1.3. потенциальные опасности наличия доступа внешнего человека к виртуальной машине

При предоставлении доступа другому человеку к виртуальной машине возникают следующие риски:

- **Чтение и изменение файлов** - пользователь может просматривать и редактировать файлы в своей домашней директории
- **Запуск вредоносного кода** - возможность выполнения любых команд на системе
- **Нагрузка на ресурсы** - запущенные процессы могут потреблять память и процессор
- **Распространение атак** - ВМ может быть использована для атак на другие узлы сети

**Меры безопасности, принятые в работе:**
- Использование SSH-ключей вместо пароля
- Отключение парольного доступа после настройки ключей
- Создание отдельного пользователя для напарника
- Временное открытие порта только на период выполнения работы

---

## 2. Настройка удалённого доступа

### 2.1. Установка SSH-клиента на основной системе
На основном компьютере (Windows) SSH-клиент уже встроен в PowerShell

### 2.2. Установка и настройка SSH-сервера на виртуальной машине

Внутри виртуальной машины выполнен установка OpenSSH-сервера:

```bash
sudo apt update
sudo apt install openssh-server -y
```
Проверка работы SSH-сервера:
```bash
sudo systemctl status ssh
```

![alt text](l71.png)


### 2.3. Проброс портов в VirtualBox

**Что такое порт TCP:** Порт - это числовой идентификатор, который позволяет операционной системе направлять трафик конкретному приложению

**Проброс портов** - это механизм VirtualBox, который перенаправляет запросы с порта хост-системы на порт гостевой системы. Это необходимо, потому что виртуальная машина в режиме NAT скрыта за основным компьютером и недоступна извне

**Настройка проброса:**

1. Виртуальная машина выключена
2. В VirtualBox Manager выбрана ВМ -> **Настроить** -> **Сеть**
3. Адаптер 1: тип подключения **NAT**
4. Нажата кнопка **«Дополнительно»** -> **«Проброс портов»**
5. Добавлено правило:

| Имя | Протокол | Адрес хоста | Порт хоста | Адрес гостя | Порт гостя |
|-----|----------|-------------|------------|-------------|------------|
| SSH | TCP | 127.0.0.1 | 2222 | пусто | 22 |

**Почему такие значения:**

| Поле | Значение | Пояснение |
|------|----------|-----------|
| Порт хоста | 2222 | Порт на основном компьютере (выбран нестандартный, чтобы не конфликтовать с другими службами) |
| Порт гостя | 22 | Стандартный порт SSH внутри виртуальной машины |

![alt text](l74.png)

### 2.4. Подключение по паролю

После настройки проброса портов проверено подключение к виртуальной машине из основной системы (Windows) с использованием пароля

В PowerShell выполнена команда:
```powershell
ssh -p 2222 _@127.0.0.1
```

После этого система запросила пароль пользователя _. После ввода пароля подключение успешно выполнено.

![alt text](l73.png)

### 2.5. Как добавить публичный ключ для подключения без пароля

Чтобы подключиться к серверу по SSH без ввода пароля, нужно добавить свой **публичный ключ** на сервер в специальный файл

**Куда добавлять:**  
Файл `~/.ssh/authorized_keys` в домашней директории пользователя на сервере

**Как добавить:**  
1. Скопировать содержимое своего публичного ключа
2. На сервере выполнить:  
   ```bash
   mkdir -p ~/.ssh
   echo "скопированный_ключ" >> ~/.ssh/authorized_keys
   chmod 700 ~/.ssh
   chmod 600 ~/.ssh/authorized_keys
   ```

**Что означают права:**
- **700** на папку .ssh - только владелец может читать и заходить
- **600** на файл authorized_keys - только владелец может его читать и писать

### 2.6. Настройка подключения по SSH-ключу

После успешного подключения по паролю настроен вход по SSH-ключу

#### 2.6.1. Создание SSH-ключа на основном компьютере

На основном компьютере (Windows) в PowerShell выполнена команда для генерации новой пары ключей:
```powershell
ssh-keygen -t ed25519 -C "lab7-key" -f C:\Users\difil\.ssh\lab7_key
```

#### 2.6.2. Добавление публичного ключа на виртуальную машину
Публичный ключ скопирован на виртуальную машину. Для этого сначала получено содержимое ключа:
```powershell
type C:\Users\difil\.ssh\lab7_key.pub
```

Затем выполнено подключение к ВМ по SSH (с паролем) и добавление ключа:
```powershell
# Подключение к ВМ
ssh -p 2222 _@127.0.0.1

# Внутри виртуальной машины:
mkdir -p ~/.ssh
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIOzQBquC6IqNzlf/P0LE/Ijojmk9lXq2EcX4VuNLhkaS lab7-key" >> ~/.ssh/authorized_keys
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
exit
```

После добавления ключа выполнено подключение с его использованием:
```powershell
ssh -p 2222 -i C:\Users\difil\.ssh\lab7_key _@127.0.0.1
```

**Результат:** подключение выполнено без запроса пароля. Сразу появилось приглашение терминала

### 2.7. Отключение доступа по паролю

Для повышения безопасности SSH-сервера доступ по паролю был отключён. Теперь вход возможен только по SSH-ключу

#### 2.7.1. Редактирование конфигурационного файла

Открыт файл конфигурации SSH-сервера:
```bash
sudo nano /etc/ssh/sshd_config
```

В файле найдена строка **#PasswordAuthentication yes** и изменена на:
```bash
PasswordAuthentication no
```

#### 2.7.2. Проверка отключения доступа по паролю
Выполнена попытка подключения с принудительным использованием только пароля (без ключа):
```powershell
ssh -p 2222 -o PubkeyAuthentication=no _@127.0.0.1
```

**Результат:** подключение по паролю больше невозможно. При этом подключение с использованием ключа продолжает работать
```powershell
Permission denied (publickey)
```

## 3. Настройка сессии для другого пользователя

### 3.1. Создание пользователя для напарника

На виртуальной машине создан отдельный пользователь для напарника

**Команда для создания пользователя:**

```bash
sudo adduser dashka
```

**Что происходит при выполнении команды:**
1. Создаётся домашняя директория /home/dashka
2. Создаётся группа с тем же именем
3. Запрашивается пароль для нового пользователя
4. Запрашиваются дополнительные данные (можно пропустить, нажав Enter)

### 3.2. Получение публичного SSH-ключа напарника и добавление его на виртуальную машину
Для того чтобы напарник мог подключаться к виртуальной машине без пароля, он сгенерировал свою пару SSH-ключей на своём компьютере и прислал публичный ключ

```bash
# 1. Создание директории .ssh для пользователя dashka
sudo mkdir -p /home/dashka/.ssh

# 2. Добавление публичного ключа в файл authorized_keys
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAILal41PjsbX3+ePFGIFb4kC6Gv/sEA2OjjMxhIFIxLZR Дарья Мокренко@DESKTOP-V1F" | sudo tee -a /home/dashka/.ssh/authorized_keys

# 3. Установка правильных прав доступа
sudo chmod 700 /home/dashka/.ssh
sudo chmod 600 /home/dashka/.ssh/authorized_keys

# 4. Установка владельца (пользователь dashka и его группа)
sudo chown -R dashka:dashka /home/dashka/.ssh
```
### 3.3. Организация общей сети
Компьютеры подключены к одной локальной сети. IP-адрес компьютера в сети:
```bash
ipconfig
```
**Результат:**
```bash
IPv4-адрес. . . . . . . . . . . . : 10.78.62.236
```

### 3.4. Проверка доступности (ping)
С компьютера напарника выполнен ping:
```bash
ping 10.78.62.236
```

**Результат:** пинг прошёл успешно

### 3.5. Открытие порта для доступа из локальной сети
В VirtualBox настроен проброс портов:

| Имя | Протокол | Адрес хоста | Порт хоста | Адрес гостя | Порт гостя |
|-----|----------|-------------|------------|-------------|------------|
| SSH | TCP | пусто | 2222 | пусто | 22 |

Пустое поле в «Адресе хоста» означает 0.0.0.0 — доступ из локальной сети разрешён

![alt text](l72.png)

### 3.6. Закрытие порта после работы
После завершения лабораторной работы для обеспечения безопасности порт был закрыт. Для этого в настройках проброса портов VirtualBox поле «Адрес хоста» было изменено с пустого на 127.0.0.1

### 3.7. Подключение к ВМ напарника
```bash
ssh -p 1000 -i C:\Users\difil\.ssh\lab7_key dashka@10.78.62.234
```

---

## 4. Развертывание программы

### 4.1. Необходимые программы на удаленной машине

Для клонирования репозитория, сборки проекта и запуска тестов на целевой машине требуются следующие программы:

| Программа | Назначение | Команда установки |
|-----------|------------|-------------------|
| **Git** | Клонирование репозитория | `sudo apt install git -y` |
| **GCC/G++** | Компиляция C/C++ кода | `sudo apt install build-essential -y` |
| **Make** | Система сборки (входит в build-essential) | `sudo apt install build-essential -y` |

**Проверка установки программ:**

```bash
git --version
g++ --version
make --version
```

### 4.2. Организация доступа к репозиторию и клонирование репозитория
Репозиторий с лабораторными работами публичный, поэтому для его клонирования не требуется аутентификация

На виртуальной машине напарника выполнен **клон репозитория:**

```bash
dashka@daria-vm:~$ git clone https://github.com/chifffi/labs_git.git
Cloning into 'labs_git'...
remote: Enumerating objects: 396, done.
remote: Counting objects: 100% (396/396), done.
remote: Compressing objects: 100% (258/258), done.
remote: Total 396 (delta 129), reused 319 (delta 81), pack-reused 0 (from 0
Receiving objects: 100% (396/396), 5.42 MiB | 1.93 MiB/s, done.
Resolving deltas: 100% (129/129), done.
```

### 4.3. Сборка проекта

```bash
dashka@daria-vm:~/labs_git/labs/lab2$ make
g++ -g -c -o build/mystring.o src/mystring.cpp
g++ -g -c -o build/basefile.o src/basefile.cpp
g++ -g -c -o build/base32file.o src/base32file.cpp
g++ -g -c -o build/rlefile.o src/rlefile.cpp
g++ -g -c -o build/base32file2.o src/base32file2.cpp
g++ -g -c -o build/rlefile2.o src/rlefile2.cpp
g++ -g -o build/lab2.out src/lab2.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
```

### 4.4. Запуск программы

```bash
dashka@daria-vm:~/labs_git/labs/lab2$ make run
./build/lab2.out
Задание 1.1
hi
bye
abcd
Hi
Bye
Abcd

Задание 1.2
hi
bye
abcd
```
### 4.5. Проверка тестов

```bash
dashka@daria-vm:~/labs_git/labs/lab2$ make test
g++ -g -o build/test_basefile.out tests/test_basefile.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
g++ -g -o build/test_base32file.out tests/test_base32file.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
g++ -g -o build/test_rlefile.out tests/test_rlefile.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
g++ -g -o build/test_base32file2.out tests/test_base32file2.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
g++ -g -o build/test_rlefile2.out tests/test_rlefile2.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
g++ -g -o build/test_composition.out tests/test_composition.cpp build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o
========================================
          ЗАПУСК ТЕСТОВ
========================================

--- Тест BaseFile ---

 Тест BaseFile со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
Записано 50000 байт
BaseFile::~BaseFile()
BaseFile::BaseFile(const char* path, const char* m)
Прочитано 50000 байт
BaseFile::~BaseFile()
Тест BaseFile со случайными данными пройден!

--- Тест Base32File ---

 Тест Base32File со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
Base32File::Base32File(const char* path, const char* m, const char* tbl)
Записано 50000 байт
Base32File::~Base32File()
BaseFile::~BaseFile()
BaseFile::BaseFile(const char* path, const char* m)
Base32File::Base32File(const char* path, const char* m, const char* tbl)
Прочитано 50000 байт
Base32File::~Base32File()
BaseFile::~BaseFile()
Тест Base32File со случайными данными пройден!

--- Тест RleFile ---

 Тест RleFile со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
RleFile::RleFile(const char*, const char*)
Записано 50000 байт
RleFile::~RleFile()
BaseFile::~BaseFile()
BaseFile::BaseFile(const char* path, const char* m)
RleFile::RleFile(const char*, const char*)
Прочитано 50000 байт
RleFile::~RleFile()
BaseFile::~BaseFile()

 Тест RleFile пройден! Данные совпадают.

--- Тест Base32File2 (композиция) ---

 Тест Base32File2 (композиция) со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
Base32File2::Base32File2()
Записано 50000 байт
BaseFile::~BaseFile()
Base32File2::~Base32File2()
BaseFile::BaseFile(const char* path, const char* m)
Base32File2::Base32File2()
Прочитано 50000 байт
BaseFile::~BaseFile()
Base32File2::~Base32File2()
Тест Base32File2 пройден!

--- Тест RleFile2 (композиция) ---

 Тест RleFile2 (композиция) со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
RleFile2::RleFile2()
Записано 50000 байт
BaseFile::~BaseFile()
RleFile2::~RleFile2()
BaseFile::BaseFile(const char* path, const char* m)
RleFile2::RleFile2()
Прочитано 50000 байт
BaseFile::~BaseFile()
RleFile2::~RleFile2()
Тест RleFile2 пройден!

--- Тест композиции RleFile2+Base32File2 ---

Тест композиции RleFile2(Base32File2) со случайными данными

BaseFile::BaseFile(const char* path, const char* m)
Base32File2::Base32File2()
RleFile2::RleFile2()
Записано 50000 байт
BaseFile::~BaseFile()
Base32File2::~Base32File2()
RleFile2::~RleFile2()
BaseFile::BaseFile(const char* path, const char* m)
Base32File2::Base32File2()
RleFile2::RleFile2()
Прочитано 50000 байт
BaseFile::~BaseFile()
Base32File2::~Base32File2()
RleFile2::~RleFile2()
Тест композиции RleFile2(Base32File2) пройден!

========================================
           ПРОВЕРКА ТЕСТОВ ЗАКОНЧЕНА
========================================
```
