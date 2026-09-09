# Termux Pro

<p align="center">
  <img src="app/src/main/res/drawable-nodpi/termux_pro_icon.png" width="128" alt="Termux Pro Logo">
</p>

<p align="center">
  <a href="https://github.com/gulbalamesiyev/termux-pro/actions"><img src="https://github.com/gulbalamesiyev/termux-pro/workflows/Build/badge.svg" alt="Build Status"></a>
  <a href="LICENSE.md"><img src="https://img.shields.io/badge/license-GPLv3-blue.svg" alt="License"></a>
  <a href="https://github.com/termux"><img src="https://img.shields.io/badge/community-Termux-orange.svg" alt="Termux Community"></a>
</p>

**Termux Pro** is a highly optimized, professional-grade terminal emulator and Linux environment for Android. It extends the core Termux functionality with enhanced X11 rendering, a polished user interface, and pre-configured tools for power users.

## 🚀 Key Features

- **Optimized Rendering**: Native C++ renderer improvements for faster terminal output.
- **X11 Integration**: Seamlessly run graphical Linux applications with built-in X11 support.
- **Professional Environment**: Custom `TermuxPRO` shell environment with enhanced prompt and aliases.
- **Architecture Support**: Optimized builds for `arm64-v8a`, `armeabi-v7a`, `x86`, and `x86_64`.
- **Reproducible Builds**: Strict Gradle configuration ensures build consistency.

## 📁 Project Structure

This repository follows a modular architecture, similar to the rəsmi Termux ecosystem:

| Module | Description |
| :--- | :--- |
| [`:app`](app/) | The main Android application module. |
| [`:lorie`](lorie/) | The X11 renderer core (based on Termux:X11). |
| [`:termux-shared`](termux-shared/) | Shared utilities and constants used across modules. |
| [`:terminal-emulator`](terminal-emulator/) | Core terminal emulation logic. |
| [`:terminal-view`](terminal-view/) | Android View for displaying the terminal. |
| [`:shell-loader`](shell-loader/) | Helper for launching shell sessions. |

## 🛠️ Building

To build **Termux Pro** from source, you need **Android Studio Koala+** or a compatible **Gradle** environment.

### Prerequisites

- Android SDK and NDK installed.
- Minimum API Level: 26 (Android 8.0).

### Build via Command Line

**Windows:**
```powershell
.\gradlew.bat assembleDebug
```

**Linux / macOS:**
```bash
./gradlew assembleDebug
```

## 🤝 Contributing

Contributions are welcome! Please read our [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## 📄 License

This project is licensed under the **GPLv3 License** - see the [LICENSE.md](LICENSE.md) file for details.

## 🔗 Resources

- **Official Documentation**: [gulbalamesiyev.github.io/termux-pro/](https://gulbalamesiyev.github.io/termux-pro/)
- **Termux Organization**: [github.com/termux](https://github.com/termux)
- **Report Bugs**: [Open an Issue](https://github.com/gulbalamesiyev/termux-pro/issues)

---
Developed with ❤️ by **[gulbalamesiyev](https://github.com/gulbalamesiyev)**.
