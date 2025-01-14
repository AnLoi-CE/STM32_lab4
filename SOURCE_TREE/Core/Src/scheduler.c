/*
 * scheduler.c
 *
 *  Created on: Dec 11, 2024
 *      Author: DELL
 */

#include "scheduler.h"
int counter;
//sTask SCH_task_G[];
void SCH_Init(void){
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
};
unsigned char SCH_Add_Task(void (* pFunction)() , unsigned int DELAY, unsigned int PERIOD){
	unsigned char Index = 0;
	while((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	if (Index >= SCH_MAX_TASKS || Index < 0){
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;

	return Index;
};
unsigned char SCH_Delete_Task(const int TASK_INDEX){
	if(TASK_INDEX < 0 || TASK_INDEX > counter-1 || counter == 0){
		return counter;
	}
	else{
		if(counter == 1){
			SCH_tasks_G[0].pTask = 0x0000;
			SCH_tasks_G[0].Delay = 0;
			SCH_tasks_G[0].Period = 0;
			SCH_tasks_G[0].RunMe = 0;
			counter = 0;
			return 1;
		}
		else{
			SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
			SCH_tasks_G[TASK_INDEX].Delay = 0;
			SCH_tasks_G[TASK_INDEX].Period = 0;
			SCH_tasks_G[TASK_INDEX].RunMe = 0;
			counter--;
			return 1;
		}
	}
};
void SCH_Update(void){
	unsigned char Index;
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].pTask){
			if(SCH_tasks_G[Index].Delay == 0){
				SCH_tasks_G[Index].RunMe++;

				if(SCH_tasks_G[Index].Period){
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
			else{
				SCH_tasks_G[Index].Delay--;
			}
		}
	}
};

void SCH_Dispatch_Tasks(void){
	unsigned char Index;
		for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe--;
			if (SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
			else{
				 sTask temp;
				 temp.Period = SCH_tasks_G[0].Period;
				 temp.pTask = SCH_tasks_G[0].pTask;
				 SCH_Delete_Task(0);
				 SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
			}
		}
	}
};


//void SCH_Update(void) {
//	for (int i = 0; i < current_index_task; i++) {
//		if (SCH_tasks_G[i].pTask) {
//			if (SCH_tasks_G[i].Delay > 0) {
//				SCH_tasks_G[i].Delay--;
//			} else {
//				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//				SCH_tasks_G[i].RunMe += 1;
//				}
//			}
//		}
//    }

//unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int  DELAY, unsigned int PERIOD) {
//	if (current_index_task < SCH_MAX_TASKS) {
//	        SCH_tasks_G[current_index_task].pTask = pFunction;
//	        SCH_tasks_G[current_index_task].Delay = DELAY;
//	        SCH_tasks_G[current_index_task].Period = PERIOD;
//	        SCH_tasks_G[current_index_task].RunMe = 0;
//	        SCH_tasks_G[current_index_task].TaskID = current_index_task;
//	        current_index_task++;
//	        return current_index_task - 1;
//	    }
//	    return -1;
//}


//void SCH_Delete_Task(uint32_t taskID) {
//	unsigned char SCH_Delete_Task ( const tByte TASK_INDEX) {
//	 unsigned char Return_code ;
//	 if ( SCH_tasks_G [TASK_INDEX ] . pTask == 0) {
//	 Return_code = RETURN_ERROR;
//	 } else {
//	 Return_code = RETURN_NORMAL;
//	 }
//	 SCH_tasks_G [TASK_INDEX ] . pTask = 0x0000 ;
//	 SCH_tasks_G [TASK_INDEX ] . Delay = 0 ;
//	 SCH_tasks_G [TASK_INDEX ] . Period = 0 ;
//	 SCH_tasks_G [TASK_INDEX ] . RunMe = 0 ;
//	 return Return_code ;
//}



