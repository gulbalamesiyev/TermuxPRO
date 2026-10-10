package com.termux.app.desktop;

import android.app.AlertDialog;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

public final class DistroSelectorDialog {

    public interface OnDistroSelectedListener {
        void onSelected(String distro, String desktopEnvironment);
    }

    private DistroSelectorDialog() {}

    public static void show(Context context, OnDistroSelectedListener listener) {
        View view = LayoutInflater.from(context).inflate(android.R.layout.simple_list_item_2, null); // custom layout or programmatic layout
        // Let's build a clean programmatic layout with 2 spinners (Distro and Desktop Environment)
        LinearLayout layout = new LinearLayout(context);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setPadding(40, 30, 40, 10);

        TextView distroLabel = new TextView(context);
        distroLabel.setText("Select Linux Distribution:");
        distroLabel.setPadding(0, 0, 0, 10);
        layout.addView(distroLabel);

        final Spinner distroSpinner = new Spinner(context);
        String[] distros = {
            "Ubuntu (ubuntu)",
            "Debian (debian)",
            "Arch Linux (archlinux)",
            "Fedora (fedora)",
            "Alpine Linux (alpine)",
            "OpenSUSE (opensuse)",
            "Pardus (pardus)",
            "Void Linux (voidlinux)"
        };
        String[] distroValues = { "ubuntu", "debian", "archlinux", "fedora", "alpine", "opensuse", "pardus", "voidlinux" };
        ArrayAdapter<String> distroAdapter = new ArrayAdapter<>(context, android.R.layout.simple_spinner_dropdown_item, distros);
        distroSpinner.setAdapter(distroAdapter);
        layout.addView(distroSpinner);

        TextView deLabel = new TextView(context);
        deLabel.setText("Select Desktop Environment:");
        deLabel.setPadding(0, 20, 0, 10);
        layout.addView(deLabel);

        final Spinner deSpinner = new Spinner(context);
        String[] des = {
            "XFCE (Default)",
            "MATE",
            "LXDE",
            "LXQt",
            "i3 Window Manager"
        };
        String[] deValues = { "startxfce4", "mate-session", "startlxde", "lxqt-session", "i3" };
        ArrayAdapter<String> deAdapter = new ArrayAdapter<>(context, android.R.layout.simple_spinner_dropdown_item, des);
        deSpinner.setAdapter(deAdapter);
        layout.addView(deSpinner);

        new AlertDialog.Builder(context)
            .setTitle("Configure Desktop Session")
            .setView(layout)
            .setPositiveButton("Start Desktop", (dialog, which) -> {
                int distroIdx = distroSpinner.getSelectedItemPosition();
                int deIdx = deSpinner.getSelectedItemPosition();
                String selectedDistro = distroValues[Math.max(0, Math.min(distroIdx, distroValues.length - 1))];
                String selectedDE = deValues[Math.max(0, Math.min(deIdx, deValues.length - 1))];
                if (listener != null) {
                    listener.onSelected(selectedDistro, selectedDE);
                }
            })
            .setNegativeButton("Cancel", null)
            .show();
    }
}
