//
// Created by awbrenn on 10/21/16.
//

#include "Solver.h"

Solver::Solver(Mesh *Rigid_mesh, double time_step, double Ground_level, double Coefficient_of_restitution,
               double Coefficient_of_friction) {
  rigid_mesh = Rigid_mesh;
  dt = time_step;
  ground_level = Ground_level;
  coeff_of_restitution = Coefficient_of_restitution;
  coeff_of_friction = Coefficient_of_friction;
}


void Solver::update(unsigned int integrator, Vector3d User_acceleration) {
  user_acceleration = User_acceleration;

  switch(integrator) {
    case LEAPFROG:
      break;
    case SIXTH:
      break;
    default:
      break;
  }
}