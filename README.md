# snakeGame
A C++ implementation of the snake game.

2/1/2020 - v5.0 Evan Roman Derived from an original snakeGame from the web

Changelog 1:
Various annotations/notes over the code has been made to describe functionality (1/15/20 - 1/25/20)
Spacing between certain lines for better readability and organization of code (1/15/20)
Changed variable name "nTail" to "tailLength" for clarity (1/15/20)
Added const variable "MAX_TAIL_LENGTH" to make code more editable (and in caps with underscores since its a const var) (1/15/20)

srand(time(0)) is added to make fruit spawn at a truly random location each time compiled (1/15/20)
Function names are added to the "tail" (end) of each brace for readability (1/15/20)
Function "void drawTopOrBottomRow()" added to avoid duplicate code for drawing the board (1/15/20)
"gameSpeed" variable added in main to clarify what the argument in Sleep() does (and can be easily modified) (1/25/20)
Changed "x" and "y" variable names to "snakeX" and "snakeY" (1/25/20)
Added "scoreEarnedPerFruit" variable to indicate how much score is earned each time the fruit is eaten, and can be easily changed (1/25/20)

Function "fruitPlacement()" added to avoid redundant code (1/25/20)
Added a line between the board and score for visual purposes (1/25/20)
Changed all if/else statements to be on multiple lines for consistency (1/25/20)
Added char "boardEdge" that allows user to change the desired character for the board (Char literal '#' replaced with
boardEdge in respective locations) (1/25/20)
The same has been done for snakeHead, fruit, and snakeTail (1/25/20)
Functions "printTailOrSpace(), checkBounds(), scoreKeeper(), checkTailHit()" added for readability and organization in the Logic() function (1/25/20)

Changelog 2:
The logic of chaining tail chars to the head of the snake has been simplified using array indices in the "Logic()" function (1/30/20)
Add some function prototypes near the beginning of the program so that the compiler will recognize them (due to order in code with respect to main) (1/30/20)
Added a "hardcore" mode and mode that will make the game end when hitting a barrier, accessed after the first playthough or by exiting in the main menu, and made by their respective functions (1/30/20)
These can be found under the "gameMode()" function, where hardcore mode ("hardcoreMode()"), when eating a fruit, speeds the game up and increases the tail length faster

Added a pause function under "stopGame()," triggered by pressing p and continued by pressing any key after pressing p (1/30/20)
Made the "Draw()" and "Logic()" functions more readable and simpler (1/30/20)
Added game instructions on start up under the function "gameInstructions()" (1/31/20)
Added a restart function under "restartGame()" that also leads into the various gamemodes when the user inputs a char for the desired gamemode to start after 1st play (1/31/20)
These gamemodes can also be accessed by exiting, going straight to the menu of different gamemodes

In the "gameOverByBounds()" function, the inequality operators have been added with an "=" operator to fix a bug that was allowing the snake to travel though the
edge of the board without collision detection (1/31/20)

Added a "ridiculous" mode under the "ridiculousMode()" function that updates the position of the fruit as the game runs (1/31/20)

Made fruitX and fruitY arrays to allow multiple fruits on the board. The number of fruits can be changed, given by NUM_FRUITS (default is 3) (2/2/20)


Notes:
There was going to be a numFruits variable that would be inserted into the fruitX and Y arrays, but arrays in VS require
a constant value for the size, while rand requires a modifiable value. This contradicts, so in the future a vector can be used instead
This code used to only allow one fruit, but has been changed
#include <ctime> needed to be included as the time() function was undefined under <windows.h>, possbily due to a different version of VS

In the video, the creator says the drawing of the board is a "matrix," so in the future a 2D array can be used to draw the board

Using x and y as variable names was alright, but if we were to change the program such as adding multiple fruits, specifying that
it is the x and y of the snake clarifies it because the fruit and tail also have an x and y coordinate on the board

Using the "scoreEarnedPerFruit" variable, a future program can change this according to something such as adding a special fruit that will give more
score, etc.

Hardcore mode is included to test the capability of the program, especially array overflowing (how long the tail can get)
Also, I believe this mode is unique because it is an actual challenge to get a high score and is quite different any other snake game out there

The ridiculous mode is included as more as a fun mode and is expected to be nearly impossible. The score is being detected but
the fruit does not disappear on collision instantly. This is expected since this is the way the position is being updated


Comments:
The idea of how the tail of the snake works is the coordinates of the head must be handed down the its tail characters. This
means that all tail chars simply the previous coordinate of the head of the snake continuously

A very simple bug was that the snake could travel through the border. This has been fixed just by changing > to >= under the gameOverBounds() function
This is because without the equal sign that would mean the snake's x and y coordinate could equal the boards exact dimensions rather than being detected
