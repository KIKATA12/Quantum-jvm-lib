#include <jni.h>
#include "../core/simulator/BlochApi.h"

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> Complex;
#else
#include <complex.h>
typedef double complex Complex;
#endif

extern "C" {
JNIEXPORT jdoubleArray JNICALL
Java_wrappers_BlochSphere_computeAngles(JNIEnv *env, jobject obj,
                                        jdouble alphaReal, jdouble alphaImag,
                                        jdouble betaReal, jdouble betaImag) {
  QubitState state = {Complex(alphaReal, alphaImag), Complex(betaReal, betaImag)};
  BlochTestResult result{};
  bloch_api_compute_result(state, &result);

  jdouble values[5] = {result.theta, result.azimuthal, result.x, result.y, result.z};
  jdoubleArray out = env->NewDoubleArray(5);
  if (!out) {
    return nullptr;
  }
  env->SetDoubleArrayRegion(out, 0, 5, values);
  return out;
}

JNIEXPORT jdoubleArray JNICALL
Java_wrappers_BlochSphere_computeVector(JNIEnv *env, jobject obj,
                                         jdouble alphaReal, jdouble alphaImag,
                                         jdouble betaReal, jdouble betaImag) {
  QubitState state = {Complex(alphaReal, alphaImag), Complex(betaReal, betaImag)};
  BlochVector vector{};
  bloch_api_compute_vector(state, &vector);

  jdouble values[3] = {vector.x, vector.y, vector.z};
  jdoubleArray out = env->NewDoubleArray(3);
  if (!out) {
    return nullptr;
  }
  env->SetDoubleArrayRegion(out, 0, 3, values);
  return out;
}

JNIEXPORT jdoubleArray JNICALL
Java_wrappers_BlochSphere_computeDensityMatrix(JNIEnv *env, jobject obj,
                                               jdouble alphaReal, jdouble alphaImag,
                                               jdouble betaReal, jdouble betaImag) {                                          
  QubitState state = {Complex(alphaReal, alphaImag), Complex(betaReal, betaImag)};
  Complex rho[2][2] = {{Complex(0.0 ,0.0), Complex(0.0,0.0)},
                       {Complex(0.0,0.0), Complex(0.0,0.0 )}};
  bloch_api_compute_density_matrix(state, rho);

  jdouble values[8] = {rho[0][0].real() , rho[0][0].imag(),
                       rho[0][1].real(), rho[0][1].imag(),
                       rho[1][0].real(), rho[1][0].imag(),
                       rho[1][1].real(), rho[1][1].imag()};
  jdoubleArray out = env->NewDoubleArray(8);
  if (!out) {
    return nullptr;
  }
  env->SetDoubleArrayRegion(out, 0, 8, values);
  return out;
}
}
