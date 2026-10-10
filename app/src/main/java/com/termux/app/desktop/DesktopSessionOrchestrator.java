package com.termux.app.desktop;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.termux.app.TermuxService;
import com.termux.shared.termux.TermuxConstants;
import com.termux.shared.termux.shell.command.runner.terminal.TermuxSession;
import com.termux.x11.DesktopNavigationState;
import android.system.ErrnoException;
import android.system.Os;
import android.util.Log;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.UUID;
import java.util.concurrent.TimeUnit;

/**
 * Starts the single graphical desktop session after the native Termux bootstrap has completed.
 * The command is deliberately owned by the app; users never need to type the X11/XFCE start sequence.
 */
public final class DesktopSessionOrchestrator {
    public static final String SESSION_NAME = "Desktop Session 1";
    public static final String DESKTOP_MARKER = "--termux-pro-desktop-session-1";

    public static final String X11_PID_FILE =
            TermuxConstants.TERMUX_HOME_DIR_PATH + "/.cache/termux-pro-x11.pid";

    public static boolean areResourcesInstalled() {
        String bin = TermuxConstants.TERMUX_BIN_PREFIX_DIR_PATH;
        String share = TermuxConstants.TERMUX_PREFIX_DIR_PATH + "/share";
        
        boolean hasXfce = new File(bin + "/xfce4-session").exists();
        boolean hasAppStore = new File(bin + "/termux-pro-app-store").exists();
        boolean hasTerminal = new File(bin + "/xfce4-terminal").exists();
        // Check for a specific file in the icon pack to ensure it's not just an empty folder
        boolean hasIcons = new File(share + "/icons/Papirus/index.theme").exists();
        
        return hasXfce && hasAppStore && hasTerminal && hasIcons;
    }

    private static String buildDesktopStartCommand(String desktopLaunchToken) {
        return buildDesktopStartCommand(desktopLaunchToken, null, "startxfce4");
    }

    private static String buildDesktopStartCommand(String desktopLaunchToken, String distro, String desktopEnvironment) {
        String PREFIX = TermuxConstants.TERMUX_PREFIX_DIR_PATH;
        String logHandle = DesktopNavigationState.getActiveInstallLogHandle();
        String logCapture = "";
        if (logHandle != null) {
            String logFile = DesktopResourceManager.getLogFilePath(logHandle)
                    .replace("'", "'\"'\"'");
            logCapture = "exec > >(tee -a '" + logFile + "') 2>&1; ";
        }

        String xstartupInner;
        if (distro != null && !distro.isEmpty()) {
            xstartupInner = "pkg install -y proot-distro >/dev/null 2>&1 || true; proot-distro install " + distro + " >/dev/null 2>&1 || true; exec proot-distro login " + distro + " --shared-tmp -- env DISPLAY=:1 HOME=/root TERM=xterm-256color PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin " + (desktopEnvironment != null ? desktopEnvironment : "startxfce4");
        } else {
            xstartupInner = "export PATH=" + PREFIX + "/bin:/data/data/com.termux/files/usr/bin:$PATH; export XDG_DATA_DIRS=" + PREFIX + "/share:$XDG_DATA_DIRS; export DISPLAY=:1; export QT_QPA_PLATFORM=xcb; export QT_X11_NO_MITSHM=1; exec dbus-launch --exit-with-session " + (desktopEnvironment != null ? desktopEnvironment : "startxfce4");
        }

        return "set +H; set +e; " + logCapture +
            "export TERMUX_PRO_DESKTOP_ID=\"" + DESKTOP_MARKER + "\"; " +
            "export TERMUX_PRO_DESKTOP_OWNER_HANDLE=\"" + desktopLaunchToken + "\"; " +
            "export DEBIAN_FRONTEND=noninteractive; " +
            "export DISPLAY=:1; " +
            "export XDG_SESSION_TYPE=x11; " +
            "export XDG_CURRENT_DESKTOP=XFCE; " +
            "export XDG_SESSION_DESKTOP=xfce; " +
            "export XKB_CONFIG_ROOT=\"" + PREFIX + "/share/X11/xkb\"; " +
            "export TMPDIR=\"" + PREFIX + "/tmp\"; mkdir -p \"$TMPDIR/.X11-unix\"; rm -f \"$TMPDIR/.X11-unix/X1\"; " +
            "mkdir -p \"$HOME/Desktop\" \"$HOME/.config/autostart\"; " +
            "CLASSPATH=" + DesktopRendererLauncher.getHostApkPathForShell() + "; export CLASSPATH; " +
            "mkdir -p \"$HOME/.cache\"; echo $$ > \"$HOME/.cache/termux-pro-x11.pid\"; " +
            "echo \"Starting Termux-X11 bridge...\"; " +
            "/system/bin/app_process -Xnoimage-dex2oat / --nice-name=termux-x11 com.termux.x11.CmdEntryPoint :1 " +
            "--desktop-owner=\"" + desktopLaunchToken + "\" -xstartup \"" + xstartupInner + "\"; " +
            "x11_status=$?; " +
            "echo \"X11 bridge stopped with status $x11_status\"; " +
            "rm -f \"$HOME/.cache/termux-pro-x11.pid\"; " +
            "exec \"" + PREFIX + "/bin/bash\" -l";
    }

