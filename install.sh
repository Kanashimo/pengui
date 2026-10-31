#!/usr/bin/env bash

# ************************************************ #
#            pengui installation script            #
# ************************************************ #

set -euo pipefail

REPOSITORY="kanashimo/pengui"
FILE="pengui.flatpak"

for cmd in jq curl flatpak; do
    if command -v "$cmd" &>/dev/null; then
        echo "$cmd found"
    else
        echo "$cmd missing, install it from your package manager and try again..."
        exit 1
    fi
done

release_url="https://api.github.com/repos/${REPOSITORY}/releases/latest"
response=$(curl -fsSL "$release_url")

bundle_url=$(jq -er \
    --arg asset "$FILE" \
    '.assets[] | select(.name == $asset) | .browser_download_url' \
    <<< "$response"
)

FILE="/tmp/$FILE"

curl -fL --retry 3 "$bundle_url" -o $FILE

flatpak remote-add --user --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install -y --noninteractive --user flathub org.gnome.Platform//51
flatpak install -y --noninteractive --user $FILE

echo "Pengui was successfully installed. You will now have to add launch shortcut manually depending on your system configuration."

rm $FILE
