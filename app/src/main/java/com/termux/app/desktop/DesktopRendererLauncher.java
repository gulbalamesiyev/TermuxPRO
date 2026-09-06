package com.termux.app.desktop;

import android.content.Context;

import com.termux.x11.DesktopNavigationState;

/** Opens or restores the internal embedded X11 renderer inside the Termux Pro task. */
public final class DesktopRendererLauncher {

    private DesktopRendererLauncher() {}

    public static void open(Context context) {
        open(context, null);
    }

    public static void open(Context context, android.os.Bundle connectionBundle) {
        DesktopNavigationState.requestDesktopForeground();
        
        android.os.Bundle bundleToUse = connectionBundle;
        if (bundleToUse == null) {
            bundleToUse = DesktopNavigationState.getLastConnectionBundle();
        }

        // Use the canonical launch path from MainActivity to ensure consistent flags and extras.
        com.termux.x11.MainActivity.launchOrReuse(context, bundleToUse, DesktopNavigationState.getPendingDesktopLaunchToken());
    }

    /** The app_process bridge loads the embedded CmdEntryPoint directly from the host APK. */
    public static String getHostApkPathForShell() {
        return "$(/system/bin/pm path com.termux | /system/bin/cut -d: -f2)";
    }
}

