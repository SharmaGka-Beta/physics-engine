#pragma once

#include "ball.h"


class Collision{

    public:
        static void worldBorder(Ball& ball, float coeffRestitution);
};