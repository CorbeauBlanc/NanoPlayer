# NanoPlayer v0.1
 
 Nanoscopic music player that runs in a terminal.
 
 Interactions only with command lines, it can work in background (with '&') : call it once to play the music and call it again with different parameters to do other actions.

 So far nothing these are implemented :
  * -p : pause the music
  * -u : unpause the music
  * -s : stop the music (and end the process)
  * -n : go to the next song. If there is no next song end the process
  * -b : go to the previous song. If there is no previous song repeat the current song
  * -v [amount] : change the volume. A positive number increase the volume and a negative one dicrease it
  * -o [path] : open a new file or directory
 
 
 ## Known issues
 
  If the process is killed (by hitting Ctrl + c for example) it does not delete its temporary file and so it will consider that an instance is always running. Solution : restart your session or (more practical) delete /tmp/nanoplayer.
 
