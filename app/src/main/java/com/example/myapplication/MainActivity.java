package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'native-lib' library on application startup.

    String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button_1 = (Button) findViewById(R.id.button1);
        button_1.setOnClickListener(this);

        // Example of a call to a native method
        MediaRecorder mMediaRecorder= new MediaRecorder();
        mMediaRecorder.native_init();

        TextView tv1 = findViewById(R.id.sample_text1);
        tv1.setText("调用Native方法printHello： "+ mMediaRecorder.printHello());
        TextView tv2 = findViewById(R.id.sample_text2);
        tv2.setText("调用Native方法printString： "+ mMediaRecorder.printString("xiaoma!!"));
    }


    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.button1) {
            JniFuncTest mJniFuncTest = new JniFuncTest();
            mJniFuncTest.testOnce();
        }
    }
}