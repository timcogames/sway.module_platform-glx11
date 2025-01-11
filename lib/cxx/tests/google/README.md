### Конфигурация сборки для Google тестов

```console
cmake -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googletest \
      -D GLOB_GTEST_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D GLOB_GMOCK_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googlemock \
      -D GLOB_GMOCK_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D GLOB_EMSCRIPTEN_PLATFORM=OFF \
      -D MODULE_PLTF_ENABLE_TESTS=ON \
      ../
```

### Запуск сборки

```console
cmake --build ./
```
