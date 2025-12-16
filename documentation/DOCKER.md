# Docker 
### Compile the game and the tests
```bash
$ docker compose build
```
### Running the game
```bash
$ docker compose run play
```
```bash
$ export XAUTHORITY=${XAUTHORITY:-$HOME/.Xauthority}
$ sudo docker compose run --rm -it -e DISPLAY="$DISPLAY" -e XAUTHORITY="$XAUTHORITY" -v /tmp/.X11-unix:/tmp/.X11-unix -v "$XAUTHORITY:$XAUTHORITY" play
```

### Running the tests
```bash
$ docker compose run test
```
```bash
$ export XAUTHORITY=${XAUTHORITY:-$HOME/.Xauthority}
$ sudo docker compose run --rm -it -e DISPLAY="$DISPLAY" -e XAUTHORITY="$XAUTHORITY" -v /tmp/.X11-unix:/tmp/.X11-unix -v "$XAUTHORITY:$XAUTHORITY" test
```
