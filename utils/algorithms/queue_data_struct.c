bool is_queue_empty(proc_queue* q) {
    return q->head == NULL;
}

void create_queue(proc_queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

void add_to_queue(proc_queue* q, process proc) {
    proc_in_queue* new_process = (proc_in_queue*)malloc(sizeof(proc_in_queue));
    if (new_process == NULL) {
        
        return;
    }
    new_process->value = proc;
    new_process->next = NULL;

    if (is_queue_empty(q)) {
        q->head = new_process;
        q->tail = new_process;
    } else {
        q->tail->next = new_process;
        q->tail = new_process;
    }
}

void add_to_queue_fifo(proc_queue* q, process proc) {
    proc_in_queue* new_process = (proc_in_queue*)malloc(sizeof(proc_in_queue));
    if (new_process == NULL) {
        return;
    }
    new_process->value = proc;
    new_process->next = NULL;

    if (is_queue_empty(q)) {
        q->head = new_process;
        q->tail = new_process;
    } else {
        if (proc.arrived_at < q->head->value.arrived_at) {
            new_process->next = q->head;
            q->head = new_process;
        } else {
            proc_in_queue* current = q->head;
            proc_in_queue* prev = NULL;

            while (current != NULL && proc.arrived_at >= current->value.arrived_at) {
                prev = current;
                current = current->next;
            }

            prev->next = new_process;
            new_process->next = current;

            if (current == NULL) {
                q->tail = new_process;
            }
        }
    }
}


process remove_from_queue(proc_queue* q) {
 
    process empty_process; 
    empty_process.name[0] = '\0';
    empty_process.arrived_at = 0;
    empty_process.execution_time = -1;
    
    if (!is_queue_empty(q)) {
        proc_in_queue* proc_to_delete = q->head;
        q->head = q->head->next;
        process result = proc_to_delete->value;
        free(proc_to_delete);
        return result;
    }
    
    return empty_process; 
}



priority_queue* init_priority_queue(int capacity) {
    priority_queue* pq = (priority_queue*)malloc(sizeof(priority_queue));
    pq->array = (process*)malloc(capacity * sizeof(process));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}


void swap(process* a, process* b) {
    process temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(priority_queue* pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    
    if (left < pq->size &&
        (pq->array[left].execution_time < pq->array[smallest].execution_time ||
         (pq->array[left].execution_time == pq->array[smallest].execution_time &&
          pq->array[left].arrived_at < pq->array[smallest].arrived_at))) {
        smallest = left;
    }

    
    if (right < pq->size &&
        (pq->array[right].execution_time < pq->array[smallest].execution_time ||
         (pq->array[right].execution_time == pq->array[smallest].execution_time &&
          pq->array[right].arrived_at < pq->array[smallest].arrived_at))) {
        smallest = right;
    }

    
    if (smallest != i) {
        swap(&pq->array[i], &pq->array[smallest]);
        heapify(pq, smallest);
    }
}


void add_to_pr_queue(priority_queue* pq, process new_process) {
    if (pq->size == pq->capacity) {
        printf("Overflow: Priority queue is full.\n");
        return;
    }

    
    int i = pq->size;
    pq->array[i] = new_process;
    pq->size++;

    
    while (i > 0 &&
           (pq->array[(i - 1) / 2].execution_time > pq->array[i].execution_time ||
            (pq->array[(i - 1) / 2].execution_time == pq->array[i].execution_time &&
             pq->array[(i - 1) / 2].arrived_at > pq->array[i].arrived_at))) {
        swap(&pq->array[i], &pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
process remove_from_pr_queue(priority_queue* pq) {
   if (pq->size <= 0) {
        process empty_process = {0, 0, 0, ""};
        return empty_process;
    }

    
    int min_index = 0;
    int i = 0;
    for (; i < pq->size; ++i) {
        if (
            pq->array[i].execution_time < pq->array[min_index].execution_time &&
            pq->array[i].execution_time > 0) {
            min_index = i;
        }
    }

    process min_process = pq->array[min_index];

    pq->array[min_index] = pq->array[pq->size - 1];
    pq->size--;

    heapify(pq, min_index);

    return min_process;
}



int is_pr_queue_empty(priority_queue* pq) {
    return pq->size == 0;
}


void free_priority_queue(priority_queue* pq) {
    free(pq->array);
    free(pq);
}
