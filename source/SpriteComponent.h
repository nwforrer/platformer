#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

#include "Texture.h"

class GameObject;

class SpriteComponent
{
public:
	SpriteComponent(Texture* texture);

	void free();
	
	void update(GameObject& obj);
	void render(GameObject& obj);

private:
	Texture *texture_;
};

#endif