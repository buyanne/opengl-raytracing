//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include "Color.h"
#include "Ray.h"

class Hit;

class Material {
public:
    Color color_;
    Color ambientColor_;
    Color specularColor_;
    Color diffuseColor_;
    float alpha_{};
    float refractIndex_{};
    float specExponent_{};
    float reflectionCoeff_{};

    Material() {};
};

class Object {
public:
    Material material_;

    Object() = default;;

    virtual bool intersect(Ray ray, Hit &hit) = 0;
};

class Hit {
public:
    Vector3d P_;
    Vector3d N_;
    Object *obj_{};
    float t_;
    Material material_;

    Hit() {};
};


#endif //GL_OBJECT_H
