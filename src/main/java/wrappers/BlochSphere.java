package wrappers;

public class BlochSphere implements AutoCloseable {
  static {
    System.loadLibrary("QubitNative");
  }


  public native double[] computeAngles(double alphaReal, double alphaImag,
                                        double betaReal, double betaImag);

  public native double[] computeVector(double alphaReal, double alphaImag,
                                       double betaReal, double betaImag);

  public native double[] computeDensityMatrix(double alphaReal, double alphaImag,
                                               double betaReal, double betaImag);
  
  @Override
  public void close() {
    // No resources to release in this wrapper class
  }
}
