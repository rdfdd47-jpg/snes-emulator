package com.example.snesemulator;

import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class RomPickerActivity extends AppCompatActivity {
    private static final int PICK_ROM_REQUEST = 1;
    public static final String RESULT_ROM_PATH = "rom_path";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        pickRomFile();
    }

    private void pickRomFile() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        intent.putExtra(Intent.EXTRA_MIME_TYPES, new String[]{"application/octet-stream"});
        startActivityForResult(intent, PICK_ROM_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == PICK_ROM_REQUEST && resultCode == RESULT_OK) {
            if (data != null && data.getData() != null) {
                Uri uri = data.getData();
                String path = getRealPathFromUri(uri);

                if (path != null) {
                    Intent resultIntent = new Intent();
                    resultIntent.putExtra(RESULT_ROM_PATH, path);
                    setResult(RESULT_OK, resultIntent);
                } else {
                    Toast.makeText(this, "Failed to get file path", Toast.LENGTH_SHORT).show();
                    setResult(RESULT_CANCELED);
                }
            }
            finish();
        } else {
            setResult(RESULT_CANCELED);
            finish();
        }
    }

    private String getRealPathFromUri(Uri uri) {
        String result = null;

        if (uri.getScheme().equals("file")) {
            result = uri.getPath();
        } else if (uri.getScheme().equals("content")) {
            Cursor cursor = getContentResolver().query(uri, null, null, null, null);
            if (cursor != null) {
                if (cursor.moveToFirst()) {
                    int index = cursor.getColumnIndex(MediaStore.MediaColumns.DATA);
                    result = cursor.getString(index);
                }
                cursor.close();
            }
        }

        return result;
    }
}
