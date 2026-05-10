package com.Cat.mod;

import android.opengl.GLSurfaceView;
import android.content.Context;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import android.os.StrictMode;

public class GLES3JNIView extends GLSurfaceView implements GLSurfaceView.Renderer {
	
    public GLES3JNIView(Context context) {
        super(context);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		getHolder().setFormat(-3);
        setEGLContextClientVersion(3);
        setRenderer(this);
    }
    
	public void onDrawFrame(GL10 gl) {
		step();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
		resize(width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		init();
	}
	
    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        imgui_Shutdown();
    }
	
	public static native void init();
	public static native void resize(int width, int height);
	public static native void step();
	public static native void imgui_Shutdown();
	public static native void MotionEventClick(boolean down,float PosX,float PosY);
	public static native String getWindowRect();
	public static native void setLoginKey(String key);

    public static String verifyKey(String key) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        try {
            // NOTE: URL updated to the Replit app
            URL url = new URL("https://serverzip--moddingcat313.replit.app/api/verify?key=" + key);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.setConnectTimeout(3000);
            
            BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            in.close();
            conn.disconnect();
            return content.toString();
        } catch (Exception e) {
            return "{\"valid\":false,\"message\":\"Connection failed\"}";
        }
    }
}
