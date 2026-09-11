package com.termux.app.activities;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import com.termux.R;

public final class AboutActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about_pro);
        
        findViewById(R.id.about_back_button).setOnClickListener(v -> finish());
    }
}
