//
// Created by Austin Brennan on 10/31/16.
//

#include "RigidObject.h"

RigidObject::RigidObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename,
                         double Mass) : Object(obj_filename, frag_shader_filename, vert_shader_filename) {

  mass = Mass;
}
