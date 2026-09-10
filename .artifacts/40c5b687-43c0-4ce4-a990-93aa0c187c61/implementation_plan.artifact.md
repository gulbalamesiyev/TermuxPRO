# Termux Pro Universal APK Pushing Plan

The goal is to build the universal release APK and push it to the `termuxpro` (gulbalamesiyev/termux-pro) GitHub repository so users can easily download it.

## User Review Required

> [!IMPORTANT]
> The universal APK size is approximately **125MB**. Pushing this directly to the Git repository will increase the repository size significantly. Standard practice is to use **GitHub Releases**, which I will also perform using the `gh` CLI.

## Proposed Changes

### Build System
#### [MODIFY] [Android.mk](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/app/src/main/cpp/Android.mk)
- Added `LOCAL_ASMFLAGS += -I$(LOCAL_PATH)` to fix the NDK build error where it couldn't find bootstrap zip files during assembly.

### Release Assets
#### [NEW] `release/termux-pro-universal.apk`
- The built universal release APK will be copied to this folder for direct access from the repository tree (as requested).

### Documentation
#### [MODIFY] [README.md](file:///C:/TermuxX11StageV8/TermuxPro-X11-renderer-stage-v8-optimized/termux-pro-app-x11-stage/README.md)
- Add a **Downloads** section with a link to the APK and the GitHub Releases page.

## Verification Plan

### Automated Tests
- I have already verified the build with `gradlew :app:assembleRelease` and it finished successfully.
- I will verify the presence of the APK in the `release/` folder.

### Manual Verification
- Verify the GitHub repository "Releases" page and the file tree after the push.
