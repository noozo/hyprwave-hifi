#!/bin/bash
# HyprWave Toggle Script

ACTION="$1"

if [ -z "$ACTION" ]; then
    echo "Usage: hyprwave-toggle {visibility|expand}"
    exit 1
fi

PID=$(pgrep -x hyprwave)
if [ -z "$PID" ]; then
    echo "HyprWave is not running"
    exit 1
fi

case "$ACTION" in
    visibility)
        kill -USR1 "$PID"
        ;;
    expand)
        kill -USR2 "$PID"
        ;;
    *)
        echo "Invalid action: $ACTION"
        echo "Usage: hyprwave-toggle {visibility|expand}"
        exit 1
        ;;
esac
