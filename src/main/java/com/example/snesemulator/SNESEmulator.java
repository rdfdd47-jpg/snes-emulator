package com.example.snesemulator;

import android.util.Log;

public class SNESEmulator {
    private static final String TAG = "SNESEmulator";

    static {
        try {
            System.loadLibrary("snes-core");
            Log.d(TAG, "Native library loaded successfully");
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "Failed to load native library", e);
        }
    }

    private boolean isRunning = false;
    private boolean isRomLoaded = false;

    public native boolean loadROM(String path);
    public native void unloadROM();
    public native void run();
    public native void pause();
    public native void reset();
    public native void renderFrame(int[] frameBuffer);
    public native void handleInput(int button, boolean pressed);

    @Override
    protected void finalize() throws Throwable {
        try {
            if (isRomLoaded) {
                unloadROM();
            }
        } finally {
            super.finalize();
        }
    }

    public boolean isRunning() {
        return isRunning;
    }

    public boolean isRomLoaded() {
        return isRomLoaded;
    }

    public void setRunning(boolean running) {
        isRunning = running;
    }

    public void setRomLoaded(boolean romLoaded) {
        isRomLoaded = romLoaded;
    }

    public void update() {
        if (isRunning) {
            // Emulation step happens in native code via renderFrame
        }
    }
}
