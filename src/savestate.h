#ifndef SAVESTATE_H
#define SAVESTATE_H

void initSaveState(void);

int lastUnlockedLevel();
int levelUnlocked(int aLevel);
int isMusicOnSaveState(void);
int isSoundOnSaveState(void);
int isInvertedSaveState(void);
int skinSaveState(void);
void unlockLevel(int aLevel);
void setMusicOnSaveState(int value);
void setSoundOnSaveState(int value);
void setSkinSaveState(int value);
void setInvertedSaveState(int value);
int ShowPositionSaveState(void);
void setShowPositionSaveState(int value);
int ShowGridSaveState(void);
void setShowGridSaveState(int value);
#endif