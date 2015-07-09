#include "GameObject.h"

GameObject::GameObject()
: sprite_(nullptr)
{}

GameObject::GameObject(SpriteComponent* sprite)
: sprite_(sprite)
{}

GameObject::~GameObject()
{
	free();
}

void GameObject::init(SpriteComponent* sprite)
{
	sprite_ = sprite;
}

void GameObject::free()
{
	if (sprite_ != nullptr)
	{
		sprite_->free();
		delete sprite_;
		sprite_ = nullptr;
	}
}

void GameObject::update()
{
	if (sprite_ != nullptr)
	{
		sprite_->update(*this);
	}
}

void GameObject::render()
{
	if (sprite_ != nullptr)
	{
		sprite_->render(*this);
	}
}