// Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "graphics.h"
#include "byte.h"
#include "sprite.h"
#include "cpu_speed.h"

#include "my_functions.h"

#define NUM_BLOCKS 10
#define MAX_CLOCK_COUNTER_FOR_100MSECOND 5

int main() {
	
	// INSERT_CODE_HERE
	//draw_string("eWWZ begins!",0,0);

	// screen setup etc
	setupGame();
	clear();
	refresh();
	
	// sprites
	byte bitHero [] = {
		BYTE( 10100000),
		BYTE( 11100000),
		BYTE( 10100000),
	};
		
	byte bitZombie [] = {
		BYTE( 11100000),
		BYTE( 01000000),
		BYTE( 11100000),
	};
	
	// screen parameters
	screen_x -= width;
	screen_y -= height;

	int middle_x = screen_x/2;
	int middle_y = screen_y/2 + 5;
	byte x, y;
	
	// test
	/*for (int i = 0; i<100; i++) {
		clear();
		draw_character((0x30 + randInRange(0,9)),middle_x,middle_y);
		refresh();
		_delay_ms(500);
	
	}*/
	
	Sprite zombies[numZombies]; 
	for (int i = 0; i<numZombies; i++) {
	zombie[i] = &zombies[i];
	init_sprite(zombie[i], middle_x + 3*i, middle_y, width, height, bitZombie);
	}
	
	Sprite swords, swordsStatus;
	sword = &swords;
	swordStatus = &swordsStatus;
	init_sprite(sword, -10,-10, width, height, bitSwordLeft);
	init_sprite(swordStatus, -10,-10, width, height, bitSwordUp);
	
	Sprite grenades, grenadesStatus;
	grenade = &grenades;
	grenadeStatus = &grenadesStatus;
	init_sprite(grenade, -10,-10, width, height, bitGrenade);
	init_sprite(grenadeStatus, -10,-10, width, height, bitGrenade);
	
	Sprite explosions;
	explosion = &explosions;
	init_sprite(explosion, -10, -10, 16, 16, bitExploded);
	explosion -> is_visible = 1;
	draw_sprite(explosion);
	
	setupGrenade();
	setupSword();
	setupZombies();
	setupPit();
	
	/*
	Sprite test_sprite; zombie = &test_sprite;
	init_sprite(zombie, x + 2*width, y, width, height, bitZombie);
	draw_sprite(zombie);
	*/
	
	// Hero sprite parameters
	x = screen_x/2 - width;
	y = screen_y/2 + 9/2;
	
	Sprite my_sprite;
	my_pointer = &my_sprite;

	init_sprite(my_pointer, middle_x, middle_y, width, height, bitHero);
	draw_sprite(my_pointer);
	for (int i = 0; i<numZombies; i++) {
	draw_sprite(zombie[i]);
	}
	
	refresh();
	
	_delay_ms(100);
	
	/*
	my_sprite.bitmap = bitmap2;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	my_sprite.bitmap = bitmap3;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	my_sprite.bitmap = bitmap4;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	refresh();
	draw_string("Press a button", 0,0);
	refresh();
	*/
	//int add = 1;
	
	// initialise vars
	int notRIGHT = 1;
	int notLEFT = 1;
	GAMEON = 1;
	while(GAMEON){
	/*
		my_pointer -> y += add;
		my_pointer2 -> y -= add;
		if (my_pointer -> y < 1) add = -add;
		if (my_pointer -> y > screen_y) add = -add;
	*/
		clear();

		if (RIGHT == 0) {
			notRIGHT = 1;
		}
		if (LEFT == 0) {
			notLEFT = 1;
		}
		
		if (RIGHT && notRIGHT) {
			notRIGHT = 0;
			Direction = (Direction-1);
			if (Direction < 0) {
			Direction = 3;
			}
			//bitmapa = my_pointer -> bitmap;
			//bitmapb = my_pointer2 -> bitmap;
			//bitmaptemp = bitmapa;
			//bitmapa = bitmapb;
			//bitmapb = bitmaptemp;
			//my_pointer -> bitmap = bitmapa;
			//my_pointer2 -> bitmap = bitmapb;
			
		}
		if (LEFT & notLEFT) {
			notLEFT = 0;
			Direction = (Direction+1)%4;
			
		}
		
		if (LEFT & RIGHT & gotGrenade) {
			if (gotGrenade) {
			grenade -> x = my_pointer -> x;
			grenade -> y = my_pointer -> y;
			grenade -> is_visible = 1;
			grenadeCounter = 0;
			grenadeDropped = 1;
			}
		}
		
		if (grenadeExploded) {
			
			int gx = grenade -> x;
			int gy = grenade -> y;
				
			for (int i = 0; i<numZombies; i++) {
							
				int top = gy - 10;
				int bottom = gy +13;
				int left = gx - 10;
				int right = gx + 13;
				
				byte zx = zombie[i] -> x;
				byte zy = zombie[i] -> y;
				
				if (zx > left && zx < right && zy > top && zy < bottom && (zombie[i] -> is_visible == 1) ) {
					zombie[i] -> is_visible = 0;
					Score++;
					activeZombies--;
				}
			}
			
			explosion -> x = gx - 3;
			explosion -> y = gy - 3;
			explosion -> is_visible = 1;
			//draw_sprite(explosion);
			explosionCounter = 0;
			gotGrenade = 0;
			grenadeExploded = 0;
			setupGrenade();
			
		}
		
		draw_sprite(my_pointer);
		draw_sprite(grenade);
		draw_sprite(sword);
		//draw_sprite(grenade);
		if (gotSword) {
		swordStatus -> x = 45;
		swordStatus -> y = 0;
		draw_sprite(swordStatus);
		}
		else {
		swordStatus -> x = -10;
		swordStatus -> y = -10;
		draw_sprite(swordStatus);
		}
		if (gotGrenade) {
		grenadeStatus -> x = 45;
		grenadeStatus -> y = 5;
		grenadeStatus -> is_visible = 1;
		draw_sprite(grenadeStatus);
		}
		else {
		grenadeStatus -> is_visible = 0;		
		}
		draw_sprite(explosion);
		for (int i = 0; i<numZombies; i++) {
		draw_sprite(zombie[i]);
		}
		drawPit();
		drawScreen();
		refresh();
		collision();
		if (activeZombies < 1) {
		winScreen();
		}
	}
	
	
	return 0;
}

