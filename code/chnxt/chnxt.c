#include <nxt.h>
#include <dlfcn.h>

ChNXT::ChNXT() {
    void *fptr;

    /* here to load the dynamically loaded library if necessary.
     * g_chnxt_dlhandle is a globle pointer pointing to the loaded DLL
     * g_chnxt_dlcount is a global int counting instances for all classess */

    if(g_chnxt_dlhandle == NULL || g_chnxt_dlcount == 0){
	g_chnxt_dlhandle = dlopen("libnxt.dl", RTLD_LAZY);
	if(g_chnxt_dlhandle == NULL){
	    printf("Error: dlopen(): %s\n", dlerror());
	}
    }

    /* to get the address by function name */
    fptr = dlsym(g_chnxt_dlhandle, "ChNXT_ChNXT_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
    }

    /* to call the chdl function in dynamically loaded library by address */
    dlrunfun(fptr, NULL, NULL);
    g_chnxt_dlcount++;
}

ChNXT::~ChNXT() {
    void *fptr;

    fptr = dlsym(g_chnxt_dlhandle, "ChNXT_dChNXT_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
    }

    /* call the chdl function in DLL by address */
    dlrunfun(fptr, NULL, NULL, this);
    if(g_chnxt_dlcount <= 0 && g_chnxt_dlhandle != NULL){
	if(dlclose(g_chnxt_dlhandle) != 0)
	    printf("Error: dlclose(): %s\n", dlerror());
    }
}
int ChNXT::connect() {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "connect_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, NULL, this, connect);
    return retval;
}

int ChNXT::connectWithAddress(char *usr_addr, int channel) {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "connectWithAddress_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, connectWithAddress, this, usr_addr, channel);
    return retval;
}

int ChNXT::disconnect() {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "disconnect_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, NULL, this, disconnect);
    return retval;
}

int ChNXT::getJointAngle(nxtJointId_t id, int *angle) {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "getJointAngle_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, getJointAngle, this, id, angle);
    return retval;
}

int ChNXT::getJointSpeedRatio(nxtJointId_t id, double *ratio) {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "getJointSpeedRatio_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, getJointSpeedRatio, this, id, ratio);
    return retval;
}

int getJointSpeedRatios(double *ratio1, double *ratio2, double *ratio3) {
    void *fptr;
    int retval;

    fptr = dlsym(g_chnxt_dlhandle, "getJointSpeedRatios_chdl");
    if(fptr == NULL) {
        fprintf(_stderr, "Error: %s(): dlsym(): %s\n", __func__,  dlerror());
        return -1;
    }
    dlrunfun(fptr, &retval, getJointSpeedRatios, ratio1, ratio2, ratio3);
    return retval;
}
