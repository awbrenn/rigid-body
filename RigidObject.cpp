//
// Created by Austin Brennan on 10/31/16.
//

#include "RigidObject.h"

RigidObject::RigidObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename,
                         double Mass, unsigned int Pinned_vertex_index) : Object(obj_filename, frag_shader_filename,
                                                                                 vert_shader_filename) {

  mass = Mass;
  pinned_vertex_index = Pinned_vertex_index;
}

void RigidObject::convertStateVectorToMesh() {
  // start the displaced mesh off as the same as the regular mesh
  displaced_mesh = mesh.copy();

  // rotate the mesh
  for (auto p = displaced_mesh.vertex_positions.begin(); p < displaced_mesh.vertex_positions.end(); ++p) {
    Matrix3x3 rotation_matrix = state.q.rotation();
    *p = *p * rotation_matrix;
  }

  // rotate the normals of the mesh
  for (auto n = displaced_mesh.vertex_normals.begin(); n < displaced_mesh.vertex_normals.end(); ++n) {
    Matrix3x3 rotation_matrix = state.q.rotation();
    *n = *n * rotation_matrix;
  }

  // move the mesh
  for (auto p = displaced_mesh.vertex_positions.begin(); p < displaced_mesh.vertex_positions.end(); ++p) {
    *p = *p + state.x;
  }
}

Vector3d RigidObject::getPinPosition() {
  return displaced_mesh.vertex_positions.at(pinned_vertex_index);
}
