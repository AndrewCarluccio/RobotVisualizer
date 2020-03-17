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
	int dr = enc_r - right_encoder;
	int dl = enc_l - left_encoder;

	double ds = (dr + dl) / (2.0);
	double d_theta = (dr - dl) / (2.0 * WIDTH);

	double dx = ds * cos(theta+d_theta);
	double dy = ds * sin(theta+d_theta);

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