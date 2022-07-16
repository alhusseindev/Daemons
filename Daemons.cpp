#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

//Creating a process id and session id
pid_t process_id, sid;

//We clone the current process using fork()
//if we follow it with an exec() call, then this creates a new process
process_id = fork();

//on failure
if(process_id < 0){
    exit(EXIT_FAILURE);
}

//on success
if(process_id > 0){
    exit(EXIT_SUCCESS);
}

//changing the file mode to unmask
unmask(0);


//we should open logs for writing

//create a unique session id
sid = setsid();

if(sid < 0){
    exit(EXIT_FAILURE);
}

//change the current working directory
if((chdir('/') < 0)){
    exit(EXIT_FAILURE);
}

//closing standard file descriptors
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

//writing the actual daemon
while(1){
    //do some stuff
    sleep(30);  // sleep for 30 seconds
}

exit(EXIT_SUCCESS);