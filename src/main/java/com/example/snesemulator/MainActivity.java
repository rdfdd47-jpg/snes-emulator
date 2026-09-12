package com.example.snesemulator;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private static final int PERMISSION_READ_EXTERNAL = 1;
    private SNESEmulatorView emulatorView;
    private SNESEmulator emulator;
    private Button playButton, pauseButton, resetButton, loadButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Check permissions
        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},
                    PERMISSION_READ_EXTERNAL);
        }

        // Initialize emulator
        emulator = new SNESEmulator();

        // Set up UI
        emulatorView = findViewById(R.id.emulator_view);
        emulatorView.setEmulator(emulator);

        playButton = findViewById(R.id.btn_play);
        pauseButton = findViewById(R.id.btn_pause);
        resetButton = findViewById(R.id.btn_reset);
        loadButton = findViewById(R.id.btn_load_rom);

        playButton.setOnClickListener(v -> emulator.run());
        pauseButton.setOnClickListener(v -> emulator.pause());
        resetButton.setOnClickListener(v -> emulator.reset());
        loadButton.setOnClickListener(v -> openFilePicker());
    }

    private void openFilePicker() {
        // TODO: Implement file picker for ROM selection
        Toast.makeText(this, "File picker not yet implemented", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (emulator != null) {
            emulator.pause();
        }
    }
}
