#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dir.h"
#include <dlfcn.h>





int main(){
    void *handle1;
    void *handle2;
        char*(*player_name1)(void);
        char*(*player_name2)(void);

        char *error;
        handle2 = dlopen ("libplayer2.so", RTLD_LAZY);
        handle1 = dlopen("libplayer1.so",RTLD_LAZY);
        if (!handle2 || !handle1  ) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        player_name1 = dlsym(handle1,"get_player_name");
        player_name2 = dlsym(handle2,"get_player_name");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        printf ("%s\n",player_name2());

        printf ("%s\n",player_name1());
        dlclose(handle1);
        dlclose(handle2);
    
    return 0;
}














