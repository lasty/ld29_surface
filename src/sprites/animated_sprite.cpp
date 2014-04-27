
#include "sprites/animated_sprite.h"



void AnimatedSprite::AddFrame(const std::string &name, Sprite &&frame, float delay)
{
	auto & animation = animations[name];

	animation.push_back({frame, delay});

	animation_times[name] += delay;  //gets constructed at zero, or recalls last value
}

Sprite & AnimatedSprite::GetFrame(const std::string &animation_name, float time)
{
	auto &animation = animations.at(animation_name);
	const float looptime = animation_times.at(animation_name);

	if (animation.size() == 0) throw std::logic_error("This animation has no frames");

	float elapsed = 0.0f;

	while (time > looptime)
	{
		time -= looptime;
	}

	for (int loop=0; loop < 2; loop++)
	{
		for (auto & frame : animation)
		{
			if (elapsed >= time)
			{
				return frame.frame;
			}
			elapsed += frame.delay;
		}
	}

	throw std::logic_error("Animation looped forever?");
}



