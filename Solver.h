//
// Created by awbrenn on 10/21/16.
//

#ifndef SQUISHYMESH_SOLVER_H
#define SQUISHYMESH_SOLVER_H

#include "RigidMesh.h"
#include "Vector.h"
#include "Mesh.h"
#include "StateVector.h"
#include "RigidObject.h"

#define EULER 0
#define RK4 4

class Solver {
  private:
    void calculateForce(StateVector K, Vector3d *body_force, Vector3d *local_force);
    StateVector calculateStateDerivative(StateVector K);


    public:
      RigidObject *rigid_object;
      double ground_level;
      double spring_constant;
      double line_length;
      Vector3d line_anchor_point;
      Vector3d user_acceleration;
      double dt; // timestep (dt for delta time per step)
      unsigned int substeps; // sub steps

      Solver(RigidObject *rigid_object, double time_step, unsigned int substeps, double ground_level,
                   double spring_constant, double Line_length, Vector3d Line_anchor);

      void update(unsigned int integrator, Vector3d user_acceleration);
      StateVector integrateEuler(StateVector K);
      void integrateRK4();
};


#endif //SQUISHYMESH_SOLVER_H
