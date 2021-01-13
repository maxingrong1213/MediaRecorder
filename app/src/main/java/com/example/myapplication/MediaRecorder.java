package com.example.myapplication;

public class MediaRecorder {
    static {
        System.loadLibrary("native-lib");
        native_init();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native final void native_init();
    public native void start() throws IllegalStateException;
    public native String printHello();
    public native String printString(String str);
}
