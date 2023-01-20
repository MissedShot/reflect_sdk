# reflect_sdk

reflect_sdk is a clean base for making full featured csgo software

## Menu screenshot

![Снимок экрана от 2022-12-29 07-33-37](https://user-images.githubusercontent.com/49341012/209904768-50eee05f-0f89-4341-a984-856efb98b300.png)

## Features

- BunnyHop
- Chams
- Prediction system
- Config system
- Input system
- ImGui menu

## Hooks

- CreateMove
- FrameStageNotify
- DrawModelExecute
- Paint
- SwapWindow
- PollEvent

## Downloading source code

Clone repository with following command

```bash
git clone https://github.com/MissedShot/reflect_sdk.git
```

## Compile needed packages

### RHEL/Fedora based distros:

```bash
sudo dnf install cmake g++ SDL2-devel
```

### Ubuntu/Debian based distros:

```bash
todo
```

### Arch based distros:

```bash
sudo pacman -S --needed git base-devel cmake
```

## Compilation

To compile shared object use following commands

```bash
cmake -D CMAKE_BUILD_TYPE=Release # Set compilation type Debug/Release
make # Start compilation
```

## Dependencies

- [ImGui](https://github.com/ocornut/imgui) - Menu and render
- [Tinyformat](https://github.com/c42f/tinyformat) - Strings format
- [Json](https://github.com/nlohmann/json) - Config system

## Credits

- [csgo-sdk](https://github.com/lagcomp/csgo_sdk) - for original sdk
- [gamesneeze](https://github.com/seksea/gamesneeze) - for code and tips
- [Osiris](https://github.com/danielkrupinski/Osiris) - for code and tips
- [winter-linux](https://github.com/Detectoour/winter-linux) - for code and tips
- [AimTux](https://github.com/AimTuxOfficial/AimTux) - for code and tips
- Other

## Useful projects
- [Injector](https://github.com/kubo/injector)
- [Cartographer](https://github.com/MissedShot/Cartographer)
- [TraceHid](https://github.com/MissedShot/TracerHid)
