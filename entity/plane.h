//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_PLANE_H
#define GL_PLANE_H


#include "Object.h"

typedef Vector3d vec;

//平面类
class plane : public Object {
public:
    //法线和平面上的一个点
    vec normal, p;
    plane(vec _p, vec _normal, Material material);

    plane() {}

    bool intersect(Ray ray, Hit& hit) override;
};


#endif //GL_PLANE_H
