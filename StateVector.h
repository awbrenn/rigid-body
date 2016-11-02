//
// Created by awbrenn on 11/2/16.
//

#ifndef RIGIDBODY_STATEVECTOR_H
#define RIGIDBODY_STATEVECTOR_H

#include <vector>
#include "Vector.h"
#include "Mesh.h"
#include <iostream>
#include <ostream>

class StateVector {

  public:
    size_t N; // number of elements in StateVector
    size_t size; // total size of the array
    Vector3d* values; // number of elements in the StateVector

    // constructor
    StateVector(size_t number_of_elements=0);
    StateVector(Mesh *mesh);

    Vector3d& operator[](size_t i);

    // friend functions
    friend StateVector operator-(const StateVector& sv1, const StateVector& sv2); // subtraction
    friend StateVector operator+(const StateVector& sv1, const StateVector& sv2); // addition
    friend StateVector operator*(double s, const StateVector& sv1); // scalar multiply
    friend StateVector operator*(const StateVector& sv1, const double s); // scalar multiply from the other side
    friend StateVector operator/(const StateVector& sv1, const double s); // scalar division
    friend std::ostream& operator<< (std::ostream& os, const StateVector& sv);

    // member functions
    Vector3d at(size_t i);
    void transferMeshToStateVector(Mesh *mesh);
};



#endif //RIGIDBODY_STATEVECTOR_H
