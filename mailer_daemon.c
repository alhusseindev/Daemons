#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>


static void mailer_daemon(){
    pid_t process_id;

    process_id = fork();

    if(process_id < 0){
        exit(EXIT_FAILURE);
    }

    if(process_id > 0){
        exit(EXIT_SUCCESS);
    }

    if(setsid() < 0){
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD , SIG_IGN);
    signal(SIGHUP, SIG_IGN)

    //double fork convention (fork again)
    process_id = fork();

    if(process_id < 0){
        exit(EXIT_FAILURE);
    }

    if(process_id > 0){
        exit(EXIT_SUCCESS);
    }

    unmask(0);

    chdir('/');

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /** alternative to the closing statements
        int x;
        for(x = sysconf(_SC_OPEN_MAX); x >= 0; --x){
            close(x)
        }
    */

    openlog("mailer_daemon", LOG_NOTICE, LOG_DAEMON);
    int my_command;
    while(1){
        syslog(LOG_NOTICE, "Daemon Started!");
        //run our mailer.py program
        my_command = system("./mailer.py");  //returns an exit status;
        sleep(20);
        break;  //end the daemon
    }

    syslog(LOG_NOTICE, "Daemon Terminated!");
    closelog();

}





int main(int argc, char **argv){

    time_t my_time = time();
    time_t my_time_b = time();
    double difference_in_time = difftime(my_time, my_time_b);

    //alternative clock_t myclock = clock();, then clock_t diffclock = my_clockb - my_clock;
    clock_t my_clock = clock();
    printf("Clock: %f", (double) my_clock);
    printf("Start Time: %f", (double) my_time);
    printf("End Time: %f", (double) my_time_b);
    printf("Difference in Time: %f", (double) difference_in_time);

    //let's call the mailer daemon
    mailer_daemon();
    return 0;
}