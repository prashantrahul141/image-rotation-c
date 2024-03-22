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

  // rotationn angle to apply.
  float rotation_angle = atof(argv[1]);
  if (rotation_angle == 0.0f) {
    fprintf(stderr,
            "Invalid rotation angle, the angle should be in degrees: %s\n%s",
            argv[1], USAGE);
    return 1;
  }

  // convert degrees to radians for internal usage.
  rotation_angle = rotation_angle / 57.32;

  // filepath
  char *filepath = argv[2];
  printf("[INFO] : Loading image : %s\n", filepath);

  // width, height, channels of original image.
  int image_width, image_height, image_channels;

  // load image.
  unsigned char *o_image =
      stbi_load(filepath, &image_width, &image_height, &image_channels, 0);

  // incase image loading fails.
  if (o_image == NULL) {
    fprintf(stderr, "[ERROR] : Failed to load image : %s\n", filepath);
    return 1;
  }

  printf("[INFO] : Loaded image data\n");

  printf("[INFO] : Image width : %d, image height : %d\n", image_width,
         image_height);

  // allocate memory for new image.
  unsigned char *new_image = (unsigned char *)calloc(
      sizeof(unsigned char) * image_width * image_height * image_channels, 1);

  rotate_image(o_image, image_height, image_width, image_channels, new_image,
               rotation_angle);

  // writing new image.
  int result = stbi_write_jpg("output.jpg", image_width, image_height,
                              image_channels, new_image, 100);

  if (result == 0) {
    fprintf(stderr, "[ERROR] : Failed to write new image.\n");
  } else {
    printf("[INFO] : Wrote new image: output.jpg\n");
  }

  // freeing image.
  stbi_image_free(o_image);
  free(new_image);

  return 0;
}
