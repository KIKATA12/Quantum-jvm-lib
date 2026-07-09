#include "blochSphere.h"
#include <complex.h>
#include <math.h>
#include <stddef.h>

static QubitState normalize_state(QubitState state) {
  double norm = cabs(state.alpha) * cabs(state.alpha) + cabs(state.beta) * cabs(state.beta);
  if (norm <= 0.0) {
    return (QubitState){1.0 + 0.0*I, 0.0 + 0.0*I};
  }
  if (fabs(norm - 1.0) > 1e-12) {
    double inv = 1.0 / sqrt(norm);
    return (QubitState){state.alpha * inv, state.beta * inv};
  }
  return state;
}

void bloch_angles_from_state(QubitState state, 
                             double* theta,
                             double* azimuthal,
                             double* x,
                             double* y,
                             double* z) {
  if (!theta && !azimuthal && !x && !y && !z) {
    return;
  }

  QubitState normalized = normalize_state(state);
  double alpha_abs = cabs(normalized.alpha);
  if (alpha_abs > 1.0) {
    alpha_abs = 1.0;
  }

  double theta_val = 2.0 * acos(alpha_abs);
  double arg_alpha = carg(normalized.alpha);
  double arg_beta = carg(normalized.beta);
  double phi_val = arg_beta - arg_alpha;
  double sin_theta = sin(theta_val);

  if (theta) *theta = theta_val;
  if (azimuthal) *azimuthal = phi_val;
  if (x) *x = sin_theta * cos(phi_val);
  if (y) *y = sin_theta * sin(phi_val);
  if (z) *z = cos(theta_val);
}

void bloch_vector_from_state(QubitState state,
                             BlochVector* out) {
  if (!out) {
    return;
  }
  bloch_angles_from_state(state, NULL, NULL, &out->x, &out->y, &out->z);
}

void bloch_density_matrix_from_state(QubitState state,
                                     double complex rho[2][2]) {
  if (!rho) {
    return;
  }

  QubitState normalized = normalize_state(state);
  rho[0][0] = normalized.alpha * conj(normalized.alpha);
  rho[0][1] = normalized.alpha * conj(normalized.beta);
  rho[1][0] = normalized.beta * conj(normalized.alpha);
  rho[1][1] = normalized.beta * conj(normalized.beta);
}

void bloch_density_matrix_from_vector(double x,
                                      double y,
                                      double z,
                                      double complex rho[2][2]) {
  if (!rho) {
    return;
  }

  rho[0][0] = 0.5 * (1.0 + z);
  rho[0][1] = 0.5 * (x - I * y);
  rho[1][0] = 0.5 * (x + I * y);
  rho[1][1] = 0.5 * (1.0 - z);
}
