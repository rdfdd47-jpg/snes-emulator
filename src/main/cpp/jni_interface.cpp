#include <jni.h>
#include "include/emulator.h"

static Emulator* g_emulator = nullptr;

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_example_snesemulator_SNESEmulator_createEmulator(JNIEnv* env, jobject obj) {
    if (g_emulator == nullptr) {
        g_emulator = new Emulator();
        g_emulator->init();
    }
    return reinterpret_cast<jlong>(g_emulator);
}

JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_destroyEmulator(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator != 0) {
        Emulator* emu = reinterpret_cast<Emulator*>(emulator);
        delete emu;
        if (emu == g_emulator) {
            g_emulator = nullptr;
        }
    }
}

JNIEXPORT jboolean JNICALL
Java_com_example_snesemulator_SNESEmulator_loadROM(JNIEnv* env, jobject obj, jlong emulator,
                                                     jbyteArray romData) {
    if (emulator == 0) {
        return JNI_FALSE;
    }

    Emulator* emu = reinterpret_cast<Emulator*>(emulator);
    jbyte* data = env->GetByteArrayElements(romData, nullptr);
    jsize size = env->GetArrayLength(romData);

    bool result = emu->loadROM(reinterpret_cast<uint8_t*>(data), size);

    env->ReleaseByteArrayElements(romData, data, JNI_ABORT);
    return result ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_runFrame(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator != 0) {
        Emulator* emu = reinterpret_cast<Emulator*>(emulator);
        emu->runFrame();
    }
}

JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_pause(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator != 0) {
        Emulator* emu = reinterpret_cast<Emulator*>(emulator);
        emu->pause();
    }
}

JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_resume(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator != 0) {
        Emulator* emu = reinterpret_cast<Emulator*>(emulator);
        emu->resume();
    }
}

JNIEXPORT void JNICALL
Java_com_example_snesemulator_SNESEmulator_reset(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator != 0) {
        Emulator* emu = reinterpret_cast<Emulator*>(emulator);
        emu->reset();
    }
}

JNIEXPORT jintArray JNICALL
Java_com_example_snesemulator_SNESEmulator_getFramebuffer(JNIEnv* env, jobject obj, jlong emulator) {
    if (emulator == 0) {
        return nullptr;
    }

    Emulator* emu = reinterpret_cast<Emulator*>(emulator);
    const uint32_t* fb = emu->getFramebuffer();

    jintArray result = env->NewIntArray(256 * 224);
    env->SetIntArrayRegion(result, 0, 256 * 224, (const jint*)fb);

    return result;
}

}
