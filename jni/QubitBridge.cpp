#include <jni.h>
#include "../core/qubit/Qubit.h"

extern "C" JNIEXPORT jlong JNICALL
Java_wrappers_Qubit_qubitMeasure(JNIEnv* env, jobject obj){
  Qubit* q = new Qubit();
  return reinterpret_cast<jlong>(q);
}

extern "C" JNIEXPORT void JNICALL
Java_wrappers_Qubit_qubitInitialize(JNIEnv* env, jobject obj, jlong ptr, jint state){
  Qubit* q = reinterpret_cast<Qubit*>(ptr);
  q->initialize(state);
}

extern "C" JNIEXPORT jint JNICALL
Java_wrappers_Qubit_qubitMeasure(JNIEnv* env, jobject obj, jlong ptr){
  Qubit* q = reinterpret_cast<Qubit*>(ptr);
  return q->measure();
}

extern "C" JNIEXPORT void JNICALL
Java_wrappers_Qubit_qubitReset(JNIEnv* env,jobject obj, jlong ptr){
  Qubit* q = reinterpret_cast<Qubit*>(ptr);
  q->reset();
}

extern "C" JNIEXPORT void JNICALL
Java_wrappers_Qubit_qubitFree(JNIEnv* env, jobject obj, jlong ptr){
  Qubit* q = reinterpret_cast<Qubit*>(ptr);
  delete q;
}
