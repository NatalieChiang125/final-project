// RhythmGameConfig.hpp
#ifndef RHYTHM_GAME_CONFIG_HPP
#define RHYTHM_GAME_CONFIG_HPP

constexpr float NOTE_SPEED = 100.0f;       // Note falling speed (pixels/sec)
constexpr float TARGET_Y = 500.0f;         // Judge line Y coordinate
constexpr float JUDGE_THRESHOLD = 100.0f;   // Tolerance for judging a hit (pixels)
constexpr float NOTE_START_Y = -50.0f;     // Initial Y position for notes
constexpr float LANE_START_X = 500.0f;     // X position for lane 0
constexpr float LANE_WIDTH = 300.0f;       // Distance between lanes

#endif // RHYTHM_GAME_CONFIG_HPP
