#include <iostream>
#include "E101.h"
#include <math.h>

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

int checkLine() {

    take_picture();

    int width = 320;
    int height = 240;

    int blackLeft = 0;
    int blackMiddle = 0;
    int blackRight = 0;

    //Loop through each col
    for(int y = 0; y < height; y+=4) {

        //Left side of screen
        for(int x = 0; x < width / 3; x+=4) {
            if(getBlack(y, x)) {
				 blackLeft++;
			}
        }

        //Middle of screen
        for(int x = width / 3; x < width / 3 * 2; x+=4) {
            if(getBlack(y, x)) {
				blackMiddle++;
			}
        }

        //Right side of screen
        for(int x = width / 3 * 2; x <  width; x+=4) {
            if(getBlack(y, x)) {
				blackRight++;
			}
        }
    }
    
    //std::cout << blackLeft << std::endl;
    //std::cout << blackMiddle << std::endl;
    //std::cout << blackRight << std::endl;

    //Make sure there is a line detected
    if(blackLeft > 75 || blackMiddle > 75 || blackRight > 75) {

        //If the left has the most "black" pixels
        if(blackLeft > blackMiddle && blackLeft > blackRight) {
            return 0;
        }

        //If the middle has the most "black" pixels
        if(blackMiddle > blackLeft && blackMiddle > blackRight) {
            return 1;
        }

        //If the right has the most "black" pixels
        if(blackRight > blackLeft && blackRight > blackMiddle) {
            return 2;
        }
    }else{
        return 3;
    }
    return 3;
}

void changeDirection(int dir) {

    if(dir == 0) {
		set_motors(5, 48);  //Left
		set_motors(1, 43);  //Right
    }

    if(dir == 1) {
        set_motors(5, 51);  //Left
		set_motors(1, 43);  //Right
    }

    if(dir == 2) {
        set_motors(5, 50);  //Left
		set_motors(1, 48);  //Right
    }

    if(dir == 3) {
        set_motors(5, 42);  //Left
		set_motors(1, 52);  //Right
    }

    hardware_exchange();
}


//Main code
int main() {
	std::cout << "Starting program..." << std::endl;
    init(0);
	set_motors(5, 48);  //Left
	set_motors(1, 48);  //Right
    hardware_exchange();

    int lastLine = 5;
    
    
    while(true) {

        int currentLine = checkLine();

        if(currentLine != lastLine) {
			lastLine = currentLine;
            switch (currentLine)
            {
            case 0:
                std::cout << "Move left!" << std::endl;
                changeDirection(currentLine);
                break;
            case 1:
                std::cout << "Stay straight" << std::endl;
                changeDirection(currentLine);
                break;
            case 2:
                std::cout << "Move right" << std::endl;
                changeDirection(currentLine);
            break;
            case 3:
                std::cout << "No line! Moving back" << std::endl;
                changeDirection(currentLine);
                break;
            }
        }
        //sleep1(200);
    }


    return 0;   
}
