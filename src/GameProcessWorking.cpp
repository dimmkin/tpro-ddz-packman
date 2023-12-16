#include "../include/GameProcessWorking.h"

void GameProcessWorking::saveProcess(GameProcess &process)
{
    __temp = process;
}

void GameProcessWorking::Swaping(GameProcess& process_1, GameProcess& process_2)
{
	__temp = process_1;
    process_1 = process_2;
    process_2 = __temp;
}

void GameProcessWorking::ProcessStarting(GameProcess &process)
{
    bool flag = false;
    process.updateGameProcess(0, flag, 1, true);
}