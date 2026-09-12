#include <jni.h>
#include <memory>
#include <string>
#include "include/snes_emulator.h"
#include <android/log.h>

#define TAG "SNESEmulator-JNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

static std::unique_ptr<SNESEmulator> g_emulator = nullptr;

extern "C" {

// Called when the library is first loaded
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad called");
    g_emulator = std::make_unique<SNESEmulator>();
    return JNI_VERSION_1_6;
}

// Called when the library is unloaded
void JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnUnload called");
    g_emulator = nullptr;
}

// Java: public native boolean loadROM(String path);
JNIEXPORT jboolean JNICALL
Java_com_example_snesemulator_SNESEmulator_loadROM(
        JNIEnv* env, jobject obj, jstring romPath) {
    if (!g_emulator) {
        LOGE("Emulator not initialized");
        return JNI_FALSE;
    }

    const char* path = env->GetStringUTFChars(romPath, nullptr);
    bool result = g_emulator->loadROM(path);
    env->ReleaseStringUTFChars(romPath, path);

    if (result) {
        LOGI("ROM loaded successfully");
    } else {
        LOGE("Failed to load ROM");
    }

    return result ? JNI_TRUE : JNI_FALSE;
}

// Java: public native void unloadROM();
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_unloadROM(
        JNIEnv* env, jobject obj) {
    if (g_emulator) {
        g_emulator->unloadROM();
        LOGI("ROM unloaded");
    }
}

// Java: public native void run();
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_run(
        JNIEnv* env, jobject obj) {
    if (g_emulator) {
        g_emulator->run();
        LOGI("Emulation started");
    }
}

// Java: public native void pause();
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_pause(
        JNIEnv* env, jobject obj) {
    if (g_emulator) {
        g_emulator->pause();
        LOGI("Emulation paused");
    }
}

// Java: public native void reset();
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_reset(
        JNIEnv* env, jobject obj) {
    if (g_emulator) {
        g_emulator->reset();
        LOGI("Emulator reset");
    }
}

// Java: public native void renderFrame(int[] frameBuffer);
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_renderFrame(
        JNIEnv* env, jobject obj, jintArray frameBuffer) {
    if (!g_emulator) return;

    jint* buffer = env->GetIntArrayElements(frameBuffer, nullptr);
    jsize length = env->GetArrayLength(frameBuffer);

    if (buffer && length >= 256 * 224) {
        g_emulator->renderFrame((uint32_t*)buffer, 256, 224);
    }

    env->ReleaseIntArrayElements(frameBuffer, buffer, 0);
}

// Java: public native void handleInput(int button, boolean pressed);
JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_handleInput(
        JNIEnv* env, jobject obj, jint button, jboolean pressed) {
    if (g_emulator) {
        g_emulator->handleInput((uint32_t)button, pressed == JNI_TRUE);
    }
}

} // extern "C"
