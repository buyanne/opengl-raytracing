//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_SPHERE_H
#define GL_SPHERE_H


#include "Vector3d.h"
#include "Color.h"
#include "Ray.h"
#include "Object.h"
class Sphere : public Object
{
public:
    Vector3d center_;
    float radius_{};
    Sphere() {};
    bool intersect(Ray ray, Hit& hit);
};

#endif //GL_SPHERE_H
