#include "TankKilledMessage.h"

TankKilledMessage::TankKilledMessage(GameEngine::Entity* killer, GameEngine::Entity* killed) : Message("TankKilled"), _killer(killer), _killed(killed)
{}