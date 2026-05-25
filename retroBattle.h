// retroBattle.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <iostream>
#include <Windows.h>
#include "external_libraries/PDCurses/curses.h"
#include "headers/metrics.h"
#include "headers/general_funcs.h"
#include "headers/draw_funcs.h"

// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
#include "headers/entity.h"
#include "headers/Player.h"
#include "headers/enemies/Enemy.h"
#include "headers/BattleManager.h"
#include "headers/Vec2D.h"
#include "headers/EntityManager.h"
#include "headers/terrain/Room.h"
#include "headers/GateKeeper.h"
<<<<<<< HEAD
#include "headers/textures/AsciiTexture.h"
#include "headers/textures/TextureManager.h"
=======
#include "headers/movements/ChaseMovement.h"
#include "headers/terrain/Terrain.h"

#define BROWN_COLOR 20
#define LIGHT_GREEN_COLOR 21
#include "headers/items/Item.h"
#include "headers/items/Relic.h"

>>>>>>> 01cb85856d1e8a494b2095b492d64ccf7de1ad6e
