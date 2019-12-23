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


void reset_time(ll *a, ll *b, ll *c){
	ll now = (ll) time(NULL);
	*a = (ll) now;
	*b = *a + *c;
}


int field_obj(int input_for_field_object, int time_for_sync, int time_for_reset, int i){

	clkReset = (ll) time(NULL);
	clkSync =  (ll) time(NULL);

	reset_duration = time_for_reset;
	Sync_duration  = time_for_sync;
	
	if(i == 0){
		clkSync--;
		clkReset--;
		reset_time(&clkReset, &tRTMax, &reset_duration);
		reset_time(&clkSync, &tSync, &Sync_duration);
		clkSync++;
		clkReset++;
	}
	
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
