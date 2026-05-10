# Integration Guide - Modcat ImGui Mod Menu

This guide explains how to integrate this mod menu framework into other Android games or applications.

## Prerequisites
- A target Android app (APK).
- Knowledge of APK decompilation/recompilation (using tools like MT Manager, NP Manager, or APKTool).
- The compiled native library (`libCatmodRX.so`).

---

## 1. Project Structure Integration

### Native Library
Place your compiled `libCatmodRX.so` into the target APK's `lib` directory (e.g., `lib/armeabi-v7a/` or `lib/arm64-v8a/`).

### Java Classes
You must include the following Java classes in the target APK (ensure they match the package `com.Cat.mod`):
1. `ModMenu.java`
2. `GLES3JNIView.java`

---

## 2. Initialization

To show the mod menu, you need to call `ModMenu.init(context)` from the target app. The best place to do this is in the `onCreate` method of the main `Activity` or a `Service`.

### Example (Activity):
```java
package com.example.game;

import android.os.Bundle;
import com.Cat.mod.ModMenu; // Import the ModMenu

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Initialize the Mod Menu
        ModMenu.init(this);
    }
}
```

---

## 3. Permissions

The mod menu uses a System Overlay to display on top of other apps. You must add the following permission to the `AndroidManifest.xml`:

```xml
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
```

For Android 6.0 (API 23) and above, you must also request this permission at runtime if it's not granted.

---

## 4. Integration into Existing Games (Injection)

If you are injecting this into a game you don't own, you can use several methods:

### Method A: Static Injection (APK Modding)
1. Decompile the target APK.
2. Add the `.so` and `.dex` files (containing the `com.Cat.mod` classes).
3. Find the main Activity in `AndroidManifest.xml`.
4. Locate its `onCreate` method in Smali code (usually `MainActivity.smali`).
5. Inside `onCreate`, find the line `.prologue` and add the following Smali code right after it:
   ```smali
   invoke-static {p0}, Lcom/Cat/mod/ModMenu;->init(Landroid/content/Context;)V
   ```
   *Note: `p0` refers to 'this' (the Activity context) in non-static methods.*
6. Recompile and sign the APK.

### Method B: Dynamic Injection (Frida/Xposed)
You can use Frida to load the library and call the init method dynamically:
```javascript
Java.perform(function () {
    var ModMenu = Java.use("com.Cat.mod.ModMenu");
    var currentActivity = Java.use("android.app.ActivityThread").currentActivity();
    ModMenu.init(currentActivity);
});
```

---

## 5. Troubleshooting

- **Overlay not showing**: Ensure you have granted "Display over other apps" permission in Android settings.
- **Touch not working**: The `vTouch` view in `ModMenu.java` handles touches. If it's not updating, check if `GLES3JNIView.getWindowRect()` is returning the correct values.
- **Crash on Start**: Check logcat for `System.loadLibrary` errors. Ensure the `.so` name matches what's in `ModMenu.java`.

---

Developed by **CatmodRX**
Telegram: [@CatmodRX_op_mods](https://t.me/CatmodRX_op_mods)
