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
            "if [ ! -f \"" + PREFIX + "/bin/termux-pro-app-store\" ]; then rm -f \"$HOME/Desktop/app-store.desktop\" \"$HOME/Desktop/App Store.desktop\"; fi; " +
            "if [ ! -d \"" + PREFIX + "/share/X11/xkb\" ]; then pkg install -y x11-repo xkeyboard-config coreutils; fi; " +
            "if [ ! -d \"" + PREFIX + "/share/icons/Papirus\" ]; then pkg install -y papirus-icon-theme; fi; " +
            "if ! pkg list-installed x11-repo >/dev/null 2>&1; then pkg install -y x11-repo; apt update; fi; " +
            "c_d() { local s=\"" + PREFIX + "/share/applications/$1\"; local d=\"$HOME/Desktop/$1\"; if [ -f \"$s\" ]; then cp \"$s\" \"$d\"; chmod 755 \"$d\"; fi; }; " +
            "for f in thunar.desktop xfce4-terminal.desktop xfce4-settings-manager.desktop xfce4-appearance-settings.desktop xfce4-display-settings.desktop xfce4-keyboard-settings.desktop xfce4-mouse-settings.desktop xfce4-accessibility-settings.desktop xfwm4-settings.desktop xfdesktop-settings.desktop xfce4-notifyd-config.desktop xfce4-power-manager-settings.desktop exo-preferred-applications.desktop xfce4-appfinder.desktop xfce4-about.desktop xfce4-mime-settings.desktop xfce4-screenshooter.desktop xfce4-session-logout.desktop xfce4-taskmanager.desktop xfwm4-workspace-settings.desktop thunar-settings.desktop thunar-bulk-rename.desktop termux-pro-app-store.desktop; do c_d \"$f\"; done; " +
            "if [ -x \"" + PREFIX + "/bin/termux-pro-app-store\" ] && [ ! -f \"$HOME/Desktop/termux-pro-app-store.desktop\" ]; then " +
            "ICON_PATH=$(find \"" + PREFIX + "/share/icons/Papirus\" -name \"mintinstall.svg\" -o -name \"mintinstall.png\" | head -n 1); " +
            "[ -z \"$ICON_PATH\" ] && ICON_PATH=\"mintinstall\"; " +
            "printf '[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=App Store\\nExec=" + PREFIX + "/bin/termux-pro-app-store\\nIcon='\"$ICON_PATH\"'\\nTerminal=false\\n' > \"$HOME/Desktop/termux-pro-app-store.desktop\"; " +
            "chmod 755 \"$HOME/Desktop/termux-pro-app-store.desktop\"; " +
            "fi; " +
            "printf '[Desktop Entry]\\nType=Application\\nName=Power Manager Override\\nHidden=true\\n' > \"$HOME/.config/autostart/xfce4-power-manager.desktop\"; " +
            "printf '#!/bin/bash\\nsleep 3\\nfor f in \"$HOME/Desktop\"/*.desktop; do [ -f \"$f\" ] || continue; chmod +x \"$f\"; command -v gio >/dev/null && gio set -t string \"$f\" metadata::xfce-exe-checksum \"$(sha256sum \"$f\" | cut -d\" \" -f1)\" 2>/dev/null; done\\nxfdesktop --reload 2>/dev/null\\n' > \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "chmod 755 \"" + PREFIX + "/bin/termux-pro-desktop-trust-icons\"; " +
            "printf '[Desktop Entry]\\nType=Application\\nName=Desktop Trust\\nExec=" + PREFIX + "/bin/termux-pro-desktop-trust-icons\\nOnlyShowIn=XFCE;\\nNoDisplay=true\\n' > \"$HOME/.config/autostart/termux-pro-desktop-trust.desktop\"; " +
            "xfconf-query -c xfce4-desktop -p /desktop-icons/style -n -t int -s 2 >/dev/null 2>&1; " +
            "xfconf-query -c xsettings -p /Net/IconThemeName -n -t string -s \"Papirus\" >/dev/null 2>&1; " +
            "CLASSPATH=" + DesktopRendererLauncher.getHostApkPathForShell() + "; export CLASSPATH; " +
            "mkdir -p \"$HOME/.cache\"; echo $$ > \"$HOME/.cache/termux-pro-x11.pid\"; " +
            "echo \"Starting Termux-X11 bridge...\"; " +
            "/system/bin/app_process -Xnoimage-dex2oat / --nice-name=termux-x11 com.termux.x11.CmdEntryPoint :1 " +
            "--desktop-owner=\"" + desktopLaunchToken + "\" -xstartup \"export XDG_DATA_DIRS=" + PREFIX + "/share:\\$XDG_DATA_DIRS; dbus-launch --exit-with-session startxfce4\"; " +
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
