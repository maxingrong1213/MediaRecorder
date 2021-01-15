package com.example.myapplication;

import android.util.Log;

public class JniFuncTest {
    private static int staticIntField = 300;
    byte[] buffer = new byte[]{1,2,3,-4,5,6,7,8,9,0};
    static {
        System.loadLibrary("native-lib");
    }
    public static native JniTest createJniObject();
    public native String transform(byte[] buf,int len);
    public void testOnce(){
        Log.d("TAG","[Java] createJniObject()调用本地方法");
        JniTest jniObj = createJniObject();
        // 调用JniTest对象的方法
        jniObj.callTest();

        Log.d("MXR","buffer长度为："+ buffer.length);
        transform(buffer,buffer.length);
    }

}
