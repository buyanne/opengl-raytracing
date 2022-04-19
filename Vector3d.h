//
// Created by 卟言呢 on 2022/4/15.
//

#ifndef GL_VECTOR3D_H
#define GL_VECTOR3D_H


class Vector3d {
public :
    float x_, y_, z_;

    Vector3d(float x = 0, float y = 0, float z = 0);

    float modul2() const;

    float modul() const;

    Vector3d cross(Vector3d &v) const;

    float dot(const Vector3d &v) const;

    Vector3d operator-(const Vector3d &v);

    Vector3d operator+(const Vector3d &v) const;

    Vector3d operator*(float x);

    bool operator==(const Vector3d &node) {
        return x_ == node.x_ && y_ == node.y_ && z_ == node.z_;
    }

    Vector3d operator/(float x) const;

    float mag() const;

    void normalize();
};


#endif //GL_VECTOR3D_H
