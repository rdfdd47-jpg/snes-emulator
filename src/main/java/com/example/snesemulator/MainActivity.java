package com.example.snesemulator;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private static final int PERMISSION_READ_EXTERNAL = 1;
    private static final int PICK_ROM_REQUEST = 2;
    
    private SNESEmulatorView emulatorView;
    private SNESEmulator emulator;
    private Button playButton, pauseButton, resetButton, loadButton;
    private ImageButton dpadUp, dpadDown, dpadLeft, dpadRight;
    private ImageButton buttonA, buttonB, buttonX, buttonY;
    private ImageButton buttonL, buttonR, buttonStart, buttonSelect;

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

        // Set up emulator view
        emulatorView = findViewById(R.id.emulator_view);
        emulatorView.setEmulator(emulator);

        // Set up buttons
        playButton = findViewById(R.id.btn_play);
        pauseButton = findViewById(R.id.btn_pause);
        resetButton = findViewById(R.id.btn_reset);
        loadButton = findViewById(R.id.btn_load_rom);

        playButton.setOnClickListener(v -> emulator.run());
        pauseButton.setOnClickListener(v -> emulator.pause());
        resetButton.setOnClickListener(v -> emulator.reset());
        loadButton.setOnClickListener(v -> openRomPicker());

        // Initialize game pad buttons (if they exist in layout)
        setupGamepadButtons();
    }

    private void setupGamepadButtons() {
        // D-Pad
        try {
            dpadUp = findViewById(R.id.btn_dpad_up);
            dpadDown = findViewById(R.id.btn_dpad_down);
            dpadLeft = findViewById(R.id.btn_dpad_left);
            dpadRight = findViewById(R.id.btn_dpad_right);

            if (dpadUp != null) {
                dpadUp.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_UP, event));
                dpadDown.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_DOWN, event));
                dpadLeft.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_LEFT, event));
                dpadRight.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_RIGHT, event));
            }

            // Action buttons
            buttonA = findViewById(R.id.btn_a);
            buttonB = findViewById(R.id.btn_b);
            buttonX = findViewById(R.id.btn_x);
            buttonY = findViewById(R.id.btn_y);
            buttonL = findViewById(R.id.btn_l);
            buttonR = findViewById(R.id.btn_r);
            buttonStart = findViewById(R.id.btn_start);
            buttonSelect = findViewById(R.id.btn_select);

            if (buttonA != null) {
                buttonA.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_A, event));
                buttonB.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_B, event));
                buttonX.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_X, event));
                buttonY.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_Y, event));
                buttonL.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_L, event));
                buttonR.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_R, event));
                buttonStart.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_START, event));
                buttonSelect.setOnTouchListener((v, event) -> handleButtonPress(InputConstants.BUTTON_SELECT, event));
            }
        } catch (Exception e) {
            // Gamepad buttons not in layout yet - that's fine
        }
    }

    private boolean handleButtonPress(int button, android.view.MotionEvent event) {
        if (event.getAction() == android.view.MotionEvent.ACTION_DOWN) {
            emulator.handleInput(button, true);
            return true;
        } else if (event.getAction() == android.view.MotionEvent.ACTION_UP) {
            emulator.handleInput(button, false);
            return true;
        }
        return false;
    }

    private void openRomPicker() {
        Intent intent = new Intent(this, RomPickerActivity.class);
        startActivityForResult(intent, PICK_ROM_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == PICK_ROM_REQUEST && resultCode == RESULT_OK) {
            if (data != null && data.hasExtra(RomPickerActivity.RESULT_ROM_PATH)) {
                String romPath = data.getStringExtra(RomPickerActivity.RESULT_ROM_PATH);
                loadRom(romPath);
            }
        }
    }

    private void loadRom(String romPath) {
        if (emulator.loadROM(romPath)) {
            Toast.makeText(this, "ROM loaded: " + romPath, Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Failed to load ROM", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (emulator != null) {
            emulator.pause();
        }
    }
}
