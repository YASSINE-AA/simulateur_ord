// SHORTEST JOB FIRST

void get_sjf_output(process* process_array, int process_array_size) {
    proc_queue* queue = (proc_queue*) malloc(sizeof(proc_queue));
    if(queue == NULL) {
        printf("Allocation error");
    }
    create_queue(queue);
    int current_time = get_earliest_time(process_array, process_array_size);
    int last_timestamp = get_last_timestamp(process_array, process_array_size);
    int new_arrival_size = 0; 
    int num_executed_processes = 0;

    process* new_arrival = get_new_arrival(current_time, NULL, 0, process_array, process_array_size, &new_arrival_size);
    process* next_proc_in_q = next_available_sjf(new_arrival, new_arrival_size, NULL);
    process* previous = next_proc_in_q;
    process* executed_processes = (process*) malloc(sizeof(process)*process_array_size);
    if (executed_processes == NULL) {
            // Handle memory allocation failure
            return;
    }
    while(!is_execution_done(executed_processes, num_executed_processes, process_array, process_array_size)) {
        if(next_proc_in_q != NULL && new_arrival != NULL) {
            //Populate queue
            while(next_proc_in_q != NULL) {
                add_to_queue(queue, *next_proc_in_q);    
                next_proc_in_q = next_available_sjf(new_arrival, new_arrival_size, next_proc_in_q);  
            }

            //Execute
            while(!is_queue_empty(queue)) {
                process executed = remove_from_queue(queue);
                executed_processes[num_executed_processes] = executed;
                num_executed_processes++;  
                printf("%s: [%d -> %d]  | ", executed.name, current_time, current_time + executed.execution_time); 
                current_time += executed.execution_time;
            }
        }   else {
            current_time++;
           
        }     
        new_arrival = get_new_arrival(current_time, executed_processes, num_executed_processes, process_array, process_array_size, &new_arrival_size);
        next_proc_in_q = next_available_sjf(new_arrival, new_arrival_size, next_proc_in_q);
    }
    if(executed_processes != NULL) free(executed_processes);
    if(new_arrival != NULL) free(new_arrival);
    if(queue != NULL) free(queue);
}