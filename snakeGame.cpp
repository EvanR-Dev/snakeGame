#include <iostream> // for cout and cin
#include <conio.h> // for_kbhit_getch
#include <windows.h> // for Sleep
#include <ctime> // for time

using namespace std;

bool gameOver; // tells whether or not user has died

int width = 20; // changed depending on whether to change/modify during runtime for const
int height = 20;
const int NUM_FRUITS = 3; // Changes number of fruit on board (default: 3)
int snakeX = 0, snakeY = 0, fruitX[NUM_FRUITS], fruitY[NUM_FRUITS], score = 0;
const int MAX_TAIL_LENGTH = 50; // Array max size of tail
int tailX[MAX_TAIL_LENGTH], tailY[MAX_TAIL_LENGTH];
int tailLength = 0, gameSpeed = 0;

char boardEdge = '#', snakeHead = 'O', snakeTail = 'o', fruitChar = 'F', restartChar = ' ';

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Allows board movement with keys
eDirecton dir; // Holds direction of the snake

 // Function prototypes to let compiler know function exists
void startGame();
void restartGame();
void noBarriers();
void gameOverByBounds();

void fruitPlacement() {
	srand(time(0)); // Seed rand to generate a different x and y position each time the program is rand

	for (int fruitNum = 0; fruitNum < NUM_FRUITS; fruitNum++) { // Assign each index (fruit) in array a rand number
		fruitX[fruitNum] = rand() % width; // posX of each fruit is random
		fruitY[fruitNum] = rand() % height; // posY of each fruit is random
	}
}	// fruitPlacement

void Setup() {
	tailLength = 0; // Allows game to restart because the game will think gameOver == true when restarting, so must restart tail
	gameSpeed = 50; // Default speed (Sleeping game per rate)
	gameOver = false; // Alive on start up
	dir = STOP; // Snake does not move when game is started until moved by user

	snakeX = width / 2; // Snake is centered horizontally
	snakeY = height / 2; // Snake is centered vertically

	fruitPlacement(); // Place fruit(s) at random for start

	score = 0; // No point when game is started (intialized)
}	// Setup

void drawTopOrBottomRow() {
	for (int i = 0; i < width + 2; i++)
		cout << boardEdge;
	cout << "\n";
}	// drawTopOrBottomRow

void printTailOrSpace(int i, int j) {
	bool printTail = false;
	for (int k = 0; k < tailLength; k++) { // Going through every element of the tail
		if (tailX[k] == j && tailY[k] == i) { // if value matches coordinates on the board print tail char
			cout << snakeTail;
			printTail = true;
		}
	}
	if (!printTail)
		cout << " ";
}	// printTailOrSpace

void printBoardAndHead() {
	for (int boardY = 0; boardY < height; boardY++) {
		for (int boardX = 0; boardX < width; boardX++) {
			bool printFruit = false;

			for (int numFruit = 0; numFruit < NUM_FRUITS; numFruit++) // Fill each index, representing 1 corrdinate of a fruit, up until total nbr of fruits
			{
				if (boardX == fruitX[numFruit] && boardY == fruitY[numFruit]) // If coordinates of board match fruit spawn, make print true
					printFruit = true;
			}
			if (boardX == 0) // draws left border of board
				cout << boardEdge;

			if (boardY == snakeY && boardX == snakeX) // Drawing snake head
				cout << snakeHead;
			else if (printFruit) // Must print char
				cout << fruitChar;
			else
				printTailOrSpace(boardY, boardX);

			if (boardX == width - 1)
				cout << boardEdge; // Prints right edge of board with boardEdge character
		}
		cout << "\n";
	}
}	// printBoardAndHead

void Draw() {
	system("cls"); //system("clear"); (clears entire screen)

	drawTopOrBottomRow();
	printBoardAndHead();
	drawTopOrBottomRow();

	cout << "\nScore:" << score << "\n"; // Prints score below last row
}	// Draw

void stopGame() {
	cout << "\n\nPress any key to continue\n";
	while (!_kbhit()) Sleep(1000);
}	// stopGame

void gameOverByBounds() {
	if (snakeX >= width || snakeX <= -1 || snakeY >= height || snakeY <= -1) { // snake hits any edge of board, game over
		gameOver = true;
	}
}	// gameOverByBounds

void hardcoreMode() { // Game gets increasingly faster and tail gets longer with more chars when fruit is eaten
	gameOverByBounds();

	for (int fruitNum = 0; fruitNum < NUM_FRUITS; fruitNum++) {
		if (snakeX == fruitX[fruitNum] && snakeY == fruitY[fruitNum]) { // Snake eats fruit
			gameSpeed -= 20; // Game gets faster

			if (gameSpeed <= 1) // time can't be negative
				gameSpeed = 1;

			tailLength += 2; // Tail gets longer quicker
		}
	}
}	// hardcoreMode

void ridiculousMode() {
	gameSpeed = 5;

	gameOverByBounds();
	fruitPlacement();
}	// ridiculousMode

