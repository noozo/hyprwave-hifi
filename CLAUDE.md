# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

HyprWave is a GTK4-based music control overlay for Wayland compositors (Hyprland, Niri, Sway). It uses gtk4-layer-shell to create a floating overlay that integrates with MPRIS2-compatible media players via D-Bus.

## Build Commands

```bash
make              # Build the binary
make run          # Build and run locally (uses local ./icons/ and ./style.css)
make install      # Install to ~/.local (binary, icons, CSS, toggle script)
make uninstall    # Remove installation
make clean        # Remove build artifacts
```

**Dependencies:** `gtk4`, `gtk4-layer-shell` (install via package manager)

## Architecture

### Module Structure

| File | Purpose |
|------|---------|
| `main.c` | Application entry, GTK4 setup, MPRIS D-Bus integration, signal handlers |
| `layout.c/h` | Edge-aware UI construction and config parsing |
| `paths.c/h` | Resource path resolution (local → user → system) |

### Key Design Patterns

**MPRIS Integration:** Uses GDBusProxy to connect to media players. The app listens for `g-properties-changed` signals to update metadata in real-time. Player discovery happens via D-Bus `ListNames` call, filtering for `org.mpris.MediaPlayer2.*` services.

**Layer Shell:** The window is created as an overlay layer (`GTK_LAYER_SHELL_LAYER_OVERLAY`) with configurable edge anchoring. The `layout` module translates edge config (right/left/top/bottom) into appropriate anchors and revealer transitions.

**Signal-based IPC:** External control uses Unix signals:
- `SIGUSR1` → Toggle visibility (hide/show entire overlay)
- `SIGUSR2` → Toggle expand (show/hide album details, auto-shows if hidden)

The `hyprwave-toggle.sh` script wraps `pkill -SIGUSRx hyprwave` for compositor keybinds.

### Resource Loading Priority

Both `get_icon_path()` and `get_style_path()` search in order:
1. `./icons/` / `./style.css` (development)
2. `~/.local/share/hyprwave/` (user install)
3. `/usr/share/hyprwave/` (system install)

### Configuration

Config file: `~/.config/hyprwave/config.conf` (auto-created on first run)

```conf
[General]
edge = right      # right | left | top | bottom
margin = 10       # pixels from edge

[Keybinds]
toggle_visibility = Super+Shift+M   # display only, actual binds in compositor
toggle_expand = Super+M
```

The keybind values are informational—actual keybinds must be configured in the compositor (Hyprland/Niri/Sway) to call `hyprwave-toggle`.

## Testing Changes

Run in development mode without installing:
```bash
make && ./hyprwave
```

This uses local `./icons/` and `./style.css` files for immediate feedback.
