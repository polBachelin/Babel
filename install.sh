mkdir -p build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build .
export ALSA_CONFIG_DIR=/usr/share/alsa