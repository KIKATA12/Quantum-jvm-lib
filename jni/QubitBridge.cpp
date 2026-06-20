#include <jni.h>
#include "../core/registers/QubitRegistry.h"

static QubitRegistry registry;
extern "C" {
  JNIEXPORT jlong JNICALL
  Java_wrappers_Qubit_qubitCreate(JNIEnv* env, jobject obj, jint state){
    return registry.createQubit(state);
  }
  
  JNIEXPORT jint JNICALL
  Java_wrappers_Qubit_qubitMeasure(JNIEnv* env, jobject obj, jint id){
    return registry.measureQubit(id);
  }
  
  JNIEXPORT void JNICALL
  Java_wrappers_Qubit_qubitReset(JNIEnv* env,jobject obj, jint id){
    registry.resetQubit(id);
  }
  
  JNIEXPORT void JNICALL
  Java_wrappers_Qubit_qubitRelease(JNIEnv* env, jobject obj, jint id){
    registry.releaseQubit(id);
  }
}
