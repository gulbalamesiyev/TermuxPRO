# Remove App Store Feature

This plan outlines the steps to completely remove the "App Store" feature while preserving all core Termux Pro functionality.

## Proposed Changes

### [app]

#### [DELETE] [termux-pro-app-store](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/assets/termux-pro-app-store)

#### [MODIFY] [DesktopResourceManager.java](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/java/com/termux/app/desktop/DesktopResourceManager.java)
- Remove `gvfs` and `yad` from the initial resource installation script.
- Remove `provisionAppStoreResources()`, `provisionAppStoreResourcesWithContext()`, `installIfMissing()`, `makeExecutable()`, and `createAppStoreScript()`.

#### [MODIFY] [DesktopSessionOrchestrator.java](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/java/com/termux/app/desktop/DesktopSessionOrchestrator.java)
- In `buildDesktopStartCommand()`:
    - Remove code that creates the `termux-pro-app-store` shell script.
    - Remove code that creates the `app-store.desktop` file.
    - Add cleanup commands to remove any existing `termux-pro-app-store` binary and desktop files.

#### [MODIFY] [SessionCenterController.java](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/java/com/termux/app/terminal/SessionCenterController.java)
- Remove the call to `DesktopResourceManager.provisionAppStoreResourcesWithContext()`.

## Verification Plan

### Automated Tests
- Build the project using `./gradlew :app:assembleDebug` to ensure no compilation errors.

### Manual Verification
1. Verify that the `termux-pro-app-store` asset is deleted.
2. Verify that the App Store provisioning methods are gone from `DesktopResourceManager.java`.
3. Verify that the resource installation script no longer includes `yad` and `gvfs`.
4. Verify that the desktop session start command no longer attempts to create the App Store script or icon.
5. Verify that core features (Session Center, XFCE startup, Native icons) are preserved in the code.
