//
// Created by os on 8/13/22.
//

#ifndef PROJECT_BASE_V1_1_TRAPHANDLER_HPP
#define PROJECT_BASE_V1_1_TRAPHANDLER_HPP

#include "../lib/hw.h"


class trapHandler {
public:

    static void supervisorTrap();
    static uint8 numOfMemory;

private:

    static void handleSupervisorTrap();


};


#endif //PROJECT_BASE_V1_1_TRAPHANDLER_HPP
