package com.termux.app.desktop;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.termux.shared.termux.TermuxConstants;
import com.termux.shared.termux.shell.command.runner.terminal.TermuxSession;
import com.termux.terminal.TerminalSession;
import com.termux.x11.DesktopNavigationState;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.List;
import java.util.UUID;

/**
 * Manages the installation of X11/XFCE resources via shell command injection.
 */
public final class DesktopResourceManager {
    private static final String LOG_TAG = "DesktopResourceManager";
    private static Context sContext = null;

    public interface ResourceDownloadCallback {
        void onDownloadStarted();
        void onDownloadFailed(String reason);
        void onDownloadCompleted();
        void onProgressUpdated();
    }

    private static ResourceDownloadCallback sCallback;
    private static long sLastRefreshTime = 0;
    private static final long REFRESH_THROTTLE_MS = 500;
    private static final long FALLBACK_TIMEOUT_MS = 15000;
    private static final Handler sHandler = new Handler(Looper.getMainLooper());
    private static long sLogFileOffset = 0;
    private static String sPendingOutput = "";

    private static final Runnable sFallbackRunnable = () -> {
        if (DesktopNavigationState.getDesktopBootState() == DesktopNavigationState.DesktopBootState.DOWNLOADING) {
            List<String> logs = DesktopNavigationState.getInstallLogs();
            boolean onlySyntheticLog = true;
            for (String log : logs) {
                if (!log.contains("Waiting") && !log.contains("Starting")) {
                    onlySyntheticLog = false;
                    break;
                }
            }
            if (onlySyntheticLog) {
                DesktopNavigationState.setDesktopFailed();
                DesktopNavigationState.addInstallLog("No CLI output received. Check connection or terminal.");
                if (sCallback != null) sCallback.onDownloadFailed("Timeout");
            }
        }
    };

    private DesktopResourceManager() {}

    public static void setContext(Context context) {
        sContext = context;
    }

    public static String getLogFilePath(String handle) {
        return TermuxConstants.TERMUX_VAR_PREFIX_DIR_PATH + "/log/termux-pro-desktop-install-" + handle + ".log";
    }

    private static String shellQuote(String value) {
        return "'" + value.replace("'", "'\"'\"'") + "'";
    }

