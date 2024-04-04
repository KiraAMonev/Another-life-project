#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <vector>
#include "grass.h"
#include <cstdlib> // Для использования функций rand() и srand()
#include <ctime>   // Для использования функции time()

#include <random>

class Animal : public Grass
{
public:
	Animal();
	void setLifeSpan(int lifeSpan);
	void setSatiety(int satiety);
	int getSatiety() const;
	void decreaseSatiety(int value);
	void setSex();
	int getSex() const;
	bool isAlive() const;
	bool isHungry(int SP) const;
	bool possibilityOfReproduction()const;

	void setCntMating();
	void increaseMating();
	int getCntMating()const;
private:
	int randomSex();
	int lifeSpan;
	int satiety;
	int sex;
	int cnt_mating;
};

#endif // !ANIMAL_H
