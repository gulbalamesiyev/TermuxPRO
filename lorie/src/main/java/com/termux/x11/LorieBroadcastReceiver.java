package com.termux.x11;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class LorieBroadcastReceiver extends BroadcastReceiver {
    private static Bundle extractConnectionBundle(Intent intent) {
        if (intent == null) return null;
        Bundle bundle = intent.getBundleExtra(CmdEntryPoint.EXTRA_CONNECTION_BUNDLE);
        if (bundle == null) {
            bundle = intent.getBundleExtra(null);
        }
        if (bundle == null) {
            Bundle extras = intent.getExtras();
            if (extras != null) {
                Object raw = extras.get(CmdEntryPoint.EXTRA_CONNECTION_BUNDLE);
                if (raw instanceof Bundle) {
                    bundle = (Bundle) raw;
                }
                if (bundle == null) {
                    bundle = extras.getBundle(null);
                }
            }
        }
        return bundle;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent == null) {
            Log.w("LorieBroadcastReceiver", "ACTION_START received with null intent");
            return;
        }

        if (!CmdEntryPoint.ACTION_START.equals(intent.getAction())) {
            MainActivity activity = MainActivity.getInstance();
            if (activity != null) {
                activity.onBroadcastReceive(context, intent);
            }
            return;
        }

        String launchToken = intent.getStringExtra(CmdEntryPoint.EXTRA_DESKTOP_OWNER_HANDLE);
        Log.i("LorieBroadcastReceiver", "ACTION_START_RECEIVED launchToken=" + launchToken);
        if (!DesktopNavigationState.isLaunchTokenValid(launchToken)) {
            Log.w("LorieBroadcastReceiver", "Ignoring stale X11 ready broadcast for launchToken=" + launchToken + " while pendingToken=" + DesktopNavigationState.getPendingDesktopLaunchToken());
            return;
        }

        Bundle connectionBundle = extractConnectionBundle(intent);
        if (connectionBundle != null) {
            Log.i("LorieBroadcastReceiver", "CONNECTION_BUNDLE_PRESENT true");
        } else {
            Log.w("LorieBroadcastReceiver", "CONNECTION_BUNDLE_PRESENT false action=" + intent.getAction());
        }

        boolean shouldForegroundRenderer =
            !DesktopNavigationState.isCliForeground()
                && DesktopNavigationState.isDesktopPending();

        DesktopNavigationState.addInstallLog("X11: ACTION_START received; bridge listener is ready.");
        // Point 9: mark the visual renderer ready only after LorieView.connected() is true.
        // setDesktopReady() is now moved to MainActivity.tryConnect() success path.

        if (!shouldForegroundRenderer) {
            return;
        }

        try {
            DesktopNavigationState.addInstallLog("X11: opening connected renderer activity.");
            MainActivity.launchOrReuse(context, connectionBundle, launchToken);
        } catch (RuntimeException e) {
            DesktopNavigationState.setDesktopStartFailureReason(
                e.getClass().getSimpleName() + ": " + e.getMessage());
            DesktopNavigationState.setDesktopFailed();
            Log.e("LorieBroadcastReceiver",
                "Failed to launch connected X11 renderer activity", e);
        }
    }
}
