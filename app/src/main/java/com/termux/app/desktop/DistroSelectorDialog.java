package com.termux.app.desktop;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

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
        
        CustomSpinnerAdapter distroAdapter = new CustomSpinnerAdapter(context, distros, R.drawable.ic_distro_linux);
        distroSpinner.setAdapter(distroAdapter);

        String[] des = {
            "XFCE (Default)",
            "MATE",
            "LXDE",
            "LXQt",
            "i3 Window Manager"
        };
        String[] deValues = { "startxfce4", "mate-session", "startlxde", "lxqt-session", "i3" };
        
        CustomSpinnerAdapter deAdapter = new CustomSpinnerAdapter(context, des, R.drawable.ic_desktop_env);
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

    private static class CustomSpinnerAdapter extends ArrayAdapter<String> {
        private final Context mContext;
        private final String[] mItems;
        private final int mIconResId;

        public CustomSpinnerAdapter(@NonNull Context context, String[] items, int iconResId) {
            super(context, R.layout.item_distro_spinner, items);
            this.mContext = context;
            this.mItems = items;
            this.mIconResId = iconResId;
        }

        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            return createCustomView(position, convertView, parent);
        }

        @Override
        public View getDropDownView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            return createCustomView(position, convertView, parent);
        }

        private View createCustomView(int position, View convertView, ViewGroup parent) {
            View view = convertView;
            if (view == null) {
                view = LayoutInflater.from(mContext).inflate(R.layout.item_distro_spinner, parent, false);
            }
            ImageView iconView = view.findViewById(R.id.img_distro_icon);
            TextView nameView = view.findViewById(R.id.text_distro_name);

            iconView.setImageResource(mIconResId);
            nameView.setText(mItems[position]);
            return view;
        }
    }
}
