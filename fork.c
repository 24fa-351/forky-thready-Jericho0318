#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void pattern1(int num) {
    int status = 0;                 
    for (int i = 0; i < num; i++) {
        pid_t pid = fork();
        sleep(1);
        if (pid < 0) {
            perror("Fork Failed!!");
            exit(1);
        } else if (pid == 0) {
            printf("   Parent: created child %d (%d)\n\n", i, getpid());
            wait(NULL);
            printf("   Process %d (%d) beginning\n", i, getpid());
            exit(0); 
        } 
    }
    
    for (int i = 0; i < num; i++) {
        wait(NULL);
        printf("   Process %d exiting\n", i);
    }
}

void pattern2(int num) {
    for (int i = 0; i < num; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork Failed!!");
            exit(1);
        } else if (pid == 0) {
            printf("   Child %d (%d) beginning\n", i, getpid()); 
            sleep(1);
        } else {
            wait(NULL);
            printf("   Child %d exiting\n\n", i);
            exit(0);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Please provide 3 arguments\n");
        exit(0);
    }

    int num_of_things = atoi(argv[1]);
    if (num_of_things <= 1 || num_of_things >= 256) {
        perror("Please provide a number between 2 and 255\n");
        exit(0);
    }

    int pattern =  atoi(argv[2]);
    if (pattern  != 1 && pattern != 2) {
        perror("Please choose a pattern between 1 and 2\n");
        exit(0);
    }

    if (pattern == 1) {
        printf("Pattern 1:\n");
        pattern1(num_of_things);
    } else if (pattern == 2) {
        printf("Pattern 2:\n");
        pattern2(num_of_things);
    }
    return 0;
}