package wrappers;

public class BlochSphere {
  static {
    System.loadLibrary("QubitNative");
  }

  public native double[] computeAngles(double alphaReal, double alphaImag,
                                        double betaReal, double betaImag);

  public native double[] computeVector(double alphaReal, double alphaImag,
                                       double betaReal, double betaImag);

  public native double[] computeDensityMatrix(double alphaReal, double alphaImag,
                                               double betaReal, double betaImag);
}
