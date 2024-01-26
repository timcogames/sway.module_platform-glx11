### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest \
      -D MODULE_PLTF_ENABLE_EXAMPLES=ON ../
```

### Запуск сборки

```console
cmake --build ./
```
