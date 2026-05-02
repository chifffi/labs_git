/**
 * Лабораторная работа №3. Перегрузка операторов, константные методы, битовые
 * поля, объединения.
 *
 * В этой работе и далее предполагается, что вы будете использовать классы,
 * написанные в прошлых работах, и дополнять их по необходимости. Эти классы
 * будут называться по имени без дополнительных указаний, что их надо взять из
 * прошлой работы.
 *
 * Предполагается, что новый классы будут созданы по аналогии с предыдущими
 * работами в отдельных файлах, которые будут включены в сборку.
 *
 * При работе с классами - в учебных целях - нельзя пользоваться контейнерами
 * стандартной библиотеки и нужно следовать принципам инкапсуляции.
 */

#include <utility>
#include <cassert>
#include <iostream>
#include <ctime>
#include "matrix.hpp"
#include "mystring.hpp"
#include "workerdb.hpp"
#include "notification.hpp"
#include "notification_queue.hpp"
#include "notification_priority_queue.hpp"
#include "basefile.hpp"
#include "boolarray.hpp"

MyString addTxtExtension(const MyString &path) { return path + ".txt"; }

int main() {

    /**
     * Задание 1. Перегрузка операторов.
     */

    /**
     * Задание 1.1. Оператор присваивания.
     *
     * Перегрузите оператор присваивания для классов `MyString` и `Matrix`.
     * Ожидается, что оператор присваивания работает так же, как конструктор
     * копирования. 
     *
     * Проверьте корректность работы оператора в следующих блоках кода.
     */

    //перегрузка - предоставление возможности обращаться c объектами пользательского типа также как с переменными базового типа
    // Оператор присваивания (operator=) вызывается, когда существующему объекту присваивается значение другого объекта
    std::cout << "Задание 1.1." << std::endl;
    {
            std::cout << "Создание объектов:" << std::endl;
            MyString s1("AAA"), s2;
            std::cout << "   s1 = "; s1.print(); //ААА
            std::cout << "   s2 = "; s2.print(); //nullptr, return ничего

            std::cout << "присваивание 1" << std::endl;
            s2 = s1; 
            std::cout << "   s2 = "; s2.print();//ААА

            std::cout << "присваивание новой строки" << std::endl;
            s1 = "CCC";
            s2 = MyString("tmp");
            std::cout << "   s1 = "; s1.print(); //ССС
            std::cout << "   s2 = "; s2.print(); //tmp
            s1 = s2;
            std::cout << "   s1 = "; s1.print(); //tmp
            std::cout << "   s2 = "; s2.print(); //tmp
            std::cout<<std::endl;
    }

    {
        std::cout << "Создание объектов:" << std::endl;
        Matrix m1(10), m2(10, 2);
        std::cout << "   m1: " << m1.get_height() << "x" << m1.get_width() << std::endl; //10x10
        std::cout << "   m2: " << m2.get_height() << "x" << m2.get_width() << std::endl; //10x2

        std::cout << "присваивание 1" << std::endl;
        m1 = m2;
        std::cout << "   m1: " << m1.get_height() << "x" << m1.get_width() << std::endl; //10x2
        std::cout << "   m2: " << m2.get_height() << "x" << m2.get_width() << std::endl; //10x2

        std::cout << "присваивание 2" << std::endl;
        m2 = Matrix(3, 4, 1.0);
        m1 = m2;
        std::cout << "   m1: " << m1.get_height() << "x" << m1.get_width() << std::endl; //3x4
        std::cout << "   m2: " << m2.get_height() << "x" << m2.get_width() << std::endl; //3x4
    }

    /**
     * Задание 1.2. Перегрузка арифметических операторов. Перегрузка методами и
     * глобальными функциями.
     */

    /**
     * Задание 1.2.1. Составное присваивание.
     *
     * Для класса `Matrix` перегрузите следующие операторы методом класса:
     * - `+=` и `-=` с объектом класса `Matrix`;
     * - `*=` и `/=` со значением double.
     *
     * Такие операторы не должны менять правый операнд. При наличии недопустимых
     * аргументов выкиньте какое-нибудь исключение.
     *
     * Ваши операторы должны работать в следующем блоке кода.
     */

    {
        std::cout << "\n Задание 1.2.1" << std::endl;
        Matrix m1(4), m2(4, 4, 1); //единичная 4х4, матрица 4х4 с значением 1.0
        m2 += m1; // m2 = m2 + m1, везде теперь значение 2
        std::cout << "m2[0][0] = " << m2.get(0, 0) << " (ожидается 2)" << std::endl;

        m2 -= m1 += m1; // сначала m1 += m1(везде занчение 2), потом m2 -= результат предыдущего(везде значение 2-2=0)
        std::cout << "m1[0][0] = " << m1.get(0, 0) << " (ожидается 2)" << std::endl;
        std::cout << "m2[0][0] = " << m2.get(0, 0) << " (ожидается 0)" << std::endl;

        m1 *= 2; // m1 = m1 * 2 (везде значение 2*2=4)
        std::cout << "m1[0][0] = " << m1.get(0, 0) << " (ожидается 4)" << std::endl;

        m2 /= 3; // m2 = m2 / 3 (везде значение 0/3 = 0)
        std::cout << "m2[0][0] = " << m2.get(0, 0) << " (ожидается 0)" << std::endl;
    }

    /**
     * Задание 1.2.2. Бинарные операторы.
     *
     * Для класса `Matrix` перегрузите следующие операторы методом класса:
     * - `+` и `-` с объектом класса `Matrix`;
     * - `*` с объектом класса `Matrix`;
     * - `*` и `/` со значением double.
     *
     * Эти операторы не должны изменять ни левый, ни правый операнд и возвращать
     * новое значение.
     */
    std::cout << "\n Задание 1.2.2" << std::endl;
    {
        Matrix m1(4), m2(4, 4, 1); //единичная матрица 4х4, матрица 4х4 из единиц
        std::cout << "Исходные матрицы:" << std::endl;
        std::cout << "m1[0][0] = " << m1.get(0, 0) << std::endl;
        std::cout << "m2[0][0] = " << m2.get(0, 0) << std::endl;
        std::cout << std::endl;

        Matrix m3 = (m1 + m2) * m1 * 4 / 2 - m2;
        std::cout << "Результат m3:" << std::endl;
        std::cout << "m3[0][0] = " << m3.get(0, 0) << std::endl;
        std::cout << std::endl;
        
        std::cout << "Проверка что исходные матрицы не изменились:" << std::endl;
        std::cout << "m1[0][0] = " << m1.get(0, 0) << " (было 1)" << std::endl;
        std::cout << "m2[0][0] = " << m2.get(0, 0) << " (было 1)" << std::endl;
        }

    /**
     * Задание 1.2.3. Перегрузка глобальными функциями.
     *
     * Перегрузите оператор `*` для операндов `double` и `Matrix` глобальной
     * функцией.
     *
     * Перегрузите унарный оператор `-` для класса `Matrix` с помощью глобальной
     * функции.
     *
     * Какую из этих функций нельзя перегрузить методом класса? Почему?
     */
    
    //Нельзя перегрузить методом класса оператор * с операндами double и Matrix в виде double * Matrix (где число стоит слева)
    //Когда оператор перегружается методом класса, он всегда вызывается для объекта класса, который является левым операндом. Метод operator* будет вызван для объекта слева от знака *.
    //Для выражения число * matrix левый операнд не объект класса Matrix, поэтому метод класса не может быть вызван

    /**
     * Задание 1.2.4. Операторы для строки.
     *
     * Перегрузите операторы `+` и `+=` для класса `MyString`, где в качестве
     * правого операнда будет `MyString` или `const char *`. Сложение в этом 
     * случае должно выполнять конкатенацию строк.
     *
     * Ваши операторы должны работать в следующем блоке кода.
     */

    {
        std::cout << "\n Задание 1.2.4" << std::endl;
        MyString s1("abc"), s2("def"), s3;
        std::cout << "Начальные значения:" << std::endl;
        std::cout << "   s1 = "; s1.print();
        std::cout << "   s2 = "; s2.print();
        std::cout << "   s3 = "; s3.print();
        std::cout << std::endl;

        std::cout << "s1 += s2 += \"111\"" << std::endl;
        s1 += s2 += "111";
        std::cout << "   s1 = "; s1.print();  // ожидается: abcdef111
        std::cout << "   s2 = "; s2.print();  // ожидается: def111
        std::cout << std::endl;

        std::cout << "s2 += \"222\" + s1 + \"333\"" << std::endl;
        s2 += "222" + s1 + "333";
        std::cout << "   s2 = "; s2.print();  // ожидается: def111222abcdef111333
        std::cout << std::endl;

        std::cout << "s3 += s3" << std::endl;
        s3 += s3;
        std::cout << "   s3 = "; s3.print();  // ожидается: пустая строка (пусто)
        std::cout << std::endl;
    }

    /**
     * Задание 1.3. Move-семантика.
     *
     * Перегрузите move-оператор присваивания и move-конструктор для классов
     * `MyString` и `Matrix`. В этих операторах нужно "забирать" данные из
     * правого операнда, а не копировать. При этом правый операнд должен
     * становиться "пустым".
     *
     * С помощью отладчика или отладочной печати отследите, сколько раз в
     * следующем блоке происходит выделение динамической памяти, - до реализации
     * move-оператора/конструктора и после.
     */

    //Move-семантика - это способ перемещения ресурсов (динамической памяти) из одного объекта в другой вместо их копирования. 
    //Данные не копируются, а просто "крадутся" – забирается указатель на память. После move-операции исходный объект становится пустым, но валидным.

    //Временный объект (rvalue) – объект без имени, который живет до конца выражения:
    //1. Результат операции: s1 + s2; 2.Возврат из функции; 3.Явное создание без имени: MyString("abc")

    //&& — rvalue-ссылка, указывает на временный объект, у которого можно забрать его данные.
    //std::move — превращает обычный объект во "временный", чтобы к нему применилась move-семантика (перемещение, а не копирование).

    {
        std::cout << "\n Задание 1.3" << std::endl;
        MyString s1("abc"); //CONSTRUCTOR (выделение памяти) - вызван конструктор MyString(const char*)

        MyString s2 = s1 + "ccc"; //COPY CONSTRUCTOR (выделение памяти) и CONSTRUCTOR (выделение памяти)
        // вызывается operator+(const MyString& left, const char* right)
        // внутри него: MyString result(left),  COPY CONSTRUCTOR (копируем s1 в result)
        // Затем result += "ccc",  внутри operator+= создаётся временный объект MyString temp("ccc"),  CONSTRUCTOR (выделение памяти)
        // нет move тк компилятор применил RVO (оптимизацию возвращаемого значения), поэтому s2 создался сразу, без копирования/перемещения.

        s1 = "abc" + s2; //CONSTRUCTOR (выделение памяти) и MOVE ASSIGNMENT (память НЕ выделяется)
        // вызывается operator+(const char* left, const MyString& right)
        // внутри: MyString result(left), CONSTRUCTOR (выделение памяти) (создаётся временный объект "abc")
        // result += right, присоединяем s2
        // для s1 = ... вызывается MOVE ASSIGNMENT, потому что: s1 уже существует (не новая переменная), правый операнд - временный объект (rvalue)

        s2 = std::move(s1); //MOVE ASSIGNMENT (память НЕ выделяется)
        // std::move(s1) превращает s1 во "временный" (rvalue)
        // s2 уже существует
        // Вызывается MOVE ASSIGNMENT - забираем данные у s1, s1 становится пустым

        std::cout << "------------" << std::endl;

        Matrix m1(4), m2 = m1 + m1; 
        // Matrix m1(4) CONSTRUCTOR (выделение памяти)
        // Matrix m2 = m1 + m; CONSTRUCTOR (выделение памяти), CONSTRUCTOR (выделение памяти), CONSTRUCTOR MxN(выделение памяти)
        // Вызывается operator+(const Matrix& left, const Matrix& right)
        // Внутри создаётся Matrix result(row, column, 0.0), CONSTRUCTOR MxN (выделение памяти) (временный результат)
        // потом сработала RVO (оптимизация возвращаемого значения) - компилятор сразу создал m2 в том месте, где operator+ создавал result. Поэтому лишнего вывода нет

        m1 = m2 * m1;
        // вызывается operator*(const Matrix& other) const
        // внутри создается Matrix result(row, other.column, 0.0) CONSTRUCTOR MxN(выделение памяти)
        // Затем вызывается move-оператор присваивания operator=(Matrix&& other) MOVE ASSIGNMENT (память НЕ выделяется)

        m2 = std::move(m1);
        // std::move(m1) превращает m1 во временный (rvalue).
        // m2 уже существует. Вызывается move-оператор присваивания
    }

    /**
     * Задание 1.4. Операторы сравнения.
     *
     * Реализуйте для класса `MyString` операторы сравнения `==`, `!=`, `<`,
     * `<=` для сравнения с объектами `MyString` и `const char *`.
     *
     * Операторы должны сравнивать строки лексикoграфически.
     */

    {
        std::cout << "\n Задание 1.4" << std::endl;
        MyString s1("abc"), s2("ab"), s3 = s1;
        assert(s2 < s1);
        assert(s1 == s3);
        assert(s1 != s2);
        assert(s1 <= s3);
        assert("ab" == s2);
        assert("aba" < s1);
        assert("aba" <= s3);
        std::cout << " Все assertы прошли успешно!" << std::endl;
    } 

    /**
     * Задание 1.5. Оператор индексирования.
     *
     * Перегрузите оператор индексирования для класса `MyString`, который
     * возвращает ссылку на i-тый символ. Если индекс выходит за границы
     * массива, киньте какое-нибудь исключение.
     */

    {
        std::cout << "\n Задание 1.5" << std::endl;
        MyString s1("abc");
        s1[0] = s1[1] = 'd';
        s1.print();
        // вызывается operator[](1), возвращается ссылка на символ с индексом 1
        // ссылка на s1[1] = 'd', через ссылку меняется символ в памяти
        // результат s1[1] = 'd' возвращает ссылку на s1[1] (на ячейку [1], которая теперь содержит 'd'), "adc"
        // вызывается operator[](0), возвращается ссылка на символ с индексом 0
        // происходит копирование значения, на которое указывает правая ссылка, в ячейку, на которую указывает левая ссылка
        // результат: [0]='d', [1]='d', [2]='c', "ddc"

    }

    /**
     * Задание 1.6. Операторы ввода и вывода с потоками стандартной библиотеки.
     *
     * Реализуйте для класса `MyString` операторы `<<`, который позволит
     * выводить строку в поток вывода `std::ostream`.
     *
     * Реализуйте для класса `MyString` оператор `>>`, который позволит вводить
     * строку до первого переноса строки из потока ввода `std::istream`.
     *
     * Проверьте работу этих операторов на следующем примере.
     */

    {
        std::cout << "\n Задание 1.6" << std::endl;
        MyString s("123");
        std::cout << "This is my string: '" << s << "'\n";
        std::cout << "Enter your string: ";
        std::cin >> s;
        std::cout << "Your string: '" << s << "'\n";
    }

    /**
     * Задание 2. Константные методы.
     *
     * Объявите все методы (в том числе перегруженные операторы), которые не
     * должны менять объект, для которого они были вызваны, константными.
     *
     * После этого следующая функция должна собираться:
     * MyString addTxtExtension(const MyString &path) { return path + ".txt"; }
     */
    //path — это константная ссылка
    //К константному объекту можно вызывать только константные методы
    //Если бы operator+ был бы методом и не был константным, его нельзя было бы вызвать для path
    std::cout << "\n Задание 2" << std::endl;
    MyString s("document");
    MyString result = addTxtExtension(s);
    std::cout << result << std::endl;  // "document.txt"

    /**
     * Задание 3. Ассоциативный массив. Итератор. Операторы инкремента.
     */

    /**
     * Задание 3.1. Ассоциативный массив.
     *
     * Создайте класс `WorkerDb`, который будет хранить базу данных рабочих
     * некой организации в виде ассоциативного массива. В таком массиве индексом
     * является не номер элемента, а какое-то другое значение. В этом случае -
     * фамилия сотрудника. В самом же массиве будет храниться структура с
     * информацией о работнике.
     *
     * Реализуйте для этого класса оператор `[]`, который будет по фамилии
     * возвращать ссылку на данные работника. Если такого работника еще нет,
     * то запись для этого работника создается.
     *
     * Используйте для хранения строковых данных ваш класс MyString.
     */

    {
        std::cout << "\n Задание 3.1" << std::endl;
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 8);
        db["Petrov"] = WorkerData("Petr", 43, 15);

        std::cout << "Ivanov's name = " << db["Ivanov"].name << std::endl;
        std::cout << "Petrov's age = " << db["Petrov"].age << std::endl;
        std::cout << "Petrov's experience = " << db["Petrov"].experience << " years" << std::endl;
    }

    /**
     * Задание 3.2. Итератор.
     *
     * На практике воспользоваться таким классом будет довольно сложно, потому
     * что чтобы получить информацию о работниках, нужно откуда-то знать их
     * фамилии (ключи в массиве).
     *
     * Чтобы решить такую проблему, часто используют паттерн *итератор*.
     * Объект-контейнер (у нас - WorkerDb) умеет возвращать объект, который
     * перебирает его элементы. Для обычного массива в С таким объектом является
     * указатель, однако, сам по себе указатель не содержит информации, когда
     * элементы массива закончатся. Поэтому в пару к указателю, который
     * указывает на элементы (`begin`), добавляют указатель, который будет
     * обозначать, что элементы закончены (`end`):
     *
     * ```
     * int arr[] = {1, 2, 3, 4, 5};
     *
     * for (int *begin = arr, *end = arr + sizeof(arr) / sizeof(arr[0]);
     *      begin != end;
     *      ++begin)
     *  {
     *      std::cout << *begin << ' ';
     *  }
     *
     * ```
     *
     * В языке C++ наследуется эта идиома: объекты-контейнеры возвращают
     * объект-итератор методами `begin()` и `end()`. Для итератора определены
     * операторы `==`, `!=`, префиксный и постфиксный `++`, а также операторы
     * разыменования `*` и `->`. Также часто итераторы копируются (оператор
     * `=`).
     *
     * Реализуйте для вашего класса `WorkerDb` итератор, который при
     * разыменовании будет возвращать ссылку на `WorkerData`, а также иметь
     * метод `key()`, который будет возвращать ключ для этих данных
     * (фамилию). Итераторы допускается объявлять дружественными для
     * класса-контейнера.
     *
     * Проверьте ниже работу итератора.
     */

    {
        std::cout << "\n Задание 3.2" << std::endl;
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 8);
        db["Petrov"] = WorkerData("Petr", 43, 15);
        for (auto it = db.begin(); it != db.end(); ++it)
        {
            std::cout << it.key() << " -> " << it->name << '\n';
        }
    }

    /**
     * Задание 3.3. Работа "прикладного программиста".
     *
     * Не меняя класс `WorkerDb`, напишите функцию `print_db(WorkerDb&)`,
     * которая будет печатать базу данных работников на консоль, и функцию
     * `double get_avg_age(WorkerDb&)`, которая будет подсчитывать средний
     * возраст сотрудников. Эти функции не должны быть дружественными классу
     * `WorkerDb`.
     */

    {
        std::cout << "\n Задание 3.3" << std::endl; 
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 8);
        db["Petrov"] = WorkerData("Petr", 43, 15);
        db["Sidorov"] = WorkerData("Sidor", 28, 5);
        db["Kuznetsov"] = WorkerData("Kuzma", 30, 10);
        
        // Печать всей базы
        print_db(db);
        
        // Средний возраст
        double avgAge = get_avg_age(db);
        std::cout << "Средний возраст сотрудников: " << avgAge << " лет" << std::endl;
    }

    /**
     * Задание 4. Объединения, полиморфизм в "старом" стиле, очередь с
     * приоритетами.
     */

    /**
     * Задание 4.1. Класс "Уведомление".
     *
     * Создайте структуру `Notification`, в котором будет информация об
     * уведомлении, поступающем на телефон.
     *
     * Уведомление должно иметь метку времени и данные, которые зависят от типа
     * уведомления. Реализуйте следующие типы.
     *
     * 1. Системное уведомление: хранит сообщение и уровень серьезности (обычное
     *    или срочное).
     * 2. Мгновенное сообщение: выводится имя контакта, от которого сообщение, и
     *    текст сообщения.
     * 3. Уведомление от приложения: выводится название приложения, заголовок
     *    уведомления и текст уведомления.
     *
     * В этой структуре должно быть отдельное поле (enum), указыающее тип
     * данных, а специфичные данные находились бы в объединении (union).
     *
     * Добавьте функции для создание уведомлений каждого типа. Добавьте функции
     * или метод для красивого вывода данных уведомления. Добавьте функцию для
     * подсчета уведомлений заданного типа в массиве. Проверьте работу этих
     * функций.
     */
    {
        std::cout << "\n Задание 4.1" << std::endl; 
        time_t now = time(nullptr);
        
        // Создаём уведомления
        Notification sysNormal = Notification::createSystem("Battery low", false, now);
        Notification sysUrgent = Notification::createSystem("System update required", true, now + 1);
        Notification instant1 = Notification::createInstant("Alice", "Hello!", now + 2);
        Notification instant2 = Notification::createInstant("Bob", "Bye", now + 3);
        Notification app1 = Notification::createApp("Max", "New message", "You have 3 new messages", now + 4);
        Notification app2 = Notification::createApp("Telegram", "Channel update", "New post", now + 5);
        
        // Вывод уведомлений
        std::cout << "Вывод уведомлений:\n";     
        sysNormal.print();
        sysUrgent.print();
        instant1.print();
        instant2.print();
        app1.print();
        app2.print();
        
        std::cout << "\n";
        
        // Проверка конструктора копирования
        std::cout << "Проверка конструктора копирования: \n";
        Notification copyOfInstant = instant1;
        std::cout << "Оригинал: ";
        instant1.print();
        std::cout << "Копия: ";
        copyOfInstant.print();
        std::cout << "\n";
        
        // Подсчёт уведомлений по типу
        std::cout << "Подсчет уведомлений по типу:\n";
        
        Notification* allNotifications[] = {
            &sysNormal, &sysUrgent, &instant1, &instant2, &app1, &app2
        };
        int totalCount = 6;
        
        int normalSystem = Notification::countByType(allNotifications, totalCount, SYSTEM_NORMAL);
        int urgentSystem = Notification::countByType(allNotifications, totalCount, SYSTEM_URGENT);
        int instantCount = Notification::countByType(allNotifications, totalCount, INSTANT);
        int appCount = Notification::countByType(allNotifications, totalCount, APP);
        
        std::cout << "Всего уведомлений: " << totalCount << "\n";
        std::cout << "Системные (обычные):   " << normalSystem << "\n";
        std::cout << "Системные (срочные):   " << urgentSystem << "\n";
        std::cout << "Мгновенные сообщения:  " << instantCount << "\n";
        std::cout << "Уведомления от приложений: " << appCount << "\n";
        
    }

    /**
     * Задание 4.2. Отличие от наследования.
     *
     * Как эту же задачу можно было бы решить с помощью наследования классов? В чем
     * преимущества и недостатки каждого из методов?
     */

    /* решение с помощью наследования: 
    Можно создать базовый класс Notification с виртуальным методом print() и от него унаследовать три класса: SystemNotification, InstantNotification и AppNotification. 
    Каждый производный класс будет хранить свои специфичные поля и переопределять метод print()

    Преимущества union + enum:
    1. Нет виртуальных вызовов: метод print() вызывается напрямую, а не через таблицу виртуальных функций, значит быстрее работает
    2. Все данные хранятся в одной области памяти (размер union = размеру самого большого типа). Нет дополнительного указателя на vtable (8 байт на объект)
    3. Не нужно создавать иерархию классов и поддерживать виртуальный деструктор
    Лучше всего использовать, если набор типов фиксирован и не будет меняться. Важна максимальная производительность и компактность памяти

    Преимущества наследования:
    1. Новый тип уведомления = новый класс. Не нужно изменчть старый код 
    2. Не нужно писать switch(type) везде, где требуется разное поведение
    3. Нельзя ошибиться и обратиться к полю, которое не относится к текущему типу. Каждый класс хранит только свои поля
    4. Инкапсуляция: каждый тип сам управляет своими данными и логикой
    Лучше всего использовать, если система будет расширяться новыми типами уведомлений. Важна гибкость, читаемость и лёгкость поддержки кода

    */

    /**
     * Задание 4.3. Очередь уведомлений.
     *
     * Реализуйте класс `NotificationQueue`, в котором были бы следующие методы:
     * 
     * - `push(notification)` - добавление уведомления в очередь;
     * - `size()` - количество уведомлений в очереди;
     * - `pop()` - возвращает следующее уведомление в порядке First In First
     *   Out (FIFO) и удаляет его из очереди;
     * - `begin()`, `end()` - возвращают итераторы для перебора всех элементов
     *   очереди, при операциях `push` или `pop` итераторы могут становиться
     *   невалидными.
     *
     * Проверьте работу этого класса.
     */

    // Использовался кольцевой буфер 
    // Кольцевой буфер — это массив фиксированного размера, который работает как очередь: когда мы доходим до конца массива, указатель заворачивается в начало.
    // указатели начала (head) и конца (tail) ходят по кругу. При достижении конца массива указатель переходит в начало (операция % capacity)
    // Эффективность: push O(1), pop O(1), нет сдвигов, просто двигаем указатели
    {
        std::cout << "\n Задание 4.3" << std::endl;
    
        time_t now = time(nullptr);
        NotificationQueue queue;
        std::cout << "Очередь создана, размер: " << queue.size() << std::endl;
        
        std::cout << "\n Добавляем уведомления в очередь:\n";
        Notification n1 = Notification::createSystem("Battery low", false, now);
        Notification n2 = Notification::createSystem("System update", true, now + 1);
        Notification n3 = Notification::createInstant("Alice", "Hello!", now + 2);
        Notification n4 = Notification::createApp("Telegram", "New message", "Hi!", now + 3);
        
        queue.push(n1);
        std::cout << "Добавлено: Battery low\n";
        queue.push(n2);
        std::cout << "Добавлено: System update\n";
        queue.push(n3);
        std::cout << "Добавлено: Alice: Hello!\n";
        queue.push(n4);
        std::cout << "Добавлено: Telegram: New message\n";
        std::cout << "Размер очереди после добавления: " << queue.size() << std::endl;
        
        std::cout << "\n Перебор всех уведомлений (через итератор):\n";
        int index = 1;
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            std::cout << "Уведомление " << index << ": ";
            (*it).print();
            index++;
        }
        
        std::cout << "\n Извлечение уведомлений:";
        int step = 1;
        while (!queue.empty()) {
            Notification n = queue.pop();
            std::cout << "Шаг " << step << ": извлечено -> ";
            n.print();
            std::cout << "Осталось в очереди: " << queue.size() << std::endl;
            step++;
        }

        std::cout << "\n Проверка автоматического расширения (добавляем 5 уведомлений):\n";
        
        NotificationQueue queue2;
        std::cout << "Начальный размер очереди: " << queue2.size() << std::endl;
        std::cout << "Добавляем 5 уведомлений (начальная вместимость 4):\n";
        
        for (int i = 0; i < 5; i++) {
            queue2.push(Notification::createSystem("Test", false, now + i));
            std::cout << "Добавлено " << (i + 1) << ", размер очереди: " << queue2.size() << std::endl;
        }

        std::cout << "\n Проверка работы после расширения (извлечение):\n";
        while (!queue2.empty()) {
            Notification n = queue2.pop();
            std::cout << "Извлечено: ";
            n.print();
        }
    }

    /**
     * Задание 4.4. Определение приоритета.
     *
     * Реализуйте класс `NotificationPriorityQueue`, в котором были бы такие
     * же методы, как и в `NotificationQueue`, но метод `pop`, возвращал бы
     * не первое добавленное уведомление, а наиболее *актуальное* по следующим
     * правилам.
     *
     * 1. Срочное системное уведомление актуальнее любого другого уведомления.
     * 2. Уведомление тем актуальнее, чем раньше оно пришло (но срочное
     *    системное актуальнее более раннего уведомления другого типа).
     * 3. Среди уведомлений за один момент времени актуальность зависит от
     *    типа так: `мгновенное сообщение` > `обычное системное` >
     *    `уведомление от приложения`.
     * 4. Среди уведомлений одного типа за один момент времени актуальнее то,
     *    что было раньше добавлено в очередь.
     * 
     * Проверьте работу этого класса при помощи автоматических тестов.
     */
    // Использовалась бинарная куча
    // Бинарная куча - это структура данных, организованная как дерево, где каждый родительский элемент имеет более высокий приоритет, чем его дети. 
    // Самое приоритетное уведомление всегда находится в корне (индекс 0).

    {
        std::cout << "\n Задание 4.4" << std::endl;
    
        time_t now = time(nullptr);
        std::cout << "Тест 1: empty() и getSize()\n";
        {
            NotificationPriorityQueue pq;
            assert(pq.empty() == true);
            assert(pq.getSize() == 0);
            
            pq.push(Notification::createSystem("Test", false, now));
            assert(pq.empty() == false);
            assert(pq.getSize() == 1);
            
            pq.pop();
            assert(pq.empty() == true);
            assert(pq.getSize() == 0);
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 2: Очередь FIFO\n";
        {
            NotificationPriorityQueue pq;
            int t1 = now;
            int t2 = now + 1;
            int t3 = now + 2;
            
            pq.push(Notification::createSystem("First", false, t1));
            pq.push(Notification::createSystem("Second", false, t2));
            pq.push(Notification::createSystem("Third", false, t3));
            
            assert(pq.pop().getTimestamp() == t1);
            assert(pq.pop().getTimestamp() == t2);
            assert(pq.pop().getTimestamp() == t3);
            assert(pq.empty() == true);
            
            std::cout << "Пройден\n";
        }

        std::cout << "\n Тест 3: SYSTEM_URGENT всегда первый\n";
        {
            NotificationPriorityQueue pq;
            
            // Добавляем в разном порядке, но URGENT должен быть первым
            pq.push(Notification::createSystem("Normal 1", false, now + 10));
            pq.push(Notification::createSystem("URGENT!", true, now + 100));
            pq.push(Notification::createInstant("Alice", "Hello", now + 5));
            pq.push(Notification::createApp("App", "Title", "Text", now + 1));
            
            Notification first = pq.pop();
            assert(first.getType() == SYSTEM_URGENT);
            
            // Проверяем, что все остальные извлеклись
            assert(pq.getSize() == 3);
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 4: Приоритет по времени\n";
        {
            NotificationPriorityQueue pq;
            
            pq.push(Notification::createSystem("Late", false, now + 10));
            pq.push(Notification::createSystem("Early", false, now + 1));
            pq.push(Notification::createInstant("Middle", "Hi", now + 5));
            
            // Самое раннее должно быть первым
            assert(pq.pop().getTimestamp() == now + 1);
            assert(pq.pop().getTimestamp() == now + 5);
            assert(pq.pop().getTimestamp() == now + 10);
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 5: Приоритет по типу\n";
        {
            NotificationPriorityQueue pq;
            time_t sameTime = now + 50;
            
            pq.push(Notification::createApp("App", "Title", "Text", sameTime));
            pq.push(Notification::createSystem("System", false, sameTime));
            pq.push(Notification::createInstant("Alice", "Hello", sameTime));
            
            // Ожидаемый порядок: INSTANT → SYSTEM_NORMAL → APP
            assert(pq.pop().getType() == INSTANT);
            assert(pq.pop().getType() == SYSTEM_NORMAL);
            assert(pq.pop().getType() == APP);
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 6: pop() возвращает копию, очередь меняется\n";
        {
            NotificationPriorityQueue pq;
            Notification n1 = Notification::createSystem("First", false, now);
            Notification n2 = Notification::createSystem("Second", false, now + 1);
            
            pq.push(n1);
            pq.push(n2);
            
            Notification popped = pq.pop();
            assert(popped.getTimestamp() == n1.getTimestamp());
            assert(pq.getSize() == 1);
            assert(pq.top().getTimestamp() == n2.getTimestamp());
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\nТест 7: top() не удаляет элемент\n";
        {
            NotificationPriorityQueue pq;
            Notification n = Notification::createSystem("Test", false, now);
            pq.push(n);
            
            assert(pq.top().getTimestamp() == n.getTimestamp());
            assert(pq.getSize() == 1);
            assert(pq.top().getTimestamp() == n.getTimestamp());  // второй раз
            assert(pq.getSize() == 1);  // размер не изменился
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 8: Автоматическое расширение\n";
        {
            NotificationPriorityQueue pq;
            
            // Добавляем больше элементов, чем начальная вместимость (4)
            for (int i = 0; i < 20; i++) {
                pq.push(Notification::createSystem("Test", false, now + i));
            }
            
            assert(pq.getSize() == 20);
            
            // Проверяем, что все элементы извлекаются (порядок правильный)
            time_t expectedTime = now;
            for (int i = 0; i < 20; i++) {
                Notification n = pq.pop();
                assert(n.getTimestamp() == expectedTime + i);
            }
            
            assert(pq.empty() == true);
            
            std::cout << "Пройден\n";
        }
        
        std::cout << "\n Тест 9: Смешанный приоритет\n";
        {
            NotificationPriorityQueue pq;
            
            // Создаём уведомления в беспорядке
            pq.push(Notification::createInstant("Bob", "Hi", now + 10));
            pq.push(Notification::createSystem("URGENT SYSTEM", true, now + 100));  // очень позднее
            pq.push(Notification::createApp("App1", "Title1", "Text1", now + 5));
            pq.push(Notification::createSystem("System normal", false, now + 3));
            pq.push(Notification::createInstant("Alice", "Hello", now + 2));
            pq.push(Notification::createApp("App2", "Title2", "Text2", now + 4));
            
            // Проверяем первый (URGENT)
            Notification first = pq.pop();
            assert(first.getType() == SYSTEM_URGENT);
            assert(first.getTimestamp() == now + 100);
            
            // Проверяем, что остальные извлеклись
            assert(pq.getSize() == 5);
            while (!pq.empty()) {
                pq.pop();
            }
            assert(pq.empty() == true);
            
            std::cout << "Пройден\n";
        }
    }

    /**
     * Задание 5. Неявно определенные операторы. Удаление операторов.
     *
     * Проверьте, определен ли оператор присваивания для класса `BaseFile` из
     * работы 2? Что он делает? Имеется ли смысл в таком операторе?
     *
     * Явно удалите оператор присваивания и конструктор копирования ключевым
     * словом `delete`, но определите их move-аналоги в этом классе.
     * Продемонстрируйте их работу.
     */

    /* Оператор присваивания для класса BaseFile определен неявно (компилятор сгенерировал его автоматически)
     Неявный оператор присваивания делает побайтовое копирование всех полей:
     1. Копирует указатель file (оба объекта будут указывать на один и тот же FILE*)
     2. Копирует массив mode (4 байта)
     В таком оператре нет особого смысла и он опасен в случае, когда например
        BaseFile f1("data.txt", "r");
        BaseFile f2;
        f2 = f1;
        f1 и f2 указывают на один и тот же файл
        если f1 выходит из области видимости или удаляется через delete, вызывается деструктор и файл закрывается 
        если после этого f2 тоже вызывается fclose, то происходит ошибка (файл уже был закрыт, двойное закрытие)
     При move семантике происходит перемещение, а не копирование:
     После перемещения исходный объект f1 теряет владение ресурсом (его указатель обнуляется)
     Поэтому при его разрушении файл не закрывается повторно
    */

    {
        std::cout << "\n Задание 5" << std::endl;
        BaseFile f1("test.txt", "w");
        BaseFile f2 = std::move(f1); // move-конструктор копирования
        // Теперь f1 пустой, f2 владеет файлом
        BaseFile f3;
        f3 = std::move(f2); // move-оператор присваивания
        // Теперь f2 пустой, f3 владеет файлом
        std::cout << "f1 is_open: " << f1.is_open() << " (должен быть 0)" << std::endl;
        std::cout << "f2 is_open: " << f2.is_open() << " (должен быть 0)" << std::endl;
        std::cout << "f3 is_open: " << f3.is_open() << " (должен быть 1)" << std::endl;
    }

    /**
     * Задание 6. Оператор неявного приведения типа.
     *
     * Реализуйте класс `BoolArray`, представляющий динамический массив
     * логических значений (тип bool). В наивной реализации (`new bool[n]`) есть
     * проблема: каждая переменная типа bool занимает 1 байт, то есть 8 бит, в
     * то время как она могла бы занимать 1 бит.
     *
     * Реализуйте этот класс таким образом, чтобы каждое значение значений
     * действительно занимало 1 бит (точнее сказать, чтобы n значений занимали
     * не более ceil(n / 8), где ceil - целая часть числа с округлением вверх).
     *
     * Класс должен поддерживать следующее поведение:
     */

    {
        std::cout << "\n Задание 6" << std::endl;
        // Создается массив из 10 значений false
        BoolArray ar1(10);
        std::cout << "ar1(10): " << ar1 << std::endl;

        // Создается массив из 5 значений true
        BoolArray ar2(5, true);
        std::cout << "ar2(5, true): " << ar2 << std::endl;

        // Создается независимая копия `ar2`
        BoolArray ar3(ar2);
        std::cout << "ar3 (копия ar2): " << ar3 << std::endl;

        // 4 и 6 элементу (нумерация с 0) устанавливаются заданное значение
        ar1[4] = ar1[6] = true;
        std::cout << "ar1 после ar1[4] = ar1[6] = true: " << ar1 << std::endl;

        /// Над полученными значениями выполняем логические операции
        ar1[2] = (!ar1[6] && ar1[8] || (ar1[0] != true));
        std::cout << "ar1 после логической операции: " << ar1 << std::endl;

        // Выведем массив на печать
        std::cout << "ar1: " << ar1 << std::endl;

        // Выведем массив на печать по-другому: индексы true элементов
        std::cout << "[";
        for (int i = 0, printed = 0; i < ar1.size(); ++i) {
            if (ar1[i]) {
                if (printed++ > 0) std::cout << ", ";
                std::cout << i;
            }
        }
        std::cout << "]\n";


       /// Метод `resize` изменяет размер массива. Если новый размер больше, то
       /// новые значения дополняются заданным значением (по умолчанию false). Если
       /// новый размер меньше, то конец массива отбрасывается.

        ar1.resize(12, true);
        std::cout << "ar1 после resize(12, true): " << ar1 << std::endl;

        ar1.resize(4, true);
        std::cout << "ar1 после resize(4, true): " << ar1 << std::endl;

    } 

	return 0;
}
