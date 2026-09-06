# Termux Pro Navigation Audit Results

## Current Navigation Structure

1. **CLI Screen (TerminalView)**:
    - **Swipe Gesture**: A left-to-right swipe opens the `DrawerLayout` containing the session list and settings.
    - **Home Overlay**: A floating button at the top-right (`home_overlay`) that opens the **Session Center**.
    - **Settings Access**: Only accessible via the drawer (requires a swipe or programmatic open).

2. **Drawer (left_drawer)**:
    - Contains:
        - `settings_button` (ID: `settings_button`) at the top.
        - `terminal_sessions_list` (ListView).
        - `toggle_keyboard_button` and `new_session_button` at the bottom.
    - **Swipe activation**: Handled by the `DrawerLayout` component in `activity_termux.xml`.

3. **Session Center**:
    - Accessible via `home_overlay`.
    - **Menu/Settings Button**: An icon at the top-left (`session_center_menu`) using `ic_settings`.
    - **Current Behavior**: Clicking `session_center_menu` calls `mActivity.getDrawer().openDrawer(...)`.

## Identified Issues vs. Requirements

- **Requirement 1**: Remove swipe gesture for session list/drawer in CLI.
    - **Audit**: The swipe gesture is a default behavior of `androidx.drawerlayout.widget.DrawerLayout`. It can be disabled by locking the drawer closed.
- **Requirement 2**: Link CLI Settings button to the same native settings flow as Session Center Settings button.
    - **Audit**:
        - CLI Settings button is currently *inside* the drawer. If the drawer is locked, it becomes inaccessible unless moved.
        - Session Center's "Settings" button (`session_center_menu`) currently opens the drawer instead of launching the `SettingsActivity`.
        - The target destination for both should be `com.termux.app.activities.SettingsActivity`.

## Proposed Solution

1. **Disable Swipe**: Set `drawer_layout.setDrawerLockMode(DrawerLayout.LOCK_MODE_LOCKED_CLOSED)` in `TermuxActivity`.
2. **Move CLI Settings Button**: Extract `settings_button` from the drawer and place it in the main CLI layout as a floating overlay (symmetric to `home_overlay`) at the top-left.
3. **Redirect Session Center Settings**: Update `SessionCenterController` to launch `SettingsActivity` directly when `session_center_menu` is clicked.
4. **Cleanup**: Remove unnecessary drawer-opening logic where it no longer fits the simplified flow.

## Impact Analysis
- **X11/Desktop**: Not affected. The `Session Center` and `home_overlay` logic remains intact.
- **Terminal Input**: Not affected. The new settings overlay will be outside the `TerminalView`.
- **Back Button/Keyboard**: Not affected.
