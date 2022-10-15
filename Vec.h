#pragma once

#include <iostream>

// basic struct for 2d vector

template <class T>
struct vec2d_basic
{
	vec2d_basic() = default;
	vec2d_basic(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	T x;
	T y;

	friend vec2d_basic<T> operator+(const vec2d_basic<T>& v1, const vec2d_basic<T>& v2) { return { v1.x + v2.x, v1.y + v2.y }; }
	friend vec2d_basic<T> operator-(const vec2d_basic<T> v1, const vec2d_basic<T>& v2) { return { v1.x - v2.x, v1.y - v2.y }; }
	friend vec2d_basic<T> operator*(const vec2d_basic<T> v1, const vec2d_basic<T>& v2) { return { v1.x * v2.x, v1.y * v2.y }; }
	friend vec2d_basic<T> operator/(const vec2d_basic<T> v1, const vec2d_basic<T>& v2) { return { v1.x / v2.x, v1.y / v2.y }; }
	friend vec2d_basic<T> operator+(const vec2d_basic<T> v1, const T v) { return { v1.x + v, v1.y + v }; }
	friend vec2d_basic<T> operator-(const vec2d_basic<T> v1, const T v) { return { v1.x - v, v1.y - v }; }
	friend vec2d_basic<T> operator*(const vec2d_basic<T> v1, const T v) { return { v1.x * v, v1.y * v }; }
	friend vec2d_basic<T> operator/(vec2d_basic<T> v1, const T v) { return { v1.x / v,	v1.y / v }; }

	friend vec2d_basic<T> operator+=(vec2d_basic<T>& v1, const vec2d_basic<T>& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	friend vec2d_basic<T> operator-=(vec2d_basic<T> v1, const vec2d_basic<T>& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	friend vec2d_basic<T> operator*=(vec2d_basic<T> v1, const vec2d_basic<T>& v2)
	{
		v1.x *= v2.x;
		v1.y *= v2.y;
		return v1;
	}

	friend vec2d_basic<T> operator/=(vec2d_basic<T> v1, const vec2d_basic<T>& v2)
	{
		v1.x /= v2.x;
		v1.y /= v2.y;
		return v1;
	}

	friend vec2d_basic<T> operator+=(vec2d_basic<T> v1, const T v)
	{
		v1.x += v;
		v1.y += v;
		return v1;
	}

	friend vec2d_basic<T> operator-=(vec2d_basic<T> v1, const T v)
	{
		v1.x -= v;
		v1.y -= v;
		return v1;
	}

	friend vec2d_basic<T> operator*=(vec2d_basic<T> v1, const T v)
	{
		v1.x *= v;
		v1.y *= v;
		return v1;
	}

	friend vec2d_basic<T> operator/=(vec2d_basic<T> v1, const T v)
	{
		v1.x /= v;
		v1.y /= v;
		return v1;
	}

	friend bool operator<(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x < v.x&& v1.y < v.y; }
	friend bool operator>(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x > v.x && v1.y > v.y; }
	friend bool operator<=(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x <= v.x && v1.y <= v.y; }
	friend bool operator>=(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x >= v.x && v1.y >= v.y; }
	friend bool operator==(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x == v.x && v1.y == v.y; }
	friend bool operator!=(const vec2d_basic<T> v1, const vec2d_basic<T> v) { return v1.x != v.x || v1.y != v.y; }

	friend bool operator<(const vec2d_basic<T> v1, const T v) { return v1.x < v&& v1.y < v; }
	friend bool operator>(const vec2d_basic<T> v1, const T v) { return v1.x > v && v1.y > v; }
	friend bool operator<=(const vec2d_basic<T> v1, const T v) { return v1.x <= v && v1.y <= v; }
	friend bool operator>=(const vec2d_basic<T> v1, const T v) { return v1.x >= v && v1.y >= v; }
	friend bool operator==(const vec2d_basic<T> v1, const T v) { return v1.x == v && v1.y == v; }
	friend bool operator!=(const vec2d_basic<T> v1, const T v) { return v1.x != v || v1.y != v; }

	template <typename T1>
	vec2d_basic<T1> to() { return vec2d_basic<T1>((T1)this->x, (T1)this->y); }

	float dot(vec2d_basic<T> v)
	{
		return this->x * v.x + this->y * v.y;
	}

	float length()
	{
		return sqrtf(dot(*this));
	}

	vec2d_basic<T> norm()
	{
		float l = length();
		return vec2d_basic<T>(this->x / l, this->y / l);
	}

	T mag() { return T(sqrtf(this->x * this->x + this->y * this->y)); }
	T mag2() { return T(this->x * this->x + this->y * this->y); }

	vec2d_basic<T> abs() { return vec2d_basic<T>(std::abs(this->x), std::abs(this->y)); }
	vec2d_basic<T> perp() { return vec2d_basic<T>(-this->y, this->x); }
	vec2d_basic<T> floor() { return vec2d_basic<T>(std::floor(this->x), std::floor(this->y)); }
	vec2d_basic<T> ceil() { return vec2d_basic<T>(std::ceil(this->x), std::ceil(this->y)); }
	vec2d_basic<T> cart() { return vec2d_basic<T>(cos(this->y) * x, sin(this->y) * this->x); }
	vec2d_basic<T> polar() { return vec2d_basic<T>(mag(), atan2(this->y, this->x)); }
	vec2d_basic<T>& ref() { return *this; }
};

typedef vec2d_basic<int> vi2d;
typedef vec2d_basic<float> vf2d;

// basic struct for 3d vector

template <class T>
struct vec3d_basic
{
	vec3d_basic() = default;
	vec3d_basic(T x, T y, T z, T w = (T)1)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	T x;
	T y;
	T z;
	T w;

	friend vec3d_basic<T> operator+(const vec3d_basic<T>& v1, const vec3d_basic<T>& v2) { return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w }; }
	friend vec3d_basic<T> operator-(const vec3d_basic<T>& v1, const vec3d_basic<T>& v2) { return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w }; }
	friend vec3d_basic<T> operator*(const vec3d_basic<T>& v1, const vec3d_basic<T>& v2) { return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w }; }
	friend vec3d_basic<T> operator/(const vec3d_basic<T>& v1, const vec3d_basic<T>& v2) { return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w }; }
	friend vec3d_basic<T> operator+(const vec3d_basic<T>& v1, const T& v) { return { v1.x + v, v1.y + v, v1.z + v, v1.w + v }; }
	friend vec3d_basic<T> operator-(const vec3d_basic<T>& v1, const T& v) { return { v1.x - v, v1.y - v, v1.z - v, v1.w - v }; }
	friend vec3d_basic<T> operator*(const vec3d_basic<T>& v1, const T& v) { return { v1.x * v, v1.y * v, v1.z * v, v1.w * v }; }
	friend vec3d_basic<T> operator/(vec3d_basic<T>& v1, const T& v) { return { v1.x / v, v1.y / v, v1.z / v, v1.w / v }; }

	friend vec3d_basic<T> operator+=(vec3d_basic<T>& v1, const vec3d_basic<T>& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		v1.w += v2.w;
		return v1;
	}

	friend vec3d_basic<T> operator-=(vec3d_basic<T>& v1, const vec3d_basic<T>& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		v1.w -= v2.w;
		return v1;
	}

	friend vec3d_basic<T> operator*=(vec3d_basic<T>& v1, const vec3d_basic<T>& v2)
	{
		v1.x *= v2.x;
		v1.y *= v2.y;
		v1.z *= v2.z;
		v1.w *= v2.w;
		return v1;
	}

	friend vec3d_basic<T> operator/=(vec3d_basic<T>& v1, const vec3d_basic<T>& v2)
	{
		v1.x /= v2.x;
		v1.y /= v2.y;
		v1.z /= v2.z;
		v1.w /= v2.w;
		return v1;
	}

	friend vec3d_basic<T> operator+=(vec3d_basic<T>& v1, const T v)
	{
		v1.x += v;
		v1.y += v;
		v1.z += v;
		v1.w += v;
		return v1;
	}

	friend vec3d_basic<T> operator-=(vec3d_basic<T>& v1, const T v)
	{
		v1.x -= v;
		v1.y -= v;
		v1.z -= v;
		v1.w -= v;
		return v1;
	}

	friend vec3d_basic<T> operator*=(vec3d_basic<T>& v1, const T v)
	{
		v1.x *= v;
		v1.y *= v;
		v1.z *= v;
		v1.w *= v;
		return v1;
	}

	friend vec3d_basic<T> operator/=(vec3d_basic<T>& v1, const T v)
	{
		v1.x /= v;
		v1.y /= v;
		v1.z /= v;
		v1.w /= v;
		return v1;
	}

	friend bool operator<(const vec3d_basic<T>& v1, const vec3d_basic<T>& v) { return v1.x < v.x&& v1.y < v.y&& v1.z < v.z&& v1.w < v.w; }
	friend bool operator>(const vec3d_basic<T>& v1, const vec3d_basic<T>& v) { return v1.x > v.x && v1.y > v.y && v1.z > v.z && v1.w > v.w; }
	friend bool operator<=(const vec3d_basic<T>& v1, const vec3d_basic<T>& v) { return v1.x <= v.x && v1.y <= v.y && v1.z <= v.z && v1.w <= v.w; }
	friend bool operator>=(const vec3d_basic<T>& v1, const vec3d_basic<T>& v) { return v1.x >= v.x && v1.y >= v.y && v1.z >= v.z && v1.w >= v.w; }
	friend bool operator!=(const vec3d_basic<T>& v1, const vec3d_basic<T>& v) { return v1.x != v.x || v1.y != v.y || v1.z != v.z || v1.w != v.w; }

	float dot(vec3d_basic<T>& v)
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}

	float length()
	{
		return sqrtf(dot(*this));
	}

	vec3d_basic<T> norm()
	{
		float l = length();
		return vec3d_basic<T>(this->x / l, this->y / l, this->z / l, this->w / l);
	}

	vec3d_basic<T> cross(vec3d_basic<T>& v)
	{
		return vec3d_basic<T>(
			this->y * v.z - this->z * v.y,
			this->z * v.x - this->x * v.z,
			this->x * v.y - this->y * v.x
		);
	}

	T mag() { return T(sqrtf(this->x * this->x + this->y * this->y + this->z * this->z)); }
	T mag2() { return T(this->x * this->x + this->y * this->y + this->z * this->z); }

	vec3d_basic<T> abs() { return vec3d_basic<T>(abs(this->x), abs(this->y), abs(this->z), abs(this - w)); }
	vec3d_basic<T> perp() { return vec3d_basic<T>(-this->y, this->x, this->z, this->w); }
	vec3d_basic<T> floor() { return vec3d_basic<T>(std::floor(this->x), std::floor(this->y), std::floor(this->z), std::floor(this->w)); }
	vec3d_basic<T> ceil() { return vec3d_basic<T>(std::ceil(this->x), std::ceil(this->y), std::ceil(this->z), std::ceil(this->w)); }
	vec3d_basic<T> cart() { return vec3d_basic<T>(cos(this->y) * x, sin(this->y) * this->x, this->z, this->w); }
	vec3d_basic<T> polar() { return vec3d_basic<T>(mag(), atan2(this->y, this->x), this->z, this->w); }
	vec3d_basic<T>& ref() { return *this; }

};

typedef vec3d_basic<int> vi3d;
typedef vec3d_basic<float> vf3d;
