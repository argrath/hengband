﻿#pragma once

#include "system/angband.h"
#include <string>

extern concptr KWD_DAM; //!< 効果文字列: 損傷 / dam
extern concptr KWD_RANGE; //!< 効果文字列: 射程 / dir
extern concptr KWD_DURATION; //!< 効果文字列: 期間 / dur
extern concptr KWD_SPHERE; //!< 効果文字列: 範囲 / range
extern concptr KWD_HEAL; //!< 効果文字列: 回復 / heal
extern concptr KWD_MANA; //!< 効果文字列: MP回復 / heal SP
extern concptr KWD_POWER; //!< 効果文字列: 効力 / power
extern concptr KWD_RANDOM; //!< 効果文字列: ランダム / random

extern const uint32_t fake_spell_flags[4];

std::string info_string_dice(concptr str, DICE_NUMBER dice, DICE_SID sides, int base);
std::string info_damage(DICE_NUMBER dice, DICE_SID sides, int base);
std::string info_duration(int base, DICE_SID sides);
std::string info_range(POSITION range);
std::string info_heal(DICE_NUMBER dice, DICE_SID sides, int base);
std::string info_delay(int base, DICE_SID sides);
std::string info_multi_damage(int dam);
std::string info_multi_damage_dice(DICE_NUMBER dice, DICE_SID sides);
std::string info_power(int power);
std::string info_power_dice(DICE_NUMBER dice, DICE_SID sides);
std::string info_radius(POSITION rad);
std::string info_weight(WEIGHT weight);

class PlayerType;
void do_cmd_browse(PlayerType *player_ptr);
void do_cmd_study(PlayerType *player_ptr);
bool do_cmd_cast(PlayerType *player_ptr);
