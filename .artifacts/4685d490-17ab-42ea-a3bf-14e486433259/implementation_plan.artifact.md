# Implementation Plan - Fix Wrong Flow in Resource Download

Fix the issue where tapping `DOWNLOAD RESOURCES` switches the app to the native CLI screen and displays Termux bootstrap output.

## Root Cause Analysis
The issue is caused by a race condition and incorrect initialization logic in `TermuxActivity.java` and `TermuxTerminalSessionActivityClient.java`:

1.  **Late Bootstrap:** `TermuxInstaller.setupBootstrapIfNeeded` is called in `onServiceConnected`. If the bootstrap extraction (Stage 1) is already done, it calls the callback immediately. However, if Stage 2 (script execution in shell) hasn't run, it will trigger when the FIRST shell session starts.
2.  **Unintended Session Start:** In the previous task, `restoreOrStartDesktop()` was removed from the boot path. This meant that on a fresh install, NO sessions were created until the user interacted with the app.
3.  **UI Takeover:** When the user taps `DOWNLOAD RESOURCES`, `DesktopResourceManager` is invoked. Simultaneously, if `TermuxService` decides to start a default session (or if `onStart()` in the view client triggers one), and if the Session Center's visibility isn't strictly enforced during the early lifecycle, the terminal can jump to the foreground.
4.  **Bootstrap Output:** The message "Starting fallback run of termux bootstrap second stage" confirms that a shell session was started and it's performing the initial Termux setup. This should happen in the background or at least not hide the Session Center.

## Proposed Changes

### [TermuxActivity.java]
- Ensure `mSessionCenterController.setVisible(true)` is called explicitly in `onCreate` and `onResume` if no desktop is active.
- In `onServiceConnected`, ensure the bootstrap callback strictly maintains Session Center visibility.

### [SessionCenterController.java]
- In `triggerResourceDownload`, add an explicit `mRootView.bringToFront()` and `mRootView.requestFocus()` to ensure the overlay stays on top during the download process.
- Ensure the `cliButton` listener is ONLY attached when appropriate, and its click strictly handles the visibility transition.

### [TermuxTerminalSessionActivityClient.java]
- In `onStart()`, avoid calling `setCurrentSession()` if the Session Center is intended to be visible, or ensure that `attachSession` doesn't hide the overlay.

## Verification Plan

### Automated Tests
- Build `:app:assembleDebug`.

### Manual Verification
1.  **Fresh Install / Clear Data**: Open the app. Verify it enters Session Center.
2.  **Tap DOWNLOAD RESOURCES**: Verify the UI stays in Session Center. The button should show `DOWNLOADING...`.
3.  **Bootstrap**: Verify that Termux bootstrap Stage 2 completes without hiding the Session Center.
4.  **No Terminal Takeover**: Ensure the terminal screen never appears unless the "CLI" button is explicitly clicked.
