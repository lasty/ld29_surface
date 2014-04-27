#ifndef OBJECT_H
#define OBJECT_H

#include "sprites/sprite.h"
#include "sprites/animated_sprite.h"

#include <glm/glm.hpp>


class Object
{
public:
	Object(glm::vec3 position, float radius, AnimatedSprite &aspr, const std::string &anim);
	Object(glm::vec3 position, float radius, Sprite &spr);
	virtual ~Object();

protected:
	bool deleteme = false;
	friend class World;

private:
	glm::vec3 position;
	float radius = 1.0f;
	bool flipped = false;

	std::string animation;
	float anim_timer = 0.0f;

	AnimatedSprite *anim_sprite = nullptr;
	Sprite *sprite = nullptr;

public:
	void PlayAnimation(const std::string &newanim);

	virtual void Update(float dt);

	virtual void Render(Renderer &rend);

	virtual void Collide(Object &o2);

	virtual void MarkForDeletion(bool d) { deleteme = d; }
	void SetFlip(bool flip);

	const glm::vec3 & GetPosition() const { return position; }
	glm::vec2 GetPosition2() const { return glm::vec2{position.x, position.y}; }
	float GetRadius() const { return radius; }

	void SetPosition2(const glm::vec2 pos2);
};


#endif // OBJECT_H
