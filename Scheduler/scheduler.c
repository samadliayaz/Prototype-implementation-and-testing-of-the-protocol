#include"stdio.h"
#include"stdbool.h"
#include <unistd.h>
#include<time.h>
#include <stdlib.h>

typedef long long int ll;

const int RESET = 0;
const int OBJ1 = 1;
const int OBJ2 = 2;
const int OBJUP = 3;
const int OBJDOWN = 4;


int Field_State = -1;
int Control_State = -1;

ll clkReset;
ll clkSync;
ll tRTMax;
ll tSync;
ll reset_duration;
ll Sync_duration;

ll clkReset_Controller;
ll tRTMax_Controller;
ll reset_duration_Controller;


void reset_time(ll *a, ll *b, ll *c){
	ll now = (ll) time(NULL);
	*a = (ll) now;
	*b = *a + *c;
}


int field_obj(int input_for_field_object, int time_for_sync, int time_for_reset)

{
	clkReset = (ll) time(NULL);
	clkSync =  (ll) time(NULL);

	reset_duration = time_for_reset;
	Sync_duration  = time_for_sync;
	
	if(clkReset >= tRTMax){
		Field_State = RESET;
		reset_time(&clkReset, &tRTMax, &reset_duration);
		reset_time(&clkSync, &tSync, &Sync_duration);
	}
	
	else if(input_for_field_object == RESET){
		reset_time(&clkReset, &tRTMax, &reset_duration);
		reset_time(&clkSync, &tSync, &Sync_duration);
		return -1;
	}
	
	else if(input_for_field_object == OBJ2 || input_for_field_object == OBJDOWN){
		reset_time(&clkReset, &tRTMax, &reset_duration);
		if(clkSync >= tSync){
			Field_State = OBJUP;
			reset_time(&clkSync, &tSync, &Sync_duration);
		}
		else{
			return -1;
		}
	}
	
	else if(clkSync >= tSync){
		if(Control_State == OBJ2 || Control_State == OBJDOWN){
			Field_State = OBJUP;
		}
		else{
			Field_State = OBJ1;
		}
		reset_time(&clkSync, &tSync, &Sync_duration);
	}
	
	else{
		return -1;
	}
	
	return Field_State;
} 

int control_obj(int input_for_control_object, ll time_for_reset){
	
	reset_duration_Controller = time_for_reset;
	clkReset_Controller = (ll) time(NULL);
	
	if(clkReset_Controller >= tRTMax_Controller){
		reset_time(&clkReset_Controller, &tRTMax_Controller, &reset_duration_Controller);
		Control_State = RESET;
	}
	
	else if(input_for_control_object == OBJ1){
		Control_State = OBJ2;
		reset_time(&clkReset_Controller, &tRTMax_Controller, &reset_duration_Controller);
	}
	
	else if(input_for_control_object == OBJUP){
		Control_State = OBJDOWN;
		reset_time(&clkReset_Controller, &tRTMax_Controller, &reset_duration_Controller);
	}
	
	else if(input_for_control_object == RESET){
		reset_time(&clkReset_Controller, &tRTMax_Controller, &reset_duration_Controller);
		return -1;
	}
	
	else{
		return -1;
	}
	
	return Control_State;
}


int main(){
	
	int field_message, control_message = -1, i;
	ll r_duration = 12, r_c_duration = 12, sync_duration = 2, begin_time;
	
	clkReset = (ll) time(NULL);
	clkSync = (ll) time(NULL);
	begin_time = (ll) time(NULL);
	
	reset_time(&clkReset, &tRTMax, &r_duration);
	reset_time(&clkSync, &tSync, &sync_duration);
	reset_time(&clkReset_Controller, &tRTMax_Controller, &r_c_duration);
	
	for(i = 0 ; i < 45; i++){
	
		field_message = field_obj(control_message, sync_duration , r_duration);
		
		ll sec = (ll) time(0) - begin_time;
		
		if(field_message == OBJ1){
			printf("%ld th second: \t" , sec);
			printf("Connecting... 'OBJ1' is sent by the Field Object to the Control Object \n");
		}
		else if(field_message == OBJUP){
			printf("%ld th second: \t" , sec);
			printf("Data Transfering... 'OBJUP' message is sent by the Field Object to the Control Object \n");
		}
		else if(field_message == RESET){
			printf("%ld th second: \t" , sec);
			printf("Restarting... Connection is resetted by the Field Object \n");
		}

		
		control_message = control_obj(field_message, r_c_duration);
		
		if(control_message == OBJ2){
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
