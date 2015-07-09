#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "SpriteComponent.h"

class GameObject
{
public:
	GameObject();
	GameObject(SpriteComponent* sprite);
	GameObject(const GameObject& object);
	~GameObject();

	void init(SpriteComponent* sprite);
	void free();

	void update();
	void render();

	SpriteComponent* getSpriteComponent() const { return sprite_; }

	int x,y;
	int velocity;

private:
	SpriteComponent* sprite_;
};

#endif