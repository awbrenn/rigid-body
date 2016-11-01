//
// Created by awbrenn on 11/1/16.
//

#ifndef RIGIDBODY_VERTEX_H
#define RIGIDBODY_VERTEX_H


#include "Vector.h"

class Vertex {
  public:
    Vector3d* position;
    Vector2d* uv;
    Vector3d* normal;

    Vertex(Vector3d* Position, Vector2d* Uv, Vector3d *Normal);
};


#endif //RIGIDBODY_VERTEX_H
