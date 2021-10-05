mkdir -p build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build . -j 3
export ALSA_CONFIG_DIR=/usr/share/alsa
