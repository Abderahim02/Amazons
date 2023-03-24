#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dir.h"
#include <dlfcn.h>





int main(){
    void *handle;
        char*(*player_name)(void);
        char *error;
        handle = dlopen ("libplayer2.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }

        player_name = dlsym(handle,"get_player_name");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        printf ("%s\n",player_name());
        dlclose(handle);
    
    return 0;
}














