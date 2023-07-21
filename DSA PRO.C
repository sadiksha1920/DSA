#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for priority levels
#define HIGH 1
#define MEDIUM 2
#define LOW 3

// Structure to represent a task
struct Task {
    char title[50];
    char description[100];
    int priority;
    int completed;
};

// Structure to represent the task scheduler
struct TaskScheduler {
    struct Task* tasks;
    int numTasks;
};

// Function to create a new task
struct Task createTask(const char* title, const char* description, int priority) {
    struct Task newTask;
    strcpy(newTask.title, title);
    strcpy(newTask.description, description);
    newTask.priority = priority;
    newTask.completed = 0; // 0 for incomplete, 1 for completed
    return newTask;
}

// Function to initialize the task scheduler
void initializeTaskScheduler(struct TaskScheduler* scheduler) {
    scheduler->tasks = NULL;
    scheduler->numTasks = 0;
}

// Function to add a new task to the task scheduler
void addTask(struct TaskScheduler* scheduler, struct Task newTask) {
    scheduler->numTasks++;
    scheduler->tasks = (struct Task*)realloc(scheduler->tasks, scheduler->numTasks * sizeof(struct Task));
    scheduler->tasks[scheduler->numTasks - 1] = newTask;
}

// Function to compare tasks for sorting based on priority
int compareTasks(const void* task1, const void* task2) {
    return ((struct Task*)task1)->priority - ((struct Task*)task2)->priority;
}

// Function to display the list of tasks
void displayTasks(struct TaskScheduler* scheduler) {
    printf("Task List:\n");
    printf("-----------\n");
    for (int i = 0; i < scheduler->numTasks; i++) {
        printf("Title: %s\n", scheduler->tasks[i].title);
        printf("Description: %s\n", scheduler->tasks[i].description);
        printf("Priority: %s\n", scheduler->tasks[i].priority == HIGH ? "High" : (scheduler->tasks[i].priority == MEDIUM ? "Medium" : "Low"));
        printf("Status: %s\n", scheduler->tasks[i].completed ? "Completed" : "Incomplete");
        printf("-----------\n");
    }
}

// Function to execute tasks in order of priority
void executeTasks(struct TaskScheduler* scheduler) {
    qsort(scheduler->tasks, scheduler->numTasks, sizeof(struct Task), compareTasks);

    printf("\nExecuting Tasks:\n");
    printf("------------------\n");
    for (int i = 0; i < scheduler->numTasks; i++) {
        printf("Executing Task: %s\n", scheduler->tasks[i].title);
        printf("Description: %s\n", scheduler->tasks[i].description);
        printf("Priority: %s\n", scheduler->tasks[i].priority == HIGH ? "High" : (scheduler->tasks[i].priority == MEDIUM ? "Medium" : "Low"));
        printf("-----------\n");
        scheduler->tasks[i].completed = 1;
    }
}

// Function to search for a task based on title or description
void searchTask(struct TaskScheduler* scheduler, const char* searchTerm) {
    printf("Search Results:\n");
    printf("-----------\n");
    for (int i = 0; i < scheduler->numTasks; i++) {
        if (strstr(scheduler->tasks[i].title, searchTerm) || strstr(scheduler->tasks[i].description, searchTerm)) {
            printf("Title: %s\n", scheduler->tasks[i].title);
            printf("Description: %s\n", scheduler->tasks[i].description);
            printf("Priority: %s\n", scheduler->tasks[i].priority == HIGH ? "High" : (scheduler->tasks[i].priority == MEDIUM ? "Medium" : "Low"));
            printf("Status: %s\n", scheduler->tasks[i].completed ? "Completed" : "Incomplete");
            printf("-----------\n");
        }
    }
}

// Function to delete a task by index
void deleteTask(struct TaskScheduler* scheduler, int index) {
    if (index < 0 || index >= scheduler->numTasks) {
        printf("Invalid task index\n");
        return;
    }

    for (int i = index; i < scheduler->numTasks - 1; i++) {
        scheduler->tasks[i] = scheduler->tasks[i + 1];
    }

    scheduler->numTasks--;
    scheduler->tasks = (struct Task*)realloc(scheduler->tasks, scheduler->numTasks * sizeof(struct Task));
}

// Function to free memory allocated for the task scheduler
void freeTaskScheduler(struct TaskScheduler* scheduler) {
    free(scheduler->tasks);
    scheduler->tasks = NULL;
    scheduler->numTasks = 0;
}

int main() {
    struct TaskScheduler scheduler;
    initializeTaskScheduler(&scheduler);

    // Add some sample tasks
    addTask(&scheduler, createTask("Finish report", "Complete the project report", HIGH));
    addTask(&scheduler, createTask("Buy groceries", "Get eggs, milk, and bread", MEDIUM));
    addTask(&scheduler, createTask("Pay bills", "Pay electricity and water bills", LOW));
    addTask(&scheduler, createTask("Call mom", "Check up on mom", HIGH));

    displayTasks(&scheduler);

    executeTasks(&scheduler);

    char searchTerm[50];
    printf("\nEnter a search term: ");
    scanf("%s", searchTerm);

    searchTask(&scheduler, searchTerm);

    int indexToDelete;
    printf("\nEnter the index of the task to delete: ");
    scanf("%d", &indexToDelete);

    deleteTask(&scheduler, indexToDelete);

    displayTasks(&scheduler);

    freeTaskScheduler(&scheduler);

    return 0;
}