void setupGame() {

	// SW0 and SW1 are connected to pins B0 and B1
	// LED1 and LED2 connected to pins B2 and B3
	// 0 for input 1 for output
	DDRB |= 0b00001100;
    // Teensy LED is connected to D6
    DDRD |= 0b01000000;
    // turn OFF LED initially
	PORTD |= 0b00000000;
	PORTB |= (1<<2)||(1<<3); //not sure why this is here
	
	//initialise clock
	//CLKPR |= 1 << CLKPCE;
	//CLKPR |= 1 << CLKPS0;
	CPU_PRESCALE(CPU_16MHz);
	
	
	LCDInitialise(LCD_DEFAULT_CONTRAST);
	clear();
	
	PinChangeInit();
	TimerInit();
	
	clear();
	draw_string("ZombieDash v1.0", 4,0); // 15*5 = 75 (84 - 75)/2 = 4
	draw_string("Lachlan Robinson", 2,9); // 16*5 = 80 (84 - 80)/2 = 2
	draw_string("n8845409", 22, 28); // 8*5 = 40 (84 - 40)/2 = 22
	refresh();
	
	seedWithButtonPress();
	buttonCheck();
	
	chooseDifficulty();	
	
	if (difficulty == 1) {
	//numZombies = 16;
	zombieSteps = 4;
	}
	CountDown();
	Lives = 3;
	Score = 0;
	activeZombies = numZombies;
	
}

void CountDown() {
	for (char i= 0x3; i>0x0; i--) {
		clear();
		draw_string("Game Start In: ", 2,22); // 15*5 = 75 (84 - 75)/2 = 4
		draw_character((0x30 + i), 75,22);
		refresh();
		_delay_ms(1000);
	}
}

