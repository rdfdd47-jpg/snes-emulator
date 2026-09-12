package com.example.snesemulator;

import android.os.Bundle;
import android.widget.FrameLayout;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private SNESEmulator emulator;
    private GameView gameView;
    private long emulatorInstance;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize emulator
        emulator = new SNESEmulator();
        emulatorInstance = emulator.createEmulator();

        // Create game view
        gameView = new GameView(this, emulatorInstance, emulator);
        FrameLayout container = findViewById(R.id.game_container);
        container.addView(gameView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (emulator != null) {
            emulator.destroyEmulator(emulatorInstance);
        }
    }
}
