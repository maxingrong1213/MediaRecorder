package com.example.myapplication;

public class JniStringTest {

    static String str = new String("just a test!");
    static {
        System.loadLibrary("native-lib");
    }

    public native String  teststring(String str);
}
