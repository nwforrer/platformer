#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

#include "Texture.h"

class GameObject;

class SpriteComponent
{
public:
	SpriteComponent(Texture* texture);
	SpriteComponent(Texture* texture, double scale);
	SpriteComponent(const SpriteComponent& sprite);

	void free();
	
	void update(GameObject& obj);
	void render(GameObject& obj);

	Texture* getTexture() const { return texture_; }
	double getScale() const { return scale_; }

private:
	Texture *texture_;
	double scale_;
};

#endif