    public static void installResources(TermuxSession session, ResourceDownloadCallback callback) {
        if (session == null || session.getTerminalSession() == null) {
            if (callback != null) callback.onDownloadFailed("Invalid session.");
            return;
        }

        TerminalSession terminal = session.getTerminalSession();

        if (DesktopNavigationState.getDesktopBootState() == DesktopNavigationState.DesktopBootState.DOWNLOADING
                && terminal.mHandle.equals(DesktopNavigationState.getActiveInstallSessionHandle())) {
            Log.i(LOG_TAG, "Installation already in progress for session " + terminal.mHandle + "; reattaching callback.");
            sCallback = callback;
            if (callback != null) {
                sHandler.post(callback::onDownloadStarted);
            }
            return;
        }

        sCallback = callback;
        String handle = UUID.randomUUID().toString().substring(0, 8);

        // Ensure C source is available for compilation
        if (sContext != null) {
            try {
                String PREFIX = TermuxConstants.TERMUX_PREFIX_DIR_PATH;
                String srcDir = PREFIX + "/src/app-store";
                String srcFile = srcDir + "/termux-pro-app-store.c";
                new File(srcDir).mkdirs();
                InputStream is = sContext.getAssets().open("termux-pro-app-store.c");
                Files.copy(is, Paths.get(srcFile), StandardCopyOption.REPLACE_EXISTING);
            } catch (IOException e) {
                Log.e(LOG_TAG, "Failed to copy App Store source asset", e);
            }
        } else {
            Log.w(LOG_TAG, "Cannot copy source: sContext is null");
        }

        DesktopNavigationState.setActiveInstallSessionHandle(terminal.mHandle);
        DesktopNavigationState.setActiveInstallLogHandle(handle);
        DesktopNavigationState.startDesktopDownload();
        DesktopNavigationState.setInstallPhase("INITIALIZING");
        DesktopNavigationState.setInstallProgress(-1);
        DesktopNavigationState.clearInstallLogs();
        DesktopNavigationState.addInstallLog("Waiting for CLI output...");
        
        sLogFileOffset = 0;
        sPendingOutput = "";

        if (callback != null) {
            sHandler.post(callback::onDownloadStarted);
        }

        String logFile = getLogFilePath(handle);
        String logDirectory = TermuxConstants.TERMUX_VAR_PREFIX_DIR_PATH + "/log";
        String installScript = "\n" +
            "mkdir -p " + shellQuote(logDirectory) + ";\n" +
            "export TERM=xterm-256color;\n" +
            "set -o pipefail 2>/dev/null || true;\n" +
            "LOG_FILE=" + shellQuote(logFile) + ";\n" +
            "{\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Preparing environment...\\n\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PHASE:DOWNLOADING\\n\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PROGRESS:5\\n\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Updating package lists...\\n\";\n" +
            "  apt update;\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PROGRESS:15\\n\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Installing x11-repo...\\n\";\n" +
            "  pkg install -y x11-repo || exit 20;\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PROGRESS:25\\n\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Downloading XFCE, X11, Python, Node.js, Git and Vim...\\n\";\n" +
            "  pkg install -y xkeyboard-config dbus gvfs xfce4 xfce4-terminal thunar libxres gtk3 clang pkg-config coreutils papirus-icon-theme python nodejs git vim || exit 21;\n" +
            "  gtk-update-icon-cache -f \"$PREFIX/share/icons/Papirus\" 2>/dev/null;\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Creating desktop shortcuts for core tools...\\n\";\n" +
            "  for tool in node git vim; do\n" +
            "    FILE=\"$PREFIX/share/applications/$tool-custom.desktop\";\n" +
            "    [ ! -f \"$FILE\" ] && printf \"[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=$tool\\nExec=xfce4-terminal -e $tool\\nIcon=utilities-terminal\\nTerminal=false\\nCategories=Development;\\n\" > \"$FILE\";\n" +
            "    cp \"$FILE\" \"$HOME/Desktop/\" 2>/dev/null;\n" +
            "    chmod 755 \"$HOME/Desktop/$(basename \"$FILE\")\" 2>/dev/null;\n" +
            "  done;\n" +
            "  gio set -t string \"$HOME/Desktop/node-custom.desktop\" metadata::xfce-exe-checksum \"$(sha256sum \"$HOME/Desktop/node-custom.desktop\" | cut -d' ' -f1)\" 2>/dev/null;\n" +
            "  gio set -t string \"$HOME/Desktop/git-custom.desktop\" metadata::xfce-exe-checksum \"$(sha256sum \"$HOME/Desktop/git-custom.desktop\" | cut -d' ' -f1)\" 2>/dev/null;\n" +
            "  gio set -t string \"$HOME/Desktop/vim-custom.desktop\" metadata::xfce-exe-checksum \"$(sha256sum \"$HOME/Desktop/vim-custom.desktop\" | cut -d' ' -f1)\" 2>/dev/null;\n" +
            "  sync;\n" +
            "  printf \"TERMUX_PRO_DESKTOP_LOG:Compiling native App Store...\\n\";\n" +
            "  clang \"$PREFIX/src/app-store/termux-pro-app-store.c\" -o \"$PREFIX/bin/termux-pro-app-store\" $(pkg-config --cflags --libs gtk+-3.0) -lpthread || exit 22;\n" +
            "  chmod 755 \"$PREFIX/bin/termux-pro-app-store\";\n" +
            "  mkdir -p \"$PREFIX/share/applications\";\n" +
            "  ICON_PATH=$(find \"$PREFIX/share/icons/Papirus\" -name \"mintinstall.svg\" -o -name \"mintinstall.png\" | head -n 1);\n" +
            "  [ -z \"$ICON_PATH\" ] && ICON_PATH=\"mintinstall\";\n" +
            "  printf '[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=App Store\\nExec=%%s/bin/termux-pro-app-store\\nIcon=%%s\\nTerminal=false\\n' \"$PREFIX\" \"$ICON_PATH\" > \"$PREFIX/share/applications/termux-pro-app-store.desktop\";\n" +
            "  chmod 755 \"$PREFIX/share/applications/termux-pro-app-store.desktop\";\n" +
            "  sync;\n" +
            "} 2>&1 | tee -a \"$LOG_FILE\";\n" +
            "pipeline_status=${PIPESTATUS[0]};\n" +
            "if [ \"$pipeline_status\" -eq 0 ]; then\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PHASE:FINALIZING\\n\" | tee -a \"$LOG_FILE\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_PROGRESS:100\\n\" | tee -a \"$LOG_FILE\";\n" +
            "  printf \"TERMUX_PRO_DESKTOP_INSTALL_SUCCEEDED\\n\" | tee -a \"$LOG_FILE\";\n" +
            "else\n" +
            "  printf \"TERMUX_PRO_DESKTOP_INSTALL_FAILED:Installation pipeline failed (exit %s)\\n\" \"$pipeline_status\" | tee -a \"$LOG_FILE\";\n" +
            "fi\n";

        sHandler.postDelayed(() -> {
            if (terminal.mHandle.equals(DesktopNavigationState.getActiveInstallSessionHandle())
                    && handle.equals(DesktopNavigationState.getActiveInstallLogHandle())) {
                terminal.write("bash -lc " + shellQuote(installScript) + "\n");
                sHandler.removeCallbacks(sFallbackRunnable);
                sHandler.postDelayed(sFallbackRunnable, FALLBACK_TIMEOUT_MS);
            }
        }, 1500);
    }

