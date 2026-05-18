#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
	int row;
    int column;
    double** matr;

public:
    Matrix();
	Matrix(int n);  //единичная матрица n×n
    Matrix(int m, int n, double fill_value = 0);  //матрица m×n с элементами fill_value
    Matrix(const Matrix &other);  //конструктор копирования

    ~Matrix();

    double get(int i, int j) const; // получить значение элемента;
    void set(int i, int j, double value); //установить значение элемента;
    int get_height() const; // получить высоту
    int get_width() const; // получить ширину
    void negate(); //операция `-A` для матрицы;
    void add_in_place(Matrix &other); //операция `this += other` для матрицы
    Matrix multiply(Matrix &other); //возвращает результат матричного умножения.

    //оператор присваивания
    //параметр: & чтобы не создавалась лишняя копия, const как гарантия что исходный объект не изменится
    Matrix& operator=(const Matrix& other);

    //операторы составного присваивания
    //параметр: & чтобы не создавалась лишняя копия, const как гарантия что исходный other объект не изменится
    Matrix& operator+=(const Matrix& other);  // сложение с матрицей
    Matrix& operator-=(const Matrix& other);  // вычитание матрицы
    Matrix& operator*=(double value);  // умножение на число
    Matrix& operator/=(double value); // деление на число

    //бинарные операторы
    //const, потому что они не изменяют текущий объект
    //Операторы возвращают новый объект Matrix, а не ссылку
    Matrix operator+(const Matrix& other) const;  // сложение матриц,
    Matrix operator-(const Matrix& other) const;  // вычитание матриц, 
    Matrix operator*(const Matrix& other) const;  // умножение матриц
    Matrix operator*(double value) const;   // умножение на число
    Matrix operator/(double value) const;   // деление на число
    
    //friend - возможно обращение к защищенным полям класса извне без геттеров и сеттеров

    //friend функция для случая число * матрица
    //для поддержки double * объект (число слева) нужна отдельная функция, так как метод класса не может иметь первый левый операнд базового типа
    friend Matrix operator*(double value, const Matrix& matrix);

    //friend функция для случая унарный минус (-Matrix)
    friend Matrix operator-(const Matrix& matrix);

    
    //Move-семантика
    //Данные не копируются, а просто "крадутся" – забирается указатель на память. После move-операции исходный объект становится пустым.
    Matrix(Matrix&& other); //move-конструктор
    Matrix& operator=(Matrix&& other); //move-оператор присваивания
    
};

#endif