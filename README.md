# sway.module_platform-glx11

[![Build Status][travis-svg]][travis-url] [![codecov][codecov-svg]][codecov-url] [![BCH compliance][bettercodehub-svg]][bettercodehub-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

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
cmake -DBOOST_ROOT=/usr/local -DCMAKE_BUILD_TYPE=Release ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`BOOST_ROOT` | PATH | Путь до корневой директории Boost библиотеки | `-`
`CMAKE_BUILD_TYPE` | STRING | Тип сборки | `Debug`
`MODULE_PLATFORM_GLX11_BUILD_SHARED` | `BOOL` | Сборка библиотеки общего пользования | `OFF`

Запускаем сборку

```console
cmake --build .
```

[travis-svg]: https://travis-ci.com/timcogames/sway.module_platform-glx11.svg?branch=master
[travis-url]: https://travis-ci.com/timcogames/sway.module_platform-glx11
[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_platform-glx11/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_platform-glx11
[bettercodehub-svg]: https://bettercodehub.com/edge/badge/timcogames/sway.module_platform-glx11?branch=master
[bettercodehub-url]: https://bettercodehub.com/
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_platform-glx11.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_platform-glx11/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
