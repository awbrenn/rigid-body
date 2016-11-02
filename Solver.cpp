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

StateVector Solver::calculateStateDerivative(StateVector K) {
  StateVector dK(K.N);

  for (size_t i = 0; i < dK.N; ++i) {
    dK[i] = K[K.N + i];
  }

  for (size_t i = dK.N; i < 2 * dK.N; ++i) {
    dK[i] = Vector3d (0.0, -9.8, 0.0);
  }

  return dK;
}


StateVector Solver::integrateEuler(StateVector K) {

}


void Solver::integrateRK4(RigidObject* rigid_object) {
  StateVector K1, K2, K3, K4;

  // calculate the forces on the particles
  K1 = calculateStateDerivative(*rigid_object->state);
  K2 = calculateStateDerivative((*rigid_object->state) + ((dt / 2.0) * K1));
  K3 = calculateStateDerivative((*rigid_object->state) + ((dt / 2.0) * K2));
  K4 = calculateStateDerivative((*rigid_object->state) + (dt * K3));

  *rigid_object->state = (*rigid_object->state) + ((dt / 6.0) * (K1 + (2*K2) + (2*K3) + K4));
}


void Solver::update(unsigned int integrator, RigidObject* rigid_object, Vector3d User_acceleration) {
  user_acceleration = User_acceleration;

  switch(integrator) {
    case EULER:
      break;
    case RK4:
      integrateRK4(rigid_object);
      break;
    default:
      break;
  }

  rigid_object->convertStateVectorToMesh();
}