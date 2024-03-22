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

bool is_outside(int x, int y, int height, int width) {
  return x < 0 || x > width || y < 0 || y > height;
}

// Rotates image from a given angle, and writes it to the new image buffer.
// # Arguments
// * o_image - pointer to the original image.
// * height - height of the image.
// * width - width of the image.
// * channels - channels of the image.
// * new_image - pointer to the new allocated image.
// * rotate_angle - Rotation angle in degrees.
void rotate_image(unsigned char *o_image, int height, int width, int channels,
                  unsigned char *new_image, double rotation_angle) {
  // loop through all the pixels of new image buffer.
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      // convert y, x to co ordinate space.
      int y_coord = y - height / 2;
      int x_coord = x - width / 2;

      // rotate y, x using trig functions.
      int y2 =
          -sin(rotation_angle) * (x_coord) + cos(rotation_angle) * (y_coord);
      int x2 =
          cos(rotation_angle) * (x_coord) + sin(rotation_angle) * (y_coord);

      // convert co ordinate space y, x back to index space.
      y2 = y2 + height / 2;
      x2 = x2 + width / 2;

      bool is_this_outside = is_outside(x2, y2, height, width);

      // hard limiting x.
      if (x2 < 0) {
        x2 = 0;
      } else if (x2 >= width) {
        x2 = width - 1;
      }

      // hard limiting y.
      if (y2 < 0) {
        y2 = 0;
      } else if (y2 >= height) {
        y2 = height - 1;
      }

      LOG("original y, x: %d, %d\n", y, x);
      LOG("coord    y, x: %d, %d\n", y_coord, x_coord);
      LOG("rotated  y, x: %d, %d\n\n", y2, x2);

      // map linear position of the current pixel in the original image.
      unsigned char *color = o_image + (channels * (y2 * height + x2));

      // map linear positon of the current pixel in new image.
      unsigned char *pixel = new_image + (channels * (y * height + x));

      // looping through the entire pixel and copying
      // channels from original image to new image.
      for (int i = 0; i < channels; i++, pixel++, color++) {
        if (is_this_outside) {
          *pixel = 0;
        } else {
          *pixel = *color;
        }
      }
    }
  }
}

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