void buttonCheck() {

	RIGHT = 0; LEFT = 0;
	
	if(PINB & 0b00000010) {
	_delay_ms(50);
	if(PINB & 0b00000010) {
		// Send output to PORTD.
		//PORTB |= (1<<3); //PORTB = 0b11111111;
		RIGHT = 1;
	}
	}
	
	if (PINB & 0b00000001 ) {
	_delay_ms(50);
	if (PINB & 0b00000001 ) {
		//PORTB |= (1<<2);
		LEFT = 1;
	}
	}
	//(fooo & foo) == fooo)
	/*
	if ((~PINB & (1<<1)) == (1<<1)) {
		PORTB &= ~((1<<3));
		RIGHT = 0;
	}
	
	if ((~PINB & (1)) == (1) ) {
		PORTB &= ~((1<<2));
		LEFT = 0;
	}
	*/
}

int randInRange(int min, int max) {
	int out = min + rand()%(max+1 - min);
	return out;
}

void seedWithButtonPress() {
// turn on teensy LED
PORTD |= 0b01000000;
// Configure port B for the buttons....
DDRB |= 0b00001100;
// Wait for the button press on SW0 while iterating the seed
unsigned int seed = 0;
while (!RIGHT && !LEFT) {
seed++;
}
// Seed the random number generator
srand(seed);
// What does dgbI do? where is it from?
// dbgI((int) seed, 10);
// turn off teensy LED
PORTD = 0b00000000;
}

void PinChangeInit(void)
{
	//Enable PCINT0 and PCINT1 (both buttons) in the PCMSK0 register
	PCMSK0 |= (1<<PCINT0);
	PCMSK0 |= (1<<PCINT1);

	//Enable Pin change interrupts in the Pin Change Interrupt Control Register
	PCICR |= (1<<PCIE0);
	
	//Set the PCINT0 and PCINT1 interrupts to trigger on rising edge
	EICRA |= ((1<<ISC00)&&(1<<ISC01)&&(1<<ISC10)&&(1<<ISC11));
		
	//Ensure to enable global interrupts as well.
	sei();
}

ISR(PCINT0_vect) {	
	RIGHT = 0; LEFT = 0;
	
	if(PINB & 0b00000010) {
	//_delay_ms(50);
	//if(PINB & 0b00000010) {
		// Send output to PORTD.
		//PORTB |= (1<<3); //PORTB = 0b11111111;
		RIGHT = 1;
	//}
	}
	
	if (PINB & 0b00000001 ) {
	//_delay_ms(50);
	//if (PINB & 0b00000001 ) {
		//PORTB |= (1<<2);
		LEFT = 1;
	//}
	}
	/*
	buttonPressed=0;
	if ((PINB>>PINB0)&1){
		buttonPressed = 1;
	}
	if ((PINB>>PINB1)&1){
		if (buttonPressed){
			buttonPressed = 3;
		} else {
			buttonPressed = 2;
		}
	}
	if (buttonPressed==1){
		heroX = heroX-3;
	} else if (buttonPressed==2){
		heroX = heroX+3;
	}
	clear();
	draw_character('*',heroX,heroY);
	refresh();
	*/
}

void TimerInit(void)
{
	//Set to Normal Timer Mode using TCCR0A and TCCR0B
	TCCR0A &= ~((1<<WGM01)|(WGM00));
	TCCR0B &= ~((1<<WGM02));
	
	//Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(Clock Speed/Prescaler)
	//Prescaler = 1024
	//Timer Speed = 128 nano seconds NOT 16MHZ
	//Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer) NOT 16MHZ
	TCCR0B |= (1<<CS02)|(1<<CS00);
	TCCR0B &= ~((1<<CS01));
	
	//Enable TOIE0 interrupt in the TIMSK0 register
	TIMSK0 |= (1<<TOIE0);
	
	//Ensure to enable global interrupts as well.
	sei();
}


