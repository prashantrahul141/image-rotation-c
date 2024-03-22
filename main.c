#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

#ifdef DEBUG
#define LOG(fmt, args...)                                                      \
  fprintf(stderr, "%s:%d: " fmt, __FILE__, __LINE__, ##args)
#else
#define LOG(fmt, args...)
#endif

#define USAGE "Usage:\n\tmain [rotation angle in degrees] [file path]\n"


// entry point
int main(int argc, char *argv[]) {
  // if argc is not 3
  if (argc != 3) {
    fprintf(stderr, USAGE);
    return 0;
  }


  return 0;
}
