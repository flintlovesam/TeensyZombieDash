// My function prototypes for Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Global Variables
volatile int LEFT = 0;
volatile int RIGHT = 0;
int screen_x = 83;
int screen_x_Full = 83;
int screen_y = 47;
int screen_y_Full = 47;
int charWidth = 8;
int charHeight = 8;
volatile int previousLEFT = 0;
volatile int previousRIGHT = 0;
volatile int buttonPressed = 0;
volatile int previousButton = 0;
volatile int Direction = 1; // {up , down, left, right};
int zDirection[8] = {1};
volatile int clockCounter = 0;
volatile int stepsCounter = 0;
volatile int scoreCounter = 0;
volatile int grenadeCounter = 0;
volatile int explosionCounter = 0;
volatile int GAMEON = 0;
volatile int Touched;
volatile int Over;
int pitLeft;
int pitRight;
int pitTop;
int pitBottom;
int activeZombies = 8;
int zombieSteps = 9;
int numZombies = 8;
int notOver = 0;
volatile int grenadeDropped = 0;
volatile int grenadeExploded = 0;
int difficulty = 0;

byte width = 3;
byte height = 3;

// Sprite pointers
Sprite *my_pointer;
Sprite *zombie[8];
Sprite *sword, *swordStatus;
Sprite *grenade, *grenadeStatus;
Sprite *explosion;

int Lives = 3;
int Score = 0;
int gotSword = 0;
int gotGrenade = 0;

byte bitSwordLeft [] = {
		BYTE( 00100000),
		BYTE( 11100000),
		BYTE( 00100000),
	};
	
	byte bitSwordRight [] = {
		BYTE( 10000000),
		BYTE( 11100000),
		BYTE( 10000000),
	};
	
	byte bitSwordUp [] = {
		BYTE( 01000000),
		BYTE( 01000000),
		BYTE( 11100000),
	};
	
	byte bitSwordDown [] = {
		BYTE( 11100000),
		BYTE( 01000000),
		BYTE( 01000000),
	};
	
	byte bitGrenade [] = {
		BYTE( 01000000),
		BYTE( 10100000),
		BYTE( 01000000),	
	};
	
	byte bitExploded [] = {
		UINT( 11000001, 10000011 ),
		UINT( 01100001, 10000110 ),
		UINT( 00110001, 10001100 ),
		UINT( 00110001, 10001100 ),
		UINT( 00011001, 10011000 ),
		UINT( 00001101, 10110000 ),
		UINT( 00000111, 11100000 ),
		UINT( 11111111, 11111111 ),
		UINT( 11111111, 11111111 ),
		UINT( 00000111, 11100000 ),
		UINT( 00001101, 10110000 ),
		UINT( 00011001, 10011000 ),
		UINT( 00110001, 10001100 ),
		UINT( 00110001, 10001100 ),
		UINT( 01100001, 10000110 ),
		UINT( 11000001, 10000011 ),
	};

// Function Prototypes

// Checks button presses
void buttonCheck(void);

/**
* Random number generation:
* - 'seedWithButtonPress()': seeds the random number generator with an
* iterated count while waiting for a button press
* - 'randInRange()': uses the random number generator (assumes it has
* been seeded) to produce a random number between
* 'min' (inclusive') and 'max' (inclusive)
*/
void seedWithButtonPress(void);

int randInRange(int min, int max);

/* Sets up the game
pins, clock and screen initialised.
*/
void setupGame(void);

// Main Game function
void playGame(void);

// Beginning countdown
void CountDown(void);

// Initialises interrupt for button press
void PinChangeInit(void);

// Initialize interrupt for timer for movement etc
void TimerInit(void);

// Move hero forward one unit
void heroForward(void);

// Draws the Current Screen
void drawScreen(void);

// not used anymore
void setupZombies(void);

// Move zombies forward one unit
void zombiesForward(void);

// places hero in the middle
void setupHero(void);

// collision detection
void collision(void);

void setupPit(void);

void drawPit(void);

int isInPit(Sprite *sprite);

void setupSword(void);

void setupGrenade(void);

void winScreen(void);

void chooseDifficulty(void);