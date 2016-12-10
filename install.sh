make install
shell=$(echo $SHELL | cut -d \/ -f 3)
read -p "Set aliases ? [y/N] " yn
case $yn in
	y ) shell+=rc
		if [ -e ~/.$shell ];then
			echo >> ~/.$shell
			echo "#####- NanoPlayer aliases -#####" >> ~/.$shell
			echo >> ~/.$shell
			echo 'function play(){nanoplayer $1}' >> ~/.$shell
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
			echo '~/.'$shell' does not exist. Aliases not written.'
		fi
		break;;
	n ) echo
		echo "Here are the implemented options :"
		echo
		echo ' pause ........................ nanoplayer -p'
		echo ' unpause ...................... nanoplayer -u'
		echo ' next song .................... nanoplayer -n'
		echo ' previous song ................ nanoplayer -b'
		echo ' stop ......................... nanoplayer -s'
		echo ' open a new file or directory . nanoplayer -o'
		echo ' change the volume ............ nanoplayer -v'
		exit;;
esac
