package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
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

        Button button_jniarraytest = (Button) findViewById(R.id.button_jniarraytest);
        button_jniarraytest.setOnClickListener(this);

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
        } else if (v.getId() == R.id.button_jniarraytest) {
            JniArrayTest mJniArrayTest = new JniArrayTest();

            boolean [] rtn_boolean = mJniArrayTest.booleanArray(JniArrayTest.boolean_array);
            for(int i=0;i<rtn_boolean.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_boolean[i]="+rtn_boolean[i]);
            }

            byte [] rtn_byte = mJniArrayTest.byteArray(JniArrayTest.byte_array);
            for(int i=0;i<rtn_byte.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_byte[i]="+rtn_byte[i]);
            }

            char [] rtn_char = mJniArrayTest.charArray(JniArrayTest.char_array);
            for(int i=0;i<rtn_char.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_char[i]="+rtn_char[i]);
            }

            short [] rtn_short = mJniArrayTest.shortArray(JniArrayTest.short_array);
            for(int i=0;i<rtn_short.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_short[i]="+rtn_short[i]);
            }

            int [] rtn_int = mJniArrayTest.intArray(JniArrayTest.int_array);
            for(int i=0;i<rtn_int.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_int[i]="+rtn_int[i]);
            }

            long [] rtn_long = mJniArrayTest.longArray(JniArrayTest.long_array);
            for(int i=0;i<rtn_long.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_long[i]="+rtn_long[i]);
            }

            float [] rtn_float = mJniArrayTest.floatArray(JniArrayTest.float_array);
            for(int i=0;i<rtn_float.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_float[i]="+rtn_float[i]);
            }

            double [] rtn_double = mJniArrayTest.doubleArray(JniArrayTest.double_array);
            for(int i=0;i<rtn_double.length;i++) {
                Log.d(TAG,"返回至Java层的rtn_double[i]="+rtn_double[i]);
            }

            mJniArrayTest.stringArray(JniArrayTest.string_array);
        }
    }
}