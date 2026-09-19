package com.termux.app.desktop;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.termux.app.TermuxService;
import com.termux.shared.termux.TermuxConstants;
import com.termux.shared.termux.shell.command.runner.terminal.TermuxSession;
import com.termux.x11.DesktopNavigationState;

import android.os.Handler;
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
        return new File(TermuxConstants.TERMUX_BIN_PREFIX_DIR_PATH + "/xfce4-session").exists();
    }

    private static String buildDesktopStartCommand(String desktopLaunchToken) {
        String PREFIX = TermuxConstants.TERMUX_PREFIX_DIR_PATH;
        String logHandle = DesktopNavigationState.getActiveInstallLogHandle();
        String logCapture = "";
        if (logHandle != null) {
            String logFile = DesktopResourceManager.getLogFilePath(logHandle)
                    .replace("'", "'\"'\"'");
            logCapture = "exec > >(tee -a '" + logFile + "') 2>&1; ";
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
            "printf '[Desktop Entry]\\nType=Application\\nName=Power Manager Override\\nHidden=true\\n' > \"$HOME/.config/autostart/xfce4-power-manager.desktop\"; " +
            "printf \"#\\\\x21/bin/bash\\ntrust_file() { [ -f \\\"\\$1\\\" ] || return; chmod +x \\\"\\$1\\\"; command -v gio >/dev/null && gio set -t string \\\"\\$1\\\" metadata::xfce-exe-checksum \\\"\\$(sha256sum \\\"\\$1\\\" | cut -d' ' -f1)\\\" 2>/dev/null; }; \" > \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "printf \"for f in \\\"\\$HOME/Desktop\\\"/*.desktop; do trust_file \\\"\\$f\\\"; done; xfdesktop --reload 2>/dev/null; \" >> \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "printf \"if command -v inotifywait >/dev/null; then inotifywait -m -e create,moved_to \\\"\\$HOME/Desktop\\\" --format '%%f' | while read NEW; do [[ \\\"\\$NEW\\\" == *.desktop ]] && { sleep 0.5; trust_file \\\"\\$HOME/Desktop/\\$NEW\\\"; }; done; fi\\n\" >> \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "chmod 755 \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "printf '[Desktop Entry]\\nType=Application\\nName=Desktop Trust\\nExec=" + PREFIX + "/bin/termux-pro-desktop-trust-icons\\nOnlyShowIn=XFCE;\\nNoDisplay=true\\n' > \"$HOME/.config/autostart/termux-pro-desktop-trust.desktop\"; " +
            "xfconf-query -c xfce4-desktop -p /desktop-icons/style -n -t int -s 2 >/dev/null 2>&1; " +
            "xfconf-query -c xsettings -p /Net/IconThemeName -n -t string -s \"Papirus\" >/dev/null 2>&1; " +
            "CLASSPATH=" + DesktopRendererLauncher.getHostApkPathForShell() + "; export CLASSPATH; " +
            "mkdir -p \"$HOME/.cache\"; echo $$ > \"$HOME/.cache/termux-pro-x11.pid\"; " +
            "echo \"Starting Termux-X11 bridge...\"; " +
            "/system/bin/app_process -Xnoimage-dex2oat / --nice-name=termux-x11 com.termux.x11.CmdEntryPoint :1 " +
            "--desktop-owner=\"" + desktopLaunchToken + "\" -xstartup \"export PATH=" + PREFIX + "/bin:\\$PATH; export XDG_DATA_DIRS=" + PREFIX + "/share:\\$XDG_DATA_DIRS; dbus-launch --exit-with-session startxfce4\"; " +
            "x11_status=$?; " +
            "echo \"X11 bridge stopped with status $x11_status\"; " +
            "rm -f \"$HOME/.cache/termux-pro-x11.pid\"; " +
            "exec \"" + PREFIX + "/bin/bash\" -l";
    }

    private DesktopSessionOrchestrator() {}

    @Nullable
    public static TermuxSession start(TermuxService service) {
        String desktopLaunchToken = "desktop-" + UUID.randomUUID();
        String command = buildDesktopStartCommand(desktopLaunchToken);

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