void Input() {
	if (_kbhit()) { // A boolean for if a key is pressed
		switch (_getch()) { // Returns ASCII value for key that is pressed
		case 'a':
		case 'A': // Assigns each key hit to a direction
			dir = LEFT;
			break;
		case 'd':
		case 'D':
			dir = RIGHT;
			break;
		case 'w':
		case 'W':
			dir = UP;
			break;
		case 's':
		case 'S':
			dir = DOWN;
			break;
		case 'x':
		case 'X':
			gameOver = true; // exits game
			break;
		case 'p':
		case 'P':
			stopGame();
			break;
		}
	}
}	// Input


void directionControls() { // Used for in-game keyboard inputs
	switch (dir) {
	case LEFT:
		snakeX--; // Decreases x-coord
		break;
	case RIGHT:
		snakeX++; // Increases x-coord
		break;
	case UP:
		snakeY--; // Decreases y-coord
		break;
	case DOWN:
		snakeY++; // Increases y-coord
		break;
	default:
		break; // Continues direction when key is pressed
	}
}	// directionControls

void noBarriers() {
	if (snakeX >= width)
		snakeX = 0;
	else if (snakeX < 0)
		snakeX = width - 1; // Snake can move to the other side of the board when going out of bounds (horizontally)

	if (snakeY >= height)
		snakeY = 0;
	else if (snakeY < 0)
		snakeY = height - 1;  // Snake can move to the other side of the board when going out of bounds (vertically)
}	// noBarriers

void checkTailHit() {
	for (int i = 0; i < tailLength; i++) {
		if (tailX[i] == snakeX && tailY[i] == snakeY) // coordinates of tail = coordinates of head = lose
			gameOver = true;
	}
}	// checkTailHit

void scoreKeeper() {
	for (int fruitNum = 0; fruitNum < NUM_FRUITS; fruitNum++) {
		if (snakeX == fruitX[fruitNum] && snakeY == fruitY[fruitNum]) { // Snake eats fruit
			int scoreEarnedPerFruit = 10; // Changed according to user

			// This will only change the position of the fruit that is eaten
			fruitX[fruitNum] = rand() % width;
			fruitY[fruitNum] = rand() % height;

			score += scoreEarnedPerFruit; // Sum of score earned per fruit collected
			tailLength++; // Increase tail length but 1 unit after eating fruit
		}
	}
}	// scoreKeeper

void gameModes() {
	if (restartChar == 'b') // Assign user's keyhits to the options in the menu
		gameOverByBounds();
	else if (restartChar == 'h')
		hardcoreMode();
	else if (restartChar == 'q')
		ridiculousMode();
	else
		noBarriers();
}	// gameModes

void tailFollowLogic() {
	for (int max = (tailLength - 1); 0 < max; max--) { // Improved logic instead of using temp variables
		tailX[max] = tailX[max - 1]; // Uses last position of array index to track last coordinate of snake head
		tailY[max] = tailY[max - 1]; // All tail chars follow head based on last coordinate head, which is stored in the prev index
	}
	tailX[0] = snakeX; // On head coordinates
	tailY[0] = snakeY;

	/*	int prevX = tailX[0]; // First element of tail must follow previous coordinate of head
		int prevY = tailY[0];

		int prev2X, prev2Y;

		tailX[0] = snakeX;
		tailY[0] = snakeY;

		for (int i = 1; i < tailLength; i++) {
			prev2X = tailX[i]; // Use of temp variables
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y; // Allows increasing tail chars to follow head
		}
	*/
}

void Logic() {
	tailFollowLogic();
	directionControls();
	gameModes();
	checkTailHit();
	scoreKeeper();
} // Logic

void gameInstructions() {
	cout << "Welcome to the Snake Game: Remastered for C++!\n\n";
	cout << "Instructions:\n";
	cout << "Press W to move up.\nPress A to move left.\nPress S to move down.\nPress D to move right.\n";
	cout << "Press P to pause the game.\nPress X to end the game and access different modes or exit.";
}	// gameInstructions

void startGame() {
	Setup();

	while (gameOver == false) { // While alive
		Draw();
		Input();
		Logic();
		Sleep(gameSpeed); //sleep(10); (slows game)
	}
	restartGame();
}	// startGame

void restartGame() { // Used for changes/inputs after game has ended for 1st time
	cout << "\nPress R and enter to restart the game as normal.\nPress B and enter to restart with boundary deaths enabled.\n";
	cout << "Press Q and enter for ridiculous mode.\nPress H and enter for hardcore mode (do at your own sanity...)\n";
	cout << "Press any other key and enter to exit the game.\n";
	cin >> restartChar;

	switch (restartChar) { // Decides game mode to be played
	case 'r':
	case 'R':
		startGame();
		break;
	case 'b':
	case 'B':
		restartChar = 'b';
		startGame();
		break;
	case 'h':
	case 'H':
		restartChar = 'h';
		startGame();
		break;
	case 'q':
	case 'Q':
		restartChar = 'q';
		startGame();
		break;
	default:
		exit(0); // leaves program when any other key is hit and entered
		break;
	}
}	// restartGame

int main() {
	gameInstructions();
	stopGame();
	startGame();
}	// main