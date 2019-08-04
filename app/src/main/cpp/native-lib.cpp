#include <jni.h>
#include <string>
#include <vector>
#include <android/log.h>

typedef struct tagJNITestC{
    int intVal;
    float floatVal;
    std::vector<int> vectorInt;
    std::vector<float> vectorFloat;
    std::vector<std::vector<int> > matrixInt;
    std::string strC;
}JNITestC;

enum SkinAnalysisError{
    success = 0,
    error = 1,
    keyInvarid = 2

};



SkinAnalysisError setVariable(JNITestC& _jniTestC){
    _jniTestC.intVal = 123;
    _jniTestC.floatVal = 456.7;
    for(int i=0; i<5; i++){
        _jniTestC.vectorInt.push_back(i*10);
        _jniTestC.vectorFloat.push_back(i*20);
    }
    _jniTestC.matrixInt.assign(25, std::vector<int>(2,0));
    for(int i=0; i<25; i++){
        for(int j=0; j<2; j++){
            _jniTestC.matrixInt[i][j] = i;
        }
    }
    _jniTestC.strC = "THIS IS JNI!";

    return SkinAnalysisError::success;
}


SkinAnalysisError getIntValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, int& out){

    try {
        jfieldID id = env->GetFieldID(clz, key, "I");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        out = env->GetIntField(testClass, id);

    }catch(...){
        env->ExceptionClear();
        return SkinAnalysisError::error;
    }

    return SkinAnalysisError::success;
}

SkinAnalysisError getFloatValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, float &out){

    try {
        jfieldID id = env->GetFieldID(clz, key, "F");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        out = env->GetFloatField(testClass, id);
    }catch(...){
        env->ExceptionClear();
        return SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}


SkinAnalysisError setIntValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key,const int& value){

    try {
        jfieldID id = env->GetFieldID(clz, key, "I");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        env->SetIntField(testClass, id, value);
    }catch(...){
        env->ExceptionClear();
        return SkinAnalysisError::error;

    }
    return SkinAnalysisError::success;
}

SkinAnalysisError setFloatValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key,const float& value){

    try {
        jfieldID id = env->GetFieldID(clz, key, "F");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        env->SetFloatField(testClass, id, value);
    }catch(...){
        env->ExceptionClear();
        return SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}

SkinAnalysisError getStringValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, std::string& out){

    try {
        jfieldID id = env->GetFieldID(clz, key, "Ljava/lang/String;");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        // 文字列を取得
        jstring strJ = (jstring) env->GetObjectField(testClass, id);
        const char *s = env->GetStringUTFChars(strJ, JNI_FALSE);
        out = s;
        env->ReleaseStringUTFChars(strJ, s);
    }catch(...){
        env->ExceptionClear();
        SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;

}

SkinAnalysisError setStringValue(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key,const std::string& str){

    try {
        jfieldID id = env->GetFieldID(clz, key, "Ljava/lang/String;");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        env->SetObjectField(testClass, id, env->NewStringUTF(str.c_str()));
    }catch(...){
        env->ExceptionClear();
        SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}

SkinAnalysisError setIntArray(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, const std::vector<int>& values){

    try {
        jfieldID id = env->GetFieldID(clz, key, "[I");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        jintArray jVec = (jintArray) env->GetObjectField(testClass, id);
        auto bufVec = env->GetIntArrayElements(jVec, nullptr);
        int size = env->GetArrayLength(jVec);

        if (size != values.size()) {
            return SkinAnalysisError::error;
        }

        for (int i = 0; i < size; i++) {
            bufVec[i] = values[i];
        }
        env->ReleaseIntArrayElements(jVec, bufVec, 0);
        env->DeleteLocalRef(jVec);
    }catch(...){
        env->ExceptionClear();
        SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}

SkinAnalysisError setFloatArray(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, const std::vector<float>& values){

    try {
        jfieldID id = env->GetFieldID(clz, key, "[F");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        jfloatArray jVec = (jfloatArray) env->GetObjectField(testClass, id);
        auto bufVec = env->GetFloatArrayElements(jVec, nullptr);

        int size = env->GetArrayLength(jVec);

        if (size != values.size()) {
            return SkinAnalysisError::error;
        }

        for (int i = 0; i < size; i++) {
            bufVec[i] = values[i];
        }
        env->ReleaseFloatArrayElements(jVec, bufVec, 0);
        env->DeleteLocalRef(jVec);
    }catch(...){
        env->ExceptionClear();
        SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}

SkinAnalysisError setIntMatrix(JNIEnv *env, const jobject &testClass, const jclass &clz, const char* key, const std::vector<std::vector<int>> matrix){

    try {
        jfieldID id = env->GetFieldID(clz, key, "[[I");
        if(id == NULL){
            env->ExceptionClear();
            return SkinAnalysisError::keyInvarid;
        }
        jobjectArray jMat = (jobjectArray) env->GetObjectField(testClass, id);
        int row = env->GetArrayLength(jMat);
        if(row != matrix.size()){
            SkinAnalysisError::error;
        }
        for (int i = 0; i < row; i++) {
            jintArray jVec = (jintArray) env->GetObjectArrayElement(jMat, i);
            int col = env->GetArrayLength(jVec);
            auto buffer = env->GetIntArrayElements(jVec, nullptr);
            for (int j = 0; j < col; j++) {
                buffer[j] = matrix[i][j];
            }
            env->ReleaseIntArrayElements(jVec, buffer, 0);
            env->DeleteLocalRef(jVec);
        }
        env->DeleteLocalRef(jMat);
    }catch(...){
        env->ExceptionClear();
        SkinAnalysisError::error;
    }
    return SkinAnalysisError::success;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_jni_1test_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz, jobject testClass) {

    const char* intKey = "intVal";
    const char* floatKey = "floatVal";
    const char* strKey = "str0";
    const char* intArrKey = "intArr";
    const char* floatArrKey = "floatArr";
    const char* intMatKey = "intArr2";
    const char* errorKey = "error";

    JNITestC _jniTestC;
    setVariable(_jniTestC);

    /*** java classを取得 ***/
    jclass clz = env->GetObjectClass(testClass);

    SkinAnalysisError ret;
    /*** class内のint値を取得 ***/
    int intVal;
    ret = getIntValue(env, testClass, clz, intKey, intVal);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** class内のint値を設定 ***/
    ret = setIntValue(env, testClass, clz, intKey, _jniTestC.intVal);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** class内のfloat値を取得 ***/
    float floatVal;
    ret = getFloatValue(env, testClass, clz, floatKey, floatVal);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** class内のfloat値を設定 ***/
    ret = setFloatValue(env, testClass, clz, floatKey, _jniTestC.floatVal);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** class内の文字列を取得 ***/
    std::string s;
    ret = getStringValue(env, testClass, clz, strKey, s);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** class内の文字列を変更 ***/
    ret = setStringValue(env, testClass, clz, strKey, _jniTestC.strC);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** 1次元配列[Int]に値を設定 ***/
    ret = setIntArray(env, testClass, clz, intArrKey, _jniTestC.vectorInt);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** 1次元配列[Float]に値を設定 ***/
    ret = setFloatArray(env, testClass, clz, floatArrKey, _jniTestC.vectorFloat);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    /*** 2次元配列[Int]に値を設定 ***/
    ret = setIntMatrix(env, testClass, clz, intMatKey, _jniTestC.matrixInt);
    if(ret != SkinAnalysisError::success){return (jint)ret;}

    // java classを解放
    env->DeleteLocalRef(clz);

    return (jint)SkinAnalysisError::success;}
