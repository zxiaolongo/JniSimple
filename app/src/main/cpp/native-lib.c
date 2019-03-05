#include<stdio.h>
#include<stdlib.h>
#include <jni.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
/**
   1.实现本地方法格式:先写返回值类型 + Java+ 要实现的本地方法所在的完整包名+类名+方法名
   2.方法名写好后 必须要加上2个参数

   3.  JNINativeInterface** env   struct JNINativeInterface 总结env是JNINativeInterface二级指针
     int i = 10;
     int* p = &i;
     int** q = &p;
     **q
     (*NewStringUTF)(JNIEnv*, const char*);
**/


jstring Java_com_demo_zxl_user_jnisimple_MainActivity_stringFromJNI(JNIEnv* env,jobject thiz ){
    // return  (**env).NewStringUTF(env,"hello java");
    return (*env)->NewStringUTF(env,"hello java");
}
JNIEXPORT void JNICALL Java_com_demo_zxl_user_jnisimple_MainActivity_unInstall
        (JNIEnv *env, jobject jobject1){
       //1.执行fork 分叉函数  当code>0
       int code = fork();
       if(code >0){
           LOGD("father==%d",code);
       }else if(code == 0){
           LOGD("child==%d",code);

          //系统会帮助创建一个子进程 并且拥有父进程的数据  怎么知道应用程序被卸载了呢
            //2.不停的监视
            int isStop =  1;
            while(isStop){
                sleep(200);//需要准备时间所以睡一下(下面的函数)
                //参数1 操作的目录  参数2
               FILE* file = fopen("/data/data/com.demo.zxl.user.jnisimple","r");
                   if (file == NULL){
                   //3.打开系统的浏览器
                   execlp("am", "am", "start", "--user","0","-a", "android.intent.action.VIEW", "-d", "http://www.itheima.com", (char *) NULL);
               }

            }
       }else{
           LOGD("error");
       }
}
