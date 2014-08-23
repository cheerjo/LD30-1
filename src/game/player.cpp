#include "Pch.h"
#include "Common.h"
#include "Game.h"

player::player() : entity(ET_PLAYER), _reload_time() {
	_flags |= EF_PLAYER;
	_colour = colours::ORANGE * 1.5f;
	_radius = 6.0f;
}

void player::tick() {
	vec2 acc = gJoyLeft;

	if (is_key_down(KEY_LEFT)) acc.x -= 1.0f;
	if (is_key_down(KEY_RIGHT)) acc.x += 1.0f;
	if (is_key_down(KEY_UP)) acc.y -= 1.0f;
	if (is_key_down(KEY_DOWN)) acc.y += 1.0f;

	if (length_sq(acc) > 1.0f)
		acc = normalise(acc);

	_vel *= 0.8f;
	_vel += acc * 55.0f;
}

void player::post_tick() {
	vec2 dir = gJoyRight;

	if (_reload_time > 0)
		_reload_time--;

	if (length_sq(dir) > 0.2f) {
		try_fire(normalise(dir));
	}
}

void player::try_fire(vec2 dir) {
	if (_reload_time > 0)
		return;

	_reload_time = 3;

	vec2 p = _pos - _vel * DT;

	for(int i = -1; i <= 1; i++) {
		bullet* b = spawn_entity(_world, new bullet);

		vec2 d = dir * 800.0f;
		
		if (i != 0)
			d = (d * 0.9f) + (perp(dir) * (15.0f * i));

		b->_pos		= p;
		b->_old_pos	= p;
		b->_vel		= _vel + d;
	}
}