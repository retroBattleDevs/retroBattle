#pragma once
#ifndef  VEC2D_H
#define  VEC2D_H

class Vec2d {

public:

	float x;
	float y;

	explicit Vec2d(float xValue = 0.0f, float yValue = 0.0f); //constructor

	~Vec2d(); //destructor

	Vec2d(const Vec2d& other); //Kopierkonstruktor

	Vec2d& operator=(const Vec2d& other);//Kopierzuweisungsoperator

	Vec2d operator+(const Vec2d& other) const; //v1+v2
	Vec2d operator-(const Vec2d& other) const; //v1-v2
	Vec2d operator*(float scalar) const; //v1*scalar
	Vec2d operator/(float scalar) const; // Skalardivision

	Vec2d(Vec2d&& other) noexcept; //Move konstruktor
	Vec2d& operator=(Vec2d&& other) noexcept;//Move Zuweisungsoperator

	float dot(const Vec2d& other) const; // Skalarprudukt

	//Zusammengesetzte Zuweisungsoperatoren (verändern den aktuellen Vektor direkt)
	Vec2d& operator+=(const Vec2d& other); // v1 += v2
	Vec2d& operator-=(const Vec2d& other); // v1 -= v2
	Vec2d& operator*=(float scalar); // v1 *= scalar
	Vec2d& operator/=(float scalar); // v1 /= scalar

};
#endif
