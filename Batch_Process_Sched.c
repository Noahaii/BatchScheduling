#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

struct node {
    int id;
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
} *table_ptr = NULL;

typedef struct node table_type;
int num_processes;

void ptrContents(table_type *local_table)
{
    int i;
    printf(" ID \t Arrival \t Total \t Start \t End \t Turnaround \n ----------------------------------------------------- \n");
    for(i = 0; i < num_processes; i += 1){
        printf(" %d \t %d \t\t %d \t ", local_table[i].id, local_table[i].arrival, local_table[i].total_cpu);
        if(local_table[i].done != 0){
            printf(" %d \t %d \t %d \n", local_table[i].start_time, local_table[i].end_time, local_table[i].turnaround_time);
        }
        else
            printf("\n");
    }
}

void parameters()
{
    printf("Enter total number of processes: ");
    scanf("%d", &num_processes);
    
    table_ptr = (table_type*)calloc(num_processes , sizeof(table_type));

    for(int i = 0; i < num_processes; i += 1){
        printf("Enter process id: ");
        scanf("%d", &table_ptr[i].id);
        printf("Enter arrival cycle for Process %d: ", i);
        scanf("%d", &table_ptr[i].arrival);
        printf("Enter total cycles for Process %d: ", i);
        scanf("%d", &table_ptr[i].total_cpu);
    }
    ptrContents(table_ptr);
    return;
}

void methodFIFO()
{
    int current_cycle = 0;
    int earliest_index;
    int num_done = 0;
    for(int i = 0; i < num_processes; i += 1){
        table_ptr[i].done = 0;
    }
    while(num_done < num_processes){
        int earliest_time = INT_MAX;
        for(int i = 0; i < num_processes; i += 1){ /* GOES THROUGH ALL PROCESSES */
            if(table_ptr[i].done == 0){ /* checks if not scheduled */
                if(table_ptr[i].arrival < earliest_time){
                    earliest_time = table_ptr[i].arrival;
                    earliest_index = i;              /* keeps track of earliest time index */
                }
            }
        }

        table_ptr[earliest_index].start_time = MAX(table_ptr[earliest_index].arrival, current_cycle);
        table_ptr[earliest_index].end_time = table_ptr[earliest_index].total_cpu + table_ptr[earliest_index].start_time;
        table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival;
        table_ptr[earliest_index].done = 1;

        num_done += 1;
        current_cycle = current_cycle + table_ptr[earliest_index].total_cpu;
    }
    ptrContents(table_ptr);
    return;
}

void methodSJF()
{  
    int at_least_one;
    int shortest_cpu;
    int current_cycle = 0;
    int shortest_cpu_index;
    int num_done = 0;
    for(int i = 0; i < num_processes; i += 1){
        table_ptr[i].done = 0;
    }
    while(num_done < num_processes){
        shortest_cpu = INT_MAX;
        at_least_one = 0;
        for(int i = 0; i < num_processes; i += 1){ /* GOES THROUGH ALL PROCESSES */
            if(table_ptr[i].done == 0){ /* checks if not scheduled */
                if(table_ptr[i].total_cpu < shortest_cpu && table_ptr[i].arrival <= current_cycle){
                    shortest_cpu = table_ptr[i].total_cpu;
                    shortest_cpu_index = i;     
                    at_least_one = 1;         /* keeps track of shortest cpu time index */
                }
            }
        }
        table_ptr[shortest_cpu_index].start_time = MAX(table_ptr[shortest_cpu_index].arrival, current_cycle);
        table_ptr[shortest_cpu_index].end_time = table_ptr[shortest_cpu_index].total_cpu + table_ptr[shortest_cpu_index].start_time;
        table_ptr[shortest_cpu_index].turnaround_time = table_ptr[shortest_cpu_index].end_time - table_ptr[shortest_cpu_index].arrival;
        table_ptr[shortest_cpu_index].done = 1;

        num_done += 1;
        current_cycle = current_cycle + table_ptr[shortest_cpu_index].total_cpu;
        
    }
    ptrContents(table_ptr);
    return;
}
/*
void methodSRT()
{
    int lowest_rem_time;
    int lowest_time_index;
    int current_cycle = 0;
    int num_done = 0;
    int at_least_one;
    for(int i = 0; i < num_processes; i += 1){
        table_ptr[i].done = 0;
        table_ptr[i].total_remaining = 0;
        table_ptr[i].already_started = 0;
    }
    while(num_done < num_processes){
        lowest_rem_time = INT_MAX;
        for(int i = 0; i < num_processes; i += 1){ 
            if(table_ptr[i].done == 0){ 
                if(table_ptr[i].total_cpu < lowest_rem_time && table_ptr[i].arrival <= current_cycle){
                    lowest_rem_time = table_ptr[i].total_cpu;
                    lowest_time_index = i;             
                }
            }
            if(table_ptr[i].already_started == 1){

            }

        }

        table_ptr[].start_time = MAX(table_ptr[].arrival, current_cycle);
        table_ptr[].end_time = table_ptr[].total_cpu + table_ptr[].start_time;
        table_ptr[].turnaround_time = table_ptr[].end_time - table_ptr[].arrival;
        table_ptr[].done = 1;

        num_done += 1;
        current_cycle = current_cycle + table_ptr[shortest_cpu_index].total_cpu;
    }
    ptrContents(table_ptr);
    return; 
} 
*/
void exitProgram()
{
    if(table_ptr != NULL){
        free(table_ptr);
    }
    return;
}

int main()
{
    int choice = 0;
    while (choice != 5)
    {
        printf("\n Batch scheduling \n------------------------------ \n 1) Enter parameters \n 2) Schedule processes with FIFO algorithm \n "
        "3) Schedule processes with SJF algorithm \n 4) Schedule processes with SRT algorithm \n 5) Quit and free memory \n");
        printf("\n Enter Selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: 
                parameters();
                break;
            case 2: 
                methodFIFO();
                break;
            case 3: 
                methodSJF(); 
                break;
            case 4: 
               // methodSRT(); 
                break;
            case 5:
                exitProgram();
                break;
            default: 
                printf("\n Invalid option!\n"); 
                break;
        }
    }
    return 1;
}