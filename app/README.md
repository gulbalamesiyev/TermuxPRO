# Termux Pro App Module

This is the main Android application module for Termux Pro. It provides the terminal interface, manages sessions, and integrates all other modules.

## 🏗️ Architecture

- **Activities**: Main entry points for terminal and settings.
- **Services**: `TermuxService` manages the lifecycle of terminal sessions and background tasks.
- **Terminal**: Logic for PTY interaction and display rendering.

## 🛠️ Build

This module requires `:termux-shared`, `:terminal-view`, and `:terminal-emulator`.

```bash
./gradlew :app:assembleDebug
```
