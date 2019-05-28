#include <iostream>
#include "E101.h"
#include "motor.h"
#include "robot.h"

int main() {

    Motor left(3, 48, true);
    Motor right(4, 48, false);
    Robot r(left, right);


    return 0;   
}