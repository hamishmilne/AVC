#include <iostream>
#include "E101.h"

class Motor {
    unsigned char num;              //Motor num
    unsigned char pwm;              //Motor speed
    bool left;                      //Is the motor on the left or right?
    
public:
    Motor();                    //Dont use
    Motor(unsigned char motor_num, unsigned char motor_speed, bool motor_left);
    void forward();
    void back();
    void stop();
};

class Robot {
    Motor left;                     //Left motor
    Motor right;                    //Right motor
    
public:
    Robot();                    //Dont use
    Robot(Motor motor_left, Motor motor_right);
    void startLeft();
    void startRight();
    void startForward();
    void stop();
};

//Motor constructer, usage: Motor m(num, pwn);
Motor::Motor(unsigned char motor_num, unsigned char motor_speed, bool motor_left) {
    num = motor_num;
    pwm = motor_speed;
    left = motor_left;
    set_motors(num, pwm);
    hardware_exchange();
}

//Move motor forward
void Motor::forward() {
    //If a motor is on the left or right sight it should move in the reverse direction to the other
    if(left) {
        pwm = 65;
    }else{
        pwm = 30;
    }
    set_motors(num, pwm);
    hardware_exchange();
}

//Move motor backwards
void Motor::back() {
    //If a motor is on the left or right sight it should move in the reverse direction to the other
    if(left) {
        pwm = 30;
    }else{
        pwm = 65;
    }
    set_motors(num, pwm);
    hardware_exchange();
}

//Stop motor
void Motor::stop() {
    pwm = 48;
    set_motors(num, pwm);
    hardware_exchange();
}

Robot::Robot(Motor motor_left, Motor motor_right) {
    left = motor_left;
    right = motor_right;
    
    //Create camera here etc
}

//Moves both motors forward
void Robot::startForward() {
    left.forward();
    right.forward();
}

//Moves robot left
void Robot::startLeft() {
    left.back();
    right.forward();
}

//Moves robot right
void Robot::startRight() {
    left.forward();
    right.back();
}

//Stop robot
void Robot::stop() {
    left.stop();
    right.stop();
}

//Main code
int main() {
    
    Motor left(3, 48, true);
    Motor right(4, 48, false);
    Robot r(left, right);
    
    
    return 0;
}
