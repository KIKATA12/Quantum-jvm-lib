package wrappers;

public class Qubit implements AutoCloseable {
 static {
   System.loadLibrary("QubitNative");
 }
  private int id;
  private boolean active;
  private long nativePtr;
 
  public Qubit(int state) {
    this.id = createQubit(state);
    this.active = true;
  }
  public int measure(){
    return measureQubit(id);
  }
  public void reset(){
    resetQubit(id);
  }
  public void release(){
   if (active) {
     releaseQubit(id);
    active = false;
   }
  }
 
  @Override
  public void close(){
    release();
  }
 
  private native int createQubit(int state);
  private native int measureQubit(int id);
  private native void resetQubit(int id);
  private native void releaseQubit(int id);
}
