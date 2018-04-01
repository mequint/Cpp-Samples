#pragma once

#include "IntroGameState.h"
#include "MainMenuGameState.h"
#include "DisplayRulesGameState.h"
#include "SetupNewGameState.h"
#include "LoadGameState.h"
#include "InGameState.h"
#include "GameOverState.h"
#include "ExitingGameState.h"

enum class GameStateType { Intro = 1, MainMenu, DisplayRules, SetupNewGame, LoadGame, InGame, GameOver, Exiting };