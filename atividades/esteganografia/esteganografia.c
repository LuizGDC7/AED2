/*
 * A simple libpng example program
 * http://zarb.org/~gc/html/libpng.html
 *
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 *
 * To build, use the next instruction on OS X.
 * $ brew install libpng
 * $ clang -lz -lpng16 libpng_test.c
 *
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

/*

4 de tamanho?

nome_arquivo hide entrada saida mensagem
nome_arquivo show entrada

hide ou show -> hide exige nome de entrada e de saida
show -> exige apenas nome de entrada

*/


#include "encap_png.h"

int main(int argc, char *argv[]) {


  printf("DEBUG\n");
  for(int i1 = 0; i1 < argc; i1++){
    printf("%s\n", argv[i1]);
  }

  if(!strcmp(argv[1], "hide")){
    if(argc != 5) abort();
    hide_message(argv[2], argv[3], argv[4]);
  }else if(!strcmp(argv[1], "show")){
    if(argc != 3) abort();
    show_mensagem(argv[2]);
  }else{
    abort();
  }

  return 0;
}

/*

pngin, pngout, mensagem

*/