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
    StateVector calculateStateDerivative(StateVector K);


    public:
    Mesh *rigid_mesh;
    double ground_level;
    double coeff_of_restitution;
    double coeff_of_friction;
    Vector3d user_acceleration;
    double dt; // timestep (dt for delta time per step)

    Solver(Mesh *spring_mesh, double time_step, double ground_level, double coefficient_of_restitution,
           double coefficient_of_friction);

    void update(unsigned int integrator, RigidObject *rigid_object, Vector3d user_acceleration);
    StateVector integrateEuler(StateVector K);
    void integrateRK4(RigidObject* rigid_object);
};


#endif //SQUISHYMESH_SOLVER_H
