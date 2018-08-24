#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H
#include <iostream>
#include <glm/glm.hpp>

constexpr float pi = 3.14159265359;
constexpr float half_pi = pi / 2.0f;
constexpr float double_pi = pi * 2.0f;

// Update system
constexpr unsigned updates_per_second = 60;
constexpr unsigned network_updates_per_second = 20;

// The number of milliseconds to skip per update
constexpr float skip_ticks = (1000.0f / float(updates_per_second));
constexpr float network_skip_ticks = (1000.0f / float(network_updates_per_second));

// The max number of times to update before rendering
constexpr unsigned max_frameskip = 1;

constexpr float delta_time = 1.0f / updates_per_second;

// Day / night cycle
constexpr float seconds_per_real_day = 86400.0f;
constexpr float game_days_per_real_day = 10000.0f;
constexpr float seconds_per_day = seconds_per_real_day / game_days_per_real_day;
constexpr float days_per_second = 1 / seconds_per_day;

constexpr float day_length = 1.0f;

// Physics / controls
constexpr float default_friction = 0.7f;
constexpr float default_gravity = -9.8f * delta_time;
constexpr float default_sensitivity = 0.3f;
constexpr float default_acceleration = 3.0f;
constexpr float player_sprint_speed = 4.0f;
constexpr float player_speed = 2.0f;

#endif // ENGINE_CONSTANTS_H
