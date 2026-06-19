package wrappers;

public class Qubit implements AutoCloseable {
 static {
   System.loadLibrary("QubitNative");
 }
  private long nativePtr;
  public Qubit() {
    nativePtr = qubitCreate();
  }
  public void initialize(int state){
    qubitInitialize(nativePtr, state);
  }
  public int measure(){
    return qubitMeasure(nativePtr);
  }
  public void reset(){
    qubitReset(nativePtr);
  }
  @Override
  public void close(){
    if (nativePtr != 0){
      qubitFree(nativePtr);
      nativePtr = 0;
    }
  }
  private native long qubitCreate();
  private native void qubitInitialize(long ptr, int state);
  private native int qubitMeasure(long ptr);
  private native void qubitReset(long ptr);
  private native void qubitFree(long ptr);
}
