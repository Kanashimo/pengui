<div align="center">
    <h1>
        <a href="https://github.com/kanashimo/pengui">
            <img src="data/icons/hicolor/scalable/apps/net.kanashimo.pengui.svg" width="200" alt="pengui">
        </a>
        <br>
        pengui
    </h1>
    Bloat-free screenshot utility
</div>

- (Features)[#features]
- (What's the difference compared to other screenshot applications?)[#whats-the-difference-compared-to-other-screenshot-applications]
- (Installing)[#installing]
  - (Automatic Installation)[#automatic-installation]
  - (Manual Installation)[#manual-installation]
- (Usage)[#usage]
- (Configuration)[#configuration]
  - (Where is the config being stored?)[#where-is-the-config-being-stored]
  - (Available properties)[#available-properties]
    - (`[crop.border]`)[#cropborder]
    - (`[crop.glow]`)[#cropborder]
    - (`[ruler.border]`)[#rulerborder]
    - (`[screenshot]`)[#screenshot]
- Building from source
- Contributing
- Acknowledgements
- License

## Features
- taking and cropping screenshots
- ruler with axis alignment (<kbd>Shift</kbd>)
- pipette 

## What's the difference compared to other screenshot applications?
Most of the popular alternatives use a huge bloated frameworks like Qt or GTK. Meanwhile, pengui uses raw OpenGL and ImGui and requires only half of the memory that KDE's Spectale needs.

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

After installation, you can assign system shortcut to pengui for launching it with for e.g. <kbd>Meta+Shift+S</kbd> or <kbd>PrntScr</kbd> in you system's settings.
### Manual Installation
1. Download latest Flatpak bundle from [releases page](https://github.com/Kanashimo/pengui/releases)
2. Add Flathub repository to your user
```bash
flatpak remote-add --user --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```
3. Install pengui
```bash
flatpak install --user pengui.flatpak
```

If you don't have GNOME runtime installed and for some reason it wasn't installed automaticlly, run this command:
```bash
flatpak install --user flathub org.gnome.Platform//51
```

Same as in automatic installation, you can assign system shortcut to pengui for launching it with for e.g. <kbd>Meta+Shift+S</kbd> or <kbd>PrntScr</kbd> in you system's settings.

## Usage

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

## Building from source
```bash
meson setup build
meson compile -C build
```
ĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄĄ
Alternatively, if you are developing the application and want to both, compile and run use `make` command.
To start a debugging session with `gdb` use `make debug`.

## Contributing
All contributions are welcome! If you have come up with and idea to add a new feature and want to implement it (or just request it), create an [issue](https://github.com/Kanashimo/pengui/issues). If you find a bug, I'd really appreciate it if you could report it.

## Acknowledgements
Special thanks to [GraphLink](https://graphlink.eu/) for making our logo.

## License
Pengui is released under the [GPLv3 license](https://github.com/Kanashimo/pengui/blob/main/LICENSE).
