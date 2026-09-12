package com.example.snesemulator;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.core.view.GestureDetectorCompat;

public class SNESEmulatorView extends SurfaceView implements SurfaceHolder.Callback, Runnable {
    private static final int WIDTH = 256;
    private static final int HEIGHT = 224;
    private static final int FPS = 60;

    private SNESEmulator emulator;
    private Thread renderThread;
    private boolean running = false;
    private Bitmap frameBitmap;
    private int[] frameBuffer;
    private GestureDetectorCompat gestureDetector;

    public SNESEmulatorView(Context context) {
        super(context);
        init();
    }

    public SNESEmulatorView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        frameBitmap = Bitmap.createBitmap(WIDTH, HEIGHT, Bitmap.Config.ARGB_8888);
        frameBuffer = new int[WIDTH * HEIGHT];
        gestureDetector = new GestureDetectorCompat(getContext(), new GestureDetector.SimpleOnGestureListener());
    }

    public void setEmulator(SNESEmulator emulator) {
        this.emulator = emulator;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        running = true;
        renderThread = new Thread(this);
        renderThread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        running = false;
        try {
            renderThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        long frameTime = 1000 / FPS;
        while (running) {
            long startTime = System.currentTimeMillis();

            if (emulator != null) {
                emulator.update();
                emulator.renderFrame(frameBuffer);
            }

            drawFrame();

            long elapsed = System.currentTimeMillis() - startTime;
            long delay = frameTime - elapsed;
            if (delay > 0) {
                try {
                    Thread.sleep(delay);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private void drawFrame() {
        SurfaceHolder holder = getHolder();
        Canvas canvas = null;
        try {
            canvas = holder.lockCanvas();
            if (canvas != null) {
                frameBitmap.setPixels(frameBuffer, 0, WIDTH, 0, 0, WIDTH, HEIGHT);
                float scaleX = (float) getWidth() / WIDTH;
                float scaleY = (float) getHeight() / HEIGHT;
                canvas.scale(scaleX, scaleY);
                canvas.drawBitmap(frameBitmap, 0, 0, null);
            }
        } finally {
            if (canvas != null) {
                holder.unlockCanvasAndPost(canvas);
            }
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }
}
