//
// Created by awbrenn on 10/21/16.
//

#include "Solver.h"

Solver::Solver(RigidObject *Rigid_object, double time_step, unsigned int Substeps, double Ground_level,
               double Spring_constant, double Line_length, Vector3d Line_anchor) {
  rigid_object = Rigid_object;
  dt = time_step;
  substeps = Substeps;
  ground_level = Ground_level;
  spring_constant = Spring_constant;
  line_length = Line_length;
  line_anchor_point = Line_anchor;
}


// calculate the forces that act on the whole body (like gravity)
void Solver::calculateForce(StateVector K, Vector3d *body_force, Vector3d *local_force) {
  Vector3d gravity(0.0, -9.8, 0.0);
  Vector3d spring_force(0.0, 0.0, 0.0);

  Vector3d rigid_body_pin_position = rigid_object->getPinPosition();
  Vector3d r = (rigid_body_pin_position - K.x).normalize(); // unit vector from rigid body position to pinned point on rigid body
  Vector3d l = (line_anchor_point - rigid_body_pin_position).normalize(); // unit vector in the direction of the anchor from the pin

  if (rigid_body_pin_position.norm() > line_length) {
    spring_force = spring_constant * ((rigid_body_pin_position.norm() - line_length) * l);
  }

  *body_force = (gravity + spring_force) * rigid_object->mass;
  *local_force = (spring_force % r) * rigid_object->mass;
}


StateVector Solver::calculateStateDerivative(StateVector K) {
  Vector3d body_force(0.0, 0.0, 0.0);
  Vector3d local_force(0.0, 0.0, 0.0);
  StateVector dK;

  calculateForce(K, &body_force, &local_force);

  // get the angular velocity
  Matrix3x3 I; // identity matrix
  I.identity();

  Vector3d w = I.transpose() * K.L;

  dK.x = (1.0 / rigid_object->mass) * (K.P);
  dK.q = 0.5 * w * K.q;
  dK.P = body_force;
  dK.L = local_force;

  return dK;
}


StateVector Solver::integrateEuler(StateVector K) {

}


void Solver::integrateRK4() {
  StateVector K1, K2, K3, K4;

  // calculate the forces on the particles
  K1 = calculateStateDerivative(rigid_object->state);
  K2 = calculateStateDerivative(rigid_object->state + ((dt / 2.0) * K1));
  K3 = calculateStateDerivative(rigid_object->state + ((dt / 2.0) * K2));
  K4 = calculateStateDerivative(rigid_object->state + (dt * K3));

  rigid_object->state = (rigid_object->state) + ((dt / 6.0) * (K1 + (2*K2) + (2*K3) + K4));
}


void Solver::update(unsigned int integrator, Vector3d User_acceleration) {
  user_acceleration = User_acceleration;

  rigid_object->convertStateVectorToMesh();

  switch(integrator) {
    case EULER:
      break;
    case RK4:
      integrateRK4();
      break;
    default:
      break;
  }
}
