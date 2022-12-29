# reflect_sdk

reflect_sdk is a clean base for making full featured csgo software

## Features

- BunnyHop
- Chams
- ImGui menu

## Downloading source code

Clone repository with following command

```bash
git clone https://github.com/MissedShot/linux_sdk.git
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
todo
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
- [gamesneeze](https://github.com/seksea/gamesneeze/blob/master/toolbox.sh) - for code and tips
- [Osiris](https://github.com/danielkrupinski/Osiris) - for code and tips
- [winter-linux](https://github.com/Detectoour/winter-linux) - for code and tips
- [AimTux](https://github.com/AimTuxOfficial/AimTux) - for code and tips
