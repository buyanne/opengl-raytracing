#include <iostream>
#include <algorithm>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include "entity/Light.h"
#include "entity/sphere.h"
#include "entity/plane.h"


const int MAX_RECURSION_DEPTH = 3;
const float VIEWPORT_X = 15;
const float VIEWPORT_Y = 11.25;
const float FOCAL_LENGTH = -2.5;
const int WINDOW_W = 800;
const int WINDOW_H = 600;

//p为视角的位置 d 为视角的方向位置，相减就是视角方向向量
const Ray camera(Vector3d(0.0f, 0.0f, 15.0f), Vector3d(0.0f, 0.0f, -1.0f));

const Vector3d upperRightCorner(VIEWPORT_X / 2, VIEWPORT_Y / 2, FOCAL_LENGTH);
const Vector3d bottomLeftCorner(-1 * VIEWPORT_X, -1 * VIEWPORT_Y, FOCAL_LENGTH);

Light light;
Color ambientLight;

std::vector<Object *> objects;
GLubyte pixelData[WINDOW_H][WINDOW_W][3];


void ConstructScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
    //光源的位置和颜色
    light = Light(Color(1.0f, 1.0f, 1.0f), Vector3d(3.0f, 15.0f, -0.5f));
    //环境光的颜色
    ambientLight = Color(0.5f, 0.5f, 0.5f);

    //在空间中添加一个球
    Sphere *sphere = new Sphere;
    sphere->center_ = Vector3d(-5.0f, 2.0f, 0.0f);
    sphere->radius_ = 1.5f;
    sphere->material_.diffuseColor_ = Color(0.1f, 0.2f, 0.8f);
    sphere->material_.ambientColor_ = Color(0.3f, 0.4f, 0.8f);
    sphere->material_.specularColor_ = Color(0.99f, 0.99f, 0.99f);
    sphere->material_.alpha_ = 1.0;
    sphere->material_.refractIndex_ = 1.5;
    sphere->material_.specExponent_ = 30.0;
    objects.push_back(sphere);

    Sphere *sphere1 = new Sphere;
    sphere1->center_ = Vector3d(-4.0f, -1.0f, -4.0f);
    sphere1->radius_ = 4.0f;
    sphere1->material_.diffuseColor_ = Color(0.1f, 0.2f, 0.1f);
    sphere1->material_.ambientColor_ = Color(0.5f, 0.3f, 0.1f);
    sphere1->material_.specularColor_ = Color(0.5f, 0.5f, 0.3f);
    sphere1->material_.alpha_ = 1.0;
    sphere1->material_.refractIndex_ = 1.5;
    sphere1->material_.specExponent_ = 15.0;
    objects.push_back(sphere1);

    //创建一个平面
    plane *p = new plane;
    p->normal = vec(1.0f, 1.0f, 1.0f);
    p->p = vec(-2.0f, -10.0f, 1.0f);
    p->material_.diffuseColor_ = Color(0.5f, 0.5f, 0.5f);
    p->material_.ambientColor_ = Color(0.3f, 0.3f, 0.3f);
    p->material_.specularColor_ = Color(0.5f, 0.5f, 0.5f);
    p->material_.alpha_ = 0.6;
    p->material_.refractIndex_ = 0.5;
    p->material_.specExponent_ = 10.0;
    objects.push_back(p);

}


Hit DetectSceneHit(Ray &ray) {
    Hit ret, hit;
    ret.material_.color_ = Color(0.1f, 0.2f, 0.3f);
    ret.t_ = std::numeric_limits<float>::infinity();
    for (auto &object: objects) {
        auto *sphere = (Sphere *) object;
        sphere->intersect(ray, hit);
        if (hit.t_ < ret.t_) {
            ret.material_ = hit.material_;
            ret.N_ = hit.N_;
            ret.P_ = hit.P_;
            ret.t_ = hit.t_;
        }
    }
    return ret;
}


Hit RayCast(Ray &ray, int depth) {
    Hit hit;
    if (depth == 0) {
        hit.material_.color_ = Color(0.1f, 0.1f, 0.1f);
        hit.t_ = std::numeric_limits<float>::infinity();
        return hit;
    }
    Hit rayHit = DetectSceneHit(ray);
    if (rayHit.t_ != std::numeric_limits<float>::infinity()) {
        //环境光就算
        rayHit.material_.color_
                = rayHit.material_.ambientColor_
                  * ambientLight;
        Ray lightRay;
        //光源点和方向
        lightRay.origin_ = rayHit.P_;
        lightRay.directionVector_ = light.P_ - rayHit.P_;
        //求最近交点
        Hit lightRayHit = DetectSceneHit(lightRay);
        if (lightRayHit.t_ == std::numeric_limits<float>::infinity()) {
            //进行标准化
            lightRay.directionVector_.normalize();
            ray.directionVector_.normalize();
            //漫反射计算，光线点乘法向量
            float dot1 = lightRay.directionVector_.dot(rayHit.N_);
            //根据公式添加上漫反射光的颜色信息
            rayHit.material_.color_
                    = rayHit.material_.color_
                      + light.color_
                        * rayHit.material_.diffuseColor_ * dot1;
            //高光反射计算
            vec h = lightRay.directionVector_ - ray.directionVector_;
            h.normalize();
            //根据高光计算公式可以直接得出该式子
            rayHit.material_.color_
                    = rayHit.material_.color_
                      + light.color_ * rayHit.material_.specularColor_
                        * powf(h.dot(rayHit.N_), rayHit.material_.specExponent_);
        }
    } else {
        rayHit.material_.color_ = Color(0.1f, 0.1f, 0.1f);
    }
    return rayHit;
}

void RenderScene() {
//Iterate through all screen pixels
    for (int i = 0; i < WINDOW_W; i++) {
        for (int j = 0; j < WINDOW_H; j++) {
//Set background color
            pixelData[j][i][0] = 30;
            pixelData[j][i][1] = 25;
            pixelData[j][i][2] = 25;
//Construct viewing ray
            float x = bottomLeftCorner.x_ + (upperRightCorner.x_ - bottomLeftCorner.x_)
                                            * ((i + 0.5) / WINDOW_W);
            float y = bottomLeftCorner.y_ + (upperRightCorner.y_ - bottomLeftCorner.y_)
                                            * ((j + 0.5) / WINDOW_H);
            Vector3d point(x, y, bottomLeftCorner.z_);
            Ray cameraRay;
            cameraRay.origin_ = camera.origin_;
            cameraRay.directionVector_ = point - (Vector3d) camera.origin_;
            Hit hit = RayCast(cameraRay, MAX_RECURSION_DEPTH);
//If an object was hit, set the color for that pixel appropriately
            pixelData[j][i][0] = std::min((int) (hit.material_.color_.r_ * 255), 255);
            pixelData[j][i][1] = std::min((int) (hit.material_.color_.g_ * 255), 255);
            pixelData[j][i][2] = std::min((int) (hit.material_.color_.b_ * 255), 255);
        }
    }
    glDrawPixels(WINDOW_W, WINDOW_H, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
}

void DisplayFunc(void) {
    ConstructScene();
    RenderScene();
    glFlush();
}

void MouseFunc(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                exit(-1);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    std::cout << "Ray Casting" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ray Casting - 3D scene");
    glutDisplayFunc(DisplayFunc);
    glutMouseFunc(MouseFunc); // register myMouse function
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // background is light gray
    glutMainLoop();
    for (auto &object: objects) delete object;

    return 0;
}

