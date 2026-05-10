# Modcat-imgui

Modcat-imgui is a powerful, high-performance Android mod menu framework built with **Dear ImGui**. It provides a sleek, modern interface for mobile games and applications, featuring a custom on-screen keyboard, particle effects, and a secure login system.

## Features

- **Draggable UI**: Both the mod menu and the custom keyboard can be freely moved around the screen.
- **Custom Keyboard**: A fully integrated on-screen keyboard for entering authentication keys without using the system keyboard.
- **Premium Aesthetics**: Vibrant pink/dark theme, modern typography, and dynamic particle animations.
- **Login System**: Secure key-based authentication with server-side verification.
- **Sidebar Navigation**: Organized tabs for Dashboard, Player Controls, Visuals, and Settings.

## How it Works

The project consists of a native C++ layer (JNI) that renders Dear ImGui using OpenGL ES 3.0. It runs as an Android Overlay (System Alert Window), allowing it to stay visible on top of games. Touches are handled through a transparent "vTouch" view that maps screen coordinates to ImGui input.

## Static Injection to Games

To add this mod menu to an existing game (APK modding), follow these general steps:

1. **Decompile**: Decompile the target APK using MT Manager or APKTool.
2. **Add Files**: Place `libCatmodRX.so` in the `lib` folder
3. **Inject Code**: Find the main Activity's `onCreate` method in Smali and add the initialization call:
   ```smali
   invoke-static {p0}, Lcom/Cat.mod/ModMenu;->init(Landroid/content/Context;)V
   ```
4. **Permissions**: Ensure `SYSTEM_ALERT_WINDOW` is added to `AndroidManifest.xml`.

For a more detailed guide, see [INTEGRATION.md](./INTEGRATION.md).

## Why Use It?

- **Flexibility**: Easily customizable UI and features.
- **Performance**: Low overhead rendering with OpenGL.
- **No System Keyboard Conflict**: The custom keyboard avoids focus issues common in Android overlays.
- **Professional Look**: Ditch basic menus for a premium, interactive experience.

## Credits & Inspiration

- **Tusar mods imgui**: This project was inspired by the work of Tusar, aiming to build upon and refine the ImGui modding experience on Android.
- **Dear ImGui**: The amazing UI library that makes this possible.

---
Developed by **CatmodRX**
Telegram: [@Catmod](https://t.me/Nepomdz)
