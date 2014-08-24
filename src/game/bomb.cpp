#include "Pch.h"
#include "Common.h"
#include "Game.h"

bomb::bomb() : entity(ET_BOMB) {
	_flags |= EF_BOMB;
	_colour = colour(colours::ORANGE, 0.0f);
	_radius = 4.0f;
	_time = 13;
}

void bomb::tick() {
	float f = 1.0f - square(_time / 13.0f);

	_radius = lerp(4.0f, 60.0f, f);

	if (--_time <= 0)
		destroy();
}

void bomb::post_tick() {
	for(auto e : _world->entities) {
		if (e->_flags & EF_DESTROYED)
			continue;

		if (!(e->_flags & EF_UNIT))
			continue;

		if (!(e->_flags & EF_ENEMY))
			continue;

		if (length_sq(_pos - e->_pos) < square(_radius + e->_radius))
			e->destroy();
	}
}

void bomb::hit_wall(int clipped) {
}

void bomb::draw(draw_context* dc) {
	for(int i = 0; i < 8; i++) {
		float f = (i / 8.0f) * PI;
		dc->push_transform(rotate_z(f));
		dc->rect(-vec2(_radius), vec2(_radius), _colour * 0.75f);
		dc->pop_transform();
	}

	float r = _radius * 0.75f;

	for(int i = 0; i < 8; i++) {
		float f = (i / 8.0f) * PI;
		dc->push_transform(rotate_z(f));
		dc->rect(-vec2(r), vec2(r), colour(0.0f, 1.0f));
		dc->pop_transform();
	}
}

void spawn_bomb(world* w, vec2 pos) {
	bomb* ent = spawn_entity(w, new bomb);

	ent->_pos = pos;
}