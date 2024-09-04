#ifndef _ENCAP_PNG_

#define _ENCAP_PNG_

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "linked_list.h"

void read_png_file(char *filename);

void write_png_file(char *filename);

//void process_png_file(c_linkedl *messageBits);

char convertBitsToChar(c_linkedl *bitsMessage);

void process_png_file_show_message(void);

void process_png_file_hide_message(c_linkedl *messageBits);

void hide_message(char *inFilename, char* outFilename, char *message);

void show_mensagem(char *filename);

#endif