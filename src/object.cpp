
#include "object.h"


Object::Object(glm::vec3 position, float radius, AnimatedSprite &aspr, const std::string &anim)
:position(position)
,radius(radius)
,animation(anim)
,anim_timer(0.0f)
,anim_sprite(&aspr)
{

}


Object::Object(glm::vec3 position, float radius, Sprite &spr)
: position(position)
, radius(radius)
, sprite(&spr)
{

}


Object::~Object()
{

}


void Object::PlayAnimation(const std::string &newanim)
{
	animation = newanim;
	anim_timer = 0.0f;
}


void Object::Update(float dt)
{
	anim_timer += dt;
}

void Object::SetFlip(bool flip)
{
	flipped = flip;
}

void Object::Render(Renderer &rend)
{
	int posx = position.x;
	int posy = position.y;
	posy -= position.z / 2.0f;

	int rot = 0;
	int zoom = 0;
	auto flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if (anim_sprite)
	{
		anim_sprite->GetFrame(animation, anim_timer).Render(rend, posx, posy, rot, zoom, flip);
	}
	else if (sprite)
	{
		sprite->Render(rend, posx, posy, rot, zoom, flip);
	}

}

void Object::SetPosition2(const glm::vec2 pos2)
{
	position.x = pos2.x;
	position.y = pos2.y;
}


void Object::Collide(Object &o2)
{

}


