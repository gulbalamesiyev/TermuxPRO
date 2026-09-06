package com.termux.app.terminal;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Color;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.button.MaterialButton;
import com.termux.R;
import com.termux.app.TermuxActivity;
import com.termux.app.TermuxService;
import com.termux.app.activities.SettingsActivity;
import com.termux.app.desktop.DesktopRendererLauncher;
import com.termux.app.desktop.DesktopResourceManager;
import com.termux.app.desktop.DesktopSessionOrchestrator;
import com.termux.shared.activity.ActivityUtils;
import com.termux.shared.termux.shell.command.runner.terminal.TermuxSession;
import com.termux.terminal.TerminalSession;
import com.termux.x11.DesktopNavigationState;
import com.termux.x11.MainActivity;

import java.util.List;

public final class SessionCenterController {
    private final TermuxActivity mActivity;
    private final View mRootView;
    private final RecyclerView mRecyclerView;
    private final SessionAdapter mAdapter;

    private String mLastDownloadError = null;

    public SessionCenterController(TermuxActivity activity, View rootView) {
        this.mActivity = activity;
        this.mRootView = rootView;
        this.mRecyclerView = rootView.findViewById(R.id.session_center_recycler);
        this.mRecyclerView.setLayoutManager(new LinearLayoutManager(activity));
        
        this.mAdapter = new SessionAdapter();
        this.mRecyclerView.setAdapter(mAdapter);

        rootView.findViewById(R.id.session_center_new_session).setOnClickListener(v -> 
            mActivity.getTermuxTerminalSessionClient().addNewSession(false, null)
        );

        rootView.findViewById(R.id.session_center_menu).setOnClickListener(v -> {
            ActivityUtils.startActivity(mActivity, new Intent(mActivity, SettingsActivity.class));
            mActivity.overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);
        });
    }

    public void setSessions(List<TermuxSession> sessions) {
        // Validate active owner still exists
        String activeHandle = DesktopNavigationState.getActiveDesktopOwnerHandle();
        if (activeHandle != null && sessions != null) {
            boolean found = false;
            for (TermuxSession s : sessions) {
                if (s.getTerminalSession().mHandle.equals(activeHandle)) {
                    found = true; break;
                }
            }
            if (!found) {
                DesktopNavigationState.clearDesktopOwner(activeHandle);
            }
        }
        mAdapter.setSessions(sessions);
    }

    public void setVisible(boolean visible) {
        setVisible(visible, true);
    }

    public void setVisible(boolean visible, boolean animate) {
        View overlay = mActivity.findViewById(R.id.home_overlay);

        if (!animate) {
            mRootView.setVisibility(visible ? View.VISIBLE : View.GONE);
            mRootView.setAlpha(1.0f);
            mRootView.setTranslationY(0);
            if (overlay != null) {
                overlay.setVisibility(visible ? View.GONE : View.VISIBLE);
                overlay.setAlpha(1.0f);
                overlay.setScaleX(1.0f);
                overlay.setScaleY(1.0f);
            }
            if (visible) {
                mRootView.bringToFront();
                mRootView.requestFocus();
            }
            return;
        }

        if (visible) {
            mRootView.setVisibility(View.VISIBLE);
            mRootView.setAlpha(0.0f);
            mRootView.setTranslationY(100f);
            mRootView.bringToFront();
            mRootView.requestFocus();

            mRootView.animate()
                    .alpha(1.0f)
                    .translationY(0)
                    .setDuration(300)
                    .setListener(null);

            if (overlay != null) {
                overlay.animate()
                        .alpha(0.0f)
                        .scaleX(0.8f)
                        .scaleY(0.8f)
                        .setDuration(200)
                        .withEndAction(() -> overlay.setVisibility(View.GONE));
            }
        } else {
            mRootView.animate()
                    .alpha(0.0f)
                    .translationY(100f)
                    .setDuration(250)
                    .withEndAction(() -> mRootView.setVisibility(View.GONE));

            if (overlay != null) {
                overlay.setVisibility(View.VISIBLE);
                overlay.setAlpha(0.0f);
                overlay.setScaleX(0.8f);
                overlay.setScaleY(0.8f);
                overlay.animate()
                        .alpha(1.0f)
                        .scaleX(1.0f)
                        .scaleY(1.0f)
                        .setDuration(300)
                        .setListener(null);
            }
        }
    }

    private void triggerResourceDownload(TermuxSession session) {
        mLastDownloadError = null;
        // Claim ownership so the UI updates to show the download state for this session.
        DesktopNavigationState.claimDesktopOwner(session.getTerminalSession().mHandle);
        setVisible(true); // Explicitly keep visible
        DesktopResourceManager.installResources(session, new DesktopResourceManager.ResourceDownloadCallback() {
            @Override
            public void onDownloadStarted() {
                mActivity.termuxSessionListNotifyUpdated();
            }

            @Override
            public void onDownloadFailed(String reason) {
                mLastDownloadError = reason;
                mActivity.termuxSessionListNotifyUpdated();
            }

            @Override
            public void onDownloadCompleted() {
                DesktopResourceManager.provisionAppStoreResourcesWithContext(mActivity);
                
                if (DesktopSessionOrchestrator.promoteAndStartInExistingSession(session)) {
                    mActivity.startDesktopBootProgress();
                } else if (!session.getTerminalSession().isRunning()) {
                    // If not running, restart it
                    mActivity.getTermuxService().removeTermuxSession(session.getTerminalSession());
                    DesktopSessionOrchestrator.start(mActivity.getTermuxService());
                    mActivity.startDesktopBootProgress();
                }
            }

            @Override
            public void onProgressUpdated() {
                mActivity.termuxSessionListNotifyUpdated();
            }
        });
    }

    private void showSessionSettingsMenu(TermuxSession session) {
        TerminalSession terminal = session.getTerminalSession();
        boolean isDesktop = DesktopSessionOrchestrator.isDesktopSession(session);
        boolean isRunning = terminal.isRunning();

        String[] options = {"Rename", "Delete session"};
        new AlertDialog.Builder(mActivity)
                .setTitle(isDesktop ? DesktopSessionOrchestrator.SESSION_NAME : terminal.mSessionName)
                .setItems(options, (dialog, which) -> {
                    if (which == 0) {
                        mActivity.getTermuxTerminalSessionClient().renameSession(terminal);
                    } else if (which == 1) {
                        showDeleteSessionConfirmation(session, isDesktop, isRunning);
                    }
                })
                .setNegativeButton(android.R.string.cancel, null)
                .show();
    }

    private void showDeleteSessionConfirmation(TermuxSession session, boolean isDesktop, boolean isRunning) {
        String title = isDesktop ? "Stop Desktop Session 1?" : "Delete session?";
        String message;
        if (isDesktop && isRunning) {
            message = "This closes the active XFCE desktop.";
        } else if (isRunning) {
            message = "This stops the shell and all processes running in this session.";
        } else {
            message = "This removes the exited session from the list.";
        }

        new AlertDialog.Builder(mActivity)
                .setTitle(title)
                .setMessage(message)
                .setPositiveButton(android.R.string.yes, (dialog, which) -> {
                    TermuxService service = mActivity.getTermuxService();
                    if (service == null) return;

                    if (DesktopSessionOrchestrator.isDesktopOwner(session)) {
                        DesktopNavigationState.clearDesktopOwner(session.getTerminalSession().mHandle);
                        DesktopSessionOrchestrator.killDesktopProcess();
                        MainActivity.cancelPendingLaunch();
                    }

                    // Force finish the session before removal to ensure background processes are killed
                    if (session.getTerminalSession() != null) {
                        session.getTerminalSession().finishIfRunning();
                    }

                    int removedIndex = service.removeTermuxSession(session.getTerminalSession());
                    if (removedIndex >= 0) {
                        // Refresh the entire UI state to ensure other sessions reflect the loss of a desktop owner
                        mActivity.termuxSessionListNotifyUpdated();
                    } else {
                        // Keep the authoritative UI if the service could not find the session.
                        mActivity.termuxSessionListNotifyUpdated();
                    }
                })
                .setNegativeButton(android.R.string.no, null)
                .show();
    }

    private TermuxSession findDesktopOwner() {
        if (mAdapter.mSessions == null) return null;
        for (TermuxSession session : mAdapter.mSessions) {
            if (DesktopSessionOrchestrator.isDesktopOwner(session)) {
                return session;
            }
        }
        return null;
    }

    private class SessionAdapter extends RecyclerView.Adapter<SessionViewHolder> {
        private List<TermuxSession> mSessions;

        @SuppressLint("NotifyDataSetChanged")
        public void setSessions(List<TermuxSession> sessions) {
            this.mSessions = sessions;
            notifyDataSetChanged();
        }

        @NonNull
        @Override
        public SessionViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_session_card, parent, false);
            return new SessionViewHolder(view);
        }

        @Override
        public void onBindViewHolder(@NonNull SessionViewHolder holder, int position) {
            holder.bind(mSessions.get(position));
        }

        @Override
        public int getItemCount() {
            return mSessions != null ? mSessions.size() : 0;
        }
    }

    private class SessionViewHolder extends RecyclerView.ViewHolder {
        private final TextView nameView;
        private final TextView statusView;
        private final MaterialButton cliButton;
        private final MaterialButton desktopButton;
        private final ProgressBar progressBar;
        private final View renameButton;
        private final View previewContainer;
        private final TextView previewText;

        public SessionViewHolder(@NonNull View itemView) {
            super(itemView);
            nameView = itemView.findViewById(R.id.session_card_name);
            statusView = itemView.findViewById(R.id.session_card_status);
            cliButton = itemView.findViewById(R.id.session_card_cli);
            desktopButton = itemView.findViewById(R.id.session_card_desktop);
            progressBar = itemView.findViewById(R.id.session_card_desktop_progress);
            renameButton = itemView.findViewById(R.id.session_card_rename);
            previewContainer = itemView.findViewById(R.id.session_card_preview_container);
            previewText = itemView.findViewById(R.id.session_card_preview_text);

            // Requirement 7 & 13: Make the preview scrollable.
            previewText.setMovementMethod(new ScrollingMovementMethod());
            previewText.setHorizontallyScrolling(false);
        }

        public void bind(TermuxSession session) {
            TerminalSession terminal = session.getTerminalSession();
            String name = terminal.mSessionName;
            if (name == null || name.isEmpty()) {
                name = "Session " + (getAdapterPosition() + 1);
            }
            nameView.setText(name);

            boolean isRunning = terminal.isRunning();
            statusView.setText(isRunning ? "RUNNING" : "EXITED");
            statusView.setTextColor(isRunning ? mActivity.getResources().getColor(R.color.terminal_green) : Color.GRAY);

            boolean isDesktopOwner = DesktopSessionOrchestrator.isDesktopOwner(session);

            cliButton.setOnClickListener(v -> {
                setVisible(false);
                mActivity.getTermuxTerminalSessionClient().setCurrentSession(terminal);
            });

            renameButton.setOnClickListener(v -> showSessionSettingsMenu(session));

            if (isDesktopOwner) {
                cliButton.setVisibility(View.GONE);

                DesktopNavigationState.DesktopBootState bootState = DesktopNavigationState.getDesktopBootState();
                boolean resourcesInstalled = DesktopSessionOrchestrator.areResourcesInstalled();

                // Reconciliation: check if process is actually running
                if (bootState == DesktopNavigationState.DesktopBootState.READY && !DesktopSessionOrchestrator.isDesktopProcessRunning()) {
                    DesktopNavigationState.resetDesktopBoot();
                    bootState = DesktopNavigationState.DesktopBootState.IDLE;
                }

                if (progressBar != null) progressBar.setVisibility(View.GONE);
                previewContainer.setVisibility(View.GONE);

                switch (bootState) {
                    case DOWNLOADING:
                        desktopButton.setEnabled(false);
                        desktopButton.setAlpha(0.6f);
                        
                        String phase = DesktopNavigationState.getInstallPhase();
                        int progress = DesktopNavigationState.getInstallProgress();
                        
                        String buttonText = phase + "...";
                        if (progress >= 0) buttonText = phase + " " + progress + "%";
                        
                        desktopButton.setText(buttonText);
                        desktopButton.setOnClickListener(null);

                        // Show preview
                        previewContainer.setVisibility(View.VISIBLE);
                        List<String> logs = DesktopNavigationState.getInstallLogs();
                        StringBuilder sb = new StringBuilder();
                        for (String log : logs) {
                            sb.append("> ").append(log).append("\n");
                        }
                        previewText.setText(sb.toString());

                        // Requirement 7: Auto-scroll to bottom.
                        int scrollAmount = previewText.getLayout() != null ? 
                            previewText.getLayout().getLineTop(previewText.getLineCount()) - previewText.getHeight() : 0;
                        if (scrollAmount > 0) previewText.scrollTo(0, scrollAmount);
                        break;
                    case BOOTING:
                        desktopButton.setEnabled(false);
                        desktopButton.setAlpha(0.6f);
                        desktopButton.setText(R.string.starting_x11);
                        desktopButton.setOnClickListener(null);
                        previewContainer.setVisibility(View.GONE);
                        break;
                    case READY:
                        boolean interactionBlocked = mActivity.isStartupInteractionBlocked()
                            || DesktopNavigationState.isDesktopLaunchPending();
                        desktopButton.setEnabled(isRunning && !interactionBlocked);
                        desktopButton.setAlpha(isRunning && !interactionBlocked ? 1.0f : 0.4f);
                        desktopButton.setText(R.string.desktop);
                        desktopButton.setOnClickListener(v -> {
                            if (isRunning && !DesktopNavigationState.isDesktopLaunchPending()) {
                                DesktopRendererLauncher.open(mActivity);
                                mActivity.overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);
                                mActivity.termuxSessionListNotifyUpdated();
                            }
                        });
                        previewContainer.setVisibility(View.GONE);
                        break;
                    case FAILED:
                        desktopButton.setEnabled(true);
                        desktopButton.setAlpha(1.0f);
                        if (!resourcesInstalled) {
                            String error = (mLastDownloadError != null) ? mLastDownloadError : "DOWNLOAD FAILED";
                            desktopButton.setText(error);

                            previewContainer.setVisibility(View.VISIBLE);
                            List<String> failedLogs = DesktopNavigationState.getInstallLogs();
                            StringBuilder sbFail = new StringBuilder();
                            for (String log : failedLogs) {
                                sbFail.append("> ").append(log).append("\n");
                            }
                            if (mLastDownloadError != null) sbFail.append("ERROR: ").append(mLastDownloadError);
                            previewText.setText(sbFail.toString());
                        } else {
                            String failureReason = DesktopNavigationState.getDesktopStartFailureReason();
                            desktopButton.setText((failureReason != null && !failureReason.isEmpty()) ? "START FAILED: " + failureReason : "START FAILED");
                        }
                        desktopButton.setOnClickListener(v -> triggerResourceDownload(session));
                        break;
                    case IDLE:
                    default:
                        boolean idleInteractionBlocked = mActivity.isStartupInteractionBlocked()
                            || DesktopNavigationState.isDesktopLaunchPending();
                        desktopButton.setEnabled(!idleInteractionBlocked);
                        desktopButton.setAlpha(idleInteractionBlocked ? 0.4f : 0.8f);
                        if (!resourcesInstalled) {
                            desktopButton.setText(R.string.download_resources);
                            desktopButton.setOnClickListener(v -> {
                                if (!idleInteractionBlocked) triggerResourceDownload(session);
                            });
                        } else {
                            desktopButton.setText(R.string.start_desktop);
                            desktopButton.setOnClickListener(v -> {
                                if (idleInteractionBlocked) return;
                                if (DesktopSessionOrchestrator.promoteAndStartInExistingSession(session)) {
                                    DesktopResourceManager.provisionAppStoreResourcesWithContext(mActivity);
                                    mActivity.startDesktopBootProgress();
                                } else if (!isRunning) {
                                    // If not running, restart it first
                                    mActivity.getTermuxService().removeTermuxSession(terminal);
                                    DesktopSessionOrchestrator.start(mActivity.getTermuxService());
                                    mActivity.startDesktopBootProgress();
                                }
                            });
                        }
                        break;
                }
            } else {
                cliButton.setVisibility(View.VISIBLE);
                if (progressBar != null) progressBar.setVisibility(View.GONE);
                previewContainer.setVisibility(View.GONE);

                TermuxSession owner = findDesktopOwner();
                boolean resourcesInstalled = DesktopSessionOrchestrator.areResourcesInstalled();

                    if (owner == null && isRunning) {
                        desktopButton.setEnabled(true);
                        desktopButton.setAlpha(0.8f);
                        if (!resourcesInstalled) {
                            desktopButton.setText(R.string.download_resources);
                            desktopButton.setOnClickListener(v -> triggerResourceDownload(session));
                        } else {
                            desktopButton.setText(R.string.start_desktop);
                            desktopButton.setOnClickListener(v -> {
                                if (DesktopSessionOrchestrator.promoteAndStartInExistingSession(session)) {
                                    DesktopResourceManager.provisionAppStoreResourcesWithContext(mActivity);
                                    mActivity.startDesktopBootProgress();
                                }
                            });
                        }
                    } else if (owner == null && !isRunning) {
                    // Allow starting desktop even if session is not running (will restart/recreate)
                    desktopButton.setEnabled(true);
                    desktopButton.setAlpha(0.8f);
                    desktopButton.setText(resourcesInstalled ? R.string.desktop : R.string.download_resources);
                    desktopButton.setOnClickListener(v -> {
                        if (resourcesInstalled) {
                             mActivity.getTermuxService().removeTermuxSession(terminal);
                             DesktopSessionOrchestrator.start(mActivity.getTermuxService());
                             mActivity.startDesktopBootProgress();
                        } else {
                             triggerResourceDownload(session);
                        }
                    });
                } else {
                    desktopButton.setAlpha(0.4f);
                    desktopButton.setText(R.string.single_engine);
                    desktopButton.setOnClickListener(v -> {
                        String ownerName = (owner != null && owner.getExecutionCommand().shellName != null)
                                ? owner.getExecutionCommand().shellName : "another session";

                        new AlertDialog.Builder(mActivity)
                                .setTitle("Desktop already active")
                                .setMessage("You have an active desktop session in " + ownerName + ".")
                                .setPositiveButton("EXIT", null)
                                .show();
                    });
                }
            }
            
            if (!isRunning) {
                cliButton.setAlpha(0.3f);
            }
        }
    }
}
