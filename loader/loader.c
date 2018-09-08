#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    void *handle;
    if (2 != argc){
       printf("usage: %s path_to_my_lib.so\n", argv[0]);
    }

    handle = dlopen (argv[1], RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    dlclose(handle);
    return 0;
}
