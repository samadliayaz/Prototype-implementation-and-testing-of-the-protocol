#include"stdio.h"
#include"stdbool.h"
#include <unistd.h>
#include<time.h>
#include <stdlib.h>
#include"FieldObject.h"

typedef long long int ll;


int main(){
	
	int field_message, control_message = -1, i;
	ll r_duration = 4, sync_duration = 2, begin_time;
	ll clkReset, clkSync, tRTMax, tSync;
	bool no_signal;
	
	clkReset = (ll) time(NULL);
	clkSync = (ll) time(NULL);
	begin_time = (ll) time(NULL);
	
	reset_time(&clkReset, &tRTMax, &r_duration);
	reset_time(&clkSync, &tSync, &sync_duration);
	
	for(i = 0 ; i < 45; i++){
		field_message = field_obj(control_message, sync_duration , r_duration, i);
		
		ll sec = (ll) time(0) - begin_time;
		no_signal = false;
		
		if(field_message == OBJ1){
			printf("%ld th second: \t" , sec);
			printf("Connecting... 'OBJ1' is sent by the Field Object to the Control Object \n");
			control_message = OBJ2;
		}
		else if(field_message == OBJUP){
			printf("%ld th second: \t" , sec);
			printf("Data Transfering... 'OBJUP' message is sent by the Field Object to the Control Object \n");
			control_message = OBJDOWN;
		}
		else if(field_message == RESET){
			printf("%ld th second: \t" , sec);
			printf("Restarting... Connection is resetted by the Field Object \n");
			control_message = -1;
		}
		else{
			no_signal = true;
		}

		
		if(i >=20 && i<=23){
			control_message = -1;
		}
		else if(no_signal){
		// do nothing
		}		
		else if(control_message == OBJ2){
			printf("%ld th second: \t" , sec);
			printf("Connected... 'OBJ2' message is sent by the Control Object to the Field Object \n");
		}
		else if(control_message == OBJDOWN){
			printf("%ld th second: \t" , sec);
			printf("Data Transfering... 'OBJDOWN' message is sent by the Control Object to the Field Object \n");
		}
		else if(control_message == RESET){
			printf("%ld th second: \t" , sec);
			printf("Restarting... Connection is resetted by the Field Object \n");
		}
		sleep(1);
	}
	
}
