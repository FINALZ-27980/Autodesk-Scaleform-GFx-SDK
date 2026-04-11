package com.scaleform.${APP_NAME};

import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.util.FloatMath;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;

/// begin GFX_SOUND_FMOD
import org.fmod.FMODAudioDevice;
/// end GFX_SOUND_FMOD

public class MainActivity extends Activity
{
    GLView View;

    private static native void NativeAppInit();
    private static native void NativeOnOpenFile(String path);
    private native void NativeOnCreate();
    private static native void NativeOnPause();
    private static native void NativeOnResume();
    private static native void NativeOnWindowFocusChanged(boolean hasFocus);
    private static native void NativeOnOrientation(int orient, boolean flip);
    private static native void NativeOnTouch(int pointerId, int event, float x, float y);
    private static native void NativeOnTouchMouse(int event, float x, float y);
    private static native void NativeOnGesture(int event, int mode, float x, float y, float panx, float pany, float scale);

    private static native void NativeOnKey(boolean down, int key);
    private static native void NativeOnChar(int code);

    private native void NativeCacheObject();
    private native void NativeClearObject();

    public static final int GEST_EVENT_END = 0;
    public static final int GEST_EVENT_BEGIN = 1;
    public static final int GEST_EVENT_GESTURE = 2;
    public static final int GEST_EVENT_SIMPLE = 3;

    public static final int GEST_EVENT_NONE = 0;
    public static final int GEST_EVENT_PAN = 1;
    public static final int GEST_EVENT_ZOOM = 2;
    public static final int GEST_EVENT_SWIPE = 3;

    public static final int ACTION_POINTER_2_MOVE = 263;

    public static final float VEL_DELTA = 2.0f;

    protected float x1 = 0.0f,
                    x2 = 0.0f,
                    y1 = 0.0f,
                    y2 = 0.0f,
                    x1_pre = 0.0f,
                    y1_pre = 0.0f,
                    x_scale = 1.0f,
                    y_scale = 1.0f,
                    dist_curr = -1.0f,
                    dist_pre = -1.0f,
                    dist_delta = 0.0f,
                    velocity = 0;

    private long time_delta = 0,
                 time_curr = 0,
                 time_pre = 0;

    private String mDebugMessage = "";

    // Used to remember the state of OnWindowFocusChanged calls. This may be required to start sounds again
    // onResume, because there may not be a subsequent OnWindowFocusChanged call, if there is no lock screen.
    private boolean WindowHasFocus = false;

/// begin GFX_SOUND_FMOD
    private FMODAudioDevice Sound = new FMODAudioDevice();
/// end GFX_SOUND_FMOD

    static
    {
/// begin GFX_SOUND_FMOD
        System.loadLibrary("fmodex");
/// end GFX_SOUND_FMOD
        System.loadLibrary("${APP_NAME}");
        NativeAppInit();
    }

    @Override
    public void onStart()
    {
        super.onStart();
        NativeCacheObject();
    }

    @Override
    public void onStop()
    {
        NativeClearObject();
        super.onStop();
    }

    @Override
    protected void onPause()
    {
/// begin GFX_SOUND_FMOD
        Sound.stop();
/// end GFX_SOUND_FMOD
        super.onPause();
        NativeOnPause();
        View.onPause();
    }
    @Override
    protected void onResume()
    {
/// begin GFX_SOUND_FMOD
        // If we are getting an onResume, and onWindowFocusChanged(FALSE) has not been called, start sounds
        // again, as this means that this window still has focus, and thus should become fully interactive.
        if (WindowHasFocus)
            Sound.start();
/// end GFX_SOUND_FMOD
        super.onResume();
        NativeOnResume();
        View.onResume();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);

        // When the window loses gains/loses focus, start/stop the sound.
/// begin GFX_SOUND_FMOD
        if (hasFocus)
            Sound.start();
        else
            Sound.stop();
/// end GFX_SOUND_FMOD

        // Record the focus state.
        WindowHasFocus = hasFocus;

