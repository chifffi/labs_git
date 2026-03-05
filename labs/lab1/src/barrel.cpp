#include "barrel.hpp"

//конструктор по умолчанию
Bochka::Bochka() {
	V_alc = 0;
	V_water = 0;
}

//конструктор с параметрами
Bochka::Bochka(double V, double Percent_alc) {
	V_alc = (Percent_alc * V) / 100.0;;
	V_water = V - V_alc;
}

//метод получения концентрации спирта из текущей бочки
double Bochka::concentr() {
	if (V_alc + V_water == 0)
	{
		return 0;
	}
	double Percent = (V_alc/(V_alc + V_water)) * 100.0;
	return Percent;
}

//метод переливания 1л из другой в текущую
void Bochka::liter_of_another(Bochka &another) {
	double actualV_another = another.V_alc + another.V_water;
	if (actualV_another  < 1.0) //если объем меньше 1л, выходим
	{
		return;
	}
	double Portion_alc = another.V_alc / actualV_another; //доля спирта в другой бочке
	double Portion_water = another.V_water / actualV_another; //доля воды в другой бочке
	//при переливании 1 литра, мы должны перелить жидкость в той же пропорции, что и в бочке

	another.V_alc -= Portion_alc; //уменьшам у другого
	another.V_water -= Portion_water;

	V_alc += Portion_alc; // увеличиваем у текущего
	V_water +=Portion_water;

}