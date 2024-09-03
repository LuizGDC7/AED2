#ifndef _ENCAP_PNG_

#define _ENCAP_PNG_

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "linked_list.h"

void read_png_file(char *filename);

void write_png_file(char *filename);

void process_png_file();

void hide_message(char *filename, char *message);

void decifrar_mensagem(char *filename);

#endif