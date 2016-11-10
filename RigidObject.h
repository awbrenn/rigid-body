//
// Created by Austin Brennan on 10/31/16.
//

#ifndef SQUISHYMESH_RIGIDOBJECT_H
#define SQUISHYMESH_RIGIDOBJECT_H

#include "Object.h"
#include "RigidMesh.h"
#include "StateVector.h"

class RigidObject : public Object {
  private:
    unsigned int pinned_vertex_index; // a vertex that is pinned for the simulation.

  public:
    double mass;
    StateVector state;
    Mesh displaced_mesh; // a mesh that is displaced by the simulation

    RigidObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename,
                    std::string diffuse_texture_filename, double Mass, unsigned int Pinned_vertex_index);

    void convertStateVectorToMesh();
    Vector3d getPinPosition();
};


#endif //SQUISHYMESH_RIGIDOBJECT_H
