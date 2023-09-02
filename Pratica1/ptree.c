#include<stdio.h>
#include <unistd.h>

int main() {

    int pid_p2 = fork();

    if(pid_p2 == 0){
        int pid_p4 = fork();

        if(pid_p4 != 0){
            int pid_p5 = fork();
        }
    } else {
        int pid_p3 = fork();
    }

    getchar();

    return 0;
}