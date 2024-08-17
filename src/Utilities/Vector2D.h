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

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend Vector2D operator+(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

// Inline implementations for simplicity
inline Vector2D::Vector2D() : x(0.0f), y(0.0f) {}

inline Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

inline Vector2D& Vector2D::Add(const Vector2D& vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

inline Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

inline Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	x *= vec.x;
	y *= vec.y;
	return *this;
}

inline Vector2D& Vector2D::Divide(const Vector2D& vec) {
	x /= vec.x;
	y /= vec.y;
	return *this;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	return Add(vec);
}

inline Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	return Subtract(vec);
}

inline Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	return Multiply(vec);
}

inline Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	return Divide(vec);
}

inline Vector2D operator+(Vector2D v1, const Vector2D& v2) {
	return v1.Add(v2);
}

inline Vector2D operator-(Vector2D v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}

inline Vector2D operator*(Vector2D v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}

inline Vector2D operator/(Vector2D v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

inline std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}