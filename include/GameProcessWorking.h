#pragma once

#include "../include/bonus.h"
#include "../include/hero.h"
#include "../include/field.h"
#include "../include/packman.h"
#include "../include/ghost.h"
#include "../include/gameprocess.h"
//#include <Windows.h>
#include <thread>
#include <cassert>
#include <map>


class GameProcessWorking
{
    GameProcess __temp;
    
    public:

    void saveProcess(GameProcess& process);
    GameProcess getProcess(){return __temp;}
    void Swaping(GameProcess& process_1, GameProcess& process_2);
    void ProcessStarting(GameProcess& process);
};