ISR(TIMER0_OVF_vect)
{
	//Clear the flag by writing a one
	TIFR0 |= (1<<TOV0);
	//Add one to our clockCounter
	clockCounter++;
	//DEBUG LED
	//PORTB ^= (1<<PINB2);
	//Check to see if our clockCounter is greater/equal to than our MAX_CLOCK_COUNTER_FOR_100MSECOND
	if(clockCounter >= MAX_CLOCK_COUNTER_FOR_100MSECOND && GAMEON)
	{
		//PORTB ^= (1<<PINB3);
		//Reset clockCounter
		clockCounter = 0;
		stepsCounter++;
		if (stepsCounter>zombieSteps) {
		scoreCounter++;
		explosionCounter++;
		if (grenadeDropped) {
		grenadeCounter++;
		}
		stepsCounter = 0;
		zombiesForward();		
		}
		if (scoreCounter>5) {
		scoreCounter = 0;
		Score++;
		}
		if ((grenadeCounter>3) & gotGrenade) {
		grenadeCounter = 0;
		grenadeDropped = 0;
		grenadeExploded = 1;
		}
		if (explosionCounter>3) {
		explosion -> is_visible = 0;
		explosionCounter = 0;		
		}
		heroForward();
	}
}

void heroForward(void) {

	int HeroX = 1;
	int HeroY = 0;
	int Up,Down,Left,Right;
	
	// is hero in pit?
	if (isInPit(my_pointer)) {
	Up = pitTop+2;
	Down = pitBottom - 4;
	Left = pitLeft+2;
	Right = pitRight -4;
	} else {
	Up = 10;
	Down = screen_y-1;
	Left = 2;
	Right = screen_x-1;
	}

	// update direction of movement
	if (Direction == 0) {
		sword -> bitmap = bitSwordDown;
		if (gotSword) {
		sword -> x = my_pointer -> x;
		sword -> y = my_pointer -> y + 4;
		}
		HeroY = 1;
		HeroX = 0;
		if (my_pointer -> y > Down) {
		HeroY = 0;
		}
	}
	if (Direction == 1) {
		sword -> bitmap = bitSwordRight;
		if (gotSword) {
		sword -> x = my_pointer -> x + 4;
		sword -> y = my_pointer -> y;
		}
		HeroX = 1;
		HeroY = 0;
		if (my_pointer -> x > Right) {
		HeroX = 0;
		}
	}
	if (Direction == 2) {
		sword -> bitmap = bitSwordUp;
		if (gotSword) {
		sword -> x = my_pointer -> x;
		sword -> y = my_pointer -> y - 4;
		}
		HeroY = -1;
		HeroX = 0;
		if (my_pointer -> y < Up) {
		HeroY = 0;
		}
	}
	if (Direction == 3) {
		sword -> bitmap = bitSwordLeft;
		if (gotSword) {
		sword -> x = my_pointer -> x - 4;
		sword -> y = my_pointer -> y;
		}
		HeroX = -1;
		HeroY = 0;
		if (my_pointer -> x < Left) {
		HeroX = 0;
		}
	}
	
	if (isInPit(my_pointer)) {
		int x = my_pointer -> x;
		int y = my_pointer -> y;
		if (LEFT && RIGHT && x > Right ) {
		
		my_pointer -> x = Right + 4;	
		
		} else if (LEFT && RIGHT && x < Left ) {
		
		my_pointer -> x = Left - 4;
		
		} else if (LEFT && RIGHT && y < Up ) {
		
		my_pointer -> y = Up - 4;
		
		} else if (LEFT && RIGHT && y > Down ) {
		
		my_pointer -> y = Down + 4;
		
		}
	}	
		
	my_pointer -> x += HeroX;
	my_pointer -> y += HeroY;

}

void zombiesForward(void) {

	int range, ZX = 0;
	int ZY = 0;
	int Up,Left,Down,Right;
	
	//for all zombies
	for (int i = 0; i<numZombies; i++) {
		
		// change of direction with probability 5% each way
		range = randInRange(1,100);
		if (range < 6) {
			zDirection[i] = (zDirection[i]-1);
			if (zDirection[i] < 0) {
			zDirection[i] = 3;
			}
		}
		else if (range > 95) {
			zDirection[i] = (zDirection[i]+1)%4;
		}
		
		// is zombie in pit?
		if (isInPit(zombie[i])) {
			Up = pitTop+2;
			Down = pitBottom - 4;
			Left = pitLeft+2;
			Right = pitRight -4;
		} else {
			Up = 10;
			Down = screen_y-1;
			Left = 2;
			Right = screen_x-1;
		}
	
		if (zDirection[i] == 0) {
			ZY = 1;
			ZX = 0;
			if ((zombie[i] -> y > Down)) {
			ZY = 0;
			}
		}
		if (zDirection[i] == 1) {
			ZX = 1;
			ZY = 0;
			if ((zombie[i] -> x > Right)) {
			ZX = 0;
			}
		}
		if (zDirection[i] == 2) {
			ZY = -1;
			ZX = 0;
			if ((zombie[i] -> y < Up)) {
			ZY = 0;
			}
		}
		if (zDirection[i] == 3) {
			ZX = -1;
			ZY = 0;
			if ((zombie[i] -> x < Left)) {
			ZX = 0;
			}
		}

		zombie[i] -> x += ZX;
		zombie[i] -> y += ZY;

	}
	
}

