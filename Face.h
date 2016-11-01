//
// Created by awbrenn on 11/1/16.
//

#ifndef RIGIDBODY_FACE_H
#define RIGIDBODY_FACE_H


#include "Vertex.h"

class Face {
  public:
    Vertex *v[3]; // vertices of face

    Face(Vertex *v0, Vertex *v1, Vertex *v2);
};


#endif //RIGIDBODY_FACE_H
