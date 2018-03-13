# NanoPlayer v0.2

 Nanoscopic music player that runs in a terminal.

 Interactions only with command lines, it can work in background (with '&') : call it once to play the music and call it again with different parameters to do other actions. Works with as much terminal as you want and with ssh.

 So far these options are implemented :
  * -p | --pause : pause the music
  * -u | --play : unpause the music
  * -s | --stop : stop the music (and end the process)
  * -n | --next : go to the next song. If there is no next song end the process
  * -b | --previous : go to the previous song. If there is no previous song repeat the current song
  * -v | --volume [amount] : change the volume. A positive number increase the volume and a negative one dicrease it
  * -o | --open [path] : open a new file or directory

## Installation
Just launch install.sh in a terminal. It will ask you if you want to set a bunch of aliases, these are here to make nanoplayer more practical (for example use `next` instead of `nanoplayer -n`) so you might want to set them. It's an advice, you do what you want.
For Raspberry Pi installation you'll have to do `make ARCH=armhf` then `make install`.

## Known issues

  If the process is killed (by hitting Ctrl + c, with the kill command, or by closing the terminal without doing `nanoplayer -s` for example) the program does not delete its temporary file and so it will always consider that an instance is already running and refuse to launch a new one.
  Solution : logout and login or just delete /tmp/nanoplayer.
