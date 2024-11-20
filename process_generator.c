#include "headers.h"
#include "Queue.h"


void clearResources(int);

void readfile();

int getAlgorithmChoice();

int main(int argc, char * argv[])
{
    signal(SIGINT, clearResources);
    
    // TODO Initialization
    // 1. Read the input files.
    readfile();
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
    getAlgorithmChoice();   
    // 3. Initiate and create the scheduler and clock processes.
    int algorithmChoice = getAlgorithmChoice();
    switch (algorithmChoice) {
        case 1:
            // Do something for SJF, perhaps set a flag or write this choice to output file.
            printf("Shortest Job First selected.\n");
            break;
        case 2:
            // Do something for Round Robin.  Ask for time quantum if needed
            printf("Round Robin selected.\n");
            break;
        case 3:
            // Do something for Priority
            printf("Priority selected.\n");
            break;
    }
    // 4. Use this function after creating the clock process to initialize clock
    initClk();
    // To get time use this
    int x = getClk();
    printf("current time is %d\n", x);
    // TODO Generation Main Loop
    // 5. Create a data structure for processes and provide it with its parameters.
    // 6. Send the information to the scheduler at the appropriate time.
    // 7. Clear clock resources
    destroyClk(true);
}

void clearResources(int signum)
{
    //TODO Clears all resources in case of interruption
}





void readfile() {
    FILE *file = fopen("processes.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return; //Error Handling.  Don't return a value from void function.
    }

    char line[100];
    struct processData process;
    Queue *q = createQueue(); // Create the queue


    //Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%d %d %d %d", &process.id, &process.arrivaltime, &process.runningtime, &process.priority) == 4) {
            enqueue(q, process); // Add to the queue
        } else {
            fprintf(stderr, "Error parsing line: %s\n", line);
        }
    }

    fclose(file);

    //Now process the queue:
    struct processData p;
    while((p = dequeue(q)).id != -1){ //Dequeue until the queue is empty
        printf("Process ID: %d, Arrival Time: %d, Running Time: %d, Priority: %d\n",
               p.id, p.arrivaltime, p.runningtime, p.priority);
    }
    free(q); //Free the queue memory
}


int getAlgorithmChoice() {
    int choice;
    do {
        printf("\nSelect scheduling algorithm:\n");
        printf("1. Shortest Job First (SJF)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Priority\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            //Clear the input buffer to prevent infinite loop
            while (getchar() != '\n'); 
        } else if (choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
    } while (choice < 1 || choice > 3);
    return choice;
}