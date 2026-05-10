# Modcat ImGui Mod Menu - APK Integration Guide

## Requirements

* Target APK
* MT Manager / NP Manager / APKTool
* `libCatmodRX.so`
* `classes.dex` containing `com.Cat.mod`

---

# 1. Add Native Library

Place the compiled library inside the target game's lib folder according to architecture:

### ARMv7

```text
lib/armeabi-v7a/libCatmodRX.so
```

### ARM64

```text
lib/arm64-v8a/libCatmodRX.so
```

---

# 2. Transfer classes.dex

Move the provided `classes.dex` into the target APK.

If the game already contains multiple dex files:

```text
classes.dex
classes2.dex
classes3.dex
```

Rename the mod dex properly to avoid conflicts.

---

# 3. Add Overlay Permission

Open `AndroidManifest.xml` and add:

```xml
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
```

This permission is required for the ImGui overlay menu.

---

# 4. Inject ModMenu Initialization

Decompile the APK and open:

```text
smali/.../MainActivity.smali
```

Find:

```smali
.method protected onCreate(Landroid/os/Bundle;)V
```

Inside `onCreate`, after `.prologue`, add:

```smali
invoke-static {p0}, Lcom/Cat/mod/ModMenu;->init(Landroid/content/Context;)V
```

`p0` is the Activity context.

---

# 5. Recompile & Sign

After editing:

1. Recompile the APK
2. Sign the APK
3. Install the game

The ImGui Mod Menu should now appear in-game.

For more detailed steps and visuals, watch the tutorial video.
