package com.example.myapplication;

public class JniArrayTest {
    static int int_array[] = new int[] { 1, 2, 3, 4, 5 };
    static String string_array[] = new String[] { "we", "are", "friends" };

    static {
        System.loadLibrary("native-lib");
    }

    public native int[] intArray(int[] num);
    public native boolean stringArray(String[] str);

}
