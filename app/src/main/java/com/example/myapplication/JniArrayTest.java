package com.example.myapplication;

public class JniArrayTest {
    static boolean boolean_array[] = new boolean[] {true,false,true,false,true};
    static byte byte_array[] = new byte[] {1,2,3,4,5};
    static char char_array[] = new char[] {'a','b','c','d','e'};
    static short short_array[] = new short[] { 1, 2, 3, 4, 5 };
    static int int_array[] = new int[] { 1, 2, 3, 4, 5 };
    static long long_array[] = new long[] { 11, 12, 13, 14, 15 };
    static float float_array[] = new float[] { 1.1f, 1.2f, 1.3f, 1.4f, 1.5f };
    static double double_array[] = new double[] { 1.1, 1.2, 1.3, 1.4, 1.5 };

    static String string_array[] = new String[] { "we", "are", "family" };

    static {
        System.loadLibrary("native-lib");
    }

    public native boolean[] booleanArray(boolean[] num);
    public native byte[] byteArray(byte[] num);
    public native char[] charArray(char[] num);
    public native short[] shortArray(short[] num);
    public native int[] intArray(int[] num);
    public native long[] longArray(long[] num);
    public native float[] floatArray(float[] num);
    public native double[] doubleArray(double[] num);

    public native boolean stringArray(String[] str);
}
