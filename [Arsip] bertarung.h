#ifndef BERTARUNG_H
#define BERTARUNG_H

#include "bertarung.h"
#include "boolean.h"
#include "unit.h"
#include "player.h"
#include "petak.h"
#include "peta.h"
#include <math.h>
#include "stdio.h"

boolean MEC_canAttack(unit A, unit B);

boolean MEC_canAttack(unit A, unit B);

boolean MEC_canRetaliates(unit X, unit Y);

void MEC_attack(unit *X, unit *Y);

void printUnitName(unit U);

void COMMAND_ATTACK(player *one, player *two, peta *m, boolean *game_over);
#endif