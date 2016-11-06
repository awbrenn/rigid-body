//
// Created by awbrenn on 11/2/16.
//

#ifndef RIGIDBODY_STATEVECTOR_H
#define RIGIDBODY_STATEVECTOR_H

#include <vector>
#include "Mesh.h"
#include "Quaternion.h"
#include <iostream>
#include <ostream>

class StateVector {

  public:
    Vector3d x; // position
    Quaternion q; // rotation embeded in a quaternion
    Vector3d P; // momentum
    Vector3d L; // angular momentum

    // constructor
    StateVector();
    StateVector(Vector3d _x, Quaternion _q, Vector3d _P, Vector3d _L);

    // friend functions
    friend StateVector operator-(const StateVector& sv1, const StateVector& sv2); // subtraction
    friend StateVector operator+(const StateVector& sv1, const StateVector& sv2); // addition
    friend StateVector operator*(double s, const StateVector& sv1); // scalar multiply
    friend StateVector operator*(const StateVector& sv1, const double s); // scalar multiply from the other side
    friend StateVector operator/(const StateVector& sv1, const double s); // scalar division
    friend std::ostream& operator<< (std::ostream& os, const StateVector& sv);
};



#endif //RIGIDBODY_STATEVECTOR_H
