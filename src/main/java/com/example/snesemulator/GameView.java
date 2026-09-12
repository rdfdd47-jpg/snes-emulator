package com.example.snesemulator;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.View;

public class GameView extends View {
    private SNESEmulator emulator;
    private long emulatorInstance;
    private Bitmap framebuffer;
    private int[] pixelData;

    public GameView(Context context, long emulatorInstance, SNESEmulator emulator) {
        super(context);
        this.emulatorInstance = emulatorInstance;
        this.emulator = emulator;
        this.framebuffer = Bitmap.createBitmap(256, 224, Bitmap.Config.ARGB_8888);
        this.pixelData = new int[256 * 224];
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        // Get framebuffer from emulator
        pixelData = emulator.getFramebuffer(emulatorInstance);
        if (pixelData != null) {
            framebuffer.setPixels(pixelData, 0, 256, 0, 0, 256, 224);
            canvas.drawBitmap(framebuffer, 0, 0, null);
        }

        // Request next frame
        invalidate();
    }
}
