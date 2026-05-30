
#include <stdio.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

static int board_scratch_board_init(void){
    printf("Board Initialized");
    return 0;
}

SYS_INIT(board_scratch_board_init, APPLICATION, 1);
