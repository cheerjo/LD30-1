#include "Pch.h"
#include "Common.h"
#include "Game.h"

tracker::tracker() : unit(ET_TRACKER), _drift_time() {
	_flags |= EF_ENEMY;
	_colour = colours::PURPLE;
	_radius = 8.0f;
}

void tracker::tick() {
	if (_drift_time-- <= 0) {
		_drift_force	= _world->r.range(vec2(10.0f));
		_drift_time		= _world->r.range(30, 60);
	}

	if (player* p = find_nearest_player(_world, _pos)) {
		_vel *= 0.9f;
		_vel += normalise(p->_pos - _pos) * 20.0f;
		_vel += _drift_force;
	}

	avoid_crowd(_world, this, true);
}

void tracker::post_tick() {
	unit::post_tick();
}

void tracker::hit_wall(int clipped) {
	if (clipped & CLIPPED_XN) _vel.x = fabsf(_vel.x);
	if (clipped & CLIPPED_XP) _vel.x = -fabsf(_vel.x);
	if (clipped & CLIPPED_YN) _vel.y = fabsf(_vel.y);
	if (clipped & CLIPPED_YP) _vel.y = -fabsf(_vel.y);
}
