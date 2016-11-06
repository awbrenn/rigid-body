//
// Created by awbrenn on 11/2/16.
//

#include "StateVector.h"

StateVector::StateVector() {
  x = Vector3d(0.0, 0.0, 0.0);
  q = Quaternion(0.0, 0.0, 0.0);
  P = Vector3d(0.0, 0.0, 0.0);
  L = Vector3d(0.0, 0.0, 0.0);
}


StateVector::StateVector(Vector3d _x, Quaternion _q, Vector3d _P, Vector3d _L) {
  x = _x;
  q = _q;
  P = _P;
  L = _L;
}


StateVector operator-(const StateVector &sv1, const StateVector &sv2) {
  StateVector r;

  r.x = sv1.x - sv2.x;
  r.q = sv1.q - sv2.q;
  r.P = sv1.P - sv2.P;
  r.L = sv1.L - sv2.L;

  return r;
}

StateVector operator+(const StateVector &sv1, const StateVector &sv2) {
  StateVector r;

  r.x = sv1.x + sv2.x;
  r.q = sv1.q + sv2.q;
  r.P = sv1.P + sv2.P;
  r.L = sv1.L + sv2.L;

  return r;
}

StateVector operator*(const StateVector &sv1, const StateVector &sv2) {
  StateVector r;

  r.x = sv1.x * sv2.x;
  r.q = sv1.q * sv2.q;
  r.P = sv1.P * sv2.P;
  r.L = sv1.L * sv2.L;

  return r;
}

StateVector operator*(const double s, const StateVector& sv1) {
  StateVector r;

  r.x = s * sv1.x;
  r.q = s * sv1.q;
  r.P = s * sv1.P;
  r.L = s * sv1.L;

  return r;
}

StateVector operator*(const StateVector& sv1, const double s) {
  StateVector r;

  r.x = sv1.x * s;
  r.q = sv1.q * s;
  r.P = sv1.P * s;
  r.L = sv1.L * s;

  return r;
}

StateVector operator/(const StateVector &sv1, const double s) {
  StateVector r;

  r.x = sv1.x / s;
  r.q = sv1.q / s;
  r.P = sv1.P / s;
  r.L = sv1.L / s;

  return r;
}


std::ostream &operator<<(std::ostream &os, const StateVector &sv) {
  os << "x(" << sv.x << ") q(" << sv.q << ") P(" << sv.P << ") L(" << sv.L << ")";
  return os;
}