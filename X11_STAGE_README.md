# Termux Pro Embedded X11 Renderer Stage

This source bundle adds the Termux:X11 Lorie renderer and its required native submodules as internal modules of the Termux Pro APK. The existing Termux Pro launcher remains the only launcher activity. The embedded renderer activity has no launcher intent and is opened by the desktop session orchestrator after the Termux bootstrap completes.

## Android Studio test

Open this folder itself as the Android Studio project. Allow Gradle sync to finish, then build and install the `app` debug configuration on an arm64 Android 8+ device.

## Expected current behavior

The source contains the native renderer and direct `app_process` entrypoint bridge, but it does not yet provision `dbus`, the X11 client runtime, or XFCE packages. A successful build verifies the renderer integration layer; the next integration stage will seed the minimal desktop runtime profile and then validate direct Desktop Session 1 startup.

## Safety

Keep the previous working source folder unchanged. This staged source is a separate Android Studio project for integration testing.
