package com.example.snesemulator;

public class SNESEmulator {
    static {
        System.loadLibrary("snes-core");
    }

    private boolean isRunning = false;

    public native boolean loadROM(String path);
    public native void unloadROM();
    public native void run();
    public native void pause();
    public native void reset();
    public native void renderFrame(int[] frameBuffer);
    public native void handleInput(int button, boolean pressed);

    public boolean isRunning() {
        return isRunning;
    }

    public void update() {
        // This is called from the render thread
        if (isRunning) {
            // Emulation step happens in native code
        }
    }
}
