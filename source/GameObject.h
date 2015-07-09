#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "SpriteComponent.h"

class GameObject
{
public:
	GameObject();
	GameObject(SpriteComponent* sprite);
	~GameObject();

	void init(SpriteComponent* sprite);
	void free();

	void update();
	void render();

	int x,y;
	int velocity;

private:
	SpriteComponent* sprite_;
};

#endif