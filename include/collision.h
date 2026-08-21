#pragma once

#include "ball.h"
#include "wall.h"


class Collision{

    public:
        static void worldBorder(Ball&, float);
        static void ballToBall(Ball&, Ball&, float);
        static void ballToWall(Ball&, Wall&, float);

};