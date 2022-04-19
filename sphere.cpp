//
// Created by 卟言呢 on 2022/4/15.
//

#include "sphere.h"

#include <cmath>
#include <algorithm>

bool Sphere::intersect(Ray ray, Hit &hit) {
    //判断是否有交点以及，最近的交点
    hit.material_ = this->material_;
    hit.t_ = std::numeric_limits<float>::infinity();
    Vector3d O = ray.origin_;
    Vector3d V = ray.directionVector_;
    Vector3d C = center_;
    Vector3d OC = O - C;
    float a = V.mag() * V.mag();
    float b = 2 * (V.dot(OC));
    float c = OC.mag() * OC.mag() - radius_ * radius_;
    float discr = b * b - 4.0f * a * c;
    if (discr < 0.0) {
        return false;
    } else {
        float t0 = (-b + std::sqrt(discr)) / (2 * a);
        float t1 = (-b - std::sqrt(discr)) / (2 * a);
        if (t0 >= 5E-5 && t1 >= 5E-5) {
            hit.t_ = std::min(t0, t1);
        } else if (t0 >= 5E-5 || t1 >= 5E-5) {
            hit.t_ = std::max(t0, t1);
        }
        if (hit.t_ != std::numeric_limits<float>::infinity()) {
            Vector3d tmp_direction = ray.directionVector_ * hit.t_;
            hit.P_ = OC + tmp_direction;
            hit.N_ = hit.P_;
        }
    }
    hit.P_ = hit.P_ + center_;
    hit.N_.normalize();
    return true;
}