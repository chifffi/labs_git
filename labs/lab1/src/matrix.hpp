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

    double get(int i, int j); // получить значение элемента;
    void set(int i, int j, double value); //установить значение элемента;
    int get_height(); // получить высоту
    int get_width(); // получить ширину
    void negate(); //операция `-A` для матрицы;
    void add_in_place(Matrix &other); //операция `this += other` для матрицы
    Matrix multiply(Matrix &other); //возвращает результат матричного умножения.
};

#endif