//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_RAY_H
#define GL_RAY_H

#include"Vector3d.h"


class Ray {
public:
    Vector3d origin_, directionVector_;

    Ray() {};

    Ray(const Vector3d &p, const Vector3d& d) : origin_{p}, directionVector_{d} {};
};


#endif //GL_RAY_H
