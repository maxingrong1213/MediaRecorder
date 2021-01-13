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
    // 这些全部是本地引用
    jclass targetClass;
    jmethodID mid;
    jobject newObject;
    jstring helloStr;
    jfieldID fid;
    jint staticIntField;
    jint result;

    // 获取JniFuncTest类的staticIntField变量的ID；
    fid = env->GetStaticFieldID(clazz,"staticIntField","I");
    // 读取jclass与jfieldID指定的成员变量值；
    staticIntField = env->GetStaticIntField(clazz,fid);
    LOGD("获取JniFuncTest类的staticIntField值:JniFuncTest.staticIntField = %d\n",staticIntField);


    // 查找生成对象的类
    targetClass = env->FindClass("com/example/myapplication/JniTest");
    // 查找构造方法
    mid = env->GetMethodID(targetClass,"<init>", "(I)V");
    // 生成JniTest对象（返回对象的引用）
    LOGD("JniTest对象生成\n");
    newObject = env->NewObject(targetClass,mid,100);


    // 调用对象的方法
    mid = env->GetMethodID(targetClass,"callByNative", "(I)I");
    result = env->CallIntMethod(newObject,mid,200);

    //设置JniObject对象的intField值
    fid = env->GetFieldID(targetClass,"intField", "I");
    LOGD("设置JniTest对象的intField值为200\n");
    env->SetIntField(newObject,fid,result);

    // 返回对象的引用
    return newObject;
}

