#include "Grass.h" // ����������� ������������� ����� ��� ������ Grass

Grass::Grass() : lifeSpan(0) {} // ����������� ������ Grass, ��������������� ��������� ����������������� ����� ����� (0)

void Grass::setLifeSpan(int lifeSpan) { // ����� ��������� ����������������� ����� �����
    this->lifeSpan = lifeSpan; // ��������� ����������������� ����� �����
}

int Grass::getLifeSpan() const { // ����� ��������� ����������������� ����� �����
    return lifeSpan; // ���������� ������� ����������������� ����� �����
}

void Grass::decreaseLifeSpan() { // ����� ���������� ����������������� ����� �����
    lifeSpan -= 1; // ��������� ����������������� ����� ����� �� �������
}

bool Grass::isAlive() const { // ����� ��������, ���� �� �����
    return lifeSpan > 0; // ���������� true, ���� ����������������� ����� ����� ������ ����, ����� false
}
