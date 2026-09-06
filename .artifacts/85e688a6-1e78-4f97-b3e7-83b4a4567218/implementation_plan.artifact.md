# Fix Duplicate Welcome Message (MOTD)

The goal is to prevent the "Welcome to TermuxPRO!" message from appearing twice when a new session is started. Currently, the `TermuxInstaller` class writes the same welcome message to both `/etc/motd` (a static file) and `/etc/motd.sh` (a shell script that prints the message). Many shell configurations in Termux display both, leading to the duplication.

## Proposed Changes

### [app]

Summary: Modify `TermuxInstaller.java` to ensure that only one source is used for the welcome message. We will keep `/etc/motd` empty and use `/etc/motd.sh` as the primary source, which is the standard way Termux handles custom or dynamic welcome messages.

#### [MODIFY] [TermuxInstaller.java](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/java/com/termux/app/TermuxInstaller.java)

- Update `updateStandardWelcomeMessage` method to clear `motdFile` (`/etc/motd`) and only populate `motdScript` (`/etc/motd.sh`).
- This ensures that even if both are triggered by the shell profile, only the script will actually print anything.

## Verification Plan

### Manual Verification
- Deploy the app to a device/emulator.
- Start a new session.
- Verify that the "Welcome to TermuxPRO!" message appears exactly once.
- Check that the shell prompt `┌──(TermuxPRO)-[~]` still appears correctly after the message.
