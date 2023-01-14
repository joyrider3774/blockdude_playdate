#ifndef game_h
#define game_h

#include "commonvars.h"
#include "cworldpart.h"

void LoadGraphics(void);
bool StageDone(CWorldPart* Player);
CWorldPart* FindPlayer(void);
void AskQuestion(int Id, char* Msg);
bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton);
void StageSelect(void);
void TitleScreen(void);
void Game(void);
void Intro(void);
void IntroInit(void);
void LevelEditor(void);

void LoadSelectedLevel(void);
void SaveSelectedLevel(void);
bool LevelErrorsFound(int* ErrorType);

void LoadFonts(void);
void UnLoadGraphics(void);

#endif