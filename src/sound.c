#include <stdint.h>
#include <string.h>
#include "pd_api.h"
#include "commonvars.h"
#include "sound.h"

int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

FilePlayer* musicPlayer;
FilePlayer* levelDoneSound;
FilePlayer* errorSound;
FilePlayer* menuSound;
FilePlayer* menuSelectSound;


void stopMusic(void)
{
    if (pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }
}

void setMusicOn(int value)
{
    music_on = value;
    if(music_on)
    {
        if (prev_music != -1)
        {
            force = 1;
            SelectMusic(prev_music);
        }
        else if (GameState == GSTitleScreen)
        {
            force = 1;
            SelectMusic(musTitle);
        }
    }
    else
    {
        stopMusic();
    }
}

void setSoundOn(int value)
{
    sound_on = value;
}

int isMusicOn(void)
{
    return music_on;
}

int isSoundOn(void)
{
    return sound_on;
}

FilePlayer* loadSoundFile(const char* path)
{
    FilePlayer* soundPlayer = pd->sound->fileplayer->newPlayer();
    pd->sound->fileplayer->setStopOnUnderrun(soundPlayer, 0);
    pd->sound->fileplayer->setVolume(soundPlayer, 0.7f, 0.7f);
    pd->sound->fileplayer->setRate(soundPlayer, 1.0f);
    pd->sound->fileplayer->loadIntoPlayer(soundPlayer, path);
    return soundPlayer;
}

void initSound(void)
{
    levelDoneSound = loadSoundFile("sound/stageend");
    errorSound = loadSoundFile("sound/error");
    menuSelectSound = loadSoundFile("sound/select");
    menuSound = loadSoundFile("sound/menu");
}

void playMusicFile(const char* path, int repeat)
{
    if(pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }

    if (pd->sound->fileplayer->loadIntoPlayer(musicPlayer, path))
    {
        pd->sound->fileplayer->play(musicPlayer, repeat);
    }
}

void SelectMusic(int musicFile)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        force = 0;
        prev_music = musicFile;
        switch (musicFile) 
        {
            case musTitle:
                playMusicFile("music/title", 0);
                break;
        }
    }
    else
    {
        //still need to remember last music we tried to play in case music was off & we reenable
        if (!music_on)
        {
            prev_music = musicFile;
        }
    }
}


void initMusic(void)
{
    prev_music = -1;
    musicPlayer = pd->sound->fileplayer->newPlayer();
    pd->sound->fileplayer->setStopOnUnderrun(musicPlayer, 0);
    pd->sound->fileplayer->setVolume(musicPlayer, 0.75f, 0.75f);
    pd->sound->fileplayer->setRate(musicPlayer, 1.0f);
}

void playSound(FilePlayer* soundPlayer)
{
    if (pd->sound->fileplayer->isPlaying(soundPlayer))
    {
        pd->sound->fileplayer->stop(soundPlayer);
    }
    pd->sound->fileplayer->play(soundPlayer, 1);   
}

void playLevelDoneSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(levelDoneSound);
}

void playErrorSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(errorSound);
}

void playMenuSelectSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuSelectSound);
}

void playMenuSound(void)
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuSound);
}