    public static void onSessionTextChanged(TerminalSession session) {
        String handle = DesktopNavigationState.getActiveInstallLogHandle();
        if (handle == null) return;

        String sessionHandle = DesktopNavigationState.getActiveInstallSessionHandle();
        if (sessionHandle == null || !sessionHandle.equals(session.mHandle)) return;

        File logFile = new File(getLogFilePath(handle));
        if (!logFile.exists()) return;

        sHandler.removeCallbacks(sFallbackRunnable);

        boolean changed = false;
        try (RandomAccessFile raf = new RandomAccessFile(logFile, "r")) {
            raf.seek(sLogFileOffset);
            byte[] buffer = new byte[8192];
            int bytesRead;
            StringBuilder content = new StringBuilder(sPendingOutput);
            
            while ((bytesRead = raf.read(buffer)) != -1) {
                content.append(new String(buffer, 0, bytesRead, StandardCharsets.UTF_8));
            }
            sLogFileOffset = raf.getFilePointer();

            String fullText = content.toString();
            int lastNewline = fullText.lastIndexOf('\n');
            if (lastNewline != -1) {
                String toProcess = fullText.substring(0, lastNewline);
                sPendingOutput = fullText.substring(lastNewline + 1);
                
                String[] lines = toProcess.split("\n");
                for (String line : lines) {
                    String lineContent = line.replaceAll("\u001B\\[[;\\d]*[A-Za-z]", "")
                                             .replaceAll("[\\x00-\\x08\\x0B\\x0C\\x0E-\\x1F\\x7F]", "")
                                             .trim();
                    if (lineContent.isEmpty()) continue;

                    if (lineContent.contains("TERMUX_PRO_DESKTOP_INSTALL_SUCCEEDED")) {
                        completeInstall();
                        return;
                    } else if (lineContent.contains("TERMUX_PRO_DESKTOP_INSTALL_FAILED:")) {
                        failInstall(lineContent.substring(lineContent.indexOf("FAILED:") + 7));
                        return;
                    } else if (lineContent.contains("TERMUX_PRO_DESKTOP_PHASE:")) {
                        String phase = lineContent.substring(lineContent.indexOf("PHASE:") + 6);
                        if (!phase.equals(DesktopNavigationState.getInstallPhase())) {
                            DesktopNavigationState.setInstallPhase(phase);
                            changed = true;
                        }
                    } else if (lineContent.contains("TERMUX_PRO_DESKTOP_PROGRESS:")) {
                        try {
                            int progress = Integer.parseInt(lineContent.substring(lineContent.indexOf("PROGRESS:") + 9).trim());
                            if (progress != DesktopNavigationState.getInstallProgress()) {
                                DesktopNavigationState.setInstallProgress(progress);
                                changed = true;
                            }
                        } catch (NumberFormatException ignored) {}
                    }

                    // Always add every line to the log for "unfiltered" experience as requested
                    DesktopNavigationState.addInstallLog(lineContent);
                    changed = true;

                    // Still perform stage detection to update UI progress indicators
                    if (lineContent.contains("Get:") || lineContent.contains("Ign:") || lineContent.contains("Hit:") || lineContent.contains("Reading package lists") || lineContent.contains("Fetched")) {
                        DesktopNavigationState.setInstallPhase("DOWNLOADING");
                        int progress = Math.max(10, Math.min(70, DesktopNavigationState.getInstallProgress() + 1));
                        if (progress != DesktopNavigationState.getInstallProgress()) {
                            DesktopNavigationState.setInstallProgress(progress);
                        }
                    } else if (lineContent.contains("Preparing to unpack") || lineContent.contains("Unpacking") || lineContent.contains("Selecting previously unselected")) {
                        DesktopNavigationState.setInstallPhase("INSTALLING");
                        int progress = Math.max(60, Math.min(90, DesktopNavigationState.getInstallProgress() == -1 ? 60 : DesktopNavigationState.getInstallProgress()));
                        if (progress != DesktopNavigationState.getInstallProgress()) {
                            DesktopNavigationState.setInstallProgress(progress);
                        }
                    } else if (lineContent.contains("Setting up") || lineContent.contains("Processing triggers") || lineContent.contains("update-alternatives")) {
                        DesktopNavigationState.setInstallPhase("FINALIZING");
                        int progress = Math.max(85, Math.min(99, DesktopNavigationState.getInstallProgress() == -1 ? 85 : DesktopNavigationState.getInstallProgress()));
                        if (progress != DesktopNavigationState.getInstallProgress()) {
                            DesktopNavigationState.setInstallProgress(progress);
                        }
                    }
                }
            } else {
                sPendingOutput = fullText;
            }
        } catch (IOException e) {
            // Ignore
        }
        
        if (changed && sCallback != null) {
            long now = System.currentTimeMillis();
            if (now - sLastRefreshTime > REFRESH_THROTTLE_MS) {
                sLastRefreshTime = now;
                sHandler.post(() -> {
                    if (sCallback != null) sCallback.onProgressUpdated();
                });
            }
        }
    }

