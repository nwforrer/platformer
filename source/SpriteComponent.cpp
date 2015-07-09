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
