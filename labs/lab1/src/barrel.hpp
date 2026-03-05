#ifndef BARREL_HPP
#define BARREL_HPP

#include <iostream>

class Bochka{

// TODO: узнать, можно ли убрать это поле или оно для чего-то нужно? 
// можно удалить, ни на что не влияет
double V_alc; //объем спирта
double V_water; //объем воды

public:
        Bochka();
        Bochka(double V, double Percent_alc); //конструктор с параметрами
        double concentr(); //метод получения концентрации спирта из текущей бочки
        void liter_of_another(Bochka &another); //метод переливания 1л из другой в текущую

};
#endif