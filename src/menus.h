#ifndef MENUS_H
#define MENUS_H

void CreateGameMenuItems();
void GameMenuItemCallback(void* userdata);
void CreateOtherMenuItems();
void CreateLevelEditorMenuItems();
void LevelEditorMenuItemCallback(void* userdata);
void OtherMenuItemCallback(void* userdata);
void DestroyMenuItems(void);

#endif