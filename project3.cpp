#include <iostream>
#include "E101.h"
class Robot { //decalarations
	private :
		int v_left, v_right, cam_tilt;
		int dv;
		double line_error;
		int quadrant ;
		const int cam_width = 320;
		const int cam_height = 240;
		const int v_left_go = 52;
		const int v_right_go = 43;
		double kp = 0.05;
		int line_present = 1;
	public:
		Rob(){}; //default constructor
		int InitHardware() ;
		void ReadSetMotors() ;
		void SetMotors() ;
		int MeasureLine() ;
		int FollowLine() ;
	} ;

int main(){
	
char inital[24] = {'P','l','e','a','s','e'};
char add[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
int port = 1024;
char pass[24];
connect_to_server(add,port);

send_to_server(inital);
receive_from_server(pass);
send_to_server(pass);
	
	Robot robot;
	robot.InitHardware();
	int count = 0;
	open_screen_stream();
		while (count<5000){
			robot.MeasureLine();
			robot.FollowLine();
			count++;
		}
		//save_picture("file1");
	close_screen_stream();
	stoph();
	return 0;	
	
{
	int Robot :: FollowLine(){
		MeasureLine() ;
			if(line_present) {
				dv=(int)(line_error∗kp);
				//dv = 0;
				v_left = v_left_go+dv;
				v_right = v_right_go+dv;
				cout << "line_error = " << line_error << " dv= " <<dv;
				SetMotors();
				} 
			else {
				//goback
				cout << "Line missing " <<endl;
				v_left = 39;
				v_right = 55;
				SetMotors();
				sleep1(100);
				}
			return 0;
		}

	}
