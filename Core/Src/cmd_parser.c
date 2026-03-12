#include "cmd_parser.h"
#include <string.h>
#include <stdio.h>
// #include "hal_usb.h" // Assume it has some tx/rx functions

#define CMD_BUFFER_SIZE 64
static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t cmd_index = 0;

void cmd_parser_init(void) {
    memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
    cmd_index = 0;
}

static void execute_command(char *cmd) {
    if (strncmp(cmd, "M", 1) == 0) {
        printf("Motor command received: %s\r\n", cmd);
        // Future integration: motor_set_speed(...)
    } else {
        printf("Unknown command: %s\r\n", cmd);
    }
}

void cmd_parser_process_char(uint8_t c) {
    if (c == '\r' || c == '\n') {
        if (cmd_index > 0) {
            cmd_buffer[cmd_index] = '\0';
            execute_command((char *)cmd_buffer);
            cmd_index = 0;
        }
    } else if (cmd_index < CMD_BUFFER_SIZE - 1) {
        cmd_buffer[cmd_index++] = c;
        // Echo back
        // hal_usb_transmit(&c, 1);
    }
}
