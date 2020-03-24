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

	//WIDTH = robot->getWidth();
	WIDTH = 80;
}

MyGame::~MyGame() {
}


void MyGame::updatePosition(int enc_r, int enc_l) {
	//Pixels to Inch Conversion: 1 inch is 14.545454 pixels
	//Ticks to Inches 1 Inch is 188.46 ticks
	float ticks_per_revolution = 116; //1496 In Encoders/Rev, 7.938 Inches/Rev, 115.46 Pixels/Rev
	float circumfrence = 116; //8.0384 In inches, 116.92218 in Pixels

	int right_encoder_change = enc_r - right_encoder;
	int left_encoder_change = enc_l - left_encoder;

	int dr = circumfrence * (right_encoder_change/ ticks_per_revolution); //In Pixels
	int dl = circumfrence * (left_encoder_change/ ticks_per_revolution);

	double ds = (dr + dl) / (2.0); //In Pixels
	double d_theta = (dr - dl) / (1.0*WIDTH);  //In Pixels

	double dx = ds * cos(theta);
	double dy = ds * sin(theta);

	robot->position.x += dx;
	robot->position.y -= dy;
	robot->rotation += d_theta;

	right_encoder = enc_r;
	left_encoder = enc_l;
	theta += d_theta;

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