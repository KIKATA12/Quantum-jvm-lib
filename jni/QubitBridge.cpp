#include <jni.h>
#include "../core/registers/QubitRegistry.h"

static QubitRegistry registry;
extern "C" {
  JNIEXPORT jlong JNICALL
  Java_wrappers_Qubit_createQubit(JNIEnv* env, jobject obj, jint state){
    return registry.createQubit(state);
  }
  
  JNIEXPORT jint JNICALL
  Java_wrappers_Qubit_measureQubit(JNIEnv* env, jobject obj, jint id){
    return registry.measureQubit(id);
  }
  
  JNIEXPORT void JNICALL
  Java_wrappers_Qubit_resetQubit(JNIEnv* env,jobject obj, jint id){
    registry.resetQubit(id);
  }
  
  JNIEXPORT void JNICALL
  Java_wrappers_Qubit_releaseQubit(JNIEnv* env, jobject obj, jint id){
    registry.releaseQubit(id);
  }
}