    private DesktopSessionOrchestrator() {}

    @Nullable
    public static TermuxSession start(TermuxService service) {
        return start(service, null, "startxfce4");
    }

    @Nullable
    public static TermuxSession start(TermuxService service, String distro, String desktopEnvironment) {
        String desktopLaunchToken = "desktop-" + UUID.randomUUID();
        String command = buildDesktopStartCommand(desktopLaunchToken, distro, desktopEnvironment);

        TermuxSession session = service.createTermuxSession(
            TermuxConstants.TERMUX_BIN_PREFIX_DIR_PATH + "/bash",
            new String[] { "-lc", command },
            null,
            TermuxConstants.TERMUX_HOME_DIR_PATH,
            false,
            SESSION_NAME
        );

        if (session != null) {
            DesktopNavigationState.claimDesktopOwner(session.getTerminalSession().mHandle);
            DesktopNavigationState.beginDesktopLaunch(session.getTerminalSession().mHandle, desktopLaunchToken);
            DesktopNavigationState.addInstallLog("X11: desktop session created; initializing command bridge...");
            // Desktop Session 1 has no visible terminal view. TerminalSession starts
            // its shell subprocess only after emulator initialization/updateSize().
            // Give the hidden command session a harmless initial PTY geometry so
            // CmdEntryPoint begins immediately; a real TerminalView will resize it
            // normally if the user later opens the session list.
            session.getTerminalSession().initializeEmulator(80, 24, 1, 1);
        }

        return session;
    }

    public static boolean isDesktopProcessRunning() {
        try {
            File pidFile = new File(X11_PID_FILE);
            if (!pidFile.exists()) return false;

            String content = new String(Files.readAllBytes(Paths.get(X11_PID_FILE)), StandardCharsets.UTF_8).trim();
            if (content.isEmpty()) {
                pidFile.delete();
                return false;
            }

            int pid = Integer.parseInt(content);
            if (pid <= 0) {
                pidFile.delete();
                return false;
            }

            Os.kill(pid, 0);
            return true;
        } catch (ErrnoException e) {
            if (e.errno == 3 /* ESRCH */) {
                new File(X11_PID_FILE).delete();
            }
            return false;
        } catch (Exception e) {
            new File(X11_PID_FILE).delete();
            return false;
        }
    }

    /** Forcefully stops any active X11 server process managed by this orchestrator. */
    public static void killDesktopProcess() {
        try {
            File pidFile = new File(X11_PID_FILE);
            if (!pidFile.exists()) return;

            String content = new String(Files.readAllBytes(Paths.get(X11_PID_FILE)), StandardCharsets.UTF_8).trim();
            if (content.isEmpty()) {
                pidFile.delete();
                return;
            }

            int pid = Integer.parseInt(content);
            if (pid > 0) {
                Log.i("TermuxProDesktop", "Sending SIGTERM to X11 process " + pid);
                try { Os.kill(pid, 15 /* SIGTERM */); } catch (Exception ignored) {}
            }
            pidFile.delete();
        } catch (Exception e) {
            Log.e("TermuxProDesktop", "Failed to kill orphaned desktop process", e);
            new File(X11_PID_FILE).delete();
        }
    }

