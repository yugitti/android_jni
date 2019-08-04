package com.example.jni_test

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method

        var t = TestClass()
        Log.d("java-side", "intVal = " + t.intVal)
        Log.d("java-side", "floatVal = " + t.floatVal)
        Log.d("java-side",  "str0 = " + t.str0)
        for(i in 0..4){
            Log.d("java-side", "IntArray[" + i + "]: e = " + t.intArr[i])
        }
        for(i in 0..4){
            Log.d("java-side", "FloatArray[" + i + "]: e = " + t.floatArr[i])
        }
        var ret:Int = stringFromJNI(t)
        Log.d("java-side", "intVal = " + t.intVal)
        Log.d("java-side", "floatVal = " + t.floatVal)
        Log.d("java-side",  "str0 = " + t.str0)
        for(i in 0..4){
            Log.d("java-side", "IntArray[" + i + "]: e = " + t.intArr[i])
        }
        for(i in 0..4){
            Log.d("java-side", "FloatArray[" + i + "]: e = " + t.floatArr[i])
        }
        for(i in 0..24){
            Log.d("java-side", "[" + i + "]:  x = " + t.intArr2[i][0]
                    + ", y = " + t.intArr2[i][1])
        }

        Log.d("java-side", "RETURN: " + ret)

    }

    class TestClass{
        var intVal:Int = 100
        var floatVal:Float = 100f
//        var arr = IntArray(5)
        var intArr:IntArray = intArrayOf(0,1,2,3,4)
        var floatArr:FloatArray = floatArrayOf(0f,1f,2f,3f,4f)
        var intArr2 = Array(25, {IntArray(2)})
        var str0:String = "HELLO WORLD"
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(t:TestClass): Int

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}