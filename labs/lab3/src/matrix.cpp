#include "matrix.hpp"
#include <iostream>

Matrix::Matrix() {
    row = 0;
    column = 0;
    matr = nullptr;
}

//единичная матрица n×n
Matrix::Matrix(int n) {
    row = n;
    column = n;
    
    if (n <= 0) 
    {
        throw "размер матрицы должен быть > 0 !!";
    }
    
    matr = new double*[row];
    std::cout << "CONSTRUCTOR (выделение памяти)" << std::endl;
    for (int i = 0; i < row; i+=1) 
    {
        matr[i] = new double[column];
        for (int j = 0; j < column; j+=1) 
        {
            if (i == j) 
            {
                matr[i][j] = 1.0;
            } 
            else 
            {
                matr[i][j] = 0.0;
            }
        }
    }
}

//матрица m×n с элементами fill_value
Matrix::Matrix(int m, int n, double fill_value) {
	row = m;
    column = n;

    if (m <= 0 || n <= 0) 
    {
        throw "размер матрицы должен быть > 0 !!";
    }
    
    matr = new double*[row];
    std::cout << "CONSTRUCTOR MxN(выделение памяти)" << std::endl;
    for (int i = 0; i < row; i+=1) 
    {
        matr[i] = new double[column];
        for (int j = 0; j < column; j+=1) 
        {
            matr[i][j] = fill_value;
        }
    }
}

//конструктор копирования
Matrix::Matrix(const Matrix &other) {
	row = other.row;
    column = other.column;

    if (row == 0 || column == 0) //проверка на пустую
    { 
        throw "матрица пустая !!";
    }

    matr = new double*[row];
    std::cout << "COPY CONSTRUCTOR (выделение памяти)" << std::endl;
    for (int i = 0; i < row; i+=1) 
    {
        matr[i] = new double[column];
        for (int j = 0; j < column; j+=1) 
        {
            matr[i][j] = other.matr[i][j];
        }
    }
}


Matrix::~Matrix() {
    if (matr != nullptr) {
        for (int i = 0; i < row; i++) 
        {
            delete[] matr[i]; 
        }
        delete[] matr; 
    }
}

// получить значение элемента
double Matrix::get(int i, int j) const{
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    if (i < 0 || i >= row || j < 0 || j >= column) 
    {
        throw "индексы выходят за границы!!";
    }
    return matr[i][j];
} //при пустой матрице выбросит исключение

//установить значение элемента
void Matrix::set(int i, int j, double value) {
    if (matr == nullptr) 
    {
        throw "матрица пустая !!";
    }
    if (i < 0 || i >= row || j < 0 || j >= column) 
    {
        throw "индексы выходят за границы!!";
    }
    matr[i][j] = value;
} //при пустой матрице выбросит исключение из-за границ

//получить высоту
int Matrix::get_height() const{
    return row;
}

//получить ширину
int Matrix::get_width() const{
    return column;
}

//операция `-A` для матрицы
void Matrix::negate() {
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    for (int i = 0; i < row; i+=1) 
    {
        for (int j = 0; j < column; j+=1) 
        {
            matr[i][j] = -matr[i][j];
        }
    }
} //при пустой матрице цикл не выполнится i = 0; i < row, не упадет, но  ничего не сделает

//операция `this += other` для матрицы
void Matrix::add_in_place(Matrix &other) {
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    if (row != other.row || column != other.column) 
    {
        throw "размеры матриц не одинаковые!!";
    }
    
    for (int i = 0; i < row; i+=1) 
    {
        for (int j = 0; j < column; j+=1) 
        {
            matr[i][j] += other.matr[i][j];
        }
    }
} //при пустой матрице выбросит исключение, тк размеры не совпадают

//возвращает результат матричного умножения
Matrix Matrix::multiply(Matrix &other) {
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    if (column != other.row) 
    {
        throw "кол-во столбцов 1ой матрицы и кол-во строк 2-ой матрицы не одинаковые!!";
    }
    
    Matrix new_matrix(row, other.column, 0.0); // вызывается конструктор матрицы m×n с элементами 0.0
    
    for (int i = 0; i < row; i+=1) 
    {
        for (int j = 0; j < other.column; j+=1) 
        {
            double sum = 0.0;
            for (int k = 0; k < column; k+=1) 
            {
                sum += matr[i][k] * other.matr[k][j];
            }
            new_matrix.matr[i][j] = sum;
        }
    }
    
    return new_matrix;
    
} // при пустой матрице выбросит исключение, тк column != other.row

//оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    //Проверка на самоприсваивание (m1 = m1)
    if (this == &other) 
    {
        return *this;
    }
    
    // Освобождаем старую память
    for (int i = 0; i < row; i++) 
    {
        delete[] matr[i];
    }
    delete[] matr;

    //Проверка корректности other
    if (other.row <= 0 || other.column <= 0 || other.matr == nullptr) {
        matr = nullptr;
        row = 0;
        column = 0;
        return *this;
    }
    
    //Копируем новые размеры
    row = other.row;
    column = other.column;
    
    //Выделяем новую память и копируем данные
    matr = new double*[row];
    for (int i = 0; i < row; i++) {
        matr[i] = new double[column];
        for (int j = 0; j < column; j++) {
            matr[i][j] = other.matr[i][j];
        }
    }
    
    // Возвращаем сам объект (разыменованный указатель) для цепочек присваиваний
    return *this;
}

