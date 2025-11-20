FROM ubuntu:22.04

RUN apt-get upgrade && apt-get update

# Fetch latest version of CMake
RUN apt-get install software-properties-common -y
RUN apt-get install lsb-release -y
RUN apt-get install ca-certificates gpg wget -y
RUN apt clean all
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 1A127079A92F09ED
RUN apt-get update
RUN apt install kitware-archive-keyring
RUN rm /etc/apt/trusted.gpg.d/kitware.gpg
RUN apt-get install cmake -y

# Install project dependencies
RUN apt-get install libboost-all-dev -y
RUN apt-get install liballegro5-dev -y
RUN apt-get install libjsoncpp-dev -y
RUN apt-get install g++ -y
RUN apt-get install pkgconf -y
RUN apt-get install libgtest-dev -y
RUN apt-get install libspdlog-dev -y

# Install vnc, xvfb in order to create a 'fake' display and firefox
# RUN     apt-get install -y x11vnc xvfb firefox
RUN     apt-get install -y x11-apps
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN     apt-get install -y x11vnc
#RUN     apt-get install -y x11
# RUN     mkdir ~/.vnc

# RUN display=:1 xvfb-run --server-args="-screen 0 1024x768x24" x11-apps &
CMD ["bash", "-lc", "xvfb :1 -screen 0 1024x768x24 -ac & export DISPLAY=:1 && exec bash"]

# RUN export uid=michele gid=michele && \
#     mkdir -p /home/michele && \
#     echo "michele:x:${uid}:${gid}:Michele,,,:/home/michele:/bin/bash" >> /etc/passwd && \
#     echo "michele:x:${uid}:" >> /etc/group && \
#     echo "michele ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/michele && \
#     chmod 0440 /etc/sudoers.d/michele && \
#     chown ${uid}:${gid} -R /home/michele

# USER michele
# ENV HOME=/home/michele
# WORKDIR /home/michele

WORKDIR /pokemon_game

COPY data/ ./
COPY data/tiles/ data/tiles/
COPY data/tiles/*.* data/tiles/*