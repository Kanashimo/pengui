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

## Features
- taking and cropping screenshots
- ruler with axis aligment (<kbd>Shift</kbd>)
- pipette 

## What's the difference compared to other screenshot applications?
Most of the popular alternatives use a huge bloated frameworks like Qt or GTK. Meanwhile, pengui uses raw OpenGL and ImGui and requires only half of the memory that KDE's Spectale needs.

> [!NOTE]
> It's a known bug that pengui can be CPU-consuming, it will be fixed in the upcoming release. Also, pengui uses GTK as a library, but only to be albe to take screenshots with `libportal`, not to display any content.

## Installing
--

## Usage

## Configuration
Pengui uses `.toml` files for its configuration, [here](https://toml.io/en/) you can get a quick tour of the language if you dont't know it yet.

### Where the config is being stored?
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
```
meson setup build
meson compile -C build
```
Alternatively, if you are developing the application and want to both, compile and run use `make` command.
To start a debugging session with `gdb` use `make debug`.

## Contributing

## Acknowledgements
Special thanks to [GraphLink](https://graphlink.eu/) for making our logo.

## License
Pengui is released under the [GPLv3 license](https://github.com/Kanashimo/pengui/blob/main/LICENSE).
