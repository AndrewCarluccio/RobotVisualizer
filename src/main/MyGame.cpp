#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"



using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene = new Scene();
	scene->loadScene("./resources/Scenes/robot_demo.json");
	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	robot = scene->getChild("Robot");

	SDL_Point pv;
	pv.x = robot->getWidth() / 2.0;
	pv.y = robot->getHeight() / 2.0;
	robot->pivot = pv;

	//WIDTH = robot->getWidth();
	WIDTH = 80;
	/*
	Robot width in real life is 5.5 inches
	Using 80 pixels as a reference, 1 inch is
	14.545454 pixels
	*/
	robot->position.x = 450;
	robot->position.y = 450;

}

MyGame::~MyGame() {
}


/*
void MyGame::updatePosition(int enc_r, int enc_l) {
	//Pixels to Inch Conversion: 1 inch is 14.545454 pixels
	//Ticks to Inches 1 Inch is 188.46 ticks
	float ticks_per_revolution = 115.46; //1496 In Encoders/Rev, 7.938 Inches/Rev, 115.46 Pixels/Rev
	float circumfrence = 116.922; //8.0384 In inches, 116.92218 in Pixels

	float right_encoder_change = enc_r - right_encoder;
	float left_encoder_change = enc_l - left_encoder;

	float dr = circumfrence * (right_encoder_change/ ticks_per_revolution); //In Pixels
	float dl = circumfrence * (left_encoder_change/ ticks_per_revolution);

	float ds =  (5.0) * ((dr + dl) / (2.0)); //In Pixels
	float d_theta = (10.0) * ((dr - dl) / (1.0*WIDTH));  //In Pixels

	float dx = ds * float(cos(theta));
	float dy = ds * float(sin(theta));

	robot->position.x += dx;
	robot->position.y -= dy;
	robot->rotation += d_theta;

	right_encoder = enc_r;
	left_encoder = enc_l;
	theta += d_theta;

}
*/

void MyGame::updatePosition(int enc_r, int enc_l) {
	int delta_tick_right = enc_r - right_encoder;
	int delta_tick_left = enc_l - left_encoder;

	double right_inches = delta_tick_right / 188.46;
	double left_inches = delta_tick_left / 188.46;

	double inches = (right_inches + left_inches) / 2.0;

	total_inches += inches;

	theta += (left_inches - right_inches) / WIDTH;
	theta -= (float)((int)(theta / 6.2831853070)) * 6.2831853070;

	inch_y_loc += (inches * cos(theta* 57.2958));
	inch_x_loc += (inches * sin(theta* 57.2958));

	int pix_y_loc = inch_y_loc * 100; //100ppi
	int pix_x_loc = inch_x_loc * 100; //100ppi

	robot->position.x = 450+pix_x_loc;
	robot->position.y = 450+pix_y_loc;
	robot->rotation = (theta * 180) / 3.14159;

	right_encoder += delta_tick_right;
	left_encoder += delta_tick_left;
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
		updatePosition(right_encoder+1, left_encoder);


		cout << "Encoders: " << right_encoder <<","<<left_encoder<< endl;
		cout << "Position: " << robot->position.x << "," << 850 -robot->position.y << endl;
		//cam->moveCameraBy(5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		updatePosition(right_encoder, left_encoder+1);


		cout << "Encoders: " << right_encoder << "," << left_encoder << endl;
		cout << "Position: " << robot->position.x << "," << 850 - robot->position.y << endl;
		//cam->moveCameraBy(-5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		updatePosition(right_encoder + 1, left_encoder + 1);


		cout << "Encoders: " << endl;
		cout << "Position: " << robot->position.x << "," << 850 - robot->position.y << endl;
		//cam->moveCameraBy(0, -5);
	}

	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		


		cout << "Encoders: " << endl;
		cout << "Position: " << robot->position.x << "," << 850 -robot->position.y << endl;
		//cam->moveCameraBy(0, 5);
	}
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam,true);
	//activeScene->draw(at);
	SDL_RenderPresent(Game::renderer);
}