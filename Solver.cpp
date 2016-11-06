//
// Created by awbrenn on 10/21/16.
//

#include "Solver.h"

Solver::Solver(RigidObject *Rigid_object, double time_step, double Ground_level, double Coefficient_of_restitution,
               double Coefficient_of_friction) {
  rigid_object = Rigid_object;
  dt = time_step;
  ground_level = Ground_level;
  coeff_of_restitution = Coefficient_of_restitution;
  coeff_of_friction = Coefficient_of_friction;
}


// calculate the forces that act on only a portion of the mesh
Vector3d Solver::calculateLocalForce(StateVector K) {
  return Vector3d(0.0, 0.0, 0.0);
}


// calculate the forces that act on the whole body (like gravity)
Vector3d Solver::calculateBodyForce(StateVector K) {
  Vector3d body_force;
  Vector3d gravity(0.0, -9.8, 0.0);


//  Vector3d line_anchor(0.0, 0.0, 0.0);
//  double line_length = 2.0;
//
//  if (K.x.norm() > line_length) {
//    Vector3d
//  }

  body_force = gravity * rigid_object->mass;

  return body_force;
}


StateVector Solver::calculateStateDerivative(StateVector K) {
  Vector3d body_force(0.0, 0.0, 0.0);
  Vector3d local_force(0.0, 0.0, 0.0);
  StateVector dK;

  body_force = calculateBodyForce(K);
  local_force = calculateLocalForce(K);

  dK.x = (1.0 / rigid_object->mass) * (K.P);
//  dK.q = 0.5 * w * K.q;
  dK.P = body_force + local_force;
//  dK.L = r * local_force;

  return dK;
}


StateVector Solver::integrateEuler(StateVector K) {

}


void Solver::integrateRK4() {
  StateVector K1, K2, K3, K4;

  // calculate the forces on the particles
  K1 = calculateStateDerivative(rigid_object->state);
  K2 = calculateStateDerivative((rigid_object->state) + ((dt / 2.0) * K1));
  K3 = calculateStateDerivative((rigid_object->state) + ((dt / 2.0) * K2));
  K4 = calculateStateDerivative((rigid_object->state) + (dt * K3));

  rigid_object->state = (rigid_object->state) + ((dt / 6.0) * (K1 + (2*K2) + (2*K3) + K4));
}


void Solver::update(unsigned int integrator, Vector3d User_acceleration) {
  user_acceleration = User_acceleration;

  switch(integrator) {
    case EULER:
      break;
    case RK4:
      integrateRK4();
      break;
    default:
      break;
  }

  rigid_object->convertStateVectorToMesh();
}
