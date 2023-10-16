# sway.module_pltf (PLATFORM)

[![codecov][codecov-svg]][codecov-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

### Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_pltf.git
```

### Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release \
      -DGLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -DGLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest \
      -DMODULE_PLTF_ENABLE_EXAMPLES=ON ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`MODULE_PLTF_SHARED_LIB` | BOOL | Создать общую библиотеку (.dylib/.so) | `OFF`

Запускаем сборку

```console
cmake --build ./
```

[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_pltf/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_pltf
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_pltf.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_pltf/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
