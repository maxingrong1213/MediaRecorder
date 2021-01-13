package com.example.myapplication;

import android.util.Log;

public class JniFuncTest {
    private static int staticIntField = 300;
    static {
        System.loadLibrary("native-lib");
    }
    public static native JniTest createJniObject();

    public void testOnce(){
        Log.d("TAG","[Java] createJniObject()调用本地方法");
        JniTest jniObj = createJniObject();
        // 调用JniTest对象的方法
        jniObj.callTest();
    }

}
