#ifndef game_h
#define game_h

#include <stdbool.h>

bool getStringUpdate(int* Id, bool* Answered, char* StringBuffer);
void getStringDraw(char* StringBuffer, bool ErasingPrevious);
char* GetString(int Id, int x, int y, char* Msg, size_t MaxLen);
void DoShowDebugInfo();
bool LevelErrorsFound(int* ErrorType);
void PlayLevelIfNoErrorsFound();
void LoadSelectedLevel(void);
void SaveSelectedLevelPositional(void);
void SaveSelectedLevel(void);
void AskQuestion(int Id, char* Msg);
bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton);
void FindLevels(void);
void FindLevelsCallBack(const char* path, void* userdata);
void FindLevelPacks(void);
void FindLevelPacksCallBack(const char* path, void* userdata);
void LoadFonts(void);
void LoadGraphics(void);
void UnLoadGraphics();

#endif