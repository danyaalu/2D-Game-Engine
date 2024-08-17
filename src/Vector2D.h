#pragma once
#include <iostream>

class Vector2D {
public:
	float x, y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	/*
		Friend keyword allows the function to access private and protected members of the class
	*/

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2); // Overload the + operator to add two Vector2D objects
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2); // Overload the - operator to subtract one Vector2D objects from another
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2); // Overload the * operator to multiply two Vector2D objects
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2); // Overload the / operator to divide one Vector2D object by another

	Vector2D& operator+=(const Vector2D& vec); // Overload the += operator to add another Vector2D object to this one
	Vector2D& operator-=(const Vector2D& vec); // Overload the -= operator to subtract another Vector2D object from this one
	Vector2D& operator*=(const Vector2D& vec); // Overload the *= operator to multiply this Vector2D object by another
	Vector2D& operator/=(const Vector2D& vec); // Overload the /= operator to divide this Vector2D object by another

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec); // Overload the << operator to output the Vector2D object to the console
};