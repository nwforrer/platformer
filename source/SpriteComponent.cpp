#include "SpriteComponent.h"
#include "GameObject.h"

SpriteComponent::SpriteComponent(Texture* texture)
{
	texture_ = texture;
}

void SpriteComponent::update(GameObject& obj)
{

}

void SpriteComponent::free()
{
	
}

void SpriteComponent::render(GameObject& obj)
{
	texture_->render(obj.x, obj.y);
}
