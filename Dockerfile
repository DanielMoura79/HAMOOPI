FROM debian
RUN apt update -y \
&& apt install -y sudo vim-tiny build-essential cmake file pkg-config zip unzip \
gcc-mingw-w64-i686 g++-mingw-w64-i686 \
gcc-multilib-i686-linux-gnu g++-multilib-i686-linux-gnu \
clang \
liballegro4-dev