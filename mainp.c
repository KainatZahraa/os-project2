// Implements: Boot Sequence, Resource Management, Task Execution, Multilevel Scheduling, Interrupts
//final project :MINI OPERATING SYSTEM BY Kainat ZAhra Mehreen Fatima
//implements 15 tasks allows basic implementation of operating system
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define MAX_TASKS 20
#define MAX_NAME_LEN 50
#define MAX_CORES 8

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int ramUse;
    int priority;
    int running;
    int minimized;
} Task;

int RAM, DISK, CORES;
int *shared_memory;
int ramAvailable;
Task tasks[MAX_TASKS];
int taskCount = 16;

pthread_t threads[MAX_TASKS];
sem_t sem;

int fgQueue[MAX_TASKS];
int bgQueue[MAX_TASKS];
int fgFront = 0, fgRear = -1;
int bgFront = 0, bgRear = -1;

int isKernelMode = 0;

// -------------------- Utility Functions --------------------
void enqueue(int queue[], int *rear, int index) {
    queue[++(*rear)] = index;
}

int dequeue(int queue[], int *front, int rear) {
    if (*front <= rear) {
        return queue[(*front)++];
    }
    return -1;
}

void bootScreen() {
    printf("\n********************************************************************************\n");
    for (int i = 0; i < 5; i++) printf("*\t\t\t\t\t\t\t\t\t\t\t\t\t*\n");
    printf("\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\t\t\tLoading MyOS Operating System\n");
    printf("\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    for (int i = 0; i < 5; i++) printf("*\t\t\t\t\t\t\t\t\t\t\t\t\t*\n");
    printf("********************************************************************************\n");
    sleep(3);
    system("clear");
}

void shutdownScreen() {
    printf("\n\nShutting down MyOS. Please wait...\n");
    sleep(2);
    printf("Goodbye from MyOS!\n");
    sleep(1);
}

void initSharedMemory() {
    int shmid = shmget((key_t)1234, sizeof(int), 0666 | IPC_CREAT);
    shared_memory = (int *)shmat(shmid, NULL, 0);
    *shared_memory = RAM;
    ramAvailable = RAM;
}

void initTasks() {
    const char *names[] = {
        "Calculator", "tictactoe", "binarysearch", "banking", "guessgame",
        "messagebox", "createfile", "deletefile", "Calender", "time",
        "factorial", "stopwatch", "stringlength", "primecheck", "hangman",
        "beepsound"
    };
    int ramUse[] = {10, 30, 40, 2, 2, 30, 6, 3, 10, 30, 11, 11, 11, 20, 15, 1};
    int priorities[] = {1, 2, 4, 3, 3, 6, 8, 7, 9, 10, 11, 15, 12, 9, 19, 1};

    for (int i = 0; i < taskCount; i++) {
        tasks[i].id = i + 1;
        strcpy(tasks[i].name, names[i]);
        tasks[i].ramUse = ramUse[i];
        tasks[i].priority = priorities[i];
        tasks[i].running = 0;
        tasks[i].minimized = 0;
    }
}

void *launchTask(void *arg) {
    int index = *(int *)arg;
    free(arg);

    sem_wait(&sem);
    printf("\nLaunching task: %s [PID simulated]\n", tasks[index].name);
    sem_post(&sem);

    if (strcmp(tasks[index].name, "beepsound") == 0) {
        for (int i = 0; i < 5; i++) {
            printf("🎵 Beep %d 🎵\n", i + 1);
            fflush(stdout);
            printf("\a"); // ANSI terminal beep
            sleep(1);     // Simulate sound length
        }
    } else {
        char command[200];
        snprintf(command, sizeof(command), "xterm -hold -e './%s'", tasks[index].name);
        system(command);
    }

    sem_wait(&sem);
    tasks[index].running = 0;
    tasks[index].minimized = 0;
    ramAvailable += tasks[index].ramUse;
    sem_post(&sem);

    return NULL;
}

void runScheduler() {
    int idx;
    while ((idx = dequeue(fgQueue, &fgFront, fgRear)) != -1 || (idx = dequeue(bgQueue, &bgFront, bgRear)) != -1) {
        if (ramAvailable < tasks[idx].ramUse) {
            printf("\n  Not enough RAM to run %s. Skipping.\n", tasks[idx].name);
            continue;
        }
        ramAvailable -= tasks[idx].ramUse;
        tasks[idx].running = 1;
        int *arg = malloc(sizeof(int));
        *arg = idx;
        pthread_create(&threads[idx], NULL, launchTask, arg);
        pthread_detach(threads[idx]);
    }
}

void showTaskStatus() {
    printf("\n--- Running Tasks ---\n");
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].running) {
            printf("%d. %s [%s]\n", i + 1, tasks[i].name, tasks[i].minimized ? "Minimized" : "Active");
        }
    }
    printf("---------------------\n");
}

