package com.termux.x11;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Process-local navigation state. It deliberately resets to desktop mode if
 * Android kills the app process; a dead process cannot preserve X11 anyway.
 */
public final class DesktopNavigationState {
    public enum DesktopBootState { IDLE, DOWNLOADING, BOOTING, READY, FAILED }

    private static final AtomicBoolean cliForeground = new AtomicBoolean(false);
    private static final AtomicBoolean desktopPending = new AtomicBoolean(false);

    private static final AtomicReference<String> activeDesktopOwnerHandle = new AtomicReference<>(null);
    private static final AtomicReference<String> pendingDesktopLaunchToken = new AtomicReference<>(null);
    private static final AtomicBoolean desktopOwnerStopping = new AtomicBoolean(false);
    private static final AtomicReference<android.os.Bundle> lastConnectionBundle = new AtomicReference<>(null);
    private static final AtomicReference<DesktopBootState> bootState = new AtomicReference<>(DesktopBootState.IDLE);
    private static final AtomicReference<String> activeInstallSessionHandle = new AtomicReference<>(null);
    private static final AtomicReference<String> activeInstallLogHandle = new AtomicReference<>(null);
    private static final AtomicReference<String> installPhase = new AtomicReference<>("");
    private static final AtomicInteger installProgress = new AtomicInteger(-1);
    private static final AtomicReference<List<String>> installLogs = new AtomicReference<>(Collections.synchronizedList(new ArrayList<>()));
    private static final AtomicReference<String> startFailureReason = new AtomicReference<>(null);
    private static final AtomicBoolean desktopLaunchPending = new AtomicBoolean(false);

    private DesktopNavigationState() {}

    public static String getInstallPhase() { return installPhase.get(); }
    public static void setInstallPhase(String phase) { installPhase.set(phase); }

    public static int getInstallProgress() { return installProgress.get(); }
    public static void setInstallProgress(int progress) { installProgress.set(progress); }

    public static List<String> getInstallLogs() {
        synchronized (installLogs.get()) {
            return new ArrayList<>(installLogs.get());
        }
    }
    public static void addInstallLog(String log) {
        if (log == null || log.isEmpty()) return;
        List<String> logs = installLogs.get();

        synchronized (logs) {
            // Avoid duplicate consecutive logs
            if (!logs.isEmpty() && logs.get(logs.size() - 1).equals(log)) return;

            logs.add(log);
            // Limit to a reasonable large history
            if (logs.size() > 5000) logs.remove(0);
        }
    }

    public static void clearInstallLogs() { installLogs.get().clear(); }

    public static void enterCliForeground() {
        cliForeground.set(true);
        desktopPending.set(false);
    }

    public static void requestDesktopForeground() {
        cliForeground.set(false);
        desktopPending.set(true);
    }

    public static void clearDesktopPending() {
        desktopPending.set(false);
        pendingDesktopLaunchToken.set(null);
    }

    public static void beginDesktopLaunch(String ownerHandle, String launchToken) {
        if (ownerHandle != null) {
            activeDesktopOwnerHandle.set(ownerHandle);
        }
        if (launchToken != null) {
            pendingDesktopLaunchToken.set(launchToken);
        }
        desktopPending.set(true);
        startFailureReason.set(null);
    }

    public static boolean isLaunchTokenValid(String launchToken) {
        if (launchToken == null) return false;
        String expectedToken = pendingDesktopLaunchToken.get();
        return expectedToken != null && expectedToken.equals(launchToken);
    }

    public static boolean isCliForeground() {
        return cliForeground.get();
    }

    public static boolean isDesktopPending() {
        return desktopPending.get();
    }

    // --- Owner Management ---

    public static String getActiveDesktopOwnerHandle() {
        return activeDesktopOwnerHandle.get();
    }

    public static String getPendingDesktopLaunchToken() {
        return pendingDesktopLaunchToken.get();
    }

    public static boolean claimDesktopOwner(String handle) {
        if (handle == null) return false;
        // Succeed if no owner, or already owner
        return activeDesktopOwnerHandle.compareAndSet(null, handle)
                || handle.equals(activeDesktopOwnerHandle.get());
    }

    public static boolean isDesktopOwner(String handle) {
        return handle != null && handle.equals(activeDesktopOwnerHandle.get());
    }

    public static void clearDesktopOwner(String handle) {
        if (handle != null && activeDesktopOwnerHandle.compareAndSet(handle, null)) {
            resetDesktopBoot();
        }
    }

    public static void clearDesktopOwner() {
        activeDesktopOwnerHandle.set(null);
        desktopOwnerStopping.set(false);
        resetDesktopBoot();
    }

    public static void beginDesktopOwnerShutdown(String ownerHandle) {
        if (ownerHandle != null && ownerHandle.equals(activeDesktopOwnerHandle.get())) {
            desktopOwnerStopping.set(true);
        }
    }

    public static boolean isDesktopOwnerStopping() {
        return desktopOwnerStopping.get();
    }

    public static void completeDesktopOwnerShutdown(String ownerHandle) {
        if (ownerHandle != null && activeDesktopOwnerHandle.compareAndSet(ownerHandle, null)) {
            desktopOwnerStopping.set(false);
            resetDesktopBoot();
        }
    }

    // --- Boot State Management ---

    public static DesktopBootState getDesktopBootState() {
        return bootState.get();
    }

    public static void startDesktopDownload() {
        bootState.set(DesktopBootState.DOWNLOADING);
    }

    public static void startDesktopBoot() {
        bootState.set(DesktopBootState.BOOTING);
    }

    public static void setDesktopReady() {
        setDesktopReady(null);
    }

    public static void setDesktopReady(android.os.Bundle connectionBundle) {
        if (connectionBundle != null) {
            lastConnectionBundle.set(connectionBundle);
        }
        bootState.set(DesktopBootState.READY);
    }

    public static void completeDesktopLaunch() {
        pendingDesktopLaunchToken.set(null);
        desktopPending.set(false);
        desktopLaunchPending.set(false);
    }

    public static void setLastConnectionBundle(android.os.Bundle connectionBundle) {
        lastConnectionBundle.set(connectionBundle);
    }

    public static android.os.Bundle getLastConnectionBundle() {
        return lastConnectionBundle.get();
    }

    public static void setDesktopFailed() {
        bootState.set(DesktopBootState.FAILED);
        pendingDesktopLaunchToken.set(null);
        desktopPending.set(false);
    }

    public static void resetDesktopBoot() {
        bootState.set(DesktopBootState.IDLE);
        pendingDesktopLaunchToken.set(null);
        desktopPending.set(false);
        desktopLaunchPending.set(false);
        lastConnectionBundle.set(null);
    }

    public static void setDesktopStartFailureReason(String reason) {
        startFailureReason.set(reason);
    }

    public static String getDesktopStartFailureReason() {
        return startFailureReason.get();
    }

    public static String getActiveInstallSessionHandle() {
        return activeInstallSessionHandle.get();
    }

    public static void setActiveInstallSessionHandle(String handle) {
        activeInstallSessionHandle.set(handle);
    }

    public static String getActiveInstallLogHandle() {
        return activeInstallLogHandle.get();
    }

    public static void setActiveInstallLogHandle(String handle) {
        activeInstallLogHandle.set(handle);
    }

    public static boolean isDesktopLaunchPending() {
        return desktopLaunchPending.get();
    }

    public static void setDesktopLaunchPending(boolean pending) {
        desktopLaunchPending.set(pending);
    }
}
