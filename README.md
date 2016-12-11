# NanoPlayer v0.1
 
 Nanoscopic music player that runs in a terminal.
 
 Interactions only with command lines, it can work in background (with '&') : call it once to play the music and call it again with different parameters to do other actions.

 So far these options are implemented :
  * -p : pause the music
  * -u : unpause the music
  * -s : stop the music (and end the process)
  * -n : go to the next song. If there is no next song end the process
  * -b : go to the previous song. If there is no previous song repeat the current song
  * -v [amount] : change the volume. A positive number increase the volume and a negative one dicrease it
  * -o [path] : open a new file or directory
 
## Installation
Just launch install.sh in a terminal. It will ask you if you want to set a bunch of aliases, these are here to make nanoplayer more practical (for example use "next" instead of "nanoplayer -n") so you might want to set them. It's an advice, you do what you want.

## Known issues
 
  If the process is killed (by hitting Ctrl + c or with the kill command for example) the program does not delete its temporary file and so it will always consider that an instance is already running. Solution : restart your session or just delete /tmp/nanoplayer.
 
