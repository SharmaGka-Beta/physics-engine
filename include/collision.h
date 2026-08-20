#pragma once

#include "ball.h"


class Collision{

    public:
        static void worldBorder(Ball&, float);
        static void ballToBall(Ball&, Ball&, float);

};