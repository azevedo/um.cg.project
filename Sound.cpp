/**
 * Sound.cpp
 */

#include <string.h>
#include <iostream>

#include "Sound.h"
#include "externs.h"

string Sound::sounds_path;
SOUND Sound::sounds[SOUND_COUNT];

void Sound::load() {
	sounds_path = conf.rstring("resources:sounds_path");


	// a musica principal e carregada e definida para tocar em looping
	Sound::loadSingle(SOUND_MAIN, conf.rstring("sound:main_music"));
	alSourcei(sounds[SOUND_MAIN].source,	AL_LOOPING,	AL_TRUE);

	Sound::loadSingle(SOUND_WIN, conf.rstring("sound:win_music"));
	alSourcei(sounds[SOUND_WIN].source,	AL_LOOPING,	AL_TRUE);
}

void Sound::loadSingle(SOUND_TYPE id, string path) {
	string file_path(sounds_path);
	file_path.append(path);

	sounds[id].buffer = alutCreateBufferFromFile(file_path.c_str());
	alGenSources (1, &(sounds[id].source));
	alSourcei(sounds[id].source,	AL_BUFFER,	sounds[id].buffer);
}

void Sound::play(SOUND_TYPE id) {
	alSourcePlay(sounds[id].source);
}

void Sound::stop(SOUND_TYPE id) {
	alSourceStop(sounds[id].source);
}