#include "SpriteComponent.h"
#include "GameObject.h"

SpriteComponent::SpriteComponent(Texture* texture)
{
	texture_ = texture;
	scale_ = 1.0f;
}

SpriteComponent::SpriteComponent(Texture* texture, double scale)
{
	texture_ = texture;
	scale_ = scale;
}

SpriteComponent::SpriteComponent(const SpriteComponent& sprite)
{
	texture_ = sprite.getTexture();
	scale_ = sprite.getScale();
}

void SpriteComponent::update(GameObject& obj)
{

}

void SpriteComponent::free()
{
	
}

void SpriteComponent::render(GameObject& obj)
{
	texture_->render(obj.x, obj.y, scale_);
}
