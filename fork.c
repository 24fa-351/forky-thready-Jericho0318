#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void pattern1(int num) {
    int status = 0;                 
    for (int ix = 0; ix < num; ix++) {
        pid_t pid = fork();
        sleep(rand() % 9);
        if (pid < 0) {
            perror("Fork Failed!!");
            exit(1);
        } else if (pid == 0) {
            printf("   Parent: created child %d (%d)\n\n", ix, getpid());
            wait(NULL);
            printf("   Process %d (%d) beginning\n", ix, getpid());
            exit(0); 
        } 
    }
    
    for (int ix = 0; ix < num; ix++) {
        wait(NULL);
        printf("   Process %d exiting\n", ix);
    }
}

void pattern2(int num) {
    for (int ix = 0; ix < num; ix++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork Failed!!");
            exit(1);
        } else if (pid == 0) {
            printf("   Child %d (%d) beginning\n", ix, getpid()); 
            sleep(rand() % 9);
        } else {
            wait(NULL);
            printf("   Child %d exiting\n\n", ix);
            exit(0);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Please provide 3 arguments: ./<filename>, num, pattern 1 or 2\n");
        exit(1);
    }

    int num_of_things = atoi(argv[1]);
    if (num_of_things <= 1 || num_of_things >= 256) {
        perror("Please provide a number between 2 and 255\n");
        exit(1);
    }

    int pattern =  atoi(argv[2]);
    if (pattern != 1 && pattern != 2) {
        perror("Please choose a pattern between 1 and 2\n");
        exit(1);
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
