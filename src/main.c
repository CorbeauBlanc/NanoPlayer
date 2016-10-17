#include <stdio.h>
#include <stdlib.h>
#include "fmod.h"

void exit_error(FMOD_RESULT res)
{
	printf("NanoPlayer : FMOD : [%d]", res);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
	FMOD_SYSTEM *system;
	FMOD_RESULT res;
	FMOD_SOUND *snd = NULL;
//	FMOD_CHANNEL *chan;
	if ((res = FMOD_System_Create(&system)) != FMOD_OK)
		exit_error(res);
	if((res = FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL)) != FMOD_OK)
		exit_error(res);
	
	
	FMOD_System_CreateSound(system, "/home/shiro/Bureau/fmod_test.mp3",
							FMOD_2D | FMOD_CREATESTREAM, NULL, &snd);
	FMOD_System_PlaySound(system, snd, NULL, 0, NULL);
	
	while(1);
	
	FMOD_Sound_Release(snd);
	
	
	FMOD_System_Close(system);
	FMOD_System_Release(system);
	exit(EXIT_SUCCESS);
}

