#ifndef game_h
#define game_h

#include "commonvars.h"
#include "cworldpart.h"

void LoadGraphics(void);
bool StageDone(CWorldPart* Player);
CWorldPart* FindPlayer();
void AskQuestion(int Id, char* Msg);
bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton);
void StageSelect();
void TitleScreen();
void Game();
void Intro();

void LoadSelectedLevel(void);

void GameMenuItemCallback(void* userdata);

void LoadFonts(void);
void UnLoadGraphics();

#endif