void drawScreen(void) {
	draw_line(0,8,screen_x_Full,8);
	draw_line(0,8,0,screen_y_Full);
	draw_line(screen_x_Full,8,screen_x_Full,screen_y_Full);
	draw_line(0,screen_y_Full,screen_x_Full,screen_y_Full);
	draw_string("L: ",0,0);
	draw_character((0x30 + Lives),11,0);
	draw_string("S: ", 21,0);
	int temp = Score/10;
	draw_character((0x30 + Score%10),37,0);
	//if (Score > 9) 
	draw_character((0x30 + temp),31,0); //
	//draw_character((0x30 + scoreCounter),40,0);
	draw_character((0x30 + Direction),78,0);
	draw_character((0x30 + isInPit(my_pointer)),70,0);

}

void setupZombies(void ) {

	int middle_x = screen_x/2;
	int middle_y = screen_y/2 + 5;
	byte x, y;
	
	for (int i = 0; i<numZombies/4; i++) {
		x = randInRange(1,middle_x-10);
		y = randInRange(9, screen_y-1);
		zombie[i] -> x = x;
		zombie[i] -> y = y;
	}
	for (int i = 0; i<numZombies/4; i++) {
		x = randInRange(middle_x+10,screen_x);
		y = randInRange(9, screen_y-1);
		zombie[i+(numZombies/4)] -> x = x;
		zombie[i+(numZombies/4)] -> y = y;
	}
	for (int i = 0; i<numZombies/4; i++) {
		x = randInRange(1,screen_x);
		y = randInRange(9, middle_y-10);
		zombie[i+(numZombies/2)] -> x = x;
		zombie[i+(numZombies/2)] -> y = y;
	}
	for (int i = 0; i<numZombies/4; i++) {
		x = randInRange(1,screen_x);
		y = randInRange(middle_y+10,screen_y);
		zombie[i+(3*numZombies/4)] -> x = x;
		zombie[i+(3*numZombies/4)] -> y = y;
	}
	for (int i = 0; i<numZombies; i++) {
	zDirection[i] = randInRange(0,3);
	if (notOver == 0) {
	zombie[i] -> is_visible = 1;
	}
	}
}

void setupHero(void) {
	int middle_x = screen_x/2;
	int middle_y = screen_y/2 + 5;
	my_pointer -> x = middle_x;
	my_pointer -> y = middle_y;
	my_pointer -> is_visible = 1;
}

