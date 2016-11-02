//
// Created by awbrenn on 11/2/16.
//

#include "StateVector.h"

StateVector::StateVector(size_t number_of_elements) {
  // double the number of elements to splitting position, velocity, and acceleration
  size = number_of_elements * 4;
  N = number_of_elements;
  values = new Vector3d[size];
}


StateVector::StateVector(Mesh *mesh) {
  size_t number_of_elements = mesh->vertex_positions.size();
  size = number_of_elements * 4;
  N = number_of_elements;
  values = new Vector3d[size];

  // set all of the initial positions to the vertex positions
  for (size_t i = 0; i < N; ++i) {
    values[i] = mesh->vertex_positions[i];
  }

  // set all other values of the state vector to zero
  for (size_t i = N; i < 4*N; ++i) {
    values[i] = Vector3d(0.0, 0.0, 0.0);
  }
}

Vector3d &StateVector::operator[](size_t i) {
  return values[i];
}

StateVector operator-(const StateVector &sv1, const StateVector &sv2) {
  StateVector r(sv1.N);

  for (size_t i = 0; i < sv1.size; ++i) {
    r[i] = sv1.values[i] - sv2.values[i];
  }

  return r;
}

StateVector operator+(const StateVector &sv1, const StateVector &sv2) {
  StateVector r(sv1.N);

  for (size_t i = 0; i < sv1.size; ++i) {
    r[i] = sv1.values[i] + sv2.values[i];
  }

  return r;
}

StateVector operator*(const StateVector &sv1, const StateVector &sv2) {
  StateVector r(sv1.N);

  for (size_t i = 0; i < sv1.size; ++i) {
    r[i] = sv1.values[i] + sv2.values[i];
  }

  return r;
}

StateVector operator*(const double s, const StateVector& sv1) {
  StateVector r(sv1.N);
  for (size_t i = 0; i < sv1.N; ++i) {
    r[i] = sv1.values[i] * s;
  }

  return r;
}

StateVector operator*(const StateVector& sv1, const double s) {
  StateVector r(sv1.N);

  for (size_t i = 0; i < sv1.size; ++i) {
    r[i] = sv1.values[i] * s;
  }

  return r;
}

StateVector operator/(const StateVector &sv1, const double s) {
  StateVector r(sv1.N);

  for (size_t i = 0; i < sv1.size; ++i) {
    r[i] = sv1.values[i] / s;
  }

  return r;
}

Vector3d StateVector::at(size_t i) {
  return values[i];
}

std::ostream &operator<<(std::ostream &os, const StateVector &sv) {
  os << "[";
  if (sv.size != 0) {
    for (size_t i = 0; i < sv.size - 1; ++i) {
      os << sv.values[i] << ", ";
    };
    os << sv.values[sv.size-1];
  }
  os << "]";

  return os;
}

void StateVector::transferMeshToStateVector(Mesh *mesh) {
  int i = 0;
  for (auto p = mesh->vertex_positions.begin(); p != mesh->vertex_positions.end(); ++p) {
    values[i] = *p;
    ++i;
  }
}
