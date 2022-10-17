#pragma once

class Vec3 {
public: 
	float x;
	float y;
	float z;

	// Constructor Method
	Vec3(float x, float y, float z) :x(x), y(y), z(z) {}

	// Unary operator
	Vec3 operator-() const { return Vec3(-x, -y, -z); }

	// Binary operator
	Vec3 operator-(const Vec3 & rhs) const {
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vec3 operator+(const Vec3& rhs) const {
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vec3 operator*(const float& rhs) const {
		return Vec3(x * rhs, y * rhs, z * rhs);
	}

	// Not my == operators
	bool operator==(const Vec3& rhs) const {
		if (rhs.x == x && rhs.y == y, rhs.z == z) {
			return true;
		}
		return false;
	}

	Vec3& operator=(const Vec3& rhs) {
		// Check for self-assignment
		if (this == &rhs)
			return *this;

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

};

class Vec2 {
public:
	float x = 0;
	float y = 0;

	// Constructor Method
	Vec2(float x, float y) : x(x), y(y) {};


	Vec2 operator=(const Vec2& rhs) {// rhs stands for right hand side, aka the value we set vec2 to
		x = rhs.x;
		y = rhs.y;

		return *this;
	}	
};