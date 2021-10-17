mkdir -p build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && make -j 11
export ALSA_CONFIG_DIR=/usr/share/alsa