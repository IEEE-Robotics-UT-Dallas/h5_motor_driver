#ifndef __CMD_PARSER_H
#define __CMD_PARSER_H

#include <stdint.h>

void cmd_parser_init(void);
void cmd_parser_process_char(uint8_t c);

#endif
