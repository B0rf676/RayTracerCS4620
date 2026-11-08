#include "Vector3.hpp"

 Vector3& Vector3::operator+=(const Vector3 &rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vector3& Vector3::operator-=(const Vector3 &rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vector3& Vector3::operator*=(const float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  float Vector3::dot(const Vector3 &rhs){
    return x*rhs.x + y*rhs.y + z * rhs.z;
  }

  Vector3 Vector3::cross(const Vector3 &rhs){
    return Vector3{
      y * rhs.z - z * rhs.y,
      z * rhs.x - x * rhs.z,
      x * rhs.y - y * rhs.x
    };
  }  

  float Vector3::length(){
    return sqrt(x*x + y*y + z*z);
  }

  Vector3 Vector3::Normalize(){
    float len = length();
    if(len == 0) return Vector3{0, 0, 0};
    return Vector3{
      x / len,
      y / len,
      z / len
    };
  }

Vector3 operator+(Vector3 lhs, const Vector3 &rhs)
{
  return lhs += rhs;
}

Vector3 operator-(Vector3 lhs, const Vector3 &rhs)
{
  return lhs -= rhs;
}

Vector3 operator*(Vector3 lhs, const float scalar)
{
  return lhs *= scalar;
}

std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
  return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}