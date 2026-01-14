#!/bin/bash
# HyprWave Toggle Script

ACTION="$1"

if [ -z "$ACTION" ]; then
    echo "Usage: hyprwave-toggle {visibility|expand}"
    exit 1
fi

if ! pgrep -x hyprwave > /dev/null; then
    echo "HyprWave is not running"
    exit 1
fi

case "$ACTION" in
    visibility)
        pkill -SIGUSR1 hyprwave
        ;;
    expand)
        pkill -SIGUSR2 hyprwave
        ;;
    *)
        echo "Invalid action: $ACTION"
        echo "Usage: hyprwave-toggle {visibility|expand}"
        exit 1
        ;;
esac
