#pragma once

#include "blochSphere.h"

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> Complex;
#else
#include <complex.h>
typedef double complex Complex;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct BlochTestResult
  {
    double theta;
    double azimuthal;
    double x;
    double y;
    double z;
  } BlochTestResult;

  void bloch_api_compute_result(QubitState state, BlochTestResult *result);
  void bloch_api_compute_vector(QubitState state, BlochVector *out);
  void bloch_api_compute_density_matrix(QubitState state, Complex rho[2][2]);

#ifdef __cplusplus
}
#endif

