//
// Created by 卟言呢 on 2022/4/15.
//
#include <cmath>

#include "Vector3d.h"

Vector3d::Vector3d(float a, float b, float c)
        : x_{a}, y_{b}, z_{c} {}

float Vector3d::modul2() const {
    return (x_ * x_ + y_ * y_ + z_ * z_);
}

float Vector3d::modul() const {
    return sqrtf(modul2());
}

Vector3d Vector3d::cross(Vector3d &v) const {
    Vector3d rev(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
    return rev;
}

float Vector3d::dot(const Vector3d &v) const {
    return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
}

Vector3d Vector3d::operator-(const Vector3d &v){
    return {x_ - v.x_, y_ - v.y_, z_ - v.z_};
}

Vector3d Vector3d::operator+(const Vector3d &v)const {
    return {x_ + v.x_, y_ + v.y_, z_ + v.z_};
}

Vector3d Vector3d::operator*(float x) {
    return {x_ * x, y_ * x, z_ * x};
}

Vector3d Vector3d::operator/(float x) const {
    return {x_ / x, y_ / x, z_ / x};
}

float Vector3d::mag() const { return sqrtf(x_ * x_ + y_ * y_ + z_ * z_); }

void Vector3d::normalize() {
    auto length = mag();
    x_ = x_ / length;
    y_ = y_ / length;
    z_ = z_ / length;
};