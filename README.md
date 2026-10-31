<div align="center">
    <h1>
        <a href="https://github.com/kanashimo/pengui">
            <img src="data/icons/hicolor/scalable/apps/net.kanashimo.pengui.svg" width="200" alt="pengui">
        </a>
        <br>
        pengui
        <br>
        <img alt="artifact build status" src="https://img.shields.io/github/actions/workflow/status/kanashimo/pengui/.github%2Fworkflows%2Fflatpak-artifact.yml?logo=githubactions&logoColor=white">
        <img alt="release" src="https://img.shields.io/github/v/release/kanashimo/pengui?color=blue">
        <img alt="C++20" src="https://img.shields.io/badge/C%2B%2B-20-blue?logo=c%2B%2B">
        <img alt="license" src="https://img.shields.io/github/license/kanashimo/pengui?logo=gnu&color=red">
    </h1>
    Bloat-free screenshot utility
</div>

- [Features and tools](#features-and-tools)
- [What's the difference compared to other screenshot applications?](#whats-the-difference-compared-to-other-screenshot-applications)
- [Installing](#installing)
  - [Automatic Installation](#automatic-installation)
  - [Manual Installation](#manual-installation)
  - [How to uninstall?](#how-to-uninstall)
- [Usage](#usage)
- [Configuration](#configuration)
  - [Where is the config being stored?](#where-is-the-config-being-stored)
  - [Available properties](#available-properties)
    - [`[crop.border]`](#cropborder)
    - [`[crop.glow]`](#cropborder)
    - [`[ruler.border]`](#rulerborder)
    - [`[screenshot]`](#screenshot)
  - [Full example of working config file](#full-example-of-working-config-file)
- [Building from source](#building-from-source)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)
- [License](#license)

## Features and tools
- Taking and cropping screenshots
- Support for both Wayland and X11
- Ruler with axis alignment (<kbd>Shift</kbd>)
- Pipette 

## What's the difference compared to other screenshot applications?
Most of the popular alternatives use a huge bloated frameworks like Qt or GTK. Meanwhile, pengui uses raw OpenGL and ImGui and requires only half of the memory that KDE's Spectacle needs.

> [!NOTE]
> It's a known bug that pengui can be CPU-consuming, it will be fixed in the upcoming release. Also, pengui uses GTK as a library, but only to be albe to take screenshots with `libportal`, not to display any content.

## Installing

### Automatic Installation
Paste this command into your terminal:
```bash
wget -O - https://pengui.kanashimo.net/install.sh | sh
```

Alternativly, if you dont't trust the first source or it just doesn't work, you can download the script directly form the repository:
```bash
wget -O - https://raw.githubusercontent.com/kanashimo/pengui/refs/heads/main/install.sh | sh
```

After installation, you can assign system shortcut to pengui for launching it with for e.g. <kbd>Meta+Shift+S</kbd> or <kbd>PrntScr</kbd> in your system's settings.

### Manual Installation
1. Download latest Flatpak bundle from [releases page](https://github.com/Kanashimo/pengui/releases).
2. Add Flathub repository to your user.
```bash
flatpak remote-add --user --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```
3. Install pengui.
```bash
flatpak install --user pengui.flatpak
```

If you don't have GNOME runtime installed and for some reason it wasn't installed automaticlly, run this command:
```bash
flatpak install --user flathub org.gnome.Platform//51
```

Same as in automatic installation, you can now assign system shortcut to pengui for launching it with for e.g. <kbd>Meta+Shift+S</kbd> or <kbd>PrntScr</kbd> in your system's settings.

### How to uninstall? 
To uninstall pengui, use `flatpak uninstall` with `--user` flag.
```bash
flatpak uninstall --user net.kanashimo.pengui
```

## Configuration
Pengui uses `.toml` files for its configuration, [here](https://toml.io/en/) you can get a quick tour of the language if you dont't know it yet.

### Where is the config being stored?
The answer is as always, it depends. If you are running this application in the "official" way (so throught Flatpak), you will be albe to find the config in `$HOME/.var/app/net.kanashimo.pengui/config/pengui`. Otherwise, if you are running it natively, your config will be in `$HOME/.config/pengui`.

### Available properties

#### `[crop.border]`
| Property | Type        | Default value    |
|----------|-------------|------------------|
| `color`  | `[R, G, B]` | `[90, 200, 255]` |
| `width`  | `number`    | `2`              |

#### `[crop.glow]` **(experimental, disabled by default)**
| Property  | Type        | Default value    |
|-----------|-------------|------------------|
| `color`   | `[R, G, B]` | `[90, 200, 255]` |
| `enabled` | `boolean`   | `false`          |

#### `[ruler.border]`
| Property | Type        | Default value    |
|----------|-------------|------------------|
| `color`  | `[R, G, B]` | `[90, 200, 255]` |
| `width`  | `number`    | `5`              |

#### `[screenshot]`
| Property         | Type               | Default value                         |
|------------------|--------------------|---------------------------------------|
| `save_location`  | `string` (path)    | `$XDG_PICTURES_DIR/PenguiScreenshots` |

### Full example of working config file
```toml
[crop.border]
color = [ 90, 200, 255 ]
width = 2.0

[crop.glow]
color = [ 90, 200, 255 ]
enabled = false

[ruler.border]
color = [ 90, 200, 255 ]
width = 5.0

[screenshot]
save_location = '/home/example/Pictures/PenguiScreenshots'
```

## Building from source

### Requirements
- [meson](https://mesonbuild.com/)
- [ninja](https://ninja-build.org/)
- [flatpak](https://github.com/flatpak/flatpak) (optional)
- [flatpak-builder](https://github.com/flatpak/flatpak-builder) (optional)

### Building pengui
```bash
meson setup build
meson compile -C build
```

After building you can run `meson install -C build` to install the binary, although it isn't recommended because pengui is intended to be a Flatpak application, so this option is never tested. Use at your own risk.

### Building pengui as a Flatpak application
```bash
meson subprojects download
flatpak-builder --user --install --force-clean build-dir flatpak/net.kanashimo.pengui.yml
```

## Contributing
All contributions are welcome! If you have come up with and idea to add a new feature and want to implement it (or just request it), create an [issue](https://github.com/Kanashimo/pengui/issues). If you found any bug, I'd really appreciate it if you could report it.

## Acknowledgements
Special thanks to [GraphLink](https://graphlink.eu/) for making our logo.

## License
Pengui is released under the [GPL-3.0 license](https://github.com/Kanashimo/pengui/blob/main/LICENSE).

The logo is under the CC BY-SA 4.0 license.
