#ifndef SPRITES_ANIMATED_SPRITE_H
#define SPRITES_ANIMATED_SPRITE_H

#include "sprites/sprite.h"

#include <vector>
#include <map>


struct Frame
{
	Sprite frame;
	float delay;
};


class AnimatedSprite
{
public:
	void AddFrame(const std::string &name, Sprite &&frame, float delay);

	Sprite & GetFrame(const std::string &animation_name, float time);

private:
	using Animation = std::vector<Frame>;
	std::map<std::string, Animation> animations;
	std::map<std::string, float> animation_times;
};


#endif // SPRITES_ANIMATED_SPRITE_H
