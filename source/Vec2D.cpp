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
// Operator overloads
Vec2d Vec2d::operator/(float scalar) const {
    if (scalar != 0.0f) {
        return Vec2d(x / scalar, y / scalar);
    }
    return Vec2d(0.0f, 0.0f); 
}

//Move constructor
Vec2d::Vec2d(Vec2d&& other) noexcept // noexcept garantiert eine sichere Verschiebung ohne Risiko von Datenverlust.
    : x(other.x), y(other.y) {
    other.x = 0.0f; 
    other.y = 0.0f;
}

// Move assignment operator
Vec2d& Vec2d::operator=(Vec2d&& other) noexcept
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        other.x = 0.0f;
        other.y = 0.0f;
    }
    return *this;
}

//Skalarprodukts 
float Vec2d::dot(const Vec2d& other) const {
    return (x * other.x) + (y * other.y);
    // Ergebnis > 0: Winkel < 90° (Gleiche Richtung)
    // Ergebnis = 0: Winkel = 90° (Orthogonal / Senkrecht)
    // Ergebnis < 0: Winkel > 90° (Entgegengesetzte Richtung)
}

//Zusammengesetzte Zuweisungsoperatoren
// v1 += v2
Vec2d& Vec2d::operator+=(const Vec2d& other) {
    x += other.x;
    y += other.y;
    return *this;
}

// v1 -= v2
Vec2d& Vec2d::operator-=(const Vec2d& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

// v1 *= scalar
Vec2d& Vec2d::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

// v1 /= scalar
Vec2d& Vec2d::operator/=(float scalar) {
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}
