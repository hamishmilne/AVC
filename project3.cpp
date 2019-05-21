#include <iostream>
#include "E101.h"
int main(){
	
	
char inital[24] = {'P','l','e','a','s','e'};
char add[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
int port = 1024;
char pass[24];
connect_to_server(add,port);

send_to_server(inital);
receive_from_server(pass);
send_to_server(pass);

}
