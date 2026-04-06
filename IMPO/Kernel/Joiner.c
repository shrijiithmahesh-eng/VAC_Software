#include "IMPO/GUI/Login.asm"
#include "IMPO/ssh/connect.c"
#include  "IMPO/ssh/time_patch.c"
// Declare external functions from other files
extern void connect_init();    // from connect.c
extern void patch_time();      // from time_patch.c
extern void login_asm_start(); // from Login.asm

void loader() {
    // These functions represent the "loading" of your logic
    connect_init(); 
    patch_time();
    login_asm_start();
}
