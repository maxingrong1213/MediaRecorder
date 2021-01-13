package com.example.myapplication;

import android.util.Log;

public class JniTest {
    private int intField;
    String TAG = "JniTest";
    // 构造方法
    public JniTest(int num){
        intField =num;
        Log.d("TAG","调用JniTest对象构造方法：intField = "+ intField);
    }

    // 此方法由JNI本地函数调用
    public int callByNative(int num) {
        Log.d("TAG","JniTest对象的callByNative ("+ num + ") 调用");
        return num;
    }

    public void callTest(){
        Log.d("TAG","JniTest对象的callTest()方法调用：intField= "+ intField);
    }
}
