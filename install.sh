clear
if [ -e /System ]
then
	echo "Automatic installation for Mac"
	echo "==============================="
	echo
	make && make install_osx
else
	echo "Automatic installation for Linux"
	echo "================================"
	echo
	make && make install
fi
shell=$(echo $SHELL | cut -d \/ -f 3)
read -p "Set aliases ? [y/N] " yn
case $yn in
	y ) shell+=rc
		if [ -e ~/.$shell ];then
			echo >> ~/.$shell
			echo "#####- NanoPlayer aliases -#####" >> ~/.$shell
			echo >> ~/.$shell
			echo 'function play(){nanoplayer $1 &}' >> ~/.$shell
			echo 'alias pause="nanoplayer -p"' >> ~/.$shell
			echo 'alias unpause="nanoplayer -u"' >> ~/.$shell
			echo 'alias next="nanoplayer -n"' >> ~/.$shell
			echo 'alias previous="nanoplayer -b"' >> ~/.$shell
			echo 'alias stop="nanoplayer -s"' >> ~/.$shell
			echo 'alias open="nanoplayer -o"' >> ~/.$shell
			echo 'alias volume="nanoplayer -v"' >> ~/.$shell
			echo
			echo 'Aliases in written in ~/.'$shell
			echo 'Restart your terminal session to use them.'
		else
			echo '~/.'$shell' does not exist. Aliases not set.'
		fi
		break;;
	n ) echo
		echo "No aliases are set. Here are the current implemented options :"
		echo
		echo ' pause ........................ nanoplayer -p|--pause'
		echo ' unpause ...................... nanoplayer -u|--play'
		echo ' next song .................... nanoplayer -n|--next'
		echo ' previous song ................ nanoplayer -b|--previous'
		echo ' stop ......................... nanoplayer -s|--stop'
		echo ' open a new file or directory . nanoplayer -o|--open'
		echo ' change the volume ............ nanoplayer -v|--volume'
		exit;;
esac
