//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_LIGHT_H
#define GL_LIGHT_H


#include "Color.h"
#include "Vector3d.h"

class Light {
public:
    Color color_;
    Vector3d P_;

    Light() {};

    Light(Color color, Vector3d v) : color_{color}, P_{v} {};
};


#endif //GL_LIGHT_H
