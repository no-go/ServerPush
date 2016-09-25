#include <jni.h>
#include <string>
#include <cstdlib>
#include <thread>
#include "lib/UniSocket.hpp"
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL
Java_click_dummer_pushclient_MainActivity_answer(JNIEnv *env, jobject instance) {
    return 43;
}

#ifdef __cplusplus
}
#endif
