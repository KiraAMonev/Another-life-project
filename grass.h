#ifndef GRASS_H
#define GRASS_H

class Grass {
public:
    Grass();
    void setLifeSpan(int lifeSpan);
    int getLifeSpan() const;
    void decreaseLifeSpan();
    bool isAlive() const;

private:
    int lifeSpan;
};

#endif // GRASS_H
