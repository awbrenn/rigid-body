//
// Created by Austin Brennan on 10/31/16.
//

#ifndef SQUISHYMESH_RIGIDOBJECT_H
#define SQUISHYMESH_RIGIDOBJECT_H

#include "Object.h"
#include "RigidMesh.h"

class RigidObject : public Object {
  public:
    double mass;

    RigidObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename, double Mass);
};


#endif //SQUISHYMESH_RIGIDOBJECT_H
