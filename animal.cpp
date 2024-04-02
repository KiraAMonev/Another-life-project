#include "animal.h"
#include "gameOfLife.h"
Animal::Animal() : lifeSpan(0), satiety(0), sex(0) {};
static const int FULL_SATIETY = 100;
void Animal::setLifeSpan(int lifeSpan) { //��������� ����������������� �����
	this->lifeSpan = lifeSpan;
}

void Animal::setSatiety(int satiety) { //��������� �������
	this->satiety = satiety;
}

int Animal::getSatiety() const { //��������� �������
	return satiety;
}

void Animal::decreaseSatiety(int value) { //���������� ������� �� ���������
	satiety -= value;
}

void Animal::setSex() { //������������ ����
	sex = randomSex();
}

int Animal::getSex() const { //��������� ����
	return sex;
}

bool Animal::isAlive() const { //�������� �� �����
	if (lifeSpan > 0 && lifeSpan+satiety > 0)
		return true;
	else
		return false;
}

bool Animal::possibilityOfReproduction() const
{
	if (lifeSpan <= HERBIVORE_ADULT_AGE)
		return true;
	return false;
}

bool Animal::isHungry(int SP) const {
	if (getSatiety() <= SP) {
		return true;
	}
	return false;
}

int Animal::randomSex() {
	// �������� ���������� ��������� �����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1); // ����������� ������������� ����� � ��������� [-1, 1]

	// ��������� ���������� ����� � ����������� ���
	return dis(gen);

}