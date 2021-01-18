#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "JNI-JNI"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

extern "C"
jstring CStr2Jstring( JNIEnv* env, const char* pat )
{
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取java String类方法String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray((jsize)strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
    //设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("utf-8");
    //将byte数组转换为java String,并输出
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MediaRecorder_start(JNIEnv *env, jobject thiz) {
    // TODO: implement start()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MediaRecorder_native_1init(JNIEnv *env, jclass clazz) {
    // TODO: implement native_init()
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MediaRecorder_printHello(JNIEnv *env, jobject thiz) {
    // TODO: implement printHello()
    return CStr2Jstring(env,"Hello World!!!!!");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MediaRecorder_printString(JNIEnv *env, jobject thiz, jstring str) {
    // TODO: implement printString()
    const char *str_c = env->GetStringUTFChars(str,0);
    return CStr2Jstring(env,str_c);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_myapplication_JniFuncTest_createJniObject(JNIEnv *env, jclass clazz) {
    // TODO: implement createJniObject()

    // 获取JniFuncTest类的staticIntField变量的ID；
    jfieldID fid = env->GetStaticFieldID(clazz,"staticIntField","I");
    // 读取jclass与jfieldID指定的成员变量值；
    jint staticIntField = env->GetStaticIntField(clazz,fid);
    LOGD("获取JniFuncTest类的staticIntField值:JniFuncTest.staticIntField = %d\n",staticIntField);


    // 查找生成对象的类
    jclass targetClass = env->FindClass("com/example/myapplication/JniTest");
    // 查找构造方法
    jmethodID mid = env->GetMethodID(targetClass,"<init>", "(I)V");
    // 生成JniTest对象（返回对象的引用）
    LOGD("JniTest对象生成\n");
    jobject newObject = env->NewObject(targetClass,mid,100);


    // 调用对象的方法
    mid = env->GetMethodID(targetClass,"callByNative", "(I)I");
    jint result = env->CallIntMethod(newObject,mid,200);

    //设置JniObject对象的intField值
    fid = env->GetFieldID(targetClass,"intField", "I");
    LOGD("设置JniTest对象的intField值为200\n");
    env->SetIntField(newObject,fid,result);

    // 返回对象的引用
    return newObject;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_JniFuncTest_transform(JNIEnv *env, jobject thiz, jbyteArray buffer,
                                                     jint len) {
    // TODO: implement transform()
    // TODO: implement transform()
    LOGD("jbyteArray buffer的长度是：%d",env->GetArrayLength(buffer));


    int i;
    jbyte recevice[len];
    memset(&recevice,0,len);
    jbyte *buf = env->GetByteArrayElements(buffer,0);
    memcpy(&recevice,buf,len);
    for (i = 0; i < 10; ++i) {
        LOGD("recevice[%d]=%d\n",i, recevice[i]);
        LOGD("sizeif recevice[%d]=%d\n",i, sizeof(recevice[i]));
    }

    u_char *recevice1=(u_char *)recevice;
    for (i = 0; i < 10; ++i) {
        LOGD("recevice1[%d]=%d\n",i, recevice1[i]);
        LOGD("sizeif recevice1[%d]=%d\n",i, sizeof(recevice1[i]));
    }

    return CStr2Jstring(env,"success");

}

extern "C"
JNIEXPORT jbooleanArray JNICALL
Java_com_example_myapplication_JniArrayTest_booleanArray(JNIEnv *env, jobject thiz, jbooleanArray array) {
    // TODO: implement booleanArray()
    jboolean* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetBooleanArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetBooleanArrayRegion()函数将传入的整形数组转存到C/C++层的jboolean arr2[length];
    jboolean arr2[length];
    env->GetBooleanArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewBooleanArray()函数创建jbooleanArray,再利用SetBooleanArrayRegion()为其赋值，最终return到Java层；
    jbooleanArray rtn_jbooleanarray = env->NewBooleanArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetBooleanArrayRegion(rtn_jintarray,0,length,arr1);
    env->SetBooleanArrayRegion(rtn_jbooleanarray,0,length,arr2);

    // 返回至Java层的boolean[]
    return rtn_jbooleanarray;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_myapplication_JniArrayTest_byteArray(JNIEnv *env, jobject thiz, jbyteArray array) {
    // TODO: implement byteArray()
    jbyte* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetByteArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetByteArrayRegion()函数将传入的整形数组转存到C/C++层的jbyte arr2[length];
    jbyte arr2[length];
    env->GetByteArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewByteArray()函数创建jbyteArray,再利用SetByteArrayRegion()为其赋值，最终return到Java层；
    jbyteArray rtn_jbytearray = env->NewByteArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetByteArrayRegion(rtn_jbytearray,0,length,arr1);
    env->SetByteArrayRegion(rtn_jbytearray,0,length,arr2);

    // 返回至Java层的byte[]
    return rtn_jbytearray;
}

extern "C"
JNIEXPORT jcharArray JNICALL
Java_com_example_myapplication_JniArrayTest_charArray(JNIEnv *env, jobject thiz, jcharArray array) {
    // TODO: implement charArray()
    jchar* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetCharArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%c",i,arr1[i]);
    }
    // 利用GetCharArrayRegion()函数将传入的整形数组转存到C/C++层的jchar arr2[length];
    jchar arr2[length];
    env->GetCharArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%c",i,arr2[i]);
    }
    // 在C/C++层中调用NewCharArray()函数创建jcharArray,再利用SetCharArrayRegion()为其赋值，最终return到Java层；
    jcharArray rtn_jchararray = env->NewCharArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetCharArrayRegion(rtn_jchararray,0,length,arr1);
    env->SetCharArrayRegion(rtn_jchararray,0,length,arr2);

    // 返回至Java层的char[]
    return rtn_jchararray;
}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_com_example_myapplication_JniArrayTest_shortArray(JNIEnv *env, jobject thiz, jshortArray array) {
    // TODO: implement shortArray()
    jshort* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetShortArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetShortArrayRegion()函数将传入的整形数组转存到C/C++层的jshort arr2[length];
    jshort arr2[length];
    env->GetShortArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewShortArray()函数创建jcharArray,再利用SetShortArrayRegion()为其赋值，最终return到Java层；
    jshortArray rtn_jshortarray = env->NewShortArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetShortArrayRegion(rtn_jshortarray,0,length,arr1);
    env->SetShortArrayRegion(rtn_jshortarray,0,length,arr2);

    // 返回至Java层的short[]
    return rtn_jshortarray;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_myapplication_JniArrayTest_intArray(JNIEnv *env, jobject thiz, jintArray array) {
    // TODO: implement intArray()
    // 利用GetArrayLength()函数将传入的整形数组转存到C/C++层的jint * arr1
    jint * arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetIntArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetIntArrayRegion()函数将传入的整形数组转存到C/C++层的jint arr2[length];
    jint arr2[length];
    env->GetIntArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewIntArray()函数创建jintArray,再利用SetIntArrayRegion()为其赋值，最终return到Java层；
    jintArray rtn_jintarray = env->NewIntArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetIntArrayRegion(rtn_jintarray,0,length,arr1);
    env->SetIntArrayRegion(rtn_jintarray,0,length,arr2);


    /** 该函数与GetIntArrayElements() 函数可以说是对应的。它完成的功能是释放资源和数据更新。
      * 由于 Java 的垃圾收集具有可能改变内存中对象的位置，如不采取必要措施，被访问的数组指针就可能不再指向正确的存区。因此，对于数组，要么把它钉在固定的存区，
      * 要么把它拷贝至固定的存区，总之在访问它的期间要使数组元素总在原地。作完操作之后，再调用这个函数，解除对它的固定。
      * 另外，在调用这个函数之前，所有更新都没有作用在数组本身上。
      * 第三个参数就是决定更新与否的。
      * 取值 零(0) 时，更新数组并释放所有元素;
      * 取值 JNI_COMMIT(1) 时，更新但不释放所有元素;
      * 取值 JNI_ABORT(2) 时，不作更新但释放所有元素；
      */
    //env->ReleaseIntArrayElements(rtn_jintarray,arr2,0);

    // 返回至Java层的int[]
    return rtn_jintarray;
}

extern "C"
JNIEXPORT jlongArray JNICALL
Java_com_example_myapplication_JniArrayTest_longArray(JNIEnv *env, jobject thiz, jlongArray array) {
    // TODO: implement longArray()
    jlong* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetLongArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetLongArrayRegion()函数将传入的整形数组转存到C/C++层的jlong arr2[length];
    jlong arr2[length];
    env->GetLongArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewLongArray()函数创建jlongArray,再利用SetLongArrayRegion()为其赋值，最终return到Java层；
    jlongArray rtn_jlongarray = env->NewLongArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetLongArrayRegion(rtn_jlongarray,0,length,arr1);
    env->SetLongArrayRegion(rtn_jlongarray,0,length,arr2);

    // 返回至Java层的long[]
    return rtn_jlongarray;
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_com_example_myapplication_JniArrayTest_floatArray(JNIEnv *env, jobject thiz, jfloatArray array) {
    // TODO: implement floatArray()
    jfloat* arr1;
    int length = env->GetArrayLength(array);
    arr1 = env->GetFloatArrayElements(array,JNI_FALSE);
    for(int i=0;i<length;i++) {
        LOGD("arr1[%d]=%d",i,arr1[i]);
    }
    // 利用GetFloatArrayRegion()函数将传入的整形数组转存到C/C++层的jlong arr2[length];
    jfloat arr2[length];
    env->GetFloatArrayRegion(array,0,length,arr2);
    for(int i=0;i<length;i++) {
        LOGD("arr2[%d]=%d",i,arr2[i]);
    }
    // 在C/C++层中调用NewLongArray()函数创建jlongArray,再利用SetLongArrayRegion()为其赋值，最终return到Java层；
    jfloatArray rtn_jfloatarray = env->NewFloatArray(length);
    // 使用arr1或arr2都是可以的；
    //env->SetFloatArrayRegion(rtn_jfloatarray,0,length,arr1);
    env->SetFloatArrayRegion(rtn_jfloatarray,0,length,arr2);

    // 返回至Java层的long[]
    return rtn_jfloatarray;
}

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_example_myapplication_JniArrayTest_doubleArray(JNIEnv *env, jobject thiz, jdoubleArray num) {
    // TODO: implement doubleArray()
}

// 在java中，String[]类型是对象，所以对应C++中的数组为jobjectArray
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_myapplication_JniArrayTest_stringArray(JNIEnv *env, jobject thiz,
                                                        jobjectArray str) {
    // TODO: implement StringArray()
    int length = env->GetArrayLength(str);
    for(int i=0;i<length;i++) {
        jstring obja = (jstring)env->GetObjectArrayElement(str,i);
        const char* chars=env->GetStringUTFChars(obja,NULL);
        LOGD("%s",chars);
    }

    jclass objClass = env->FindClass("java/lang/String");//定义数组中元素类型；
    jobjectArray new_str = env->NewObjectArray(length,objClass,0);//创建一个String类型数组；
    jstring jstr_temp;
    for(int i=0;i<length;i++) {
        jstr_temp = (jstring)env->GetObjectArrayElement(str,i);
        env->SetObjectArrayElement(new_str,i,jstr_temp);
    }
    for(int i=0;i<length;i++) {
        jstring str_1 = (jstring)env->GetObjectArrayElement(new_str,i);
        const char* chars = env->GetStringUTFChars(str_1,NULL);
        LOGD("%s",chars);
    }

    return JNI_TRUE;
}

