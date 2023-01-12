#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>
#include "pd_api.h"

#define musTitle 1
#define SFX_SUSTAIN 100

void initSound(void);
void SelectMusic(int musicFile);
void initMusic(void);
void playMenuSound(void);
void playMenuSelectSound(void);
void playErrorSound(void);
void playLevelDoneSound(void);
void playMenuBackSound(void);
void setMusicOn(int value);
void setSoundOn(int value);
int isMusicOn(void);
int isSoundOn(void);
void stopMusic(void);
FilePlayer* loadSoundFile(const char* path);

#endif