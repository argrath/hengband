﻿#pragma once

#include "spell/spells-util.h"
#include "system/angband.h"
#include <optional>
#include <string>

class PlayerType;
std::optional<std::string> do_arcane_spell(PlayerType *player_ptr, SPELL_IDX spell, SpellProcessType mode);
