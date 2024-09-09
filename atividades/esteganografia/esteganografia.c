
/**
 * Program designed by Luiz Catulio to hide messages inside png images
 */

#include "encap_png.h"

int main(int argc, char *argv[]) {

/*

  printf("DEBUG\n");
  for(int i1 = 0; i1 < argc; i1++){
    printf("%s\n", argv[i1]);
  }
*/

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
