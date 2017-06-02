#include "sound.h"

Mix_Music *begin;
Mix_Chunk *eat;
Mix_Chunk *death;
Mix_Chunk *change;
Mix_Chunk *win;

int beginCount = 0;
int deathCount = 0;
int winCount = 0;

void loadingSounds()
{
	//sound sampling frequency : 22050
	//sound format : MIX_DEFAULT_FORMAT
	//stereo channal : 2
	//audio buffer : 4096

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Sound files not found!\n");
		return;
	}

	begin = Mix_LoadMUS("sound/beginning.wav");
	eat = Mix_LoadWAV("sound/eating.wav");
	death = Mix_LoadWAV("sound/death.wav");
	change = Mix_LoadWAV("sound/change.wav");
	win = Mix_LoadWAV("sound/win.wav");
}

void setVolume(Mix_Chunk *chunk, float volume)
{
	Mix_VolumeChunk(chunk, volume * MIX_MAX_VOLUME);
}

void setSoundInit()
{
	beginCount = 0;
	deathCount = 0;
	winCount = 0;
}

void playSound(int num)
{
	switch (num)
	{
	case 1:
		if (beginCount == 0)
		{
			setVolume(eat, 0.5);
			Mix_PlayMusic(begin, 0);
		}
		beginCount++;
		break;

	case 2:
		setVolume(eat, 0.5);
		Mix_PlayChannel(2, eat, 0);
		break;

	case 3:
		if (deathCount == 0)
		{
			setVolume(death, 0.5);
			Mix_PlayChannel(3, death, 0);
		}
		deathCount++;
		break;

	case 4:
		setVolume(change, 0.5);
		Mix_PlayChannel(4, change, 0);
		break;

	case 5:
		if (winCount == 0)
		{
			setVolume(win, 0.5);
			Mix_PlayChannel(4, win, 0);
		}
		winCount++;
		break;
	}
	default:
		break;
}

void pauseSound(int num)
{
	switch (num)
	{
	case 1:
		Mix_Pause(1);
		break;

	case 2:
		Mix_Pause(2);
		break;

	case 3:
		Mix_Pause(3);
		break;

	case 4:
		Mix_Pause(4);
		break;

	case 5:
		Mix_Pause(4);
		break;

	default:
		break;
	}
}

void freeSounds()
{
	Mix_CloseAudio();
}