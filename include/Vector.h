// #pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include <ostream>
#include <array>

using byte = unsigned char;
using uchar = unsigned char;

/**
 * normalize types
 */
enum class NORMALIZE_TYPE
{
    L1_NORMALIZE,
    L2_NORMALIZE
};

/**
 * Vector class
 * supports 1d, 2d, 3d, 4d
 */
template <typename T, byte LEN>
class Vector
{
public:
    const byte len = LEN;
    union
    {
        std::array<T, LEN> val;
        struct
        {
            T x, y, z, w;
        };
        struct
        {
            T r, g, b;
        };
    };

    Vector() = default;
    ~Vector() = default;
    /**
     * construct with number
     */
    Vector(T v0) { val = {v0}; }
    Vector(T v0, T v1) { val = {v0, v1}; }
    Vector(T v0, T v1, T v2) { val = {v0, v1, v2}; }
    Vector(T v0, T v1, T v2, T v3) { val = {v0, v1, v2, v3}; }
    /**
     * construct from array
     */
    Vector(T *src) // construct from an array
    {
        for (byte i = 0; i < len; ++i)
            val.at(i) = src[i];
    }
    /**
     * construct from std::array
     */
    Vector(const std::array<T, LEN> &src)
    {
        for (byte i = 0; i < len; ++i)
            val.at(i) = src.at(i);
    }
    T at(byte index) const
    {
        return val.at(index);
    }
    T &at(byte index)
    {
        return val.at(index);
    }
    T operator[](byte index) const
    {
        return val.at(index);
    }
    T &operator[](byte index)
    {
        return val.at(index);
    }
    const byte size() const;
    double length() const;
    double length2() const;
    Vector &operator=(const Vector<T, LEN> &rhs);
    Vector operator-() const;
    Vector operator+(const Vector<T, LEN> &rhs) const;
    Vector operator-(const Vector<T, LEN> &rhs) const;
    Vector operator*(const Vector<T, LEN> &rhs) const;
    template <typename Tnum>
    Vector operator*(const Tnum &num) const;
    template <typename Tnum>
    Vector operator/(const Tnum &num) const;
    Vector &operator+=(const Vector<T, LEN> &rhs);
    Vector &operator-=(const Vector<T, LEN> &rhs);
    Vector &operator*=(const Vector<T, LEN> &rhs);
    template <typename Tnum>
    Vector &operator*=(const Tnum &num);
    template <typename Tnum>
    Vector &operator/=(const Tnum &num);
    T dot(const Vector &rhs) const;
    Vector cross(const Vector &rhs) const;
    Vector &normalize(NORMALIZE_TYPE normType = NORMALIZE_TYPE::L2_NORMALIZE);
    Vector normalized(NORMALIZE_TYPE normType = NORMALIZE_TYPE::L2_NORMALIZE) const;
    friend std::ostream &operator<<(std::ostream &os, const Vector &v)
    {
        for (byte i = 0; i < v.len; ++i)
            os << v.at(i) << " ";
        return os;
    }
    template <typename Tnum>
    friend Vector operator*(const Tnum &num, const Vector &v)
    {
        return v * num;
    }
    void print() const;
};

template <typename T, byte LEN>
const byte Vector<T, LEN>::size() const
{
    return len;
}

/**
 * return length of the vector
 */
template <typename T, byte LEN>
double Vector<T, LEN>::length() const
{
    double pow_sum = 0;
    for (byte i = 0; i < len; ++i)
        pow_sum += val.at(i) * val.at(i);
    return sqrt(pow_sum);
}

/**
 * return square length of the vector
 */
template <typename T, byte LEN>
double Vector<T, LEN>::length2() const
{
    double pow_sum = 0;
    for (byte i = 0; i < len; ++i)
        pow_sum += val.at(i) * val.at(i);
    return pow_sum;
}

template <typename T, byte LEN>
Vector<T, LEN> &Vector<T, LEN>::operator=(const Vector<T, LEN> &rhs)
{
    val = rhs.val;
    return *this;
}

template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::operator-() const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = -val.at(i);
    return newVec;
}

template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::operator+(const Vector<T, LEN> &rhs) const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = val.at(i) + rhs.at(i);
    return newVec;
}

template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::operator-(const Vector<T, LEN> &rhs) const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = val.at(i) - rhs.at(i);
    return newVec;
}

