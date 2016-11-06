//
// Created by Austin Brennan on 10/31/16.
//

#include "RigidObject.h"

RigidObject::RigidObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename,
                         double Mass) : Object(obj_filename, frag_shader_filename, vert_shader_filename) {

  mass = Mass;
}

void RigidObject::convertStateVectorToMesh() {
  // start the displaced mesh off as the same as the regular mesh
  displaced_mesh = mesh.copy();

  // TODO rotate the mesh
  for (auto p = displaced_mesh.vertex_positions.begin(); p < displaced_mesh.vertex_positions.end(); ++p) {
    Matrix3x3 rotation_matrix = state.q.rotation();
    *p = *p * rotation_matrix;
  }

  // TODO move the mesh
  for (auto p = displaced_mesh.vertex_positions.begin(); p < displaced_mesh.vertex_positions.end(); ++p) {
    *p = *p + state.x;
  }
}
