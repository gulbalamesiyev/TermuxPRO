package com.termux.app.desktop;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.termux.R;

public final class DistroSelectorDialog {

    public interface OnDistroSelectedListener {
        void onSelected(String distro, String desktopEnvironment);
    }

    private DistroSelectorDialog() {}

    public static void show(Context context, OnDistroSelectedListener listener) {
        View view = LayoutInflater.from(context).inflate(R.layout.dialog_distro_selector, null);

        Spinner distroSpinner = view.findViewById(R.id.spinner_distro);
        Spinner deSpinner = view.findViewById(R.id.spinner_de);

        String[] distros = {
            "🟠 Ubuntu (ubuntu)",
            "🔴 Debian (debian)",
            "🔷 Arch Linux (archlinux)",
            "🔵 Fedora (fedora)",
            "🏔️ Alpine Linux (alpine)",
            "🟢 OpenSUSE (opensuse)",
            "🟥 Pardus (pardus)",
            "⚫ Void Linux (voidlinux)"
        };
        String[] distroValues = { "ubuntu", "debian", "archlinux", "fedora", "alpine", "opensuse", "pardus", "voidlinux" };
        ArrayAdapter<String> distroAdapter = new ArrayAdapter<>(context, android.R.layout.simple_spinner_dropdown_item, distros);
        distroSpinner.setAdapter(distroAdapter);

        String[] des = {
            "🖥️ XFCE (Default)",
            "🪟 MATE",
            "🪶 LXDE",
            "🍃 LXQt",
            "⚡ i3 Window Manager"
        };
        String[] deValues = { "startxfce4", "mate-session", "startlxde", "lxqt-session", "i3" };
        ArrayAdapter<String> deAdapter = new ArrayAdapter<>(context, android.R.layout.simple_spinner_dropdown_item, des);
        deSpinner.setAdapter(deAdapter);

        new MaterialAlertDialogBuilder(context)
            .setView(view)
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