template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::operator*(const Vector<T, LEN> &rhs) const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = val.at(i) * rhs.at(i);
    return newVec;
}

template <typename T, byte LEN>
template <typename Tnum>
Vector<T, LEN> Vector<T, LEN>::operator*(const Tnum &num) const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = val.at(i) * num;
    return newVec;
}

template <typename T, byte LEN>
template <typename Tnum>
Vector<T, LEN> Vector<T, LEN>::operator/(const Tnum &num) const
{
    Vector newVec;
    for (byte i = 0; i < len; ++i)
        newVec.at(i) = val.at(i) / num;
    return newVec;
}

template <typename T, byte LEN>
Vector<T, LEN> &Vector<T, LEN>::operator+=(const Vector<T, LEN> &rhs)
{
    for (byte i = 0; i < len; ++i)
        val.at(i) += rhs.at(i);
    return *this;
}

template <typename T, byte LEN>
Vector<T, LEN> &Vector<T, LEN>::operator-=(const Vector<T, LEN> &rhs)
{
    for (byte i = 0; i < len; ++i)
        val.at(i) -= rhs.at(i);
    return *this;
}

template <typename T, byte LEN>
Vector<T, LEN> &Vector<T, LEN>::operator*=(const Vector<T, LEN> &rhs)
{
    for (byte i = 0; i < len; ++i)
        val.at(i) *= rhs.at(i);
    return *this;
}

template <typename T, byte LEN>
template <typename Tnum>
Vector<T, LEN> &Vector<T, LEN>::operator*=(const Tnum &num)
{
    for (byte i = 0; i < len; ++i)
        val.at(i) *= num;
    return *this;
}

template <typename T, byte LEN>
template <typename Tnum>
Vector<T, LEN> &Vector<T, LEN>::operator/=(const Tnum &num)
{
    for (byte i = 0; i < len; ++i)
        val.at(i) /= num;
    return *this;
}

/**
 * return the dot product of two vectors
 * they must have the same dimensions
 */
template <typename T, byte LEN>
T Vector<T, LEN>::dot(const Vector<T, LEN> &rhs) const
{
    if (len == 1)
        return x * rhs.x;
    else if (len == 2)
        return x * rhs.x + y * rhs.y;
    else if (len == 3)
        return x * rhs.x + y * rhs.y + z * rhs.z;
    else
        return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

/**
 * return the cross product of two vectors
 * they must be 3d vectors
 */
template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::cross(const Vector<T, LEN> &rhs) const
{
    return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x};
}

template <typename T, byte LEN>
Vector<T, LEN> &Vector<T, LEN>::normalize(NORMALIZE_TYPE normType)
{
    double sum = 0;
    switch (normType)
    {
    case NORMALIZE_TYPE::L1_NORMALIZE:
    {
        for (byte i = 0; i < len; ++i)
            sum += val.at(i);
        break;
    }
    case NORMALIZE_TYPE::L2_NORMALIZE:
    {
        for (byte i = 0; i < len; ++i)
            sum += 1.0 * val.at(i) * val.at(i);
        sum = sqrt(sum);
        break;
    }
    default:
        break;
    }
    return ((*this) *= 1.0 / sum);
}

template <typename T, byte LEN>
Vector<T, LEN> Vector<T, LEN>::normalized(NORMALIZE_TYPE normType) const
{
    return Vector<T, LEN>(*this).normalize(normType);
}

template <typename T, byte LEN>
void Vector<T, LEN>::print() const
{
    for (byte i = 0; i < len; ++i)
        std::cout << val.at(i) << " ";
    std::cout << std::endl;
}

using Vector3f = Vector<float, 3>;
using Vector3d = Vector<double, 3>;
using Vector3b = Vector<byte, 3>;
using Vector3i = Vector<int, 3>;
using Vector2f = Vector<float, 2>;
using Vector2d = Vector<double, 2>;
using Vector2b = Vector<byte, 2>;
using Vector2i = Vector<int, 2>;
using Point3f = Vector<float, 3>;
using Point2f = Vector<float, 2>;
using Point3d = Vector<double, 3>;
using Point2d = Vector<double, 2>;
using Color3d = Vector<double, 3>;
using Color3f = Vector<float, 3>;
using Color3b = Vector<byte, 3>;
using Color3i = Vector<int, 3>;

#endif