/*
 * A simple libpng example program
 * http://zarb.org/~gc/html/libpng.html
 *
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 * 
 * Modified by Luiz Catulio to allow messages to be hidden inside png files 
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

#include "encap_png.h"

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers = NULL;

void read_png_file(char *filename) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  if (row_pointers) abort();

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, row_pointers);

  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);

  png_destroy_read_struct(&png, &info, NULL);
  png=NULL;
  info=NULL;

}

void write_png_file(char *filename) {

  FILE *fp = fopen(filename, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
    png,
    info,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  if (!row_pointers) abort();

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);

  fclose(fp);

  png_destroy_write_struct(&png, &info);

  if (png && info)
        png_destroy_write_struct(&png, &info);
}

void process_png_file_hide_message(c_linkedl *messageBits) {

  char write1 = 1;
  char write0 = 255 - 1;

  for(int y = 0; y < height && messageBits->tamanho; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width && messageBits->tamanho; x++) {
      png_bytep px = &(row[x * 4]);

      for(int z = 0; z < 4 && messageBits->tamanho; z++){
        
        if(messageBits->inicio->informacoes.valor == 1){
            px[z] = px[z] | write1;
        }else{
            px[z] = px[z] & write0; 
        }

        del_c_list_element(messageBits, messageBits->inicio, 1);

      }
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
    }
  }
}

char convertBitsToChar(c_linkedl *bitsMessage){
  int convert[8] = {128, 64, 32, 16, 8, 4, 2, 1};
  char caracter = 0;

  for(int i1 = 0; i1 <= 7 && bitsMessage->tamanho; i1++){
    if(bitsMessage->inicio->informacoes.valor){
      caracter += convert[i1];
    }
    del_c_list_element(bitsMessage, bitsMessage->inicio, 1);
  }

  return caracter;
}

void process_png_file_show_message(void) {

  char end = 1;
  c_linkedl messageBits = create_c_list();
  c_linkedl* listAdress = &messageBits;

  for(int y = 0; y < height && end; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width && end; x++) {
      png_bytep px = &(row[x * 4]);
      for(int z = 0; z < 4 && end; z++){
        
        insert_c_list(listAdress, create_node(1 & px[z]));
        if(listAdress->tamanho == 8){
          char caracter = convertBitsToChar(listAdress);
          printf("%c", caracter);
          if(caracter == '\0'){
            end = 0;
          }
        }

      }
    }
  }

  putchar('\n');
  kill_c_list(listAdress);

}

void hide_message(char *inFilename, char* outFilename, char *inText){

    FILE *info = fopen(inText, "r");
    if(info == NULL) abort();
    fseek(info, 0, SEEK_END);
    long long sizeMessage = ftell(info);
    fseek(info, 0, SEEK_SET);
    char *message = (char*) malloc(sizeMessage + 1);
    if(message == NULL) abort();
    fread(message, 1, sizeMessage, info);
    message[sizeMessage] = '\0';

    c_linkedl messageBits = create_c_list(); 
    c_linkedl* listAdress = &messageBits;
    read_png_file(inFilename);

    if(sizeMessage > height * width) abort();

    for(int i1 = 0; i1 < sizeMessage + 1; i1++){
        for(int i2 = 7, pos = 128; i2 >= 0; i2--, pos >>= 1){
            insert_c_list(listAdress, create_node(1 && (pos & message[i1])));
        }
    }

    process_png_file_hide_message(listAdress);
    write_png_file(outFilename);

    kill_c_list(listAdress);
    fclose(info);
    free(message);
}

void show_mensagem(char *filename){
  read_png_file(filename);
  process_png_file_show_message();
}