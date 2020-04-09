#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/Sound.h"
#include "../engine/TweenJuggler.h"
#include "../engine/EventDispatcher.h"
#include "../engine/TweenEvent.h"
#include "../engine/TweenListener.h"
#include "../engine/Tween.h"
#include <cmath>


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform& at, Camera* cam);

	Scene* scene;
	DisplayObject* robot;


	TweenJuggler* tweenJuggler;

	Camera* cam;

	Sound* sfx;

	bool moveFlag = false;

	EventDispatcher* dispatch;

	int WIDTH;

	int left_encoder = 0;
	int right_encoder = 0;
	double theta = 0;

	double total_inches = 0;
	double inch_y_loc = 0;
	double inch_x_loc = 0;

	void updatePosition(int enc_r, int enc_l);

private:
	Scene* activeScene;
	bool show1 = true;
	bool collision = false;
};

#endif