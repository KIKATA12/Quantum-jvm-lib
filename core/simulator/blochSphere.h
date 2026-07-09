#pragma once

#include <complex.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct BlochVector
  {
    double x;
    double y;
    double z;
  } BlochVector;

  typedef struct QubitState
  {
    double complex alpha;
    double complex beta;
  } QubitState;

  /**
   * Compute Bloch sphere angles and coordinates from a qubit state.
   *
   * The input state is |ψ⟩ = α|0⟩ + β|1⟩. The function normalizes the state
   * if needed, then computes:
   *   θ = 2 acos(|α|)
   *   φ = arg(β) - arg(α)
   *   x = sin θ cos φ
   *   y = sin θ sin φ
   *   z = cos θ
   */
  void bloch_angles_from_state(QubitState state, double *theta, 
                                                 double *azimuthal, 
                                                 double *x, 
                                                 double *y, 
                                                 double *z);

  /**
   * Compute the Bloch vector from a qubit state.
   */
  void bloch_vector_from_state(QubitState state,
                               BlochVector *out);

  /**
   * Compute the density matrix for a pure qubit state |ψ⟩ = α|0⟩ + β|1⟩.
   * The result is a 2x2 matrix:
   *   ρ = |ψ⟩⟨ψ|.
   */
  void bloch_density_matrix_from_state(QubitState state,
                                       double complex rho[2][2]);

  /**
   * Compute the density matrix directly from a Bloch vector.
   * This supports mixed-state density matrices via:
   *   ρ = 1/2 (I + x σ_x + y σ_y + z σ_z)
   */
  void bloch_density_matrix_from_vector(double x,
                                        double y,
                                        double z,
                                        double complex rho[2][2]);

#ifdef __cplusplus
}
#endif