        NativeOnWindowFocusChanged(hasFocus);
    }

    public void OpenVirtualKeyboard(boolean multiline)
    {
        if (Debug.ENABLED){ Log.d("GFxPlayer", "OpenVirtualKeyboard called"); }

        InputMethodManager imm = (InputMethodManager) this.getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm == null)
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "OpenVirtualKeyboard Input Method Service not found!"); }
            return;
        }
        Configuration config = this.getResources().getConfiguration();
        if (config.hardKeyboardHidden == Configuration.HARDKEYBOARDHIDDEN_YES)
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "OpenVirtualKeyboard Showing soft input! multiline = " + multiline); }
            View.setMultilineTextfieldMode(multiline);
            imm.restartInput(View);
            imm.showSoftInput(View, 0);
        }
        else
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "HARDKEYBOARDHIDDEN_YES is false!"); }
        }
    }
    public void CloseVirtualKeyboard()
    {
        if (Debug.ENABLED){ Log.d("GFxPlayer", "CloseVirtualKeyboard called"); }

        InputMethodManager imm = (InputMethodManager) this.getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm == null)
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "CloseVirtualKeyboard Input Method Service not found!"); }
            return;
        }
        Configuration config = this.getResources().getConfiguration();
        if (config.hardKeyboardHidden == Configuration.HARDKEYBOARDHIDDEN_YES)
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "CloseVirtualKeyboard Hiding soft input!"); }
            imm.hideSoftInputFromWindow(View.getWindowToken(), 0);
        }
        else
        {
            if (Debug.ENABLED){ Log.d("GFxPlayer", "HARDKEYBOARDHIDDEN_YES is false!"); }
        }
    }

    public void OpenURL(String url)
    {
        if (!url.startsWith("https://") && !url.startsWith("http://"))
            url = "http://" + url;

        Uri uriUrl = Uri.parse(url);

        Intent intent = new Intent(Intent.ACTION_VIEW, uriUrl);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        NativeOnCreate();

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

        onNewIntent(getIntent());

        View = new GLView(getApplication(), this);
        setContentView(View);
    }

    protected void onNewIntent(Intent in)
    {
        if (Intent.ACTION_VIEW.equals(in.getAction()) && getIntent().getData().getScheme().equals("file"))
        {
            String path = in.getData().getPath();
            String[] s = path.split("\\.");

            if (s.length >= 2 && s[s.length-1].equals("swf"))
            {
                NativeOnOpenFile(path);
            }
        }
    }

    public void onConfigurationChanged(Configuration config) {
        super.onConfigurationChanged(config);

        //NativeOnOrientation(config.orientation == Configuration.ORIENTATION_PORTRAIT ? 1 : 2, false);
    }

    public boolean onKeyDown (int key, KeyEvent event)
    {
      switch (key)
      {
         case KeyEvent.KEYCODE_MENU:
            NativeOnKey (true, 19);
            return true;
         case KeyEvent.KEYCODE_VOLUME_UP:
         case KeyEvent.KEYCODE_VOLUME_DOWN:
         case KeyEvent.KEYCODE_BACK:
            // We let the system handle volume up, down and back
            return super.onKeyDown (key, event);
      }
      //return super.onKeyDown(key, event);
      NativeOnKey (true, key);
      return true;
    }
    public boolean onKeyUp(int key, KeyEvent event)
    {
        switch (key)
        {
        case KeyEvent.KEYCODE_MENU:
            NativeOnKey(false, 19);
            return true;
        }
        //return super.onKeyUp(key, event);
        NativeOnKey(false, key);
        return true;
    }

    public void onChar(int code)
    {
        NativeOnChar(code);
    }

    public boolean onTouchEvent(MotionEvent event)
    {
        // If the renderer hasn't rendered anything yet, 'swallow' all of the touch events.
        if(!View.RendererInitComplete())
            return true;

        int action = event.getAction();
        int p_count = event.getPointerCount();

        // Pointer 1 Coords
        x1 = event.getX(0);
        y1 = event.getY(0);

        // Time between this Touch and Last
        time_curr = android.os.SystemClock.uptimeMillis();
        time_delta = time_curr - time_pre;

        // Distance between this Touch and Last
        dist_curr = FloatMath.sqrt((x1 - x1_pre) * (x1 - x1_pre) + (y1 - y1_pre) * (y1 - y1_pre));
        dist_delta = dist_curr - dist_pre;

        // Current Velocity
        velocity = Math.abs(dist_delta / (float) time_delta);

        // Single Touch Point
        // Two Gestures Available - Pan & Swipe
        if (p_count == 1)
        {
            switch (action)
            {
            case MotionEvent.ACTION_DOWN:
                if (Debug.ENABLED) { Log.d("GFxPlayer", "Sent Action: DOWN " + Integer.toString(action)); }
                NativeOnTouchMouse(action, x1, y1);
                NativeOnGesture(GEST_EVENT_BEGIN, GEST_EVENT_PAN, x1, y1, 0, 0, 1);
                break;
            case MotionEvent.ACTION_UP:
                if (Debug.ENABLED) { Log.d("GFxPlayer", "Sent Action: UP " + Integer.toString(action)); }
                NativeOnTouchMouse(action, x1, y1);
                NativeOnGesture(GEST_EVENT_END, GEST_EVENT_PAN, x1, y1, 0, 0, 1);
                break;
            case MotionEvent.ACTION_MOVE:
                if (Debug.ENABLED) { Log.d("GFxPlayer", "Sent Action: MOVE " + Integer.toString(action)); }
                NativeOnTouchMouse(action, x1, y1);
                if (velocity > VEL_DELTA)
                {
                    NativeOnGesture(GEST_EVENT_END, GEST_EVENT_PAN, x1, y1, 0, 0, 1);
                    NativeOnGesture(GEST_EVENT_SIMPLE, GEST_EVENT_SWIPE, x1, y1, x1 - x1_pre, y1 - y1_pre, velocity);
                }
                else
                {
                    NativeOnGesture(GEST_EVENT_GESTURE, GEST_EVENT_PAN, x1, y1, x1 - x1_pre, y1 - y1_pre, 1);
                }
                break;
            default:
                if (Debug.ENABLED) { Log.d("GFxPlayer", "     Action: " + Integer.toString(action)); }
            }
        }
        else // Multiple Touch Points
             // Two Gestures Available - Zoom & Rotate
        {
            // Pointer 2 Coords
            x2 = event.getX(1);
            y2 = event.getY(1);

            // Distance between P1 & P2
            dist_curr = (float) Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
            dist_delta = dist_curr - dist_pre;

            switch (action)
            {
            case MotionEvent.ACTION_POINTER_1_DOWN:
            case MotionEvent.ACTION_POINTER_2_DOWN:
                NativeOnGesture(GEST_EVENT_BEGIN, GEST_EVENT_ZOOM, x1, y1, 0, 0, 1);
                if (Debug.ENABLED) { mDebugMessage = mDebugMessage + "Sent Action: " + Integer.toString(action); }
                break;
            case MotionEvent.ACTION_POINTER_2_UP:
            case MotionEvent.ACTION_POINTER_1_UP:
                NativeOnGesture(GEST_EVENT_END, GEST_EVENT_ZOOM, x1, y1, 0, 0, 1);
                if (Debug.ENABLED) { mDebugMessage = mDebugMessage + "Sent Action: " + Integer.toString(action); }
                break;
            case MotionEvent.ACTION_MOVE:
                NativeOnGesture(GEST_EVENT_GESTURE, GEST_EVENT_ZOOM, x1, y1, 0, 0, dist_curr/dist_pre);
                if (Debug.ENABLED) { mDebugMessage = mDebugMessage + "Sent Action: " + Integer.toString(ACTION_POINTER_2_MOVE); }
                break;
            default:
                if (Debug.ENABLED) { mDebugMessage = mDebugMessage + "     Action: " + Integer.toString(action); }
            }
            if (dist_delta != 0)
            {
                if (Debug.ENABLED) { mDebugMessage = mDebugMessage + "\tdistDelta: " + Float.toString(dist_delta)
                                                                 + "\tdistCurrent: " + Float.toString(dist_curr); }
            }
           }
        x1_pre = x1; y1_pre = y1;
        dist_pre = dist_curr;
        time_pre = time_curr;

        for (int i = 0; i < p_count; i++)
        {
            if (Debug.ENABLED) { Log.d("GFxPlayer", " PointerIds: " + " " + event.getPointerId(i)); }
            NativeOnTouch(event.getPointerId(i), action, event.getX(i), event.getY(i));
        }

        return true;
    }
}