    public static void restartInExistingSession(@NonNull TermuxSession session) {
        restartInExistingSession(session, "desktop-" + UUID.randomUUID());
    }


    public static void restartInExistingSession(@NonNull TermuxSession session, @NonNull String launchToken) {
        if (session.getTerminalSession() == null || !session.getTerminalSession().isRunning()) {
            return;
        }

        Log.i("TermuxProDesktop", "Restarting X11 in existing session (immediate)");
        // requestDesktopForeground and beginDesktopLaunch are already called in promoteAndStartInExistingSession
        // if this was a promotion. We only repeat them if this is a direct manual restart.
        if (!launchToken.equals(DesktopNavigationState.getPendingDesktopLaunchToken())) {
            DesktopNavigationState.requestDesktopForeground();
            DesktopNavigationState.beginDesktopLaunch(session.getTerminalSession().mHandle, launchToken);
        }
        DesktopNavigationState.addInstallLog("X11: starting CmdEntryPoint (token " + launchToken + ")...");
        session.getTerminalSession().write(buildDesktopStartCommand(launchToken) + "\n");
    }

    public static boolean promoteAndStartInExistingSession(@NonNull TermuxSession session) {
        if (session.getTerminalSession() == null || !session.getTerminalSession().isRunning()) {
            return false;
        }

        if (DesktopNavigationState.isDesktopOwnerStopping()) return false;
        
        if (isDesktopProcessRunning()) {
            String activeOwner = DesktopNavigationState.getActiveDesktopOwnerHandle();
            if (activeOwner == null || !activeOwner.equals(session.getTerminalSession().mHandle)) {
                // Process is orphaned or owned by another session.
                Log.w("TermuxProDesktop", "Cleaning up existing X11 process to allow new start.");
                killDesktopProcess();
                DesktopNavigationState.clearDesktopOwner();
            } else {
                // Already owner and running
                return true;
            }
        }

        if (DesktopNavigationState.claimDesktopOwner(session.getTerminalSession().mHandle)) {
            String launchToken = "desktop-" + UUID.randomUUID();
            DesktopNavigationState.beginDesktopLaunch(session.getTerminalSession().mHandle, launchToken);
            Log.i("TermuxProDesktop", "Session promoted to desktop owner: " + session.getTerminalSession().mHandle);
            DesktopNavigationState.addInstallLog("X11: desktop owner promoted; starting command bridge...");
            DesktopNavigationState.startDesktopBoot();
            restartInExistingSession(session, launchToken);
            return true;
        }

        return false;
    }

    public static boolean isDesktopOwner(@Nullable TermuxSession session) {
        if (session == null || session.getTerminalSession() == null) return false;
        String handle = session.getTerminalSession().mHandle;
        return DesktopNavigationState.isDesktopOwner(handle) || isDesktopSession(session);
    }

    public static boolean isDesktopSession(@Nullable TermuxSession session) {
        if (session == null || session.getExecutionCommand() == null)
            return false;

        String[] arguments = session.getExecutionCommand().arguments;
        if (arguments == null) return false;

        // 1. Modern Marker Check
        for (String arg : arguments) {
            if (arg != null && arg.contains(DESKTOP_MARKER)) return true;
        }

        // 2. Legacy Fallback Check
        boolean hasEntryPoint = false;
        boolean hasNiceName = false;
        boolean hasXfce = false;

        for (String arg : arguments) {
            if (arg == null) continue;
            if (arg.contains("com.termux.x11.CmdEntryPoint")) hasEntryPoint = true;
            if (arg.contains("--nice-name=termux-x11")) hasNiceName = true;
            if (arg.contains("xfce4-session")) hasXfce = true;
        }

        return hasEntryPoint && hasNiceName && hasXfce;
    }
}
