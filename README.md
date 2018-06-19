# sway.module_platform-glx11 [![Discord](https://discordapp.com/api/guilds/402238411639095297/widget.png)](https://discord.gg/vCMcgwQ)

[![Build Status](https://travis-ci.com/timcogames/sway.module_platform-glx11.svg?branch=master)](https://travis-ci.com/timcogames/sway.module_platform-glx11)
[![BCH compliance](https://bettercodehub.com/edge/badge/timcogames/sway.module_platform-glx11?branch=master)](https://bettercodehub.com/)
[![Documentation](https://codedocs.xyz/timcogames/sway.module_platform-glx11.svg)](https://codedocs.xyz/timcogames/sway.module_platform-glx11/)

### Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_platform-glx11.git
```

### Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release ../
```

Опция сборки | Описание | По умолчанию
:---|:---|:---:
`BUILD_SHARED` | Сборка библиотеки общего пользования | `OFF`

Запускаем сборку

```console
cmake --build .
```
