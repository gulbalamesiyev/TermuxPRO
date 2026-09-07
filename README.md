# Termux Pro

<p align="center">
  <img src="https://raw.githubusercontent.com/termux/termux-app/master/app/src/main/res/mipmap-xxxhdpi/ic_launcher.png" width="128" alt="Termux Pro">
</p>

<h3 align="center">A faster and more powerful Termux experience for Android</h3>

<p align="center">
  X11 rendering improvements, a professional shell prompt, and an optimized terminal workflow.
</p>

<p align="center">
  <a href="https://github.com/gulbalamesiyev/termux-pro/releases/latest">
    <img src="https://img.shields.io/badge/Download%20APK-Latest%20Release-2ea44f?style=for-the-badge&logo=android" alt="Download latest APK">
  </a>
  <a href="https://github.com/gulbalamesiyev/termux-pro/releases">
    <img src="https://img.shields.io/badge/View%20All%20Releases- GitHub-181717?style=for-the-badge&logo=github" alt="View all releases">
  </a>
</p>

## Download Termux Pro

Open the latest release page and scroll to **Assets**. Choose the APK that matches your device:

| File | Use |
| --- | --- |
| `universal.apk` | Recommended for most devices |
| `arm64-v8a.apk` | Modern 64-bit ARM phones and tablets |
| `armeabi-v7a.apk` | Older 32-bit ARM devices |
| `x86_64.apk` | 64-bit x86 Android devices |
| `x86.apk` | 32-bit x86 Android devices |

**[Download the latest Termux Pro APK from Releases](https://github.com/gulbalamesiyev/termux-pro/releases/latest)**

> APK files are available in the release page's **Assets** section. If Android reports a signature conflict, uninstall an older Termux build from another source before installing this build.

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