void showMenu() {
    printf("\nAvailable Tasks:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s (RAM: %dMB, Priority: %d)\n", i + 1, tasks[i].name, tasks[i].ramUse, tasks[i].priority);
    }
    printf("S. Show Running Tasks\n");
    printf("M. Switch to %s Mode\n", isKernelMode ? "User" : "Kernel");
    printf("I. Interrupt Task\n");
    printf("R. Run Scheduler\n");
    printf("Q. Quit\n");
}

void interruptTask() {
    if (!isKernelMode) {
        printf("\n  Only Kernel Mode can interrupt tasks.\n");
        return;
    }
    showTaskStatus();
    printf("Enter task number to minimize/close: ");
    int choice;
    scanf("%d", &choice);
    int idx = choice - 1;
    if (idx >= 0 && idx < taskCount && tasks[idx].running) {
        printf("1. Minimize\n2. Close\nEnter choice: ");
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            tasks[idx].minimized = 1;
            printf("%s minimized.\n", tasks[idx].name);
        } else if (opt == 2) {
            tasks[idx].running = 0;
            tasks[idx].minimized = 0;
            ramAvailable += tasks[idx].ramUse;
            printf("%s closed. RAM reclaimed.\n", tasks[idx].name);
        }
    } else {
        printf("Invalid task or task not running.\n");
    }
}

void startInterface() {
    char input[10];
    while (1) {
        showMenu();
        printf("\nEnter option: ");
        scanf("%s", input);

        if (input[0] == 'Q' || input[0] == 'q') {
            shutdownScreen();
            break;
        } else if (input[0] == 'M' || input[0] == 'm') {
            isKernelMode = !isKernelMode;
            printf("Switched to %s Mode\n", isKernelMode ? "Kernel" : "User");
        } else if (input[0] == 'R' || input[0] == 'r') {
            runScheduler();
        } else if (input[0] == 'I' || input[0] == 'i') {
            interruptTask();
        } else if (input[0] == 'S' || input[0] == 's') {
            showTaskStatus();
        } else {
            int choice = atoi(input);
            if (choice >= 1 && choice <= taskCount) {
                int idx = choice - 1;
                if (tasks[idx].priority >= 10)
                    enqueue(fgQueue, &fgRear, idx);
                else
                    enqueue(bgQueue, &bgRear, idx);
                printf("%s added to queue.\n", tasks[idx].name);
            } else {
                printf("Invalid choice.\n");
            }
}
}
}
int main() {
printf("Enter RAM (MB): ");
scanf("%d", &RAM);
printf("Enter Disk (MB): ");
scanf("%d", &DISK);
printf("Enter CPU Cores (1-8): ");
scanf("%d", &CORES);
bootScreen();
initSharedMemory();
initTasks();
sem_init(&sem, 0, 1);
enqueue(fgQueue, &fgRear, 8);  // Calendar
enqueue(fgQueue, &fgRear, 9);  // Time
enqueue(bgQueue, &bgRear, 15); // BeepSound background process
runScheduler();
startInterface();
sem_destroy(&sem);
shmdt(shared_memory);
return 0;
}