    private static void completeInstall() {
        sHandler.removeCallbacks(sFallbackRunnable);
        DesktopNavigationState.setInstallPhase("FINALIZING");
        DesktopNavigationState.setInstallProgress(100);
        if (sCallback != null) {
            sCallback.onDownloadCompleted();
            sCallback = null;
        }
    }

    private static void failInstall(String reason) {
        sHandler.removeCallbacks(sFallbackRunnable);
        sLogFileOffset = 0;
        sPendingOutput = "";
        DesktopNavigationState.setActiveInstallSessionHandle(null);
        DesktopNavigationState.setActiveInstallLogHandle(null);
        sHandler.post(() -> {
            if (sCallback != null) {
                DesktopNavigationState.setDesktopFailed();
                sCallback.onDownloadFailed(reason);
                sCallback = null;
            }
        });
    }

    /**
     * Provisions GTK3 Native App Store resources
     */
    public static void provisionAppStoreResourcesWithContext(Context context) {
        if (context == null) return;
        new Thread(() -> {
            try {
                String PREFIX = TermuxConstants.TERMUX_PREFIX_DIR_PATH;
                String binPath = PREFIX + "/bin/termux-pro-app-store";
                String srcDir = PREFIX + "/src/app-store";
                String srcFile = srcDir + "/termux-pro-app-store.c";

                // Ensure build tools, sync tools and certificates are present
                new ProcessBuilder(PREFIX + "/bin/bash", "-c", "pkg install -y clang pkg-config gtk3 curl ca-certificates").start().waitFor();

                // Ensure directories
                new ProcessBuilder(PREFIX + "/bin/bash", "-c", "mkdir -p " + srcDir + " && mkdir -p " + PREFIX + "/var/lib/termux-pro").start().waitFor();

                // Copy asset to Termux environment
                InputStream is = context.getAssets().open("termux-pro-app-store.c");
                Files.copy(is, Paths.get(srcFile), StandardCopyOption.REPLACE_EXISTING);

                // Compile native app with full path
                String compileCmd = "clang " + srcFile + " -o " + binPath + " $(pkg-config --cflags --libs gtk+-3.0) -lpthread";
                Log.d(LOG_TAG, "Compiling native App Store: " + compileCmd);
                ProcessBuilder pb = new ProcessBuilder(PREFIX + "/bin/bash", "-c", compileCmd);
                pb.environment().put("PATH", PREFIX + "/bin:" + System.getenv("PATH"));
                pb.environment().put("PREFIX", PREFIX);
                Process p = pb.start();
                int exitCode = p.waitFor();
                
                if (exitCode == 0) {
                    new ProcessBuilder(PREFIX + "/bin/bash", "-c", "chmod 755 " + binPath).start().waitFor();
                    Log.d(LOG_TAG, "Native App Store compiled successfully");
                    
                    // Create desktop icon in share/applications
                    String appsDir = PREFIX + "/share/applications";
                    String desktopFile = appsDir + "/termux-pro-app-store.desktop";
                    
                    // Requirement: Use a highly professional Blue App Store icon (Papirus Software Center)
                    String desktopIconCmd = "mkdir -p " + appsDir + " && " +
                        "printf '[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=App Store\\nExec=" + binPath + "\\nIcon=org.gnome.Software\\nTerminal=false\\nCategories=System;\\n' > " + desktopFile + " && " +
                        "chmod 755 " + desktopFile + " && " +
                        "rm -f $HOME/Desktop/termux-pro-app-store.desktop && " +
                        "cp " + desktopFile + " $HOME/Desktop/ 2>/dev/null && " +
                        "chmod 755 $HOME/Desktop/termux-pro-app-store.desktop 2>/dev/null && " +
                        "if command -v gio >/dev/null; then " +
                        "  gio set -t string $HOME/Desktop/termux-pro-app-store.desktop metadata::xfce-exe-checksum \"$(sha256sum $HOME/Desktop/termux-pro-app-store.desktop | cut -d' ' -f1)\" 2>/dev/null; " +
                        "fi; " +
                        "touch $HOME/Desktop/termux-pro-app-store.desktop && " +
                        "sync";
                    
                    new ProcessBuilder(PREFIX + "/bin/bash", "-c", desktopIconCmd).start().waitFor();
                    new ProcessBuilder(PREFIX + "/bin/bash", "-c", "sync").start().waitFor();
                    Log.d(LOG_TAG, "Desktop icon created successfully at " + desktopFile);
                } else {
                    Log.e(LOG_TAG, "Compilation failed with exit code " + exitCode);
                }
            } catch (Exception e) {
                Log.e(LOG_TAG, "Provisioning failed", e);
            }
        }).start();
    }
}
