#include "headers/Vec2D.h" 
#include <iostream>
// Erzeugt einen Vec2d-Punkt und initialisiert die Koordinaten
Vec2d::Vec2d(float xValue, float yValue) : x(xValue), y(yValue) {} //Member Initializer List

//Destruktor
Vec2d::~Vec2d() {}

// Copy constructor
Vec2d::Vec2d(const Vec2d& other) {
    x = other.x;
    y = other.y;
}

// Copy assignment operator (ermöglicht Kettenzuweisung)
Vec2d& Vec2d::operator=(const Vec2d& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}
// Operator overloads
Vec2d Vec2d::operator+(const Vec2d& other) const
{
    return Vec2d(x + other.x, y + other.y);
}

// Operator overloads
Vec2d Vec2d::operator-(const Vec2d& other) const
{
    return Vec2d(x - other.x, y - other.y);
}

// Operator overloads
Vec2d Vec2d::operator*(float scalar) const
{
    return Vec2d(x * scalar, y * scalar);
}

/*Move constructor, nicht nötig
Vec2d::Vec2d(Vec2d&& other) noexcept // noexcept garantiert eine sichere Verschiebung ohne Risiko von Datenverlust.
    : x(other.x), y(other.y) {
}

// Move assignment operator
Vec2d& Vec2d::operator=(Vec2d&& other) noexcept
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}*/
