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
        int[] distroIcons = {
            R.drawable.ic_distro_ubuntu,
            R.drawable.ic_distro_debian,
            R.drawable.ic_distro_arch,
            R.drawable.ic_distro_fedora,
            R.drawable.ic_distro_alpine,
            R.drawable.ic_distro_opensuse,
            R.drawable.ic_distro_pardus,
            R.drawable.ic_distro_void
        };
        
        CustomDistroAdapter distroAdapter = new CustomDistroAdapter(context, distros, distroIcons);
        distroSpinner.setAdapter(distroAdapter);

        String[] des = {
            "XFCE (Default)",
            "MATE",
            "LXDE",
            "LXQt",
            "i3 Window Manager"
        };
        String[] deValues = { "startxfce4", "mate-session", "startlxde", "lxqt-session", "i3" };
        int[] deIcons = {
            R.drawable.ic_de_xfce,
            R.drawable.ic_de_mate,
            R.drawable.ic_de_lxde,
            R.drawable.ic_de_lxqt,
            R.drawable.ic_de_i3
        };
        
        CustomDistroAdapter deAdapter = new CustomDistroAdapter(context, des, deIcons);
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

    private static class CustomDistroAdapter extends ArrayAdapter<String> {
        private final Context mContext;
        private final String[] mItems;
        private final int[] mIconResIds;

        public CustomDistroAdapter(@NonNull Context context, String[] items, int[] iconResIds) {
            super(context, 0, items);
            this.mContext = context;
            this.mItems = items;
            this.mIconResIds = iconResIds;
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
            View view = convertView != null ? convertView : LayoutInflater.from(mContext).inflate(R.layout.item_distro_spinner, parent, false);
            ImageView iconView = view.findViewById(R.id.img_distro_icon);
            TextView nameView = view.findViewById(R.id.text_distro_name);

            if (position >= 0 && position < mIconResIds.length) {
                iconView.setImageResource(mIconResIds[position]);
            }
            nameView.setText(mItems[position]);
            return view;
        }
    }
}