// Оператор += (сложение с другой матрицей)
Matrix& Matrix::operator+=(const Matrix& other) {
    // Проверка на пустые матрицы
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    
    // Проверка совпадения размеров
    if (row != other.row || column != other.column) {
        throw "размеры матриц не совпадают для операции += !!";
    }
    
    // Поэлементное сложение
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matr[i][j] += other.matr[i][j];
        }
    }
    
    return *this;  // возвращаем сам объект (разыменованный указатель) для цепочек присваиваний
}

// Оператор -= (вычитание другой матрицы)
Matrix& Matrix::operator-=(const Matrix& other) {
    // Проверка на пустые матрицы
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    
    // Проверка совпадения размеров
    if (row != other.row || column != other.column) {
        throw "размеры матриц не совпадают для операции -= !!";
    }
    
    // Поэлементное вычитание
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matr[i][j] -= other.matr[i][j];
        }
    }
    
    return *this;
}

// Оператор *= (умножение на число)
Matrix& Matrix::operator*=(double value) {
    // Проверка на пустую матрицу
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    
    // Умножение всех элементов на число
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matr[i][j] *= value;
        }
    }
    
    return *this;
}

// Оператор /= (деление на число)
Matrix& Matrix::operator/=(double value) {
    // Проверка на пустую матрицу
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    
    // Проверка деления на ноль
    if (value == 0) {
        throw "деление на ноль в операции /= !!";
    }
    
    // Деление всех элементов на число
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matr[i][j] /= value;
        }
    }
    
    return *this;
}

// Оператор + (сложение матриц)
Matrix Matrix::operator+(const Matrix& other) const {
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    
    // Проверка совпадения размеров
    if (row != other.row || column != other.column) {
        throw "размеры матриц не совпадают для операции + !!";
    }
    
    // новая матрица с результатом
    Matrix result(row, column, 0.0);
    
    // Поэлементное сложение
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            result.matr[i][j] = matr[i][j] + other.matr[i][j];
        }
    }
    
    return result;
}

// Оператор - (вычитание матриц)
Matrix Matrix::operator-(const Matrix& other) const {
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    
    // Проверка совпадения размеров
    if (row != other.row || column != other.column) {
        throw "размеры матриц не совпадают для операции - !!";
    }
    
    //новая матрица с результатом
    Matrix result(row, column, 0.0);
    
    // Поэлементное вычитание
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            result.matr[i][j] = matr[i][j] - other.matr[i][j];
        }
    }
    
    return result;
}

// Оператор * (умножение матриц)
Matrix Matrix::operator*(const Matrix& other) const {
    if (matr == nullptr || other.matr == nullptr) {
        throw "одна из матриц пустая !!";
    }
    
    // Проверка совпадения размеров для умножения (количество столбцов первой = количество строк второй)
    if (column != other.row) {
        throw "количество столбцов первой матрицы не равно количеству строк второй!!";
    }
    
    //новая матрица с результатом размером row x other.column
    Matrix result(row, other.column, 0.0);
    
    // Матричное умножение
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < other.column; j++) {
            double sum = 0.0;
            for (int k = 0; k < column; k++) {
                sum += matr[i][k] * other.matr[k][j];
            }
            result.matr[i][j] = sum;
        }
    }
    
    return result;
}

// Оператор * (умножение матрицы на число)
Matrix Matrix::operator*(double value) const {
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    
    // новая матрица с результатом
    Matrix result(row, column, 0.0);
    
    // Умножение всех элементов на число
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            result.matr[i][j] = matr[i][j] * value;
        }
    }
    
    return result;
}

// Оператор / (деление матрицы на число)
Matrix Matrix::operator/(double value) const {
    if (matr == nullptr) {
        throw "матрица пустая !!";
    }
    
    // Проверка деления на ноль
    if (value == 0) {
        throw "деление на ноль в операции / !!";
    }
    
    // новая матрица с результатом
    Matrix result(row, column, 0.0);
    
    // Деление всех элементов на число
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            result.matr[i][j] = matr[i][j] / value;
        }
    }
    
    return result;
}

// Глобальная функция: умножение числа на матрицу
Matrix operator*(double value, const Matrix& matrix) {
    // вызов уже реализованного оператора matrix.operator*(value)
    return matrix * value;
}

// Глобальная функция: унарный минус (-Matrix)
Matrix operator-(const Matrix& matrix) {
    if (matrix.matr == nullptr) {
        throw "матрица пустая !!";
    }
    
    // новая матрица с результатом
    Matrix result(matrix.row, matrix.column, 0.0);
    
    // Меняем знак всех элементов
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.column; j++) {
            result.matr[i][j] = -matrix.matr[i][j];
        }
    }
    
    return result;
}

// Move-конструктор
Matrix::Matrix(Matrix&& other)
    : row(other.row), column(other.column), matr(other.matr)
{
    std::cout << "MOVE CONSTRUCTOR (память НЕ выделяется)" << std::endl;
    other.row = 0;
    other.column = 0;
    other.matr = nullptr;
}

// Move-оператор присваивания
Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) {
        // освободить старую память
        for (int i = 0; i < row; i++) delete[] matr[i];
        delete[] matr;
        
        // забрать данные other
        row = other.row;
        column = other.column;
        matr = other.matr;
        
        // обнулить other
        other.row = 0;
        other.column = 0;
        other.matr = nullptr;
         std::cout << "MOVE ASSIGNMENT (память НЕ выделяется)" << std::endl; 
    }
    return *this;
}
