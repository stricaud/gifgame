#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <gif_lib.h>

#include "palette.h"

#define MAX_COLOR_COUNT 256
#define EXP_COLORS 8
#define IMG_WIDTH 500
#define IMG_HEIGHT 500

int main(void)
{
  ColorMapObject *gif_cmap = NULL;
  GifColorType *gif_color = NULL;
  GifFileType *gif_file = NULL; 
  GifPixelType *pixels_line = malloc(sizeof(GifPixelType) * IMG_WIDTH);
  
  int error;


  gif_cmap = GifMakeMapObject(MAX_COLOR_COUNT, NULL);
  if (!gif_cmap) {
    fprintf(stderr, "Error allocating color map\n");
  }

  for (int i = 0; i < COLOR_COUNT; i++) {
    gif_cmap->Colors[i].Red = (unsigned char)palette[i][0];
    gif_cmap->Colors[i].Green = (unsigned char)palette[i][1];
    gif_cmap->Colors[i].Blue = (unsigned char)palette[i][2];
  }

  gif_file = EGifOpenFileName("out.gif", 0, &error);
  if (!gif_file) {
    fprintf(stderr, "Error creating gif file\n");
  }
  EGifSetGifVersion(gif_file, 1);
  error = EGifPutScreenDesc(gif_file, IMG_WIDTH, IMG_HEIGHT, EXP_COLORS, 0, gif_cmap);
  error = EGifPutImageDesc(gif_file, 0, 0, IMG_WIDTH, IMG_HEIGHT, 0, NULL);
    
  for (int row=0; row < IMG_HEIGHT; row++) {
    for (int i = 0; i < IMG_WIDTH; i++) {
      unsigned char pixel = (rand() % (COLOR_COUNT));
      pixels_line[i] = pixel;
    }
    error = EGifPutLine(gif_file, (GifPixelType*)pixels_line, IMG_WIDTH);
    if (error == GIF_ERROR) {
      fprintf(stderr, "Error puting line\n");
    }
  }
  
  EGifSpew(gif_file);
                       
  EGifCloseFile(gif_file, &error);
  GifFreeMapObject(gif_cmap);
  free(pixels_line);
  
  return 0;
}
