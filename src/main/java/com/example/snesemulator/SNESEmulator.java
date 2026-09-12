package com.example.snesemulator;

public class SNESEmulator {
    static {
        System.loadLibrary("snes-emulator-native");
    }

    // JNI methods
    public native long createEmulator();
    public native void destroyEmulator(long emulator);
    public native boolean loadROM(long emulator, byte[] romData);
    public native void runFrame(long emulator);
    public native void pause(long emulator);
    public native void resume(long emulator);
    public native void reset(long emulator);
    public native int[] getFramebuffer(long emulator);
}
