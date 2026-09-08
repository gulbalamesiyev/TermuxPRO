# Termux Pro

<p align="center">
  <img src="app/src/main/res/drawable-nodpi/termux_pro_icon.png" width="128" alt="Termux Pro">
</p>

<h3 align="center">A faster and more powerful Termux experience for Android</h3>

<p align="center">
  X11 rendering improvements, a professional shell prompt, and an optimized terminal workflow.
</p>

## Features

- Optimized terminal rendering for smoother output.
- Embedded X11 renderer integration.
- Professional `TermuxPRO` shell prompt.
- Termux-compatible package management and workflows.
- Debug and release APK builds for supported Android architectures.

## Requirements

- Android 7.0 or newer for the `apt-android-7` build.
- Install all Termux add-ons from the same source and with the same signing key.
- X11 desktop features are still being integrated and may require additional runtime packages.

## Build locally

Open the repository in Android Studio, allow Gradle synchronization to finish, and build the `app` module.

On Windows:

```powershell
.\gradlew.bat assembleDebug
```

On Linux or macOS:

```bash
bash ./gradlew assembleDebug
```

## Project status

The terminal application is functional. X11 renderer integration is included, while the complete desktop profile (`dbus`, X11 client runtime, and XFCE packages) is still being integrated.

## Developer

Developed and optimized by **[gulbalamesiyev](https://github.com/gulbalamesiyev)**.

## License

See [LICENSE.md](LICENSE.md).
