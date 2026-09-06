package com.termux.app.terminal;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.TextUtils;
import android.text.style.StyleSpan;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;

import com.termux.R;
import com.termux.app.TermuxActivity;
import com.termux.app.desktop.DesktopRendererLauncher;
import com.termux.app.desktop.DesktopSessionOrchestrator;
import com.termux.shared.termux.shell.command.runner.terminal.TermuxSession;
import com.termux.shared.theme.NightMode;
import com.termux.shared.theme.ThemeUtils;
import com.termux.terminal.TerminalSession;
import com.termux.x11.DesktopNavigationState;

import java.util.List;

public class TermuxSessionsListViewController extends ArrayAdapter<TermuxSession> implements AdapterView.OnItemClickListener, AdapterView.OnItemLongClickListener {

    final TermuxActivity mActivity;

    final StyleSpan boldSpan = new StyleSpan(Typeface.BOLD);
    final StyleSpan italicSpan = new StyleSpan(Typeface.ITALIC);

    public TermuxSessionsListViewController(TermuxActivity activity, List<TermuxSession> sessionList) {
        super(activity.getApplicationContext(), R.layout.item_terminal_sessions_list, sessionList);
        this.mActivity = activity;
    }

    @SuppressLint("SetTextI18n")
    @NonNull
    @Override
    public View getView(int position, View convertView, @NonNull ViewGroup parent) {
        View sessionRowView = convertView;
        if (sessionRowView == null) {
            LayoutInflater inflater = mActivity.getLayoutInflater();
            sessionRowView = inflater.inflate(R.layout.item_terminal_sessions_list, parent, false);
        }

        TextView sessionTitleView = sessionRowView.findViewById(R.id.session_title);

        TerminalSession sessionAtRow = getItem(position).getTerminalSession();
        if (sessionAtRow == null) {
            sessionTitleView.setText("null session");
            return sessionRowView;
        }

        boolean shouldEnableDarkTheme = ThemeUtils.shouldEnableDarkTheme(mActivity, NightMode.getAppNightMode().getName());

        if (shouldEnableDarkTheme) {
            sessionTitleView.setBackground(
                ContextCompat.getDrawable(mActivity, R.drawable.session_background_black_selected)
            );
        }

        String name = sessionAtRow.mSessionName;
        String sessionTitle = sessionAtRow.getTitle();

        String numberPart = "[" + (position + 1) + "] ";
        String sessionNamePart = (TextUtils.isEmpty(name) ? "" : name);
        String sessionTitlePart = (TextUtils.isEmpty(sessionTitle) ? "" : ((sessionNamePart.isEmpty() ? "" : "\n") + sessionTitle));

        String fullSessionTitle = numberPart + sessionNamePart + sessionTitlePart;
        SpannableString fullSessionTitleStyled = new SpannableString(fullSessionTitle);
        fullSessionTitleStyled.setSpan(boldSpan, 0, numberPart.length() + sessionNamePart.length(), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        fullSessionTitleStyled.setSpan(italicSpan, numberPart.length() + sessionNamePart.length(), fullSessionTitle.length(), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);

        sessionTitleView.setText(fullSessionTitleStyled);

        boolean sessionRunning = sessionAtRow.isRunning();

        if (sessionRunning) {
            sessionTitleView.setPaintFlags(sessionTitleView.getPaintFlags() & ~Paint.STRIKE_THRU_TEXT_FLAG);
        } else {
            sessionTitleView.setPaintFlags(sessionTitleView.getPaintFlags() | Paint.STRIKE_THRU_TEXT_FLAG);
        }
        int defaultColor = shouldEnableDarkTheme ? Color.WHITE : Color.BLACK;
        int color = sessionRunning || sessionAtRow.getExitStatus() == 0 ? defaultColor : Color.RED;
        sessionTitleView.setTextColor(color);
        return sessionRowView;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        TermuxSession clickedSession = getItem(position);
        mActivity.getTermuxTerminalSessionClient().setCurrentSession(clickedSession.getTerminalSession());
        mActivity.getDrawer().closeDrawers();
    }

    @Override
    public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
        TermuxSession selectedSession = getItem(position);
        if (selectedSession == null) return false;
        showSessionActions(selectedSession);
        return true;
    }

    private boolean isDesktopSession(TermuxSession session) {
        return DesktopSessionOrchestrator.isDesktopSession(session);
    }

    private boolean isSessionRunning(TermuxSession session) {
        return session.getTerminalSession() != null
                && session.getTerminalSession().isRunning();
    }

    private String sessionTitle(TermuxSession session, boolean isDesktop, boolean isRunning) {
        String title = isDesktop
                ? DesktopSessionOrchestrator.SESSION_NAME
                : session.getExecutionCommand().shellName;
        return isRunning ? title : title + " (exited)";
    }

    private void openTerminal(TermuxSession session) {
        mActivity.getTermuxTerminalSessionClient()
                .setCurrentSession(session.getTerminalSession());
        mActivity.getDrawer().closeDrawers();
    }

    private void showSessionActions(TermuxSession session) {
        boolean desktop = isDesktopSession(session);
        boolean running = isSessionRunning(session);

        String openAction = desktop && running ? "Open desktop" : "Open terminal";
        String[] options = {openAction, "Rename", "Delete session"};

        new AlertDialog.Builder(mActivity)
                .setTitle(sessionTitle(session, desktop, running))
                .setItems(options, (dialog, which) -> {
                    String selection = options[which];
                    switch (selection) {
                        case "Open desktop":
                            if (DesktopSessionOrchestrator.isDesktopProcessRunning()) {
                                DesktopRendererLauncher.open(mActivity);
                            } else {
                                DesktopSessionOrchestrator.restartInExistingSession(session);
                            }
                            break;
                        case "Open terminal":
                            openTerminal(session);
                            break;
                        case "Rename":
                            mActivity.getTermuxTerminalSessionClient()
                                    .renameSession(session.getTerminalSession());
                            break;
                        case "Delete session":
                            showDeleteSessionConfirmation(session, desktop, running);
                            break;
                    }
                })
                .show();
    }

    private void showDeleteSessionConfirmation(TermuxSession session,
                                               boolean desktop,
                                               boolean running) {
        String title = desktop ? "Stop Desktop Session 1?" : "Delete session?";
        String message;
        if (desktop && running) {
            message = "This closes the active XFCE desktop.";
        } else if (running) {
            message = "This stops the shell and all processes running in this session.";
        } else {
            message = "This removes the exited session from the list.";
        }

        new AlertDialog.Builder(mActivity)
                .setTitle(title)
                .setMessage(message)
                .setPositiveButton(android.R.string.yes, (dialog, which) -> {
                    if (DesktopSessionOrchestrator.isDesktopOwner(session)) {
                        DesktopNavigationState.clearDesktopOwner(session.getTerminalSession().mHandle);
                        DesktopSessionOrchestrator.killDesktopProcess();
                    }
                    if (session.getTerminalSession() != null) {
                        session.getTerminalSession().finishIfRunning();
                    }
                    mActivity.getTermuxService().removeTermuxSession(session.getTerminalSession());
                })
                .setNegativeButton(android.R.string.no, null)
                .show();
    }

}
