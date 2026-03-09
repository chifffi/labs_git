#include "matrix.hpp"

// TODO: проверить что другие методы работают корректно с матрицей, инициализированной таким способом
// методы get, set при пустой матрице выбросит исключение из-за границ
// метод negate при пустой матрице цикл не выполнится i = 0; i < row, не упадет, но  ничего не сделает
// метод add_in_place при пустой матрице выбросит исключение, тк размеры не совпадают
// метод multiply  при пустой матрице выбросит исключение, тк column != other.row
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
double Matrix::get(int i, int j) {
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
int Matrix::get_height() {
    return row;
}

//получить ширину
int Matrix::get_width() {
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
