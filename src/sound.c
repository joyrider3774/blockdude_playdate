#include <stdint.h>
#include <string.h>
#include "sound.h"
#include "pd_api.h"
#include "commonvars.h"


int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

FilePlayer* musicPlayer;

SamplePlayer* levelDoneSoundPlayer;
SamplePlayer* errorSoundPlayer;
SamplePlayer* menuSoundPlayer;
SamplePlayer* menuSelectSoundPlayer;
SamplePlayer* menuBackSoundPlayer;
SamplePlayer* pickupSoundPlayer;
SamplePlayer* dropSoundPlayer;
SamplePlayer* jumpSoundPlayer;
SamplePlayer* walkSoundPlayer;
SamplePlayer* fallSoundPlayer;

AudioSample* levelDoneSound;
AudioSample* errorSound;
AudioSample* menuSound;
AudioSample* menuSelectSound;
AudioSample* menuBackSound;
AudioSample* pickupSound;
AudioSample* dropSound;
AudioSample* jumpSound;
AudioSample* walkSound;
AudioSample* fallSound;

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

SamplePlayer* loadSoundFile(AudioSample* Sample, const char* path)
{   
    Sample = NULL;
    SamplePlayer* soundPlayer = pd->sound->sampleplayer->newPlayer();
    if (soundPlayer)
    {
        Sample = pd->sound->sample->load(path);
        if (Sample)
        {
            pd->sound->sampleplayer->setSample(soundPlayer, Sample);
            pd->sound->sampleplayer->setVolume(soundPlayer, 0.7f, 0.7f);
            pd->sound->sampleplayer->setRate(soundPlayer, 1.0f);
        }
    }
    return soundPlayer;
}

void FreeSample(AudioSample* Sample)
{
    if (Sample)
    {
        pd->sound->sample->freeSample(Sample);
    }
    Sample = NULL;
}

void FreeSoundPlayer(SamplePlayer* SoundPlayer)
{
    if (SoundPlayer)
    {
        pd->sound->sampleplayer->freePlayer(SoundPlayer);
    }
    SoundPlayer = NULL;
}

void initSound(void)
{
    levelDoneSoundPlayer = loadSoundFile(levelDoneSound, "sound/stageend");
    errorSoundPlayer = loadSoundFile(errorSound, "sound/error");
    menuSelectSoundPlayer = loadSoundFile(menuSelectSound, "sound/select");
    menuSoundPlayer = loadSoundFile(menuSound, "sound/menu");
    menuBackSoundPlayer = loadSoundFile(menuBackSound, "sound/back");
    pickupSoundPlayer = loadSoundFile(pickupSound, "sound/pickup");
    dropSoundPlayer = loadSoundFile(dropSound, "sound/drop");
    jumpSoundPlayer = loadSoundFile(jumpSound, "sound/jump");
    walkSoundPlayer = loadSoundFile(walkSound, "sound/walk");
    fallSoundPlayer = loadSoundFile(fallSound, "sound/fall");
}

void deInitSound(void)
{
    FreeSample(levelDoneSound);
    FreeSample(errorSound);
    FreeSample(menuSelectSound);
    FreeSample(menuSound);
    FreeSample(pickupSound);
    FreeSample(dropSound);
    FreeSample(jumpSound);
    FreeSample(walkSound);
    FreeSample(fallSound);

    FreeSoundPlayer(levelDoneSoundPlayer);
    FreeSoundPlayer(errorSoundPlayer);
    FreeSoundPlayer(menuSelectSoundPlayer);
    FreeSoundPlayer(menuSoundPlayer);
    FreeSoundPlayer(pickupSoundPlayer);
    FreeSoundPlayer(dropSoundPlayer);
    FreeSoundPlayer(jumpSoundPlayer);
    FreeSoundPlayer(walkSoundPlayer);
    FreeSoundPlayer(fallSoundPlayer);
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
    pd->sound->fileplayer->setVolume(musicPlayer, 0.55f, 0.55f);
    pd->sound->fileplayer->setRate(musicPlayer, 1.0f);
}

void deInitMusic(void)
{
    if (pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }

    pd->sound->fileplayer->freePlayer(musicPlayer);
    musicPlayer = NULL;
}

void playSound(SamplePlayer* soundPlayer)
{
    if (!sound_on)
    {
        return;
    }

    if (pd->sound->sampleplayer->isPlaying(soundPlayer))
    {
        pd->sound->sampleplayer->stop(soundPlayer);
    }
    pd->sound->sampleplayer->play(soundPlayer, 1, 1.0f);   
}

void playJumpSound(void)
{
    playSound(jumpSoundPlayer);
}

void playFallSound(void)
{
    playSound(fallSoundPlayer);
}

void playLevelDoneSound(void)
{
    playSound(levelDoneSoundPlayer);
}

void playWalkSound(void)
{
    playSound(walkSoundPlayer);
}

void playErrorSound(void)
{
    playSound(errorSoundPlayer);
}

void playMenuSelectSound(void)
{
    playSound(menuSelectSoundPlayer);
}

void playMenuBackSound(void)
{
    playSound(menuBackSoundPlayer);
}

void playPickupSound(void)
{
    playSound(pickupSoundPlayer);
}

void playDropSound(void)
{
    if(!pd->sound->sampleplayer->isPlaying(dropSoundPlayer))
        playSound(dropSoundPlayer);
}

void playMenuSound(void)
{
    playSound(menuSoundPlayer);
}