void collision(void) {

	int middle_x = screen_x/2;
	int middle_y = screen_y/2;
	
	byte x = my_pointer -> x;
	byte y = my_pointer -> y;
	
	int sx = sword -> x;
	int sy = sword -> y;
	
	int gx = grenade -> x;
	int gy = grenade -> y;
	
	// checking zombie collisions
	for (int i = 0; i<numZombies; i++) {
		byte zx = zombie[i] -> x;
		byte zy = zombie[i] -> y;
		
		if (sx > zx - width && sx < zx + width && sy > zy - height && sy < zy + height && gotSword && (zombie[i] -> is_visible == 1) ) {
			zombie[i] -> is_visible = 0;
			Score++;
			activeZombies--;
		}
		
		if (x > zx - width && x < zx + width && y > zy - height && y < zy + height && (zombie[i] -> is_visible == 1) ) {
		GAMEON = 0;
			if (Lives>0) {
				_delay_ms(300);
				clear();
				draw_string("Touched A Zombie!",0,middle_y);
				refresh();
				_delay_ms(1500);
				Lives--;
				setupHero();
				notOver = 1;
				setupZombies();
				notOver = 0;
				setupSword();
				gotSword = 0;
				setupGrenade();
				gotGrenade = 0;
				grenadeDropped = 0;
				grenadeExploded = 0;
			}
			else {
				_delay_ms(300);
				clear();
				draw_string("Game OVER!", middle_x-25,middle_y);
				refresh();
				_delay_ms(1500);
				setupGame();
				setupHero();
				setupZombies();	
				setupPit();
				setupSword();
				gotSword = 0;
				setupGrenade();
				gotGrenade = 0;
				grenadeDropped = 0;
				grenadeExploded = 0;
			}
		GAMEON = 1;	
		}
	} 
	
	// sword collision and collection
	if (x > sx - width && x < sx + width && y > sy - height && y < sy + height) {
	gotSword = 1;
	}
	if (x > gx - width && x < gx + width && y > gy - height && y < gy + height && gotGrenade == 0) {
	gotGrenade = 1;
	grenade -> is_visible = 0;
	}
	
}

void setupPit(void) {

	int pitwidth = randInRange(6,12);
	int pitheight = randInRange(6,12);
	pitLeft = randInRange(20,screen_x_Full-20);
	pitRight = pitLeft + pitwidth;
	pitTop = randInRange(9+20,screen_y_Full-20);
	pitBottom = pitTop + pitheight;
	drawPit();

}

void drawPit(void) {

	draw_line(pitLeft,pitTop,pitRight,pitTop);
	draw_line(pitLeft,pitBottom,pitRight,pitBottom);
	draw_line(pitLeft,pitTop,pitLeft,pitBottom);
	draw_line(pitRight,pitTop,pitRight,pitBottom);
	
}

int isInPit(Sprite *sprite) {
	int x = sprite -> x;
	int y = sprite -> y;
	if ((x > pitLeft && x < pitRight - width +1 && y > pitTop && y < pitBottom - height +1)) {
	return 1;
	}
	else {
	return 0;
	}

}

void setupSword(void) {
	int x = randInRange(2,screen_x);
	int y = randInRange(9,screen_y);
	sword -> x = x;
	sword -> y = y;
	sword -> is_visible = 1;
}

void setupGrenade(void) {
	int x = randInRange(2,screen_x);
	int y = randInRange(9,screen_y);
	grenade -> x = x;
	grenade -> y = y;
	grenade -> is_visible = 1;
}

void winScreen(void) {

	int middle_x = screen_x/2;
	int middle_y = screen_y/2;
	_delay_ms(500);
	clear();
	draw_string("You WIN!", middle_x-17,middle_y);
	refresh();
	_delay_ms(1500);
	setupGame();
	setupHero();
	setupZombies();	
	setupPit();
	setupSword();
	gotSword = 0;
	setupGrenade();
	gotGrenade = 0;
	grenadeDropped = 0;
	grenadeExploded = 0;

}

void chooseDifficulty(void) {
	
	int notRIGHT = 1;
	int notLEFT = 1;
	int middle_x = screen_x/2;
	int middle_y = screen_y/2;
	difficulty = 0;
	clear();
	draw_string("Standard", middle_x - 4*5, middle_y);
	refresh();
	//_delay_ms(3000);
	buttonCheck();
	
	while ( (LEFT == 0) && (notLEFT) ) {
	
		clear();
		if (RIGHT == 0) {
			notRIGHT = 1;
		}
		if (LEFT == 0) {
			notLEFT = 1;
		}
		if (RIGHT && notRIGHT) {
			notRIGHT = 0;
			difficulty = (difficulty+1)%2;
		}
		if (difficulty == 0) {
		draw_string("Difficulty:", middle_x - 5*5, middle_y-9);
		draw_string("Standard", middle_x - 4*5, middle_y);
		}
		else {
		draw_string("Difficulty:", middle_x - 5*5, middle_y-9);
		draw_string("Advanced", middle_x - 4*5, middle_y);
		}
		refresh();
	
	}
	//difficulty = toggle;
}
