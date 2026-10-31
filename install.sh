#!/bin/sh

# ************************************************ #
#            pengui installation script            #
# ************************************************ #

set -eu

REPOSITORY="kanashimo/pengui"
FILE="pengui.flatpak"

for cmd in curl flatpak; do
    if command -v "$cmd" > /dev/null 2>&1; then
        echo "$cmd found"
    else
        echo "$cmd missing, install it from your package manager and try again..."
        exit 1
    fi
done

release_url="https://github.com/$REPOSITORY/releases/latest/download/$FILE"

FILE="/tmp/$FILE"

curl -fL --retry 3 "$release_url" -o "$FILE"

flatpak remote-add --user --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install -y --noninteractive --user flathub org.gnome.Platform//51
flatpak install -y --noninteractive --user "$FILE"

echo "Pengui was successfully installed. You will now have to add launch shortcut manually depending on your system configuration."

rm "$FILE"
