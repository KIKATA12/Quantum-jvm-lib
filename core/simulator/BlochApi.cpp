#include "BlochApi.h"

void bloch_api_compute_result(QubitState state, BlochTestResult *result) {
  if (!result) {
    return;
  }

  bloch_angles_from_state(state, &result->theta, &result->azimuthal,
                          &result->x, &result->y, &result->z);
}

void bloch_api_compute_vector(QubitState state, BlochVector *out) {
  if (!out) {
    return;
  }

  bloch_vector_from_state(state, out);
}

void bloch_api_compute_density_matrix(QubitState state, std::complex<double> rho[2][2]) {
  bloch_density_matrix_from_state(state, rho);
}
