//
// Created by 卟言呢 on 2022/4/15.
//

#include "plane.h"

plane::plane(vec _p, vec _normal, Material material) {
    normal = _normal;
    normal.normalize();
    p = _p;
    material_ = material;
}

bool plane::intersect(Ray ray, Hit &hit) {
    float n = ray.directionVector_.dot(normal);

    if (n == 0) {
        return false;
    }
    float t1 = (normal.dot(p) - ray.origin_.dot(normal)) / n;
    if (t1 < 0) {
        return false;
    }
    hit.t_ = t1;
    hit.P_ = ray.origin_ + ray.directionVector_ * hit.t_;
    hit.N_ = normal;
    hit.N_.normalize();
    hit.material_ = material_;
    return true;
}
