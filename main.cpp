#include <iostream>
#include "E101.h"
#include <math.h>

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
        int checkLine();
};

//Motor constructer, usage: Motor m(num, pwn);
Motor::Motor(unsigned char motor_num, unsigned char motor_speed, bool motor_left) {
    num = motor_num;
    pwm = motor_speed;
    left = motor_left;
    set_motors(num, pwm);
    hardware_exchange();
}

//Does nothing
Motor::Motor() {

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

//Does nothing
Robot::Robot() {

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

bool getBlack(int x, int y) {
    int r = get_pixel(x, y, 0);
    int g = get_pixel(x, y, 1);
    int b = get_pixel(x, y, 2);

    //Normalize and gamma correct
    float rr = pow(r / 255.0, 2.2);
    float gg = pow(g / 255.0, 2.2);
    float bb = pow(b / 255.0, 2.2);

    //Calculate luminance
    float lum = 0.2126 * rr + 0.7152 * gg + 0.0722 * bb;

    // Gamma compand and rescale to byte range:
    int greyLevel = (int) (255.0 * pow(lum, 1.0 / 2.2));
    
    if(greyLevel > 255/3) {
		return false;
	}else{
		return true;
	}
}

int Robot::checkLine() {

    take_picture();

    int width = 320;
    int height = 240;

    int blackLeft = 0;
    int blackMiddle = 0;
    int blackRight = 0;

    //Loop through each col
    for(int y = 0; y < height; y++) {

        //Left side of screen
        for(int x = 0; x < width / 3; x++) {
            if(getBlack(y, x)) {
				 blackLeft++;
			}
        }

        //Middle of screen
        for(int x = width / 3; x < width / 3 * 2; x++) {
            if(getBlack(y, x)) {
				blackMiddle++;
			}
        }

        //Right side of screen
        for(int x = width / 3 * 2; x <  width; x++) {
            if(getBlack(y, x)) {
				blackRight++;
			}
        }
    }
    
    std::cout << blackLeft << std::endl;
    std::cout << blackMiddle << std::endl;
    std::cout << blackRight << std::endl;

    if(blackLeft > blackMiddle && blackLeft > blackRight) return 0;

    if(blackMiddle > blackLeft && blackMiddle > blackRight) return 1;

    if(blackRight > blackLeft && blackRight > blackMiddle) return 2;
    

    return 3;
}


//Main code
int main() {
    init(0);

    Motor left(3, 48, true);    //Left motor is on port 3
    Motor right(4, 48, false);  //Right motor is on port 4
    Robot r(left, right);

    open_screen_stream();

    while(true) {
        std::cout << r.checkLine() << std::endl;
        update_screen();
        sleep1(300);
    }


    return 0;   
}
