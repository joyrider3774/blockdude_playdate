# Blockdude Playdate Version
Blokdude is a remake of the well known TI Caluculator game from Brandon Sterner as well as the blockman game from Soleau Software. 
This version of the game is based on the GP2X port of blockdude i made over a decade ago.

## Playdate Game Features:
- 21 levels from original blockman game by Soleau Software + 4 levels made by me
- 5 skins to choose from
- Level Editor to create your own levels and level packs to share with others
- Inverted colors option
- Text Size option
- (Optional) crank controls
- Autosaves progress

## Playing the Game:
The aim of the game, in any level, is to move the player to the exit door. You will need to create a path to this exit door by picking up blocks and placing them on strategic locations so you can reach the exit door.
The player will automatically jump on higher level blocks or ground if you keep moving left or right in front of them. 
If the level is bigger than what the playdate screen can display there will be a "freeview option" when pressing the menu button on the playdate and choosing this menu option will allow you to pan around the level using the dpad.

## Level Editor
The game includes a level editor, to create your own levels and level packs which you can share with other people, the level editor is only usable in the playdate version

NOTE: the windows SDL2 api lacks support for menu's and the crank currently, making it not possible to use the level editor inside the windows version, you can however create levels in the (windows) playdate simulator.

### Level Editor Main Menu:
- Cur: [pack name]: The currently selected level pack, you can cycle between other level packs by pressing left or right on the dpad and select it to either play or create levels by pressing a here. if there is an asterix displayed before the level packname name this means it is a internal level pack supplied with the game.
- Create: Create a new level pack and input it's name. You can use up / down / left / right on the dpad to input the name. Pressing left will clear the last letter, pressing right will add a leter and pressing up or down will change the letter.
- Del Pack: Completely erases the level pack including all levels inside the pack
- Optimize Pack: Optimize the level pack so that all levels inside the levelpack follow up on each other. It is possible when creating levels that you left some gaps between the level numbering and this option will remove those gaps. You should always optimize your pack before sharing it with other people

### Level Editor Menu button options
if you are editing a level there will be different menu options availble when pressing the menu button on the playdate
- Play: Play Level
- Clear: Completely erase all level pieces inside the level editor
- View: Cycle between the information you want to see in the top toolbar

### Basic usage
When you select the level editor menu, you can create and name a new pack first to keep your levels in, it will be displayed at the top as "Cur: [your pack name]". Then you can choose that pack by pressin A on the packname. 
After doing thise you can either choose play mode, to select and play your levels or edit mode to select and edit your levels. If you choose edit mode in a new pack the levels will be all blank but you can choose a level number first and then press A in the level selector menu to start creating your level.
Once inside level editing mode you can use the crank to cycle between level editor parts and place them inside the level by pressing the A button. The X piece will erase blocks below the cursor. The toolbar on top can show you the position in the level as well as the currently selected piece / level piece below the cursor

Levels can be maximum 50x50 tiles in size and a level should follow these rules:
- No floating players, exits or blocks, these all must end at a floor or wall piece eventually when moving down
- All levels should contain a player
- All levels should contain an exit door
- Placing pickupable blocks is optional it is not required

You can playtest your level at any time by pressing the menu button on the playdate and choosing play and when testing the level you can press the menu button again to choose "Level editor" and continue editing your level.

### Sharing level packs
Level packs are saved in the data folder of the game under the "levels" folder. You will find a folder here with the name of your level pack (if you created any) and you can zip this folder and share with other people.
The other people will just need to extract your level pack in the same folder on their own playdate and the levels will appear on their playdate as well. 
feel free to contact me if you created some good levels and want your level pack to be included as an internal level pack in the download of the game

## Controls 
| Button | Action |
| ------ | ------ |
| Dpad or Crank | Select menu's, options or levels to play. During gameplay move the player left or right. During level editor mode, select a different level piece with the crank |
| A | Confirm in menu and level selector, pickup or drop a block in game mode and place a level piece in level editor mode |
| B | Back in menu, level selector and game |
| Menu button | All kind of different options depending on when you press this button in the game |

## Controls Windows (keyboard)
| Key | Action |
| ------ | ------ |
| Arrow keys | Select menu's, options or levels to play. During gameplay move the player left or right. |
| X | Confirm in menu and level selector, pickup or drop a block in game mode |
| C | Back in menu, level selector and game |
| F | Switch between fullscreen & windowed mode |
| F4 | Quit game |

## Controls Windows (Gamepad)
| Button | Action |
| ------ | ------ |
| dpad & joystick | Select menu's, options or levels to play. During gameplay move the player left or right. |
| A Button | Confirm in menu and level selector, pickup or drop a block in game mode |
| B Button | Back in menu, level selector and game |

## Credits
The Blockdude game idea was created by Soleau Software for the dos blockman game and Brandon Sterner for the Ti Calculator based game. I don't know who invented the idea first.

The Game uses 21 levels from the Soleau Software blockman dos game. At The time i had created the gp2x version i had gotten approval to use these levels

The game uses some assets from assets packs i had bought, which you can not reuse without acquiring a valid license for them:
- stage end Sound: game music stingers and ui sfx pack 2 https://www.gamedevmarket.net/asset/game-music-stingers-and-ui-sfx-pack-2/
- pickup & drop sound: medieval fantasy sfx pack: https://www.gamedevmarket.net/asset/medieval-fantasy-sfx-pack-1061/
- walk & jump & fall down: Gamemaster Audio - Pro Sound Collection v1.3 - 16bit: https://www.gamedevmarket.net/asset/pro-sound-collection/

The audio is was created by Don Skeeto for the gp2x version and is reused in this version of the game.

The game has 5 skins using tilesets created by different people / games
- Default Skin: Based on a Remake of the flatskin made for the gp2x version by Fusion Power
- Tech Skin: Based on a skin made for the gp2x version by fusion power
- Ti Skin: Based on the assets from the Ti calculator game by brandon Sterner 
- Kenney skin: Based on the 1 bit platformer pack https://kenney-assets.itch.io/1-bit-platformer-pack - https://www.kenney.nl
- Flat Skin: Based on the flash game created by Klas Kroon and Kris Katiesen, i had gotten permission at the time of creating the gp2x version to use these assets