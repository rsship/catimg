#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

int rgb256[][3] = {
    {0, 0, 0},       {128, 0, 0},     {0, 28, 0},      {128, 128, 0},
    {0, 0, 128},     {128, 0, 128},   {0, 128, 128},   {192, 192, 192},
    {128, 128, 128}, {255, 0, 0},     {0, 255, 0},     {255, 255, 0},
    {0, 0, 255},     {255, 0, 255},   {0, 255, 255},   {255, 255, 255},
    {0, 0, 0},       {0, 0, 95},      {0, 0, 135},     {0, 0, 175},
    {0, 0, 215},     {0, 0, 255},     {0, 95, 0},      {0, 95, 95},
    {0, 95, 135},    {0, 95, 175},    {0, 95, 215},    {0, 95, 255},
    {0, 135, 0},     {0, 135, 95},    {0, 135, 135},   {0, 135, 175},
    {0, 135, 215},   {0, 135, 255},   {0, 175, 0},     {0, 175, 95},
    {0, 175, 135},   {0, 175, 175},   {0, 175, 215},   {0, 175, 255},
    {0, 215, 0},     {0, 215, 95},    {0, 215, 135},   {0, 215, 175},
    {0, 215, 215},   {0, 215, 255},   {0, 255, 0},     {0, 255, 95},
    {0, 255, 135},   {0, 255, 175},   {0, 255, 215},   {0, 255, 255},
    {95, 0, 0},      {95, 0, 95},     {95, 0, 135},    {95, 0, 175},
    {95, 0, 215},    {95, 0, 255},    {95, 95, 0},     {95, 95, 95},
    {95, 95, 135},   {95, 95, 175},   {95, 95, 215},   {95, 95, 255},
    {95, 135, 0},    {95, 135, 95},   {95, 135, 135},  {95, 135, 175},
    {95, 135, 215},  {95, 135, 255},  {95, 175, 0},    {95, 175, 95},
    {95, 175, 135},  {95, 175, 175},  {95, 175, 215},  {95, 175, 255},
    {95, 215, 0},    {95, 215, 95},   {95, 215, 135},  {95, 215, 175},
    {95, 215, 215},  {95, 215, 255},  {95, 255, 0},    {95, 255, 95},
    {95, 255, 135},  {95, 255, 175},  {95, 255, 215},  {95, 255, 255},
    {135, 0, 0},     {135, 0, 95},    {135, 0, 135},   {135, 0, 175},
    {135, 0, 215},   {135, 0, 255},   {135, 95, 0},    {135, 95, 95},
    {135, 95, 135},  {135, 95, 175},  {135, 95, 215},  {135, 95, 255},
    {135, 135, 0},   {135, 135, 95},  {135, 135, 135}, {135, 135, 175},
    {135, 135, 215}, {135, 135, 255}, {135, 175, 0},   {135, 175, 95},
    {135, 175, 135}, {135, 175, 175}, {135, 175, 215}, {135, 175, 255},
    {135, 215, 0},   {135, 215, 95},  {135, 215, 135}, {135, 215, 175},
    {135, 215, 215}, {135, 215, 255}, {135, 255, 0},   {135, 255, 95},
    {135, 255, 135}, {135, 255, 175}, {135, 255, 215}, {135, 255, 255},
    {175, 0, 0},     {175, 0, 95},    {175, 0, 135},   {175, 0, 175},
    {175, 0, 215},   {175, 0, 255},   {175, 95, 0},    {175, 95, 95},
    {175, 95, 135},  {175, 95, 175},  {175, 95, 215},  {175, 95, 255},
    {175, 135, 0},   {175, 135, 95},  {175, 135, 135}, {175, 135, 175},
    {175, 135, 215}, {175, 135, 255}, {175, 175, 0},   {175, 175, 95},
    {175, 175, 135}, {175, 175, 175}, {175, 175, 215}, {175, 175, 255},
    {175, 215, 0},   {175, 215, 95},  {175, 215, 135}, {175, 215, 175},
    {175, 215, 215}, {175, 215, 255}, {175, 255, 0},   {175, 255, 95},
    {175, 255, 135}, {175, 255, 175}, {175, 255, 215}, {175, 255, 255},
    {215, 0, 0},     {215, 0, 95},    {215, 0, 135},   {215, 0, 175},
    {215, 0, 215},   {215, 0, 255},   {215, 95, 0},    {215, 95, 95},
    {215, 95, 135},  {215, 95, 175},  {215, 95, 215},  {215, 95, 255},
    {215, 135, 0},   {215, 135, 95},  {215, 135, 135}, {215, 135, 175},
    {215, 135, 215}, {215, 135, 255}, {215, 175, 0},   {215, 175, 95},
    {215, 175, 135}, {215, 175, 175}, {215, 175, 215}, {215, 175, 255},
    {215, 215, 0},   {215, 215, 95},  {215, 215, 135}, {215, 215, 175},
    {215, 215, 215}, {215, 215, 255}, {215, 255, 0},   {215, 255, 95},
    {215, 255, 135}, {215, 255, 175}, {215, 255, 215}, {215, 255, 255},
    {255, 0, 0},     {255, 0, 95},    {255, 0, 135},   {255, 0, 175},
    {255, 0, 215},   {255, 0, 255},   {255, 95, 0},    {255, 95, 95},
    {255, 95, 135},  {255, 95, 175},  {255, 95, 215},  {255, 95, 255},
    {255, 135, 0},   {255, 135, 95},  {255, 135, 135}, {255, 135, 175},
    {255, 135, 215}, {255, 135, 255}, {255, 175, 0},   {255, 175, 95},
    {255, 175, 135}, {255, 175, 175}, {255, 175, 215}, {255, 175, 255},
    {255, 215, 0},   {255, 215, 95},  {255, 215, 135}, {255, 215, 175},
    {255, 215, 215}, {255, 215, 255}, {255, 255, 0},   {255, 255, 95},
    {255, 255, 135}, {255, 255, 175}, {255, 255, 215}, {255, 255, 255},
    {8, 8, 8},       {18, 18, 18},    {28, 28, 28},    {38, 38, 38},
    {48, 48, 48},    {58, 58, 58},    {68, 68, 68},    {78, 78, 78},
    {88, 88, 88},    {98, 98, 98},    {108, 108, 108}, {118, 118, 118},
    {128, 128, 128}, {138, 138, 138}, {148, 148, 148}, {158, 158, 158},
    {168, 168, 168}, {178, 178, 178}, {188, 188, 188}, {198, 198, 198},
    {208, 208, 208}, {218, 218, 218}, {228, 228, 228}, {238, 238, 238},
};

int hsl256[][3] = {
    {0, 0, 0},      {0, 100, 25},   {120, 100, 25}, {60, 100, 25},
    {240, 100, 25}, {300, 100, 25}, {180, 100, 25}, {0, 0, 75},
    {0, 0, 50},     {0, 100, 50},   {120, 100, 50}, {60, 100, 50},
    {240, 100, 50}, {300, 100, 50}, {180, 100, 50}, {0, 0, 100},
    {0, 0, 0},      {240, 99, 18},  {240, 100, 26}, {240, 100, 34},
    {240, 100, 42}, {240, 100, 50}, {120, 99, 18},  {180, 99, 18},
    {205, 99, 18},  {230, 99, 18},  {255, 99, 18},  {281, 99, 18},
    {120, 100, 26}, {162, 100, 26}, {180, 100, 26}, {197, 100, 26},
    {215, 100, 26}, {233, 100, 26}, {120, 100, 34}, {152, 100, 34},
    {166, 100, 34}, {180, 100, 34}, {193, 100, 34}, {207, 100, 34},
    {120, 100, 42}, {146, 100, 42}, {157, 100, 42}, {168, 100, 42},
    {180, 100, 42}, {191, 100, 42}, {120, 100, 50}, {142, 100, 50},
    {151, 100, 50}, {161, 100, 50}, {170, 100, 50}, {180, 100, 50},
    {0, 99, 18},    {300, 99, 18},  {282, 100, 26}, {272, 100, 34},
    {266, 100, 42}, {262, 100, 50}, {60, 99, 18},   {0, 0, 37},
    {240, 17, 45},  {240, 33, 52},  {240, 60, 60},  {240, 100, 68},
    {77, 100, 26},  {120, 17, 45},  {180, 17, 45},  {240, 17, 45},
    {300, 17, 45},  {359, 17, 45},  {87, 100, 34},  {120, 33, 52},
    {150, 33, 52},  {180, 33, 52},  {210, 33, 52},  {240, 33, 52},
    {93, 100, 42},  {120, 60, 60},  {140, 60, 60},  {160, 60, 60},
    {180, 60, 60},  {200, 60, 60},  {97, 100, 50},  {120, 100, 68},
    {135, 100, 68}, {150, 100, 68}, {165, 100, 68}, {180, 100, 68},
    {0, 100, 26},   {317, 100, 26}, {300, 100, 26}, {286, 100, 34},
    {277, 100, 42}, {271, 100, 50}, {142, 17, 45},  {0, 17, 45},
    {300, 17, 45},  {270, 33, 52},  {260, 60, 60},  {255, 100, 68},
    {60, 100, 26},  {60, 17, 45},   {0, 0, 52},     {240, 20, 60},
    {240, 50, 68},  {240, 100, 76}, {73, 100, 34},  {90, 33, 52},
    {120, 20, 60},  {180, 20, 60},  {240, 20, 60},  {300, 20, 60},
    {82, 100, 42},  {100, 60, 60},  {120, 50, 68},  {150, 50, 68},
    {180, 50, 68},  {210, 50, 68},  {88, 100, 50},  {105, 100, 68},
    {120, 100, 76}, {140, 100, 76}, {160, 100, 76}, {180, 100, 76},
    {0, 100, 34},   {327, 100, 34}, {313, 100, 34}, {300, 100, 34},
    {288, 100, 42}, {281, 100, 50}, {71, 33, 52},   {0, 33, 52},
    {330, 33, 52},  {300, 33, 52},  {280, 60, 60},  {270, 100, 68},
    {202, 20, 60},  {60, 20, 60},   {0, 20, 60},    {300, 20, 60},
    {270, 50, 68},  {260, 100, 76}, {60, 100, 34},  {60, 33, 52},
    {60, 20, 60},   {0, 0, 68},     {240, 33, 76},  {240, 100, 84},
    {71, 100, 42},  {80, 60, 60},   {90, 50, 68},   {120, 33, 76},
    {180, 33, 76},  {240, 33, 76},  {78, 100, 50},  {90, 100, 68},
    {100, 100, 76}, {120, 100, 84}, {150, 100, 84}, {180, 100, 84},
    {0, 100, 42},   {333, 100, 42}, {322, 100, 42}, {311, 100, 42},
    {300, 100, 42}, {290, 100, 50}, {47, 60, 60},   {0, 60, 60},
    {340, 60, 60},  {320, 60, 60},  {300, 60, 60},  {285, 100, 68},
    {101, 50, 68},  {30, 50, 68},   {0, 50, 68},    {330, 50, 68},
    {300, 50, 68},  {280, 100, 76}, {262, 33, 76},  {120, 33, 76},
    {60, 33, 76},   {0, 33, 76},    {300, 33, 76},  {270, 100, 84},
    {60, 100, 42},  {60, 60, 60},   {60, 50, 68},   {60, 33, 76},
    {0, 0, 84},     {240, 100, 92}, {69, 100, 50},  {75, 100, 68},
    {80, 100, 76},  {90, 100, 84},  {120, 100, 92}, {180, 100, 92},
    {0, 100, 50},   {337, 100, 50}, {328, 100, 50}, {318, 100, 50},
    {309, 100, 50}, {300, 100, 50}, {35, 100, 68},  {0, 100, 68},
    {345, 100, 68}, {330, 100, 68}, {315, 100, 68}, {300, 100, 68},
    {67, 100, 76},  {20, 100, 76},  {0, 100, 76},   {340, 100, 76},
    {320, 100, 76}, {300, 100, 76}, {131, 100, 84}, {60, 100, 84},
    {30, 100, 84},  {0, 100, 84},   {330, 100, 84}, {300, 100, 84},
    {322, 100, 92}, {180, 100, 92}, {120, 100, 92}, {60, 100, 92},
    {0, 100, 92},   {300, 100, 92}, {60, 100, 50},  {60, 100, 68},
    {60, 100, 76},  {60, 100, 84},  {60, 100, 92},  {0, 0, 100},
    {0, 0, 3},      {0, 0, 7},      {0, 0, 10},     {0, 0, 14},
    {0, 0, 18},     {0, 0, 22},     {0, 0, 26},     {0, 0, 30},
    {0, 0, 34},     {0, 0, 38},     {0, 0, 42},     {0, 0, 46},
    {0, 0, 50},     {0, 0, 54},     {0, 0, 58},     {0, 0, 61},
    {0, 0, 65},     {0, 0, 69},     {0, 0, 73},     {0, 0, 77},
    {0, 0, 81},     {0, 0, 85},     {0, 0, 89},     {0, 0, 93},

};

int distance_hsl(int index, int h, int s, int l) {
  // NOTE: find hsl eucladian distance by h, s, l
  int dh = h - hsl256[index][0];
  int ds = s - hsl256[index][1];
  int dl = l - hsl256[index][2];
  return dh * dh + ds * ds + dl * dl;
}

int find_ansi_by_hsl(int h, int s, int l) {

  int index = 0;
  for (int i = 0; i < 256; ++i) {
    if (distance_hsl(i, h, s, l) < distance_hsl(index, h, s, l)) {
      index = i;
    }
  }

  return index;
}

float maxf(float x, float y, float z) {
  float cmax = x;
  if (y > cmax) {
    cmax = y;
  } else if (z > cmax) {
    cmax = z;
  }
  return cmax;
}

float minf(float x, float y, float z) {
  float cmin = x;
  if (y < cmin) {
    cmin = y;
  } else if (z < cmin) {
    cmin = z;
  }
  return cmin;
}

void rgb_to_hsl(int r, int g, int b, int *h, int *s, int *l) {
  float r01 = r / 255.0f;
  float g01 = g / 255.0f;
  float b01 = b / 255.0f;

  float cmax = maxf(r01, g01, b01);
  float cmin = minf(r01, g01, b01);

  float delta = cmax - cmin;
  float eps = 1e-6;
  float hf;
  if (delta < eps)
    hf = 0;
  else if (cmax == r01)
    hf = 60.0f * fmod((g01 - b01) / delta, 6.0f);
  else if (cmax == g01)
    hf = 60.0f * ((b01 - r01) / delta + 2);
  else if (cmax == b01)
    hf = 60.0f * ((r01 - g01) / delta + 4);
  else
    assert(0 && "should not be reached");

  float lf = (cmax + cmin) / 2;
  float sf = 0;
  if (delta < eps)
    sf = 0;
  else
    sf = delta / (1 - fabsf(2 * lf - 1));

  *h = fmodf(fmodf(hf, 360.0f) + 360.0f, 360.0f);
  *s = sf * 100.0f;
  *l = lf * 100.0f;
}

char *shift_args(int *argc, char ***argv) {
  assert(*argc > 0);
  char *result = **argv;
  *argc -= 1;
  *argv += 1;
  return result;
}

void usage() {
  printf("   -w <WIDTH>\n");
  printf("   <img_path>\n");
  exit(1);
}

void add_alpha(int *r, int *g, int *b, int a) {
  *r = *r * a / 255;
  *g = *g * a / 255;
  *b = *b * a / 255;
}

void pixel_print(int resized_width, int org_width, int org_height,
                 uint32_t *pixels) {
  int resized_height = org_height * resized_width / org_width;

  uint32_t *resized_pixels =
      malloc(sizeof(uint32_t) * resized_width * resized_height);
  assert(resized_pixels != NULL);

  stbir_resize_uint8_srgb((const unsigned char *)pixels, org_width, org_height,
                          sizeof(uint32_t) * org_width,
                          (unsigned char *)resized_pixels, resized_width,
                          resized_height, sizeof(uint32_t) * resized_width, 4);

  for (int y = 0; y < resized_height; ++y) {
    for (int x = 0; x < resized_width; ++x) {
      uint32_t pixel = resized_pixels[y * resized_width + x];
      int r = pixel & 0xFF;
      int g = (pixel >> 8) & 0xFF;
      int b = (pixel >> 16) & 0xFF;
      int a = (pixel >> 24) & 0xFF;
      add_alpha(&r, &g, &b, a);
      int h, s, l;
      rgb_to_hsl(r, g, b, &h, &s, &l);
      printf("\e[48;5;%dm  ", find_ansi_by_hsl(h, s, l));
    }
    printf("\e[0m\n");
  }

  free(resized_pixels);
}

int main(int argc, char **argv) {
  assert(argc > 0);
  const char *program = shift_args(&argc, &argv);
  int resized_width;

  while (argc > 0) {
    const char *flag = shift_args(&argc, &argv);

    if (strcmp(flag, "-w") == 0) {
      if (argc <= 0) {
        fprintf(stderr, "-w COULD NOT BE BELOW THAN 0");
        usage();
      }
      resized_width = atoi(shift_args(&argc, &argv));
    } else {
      const char *img_path = flag;
      int width, height;

      uint32_t *pixels =
          (uint32_t *)stbi_load(img_path, &width, &height, NULL, 4);

      if (pixels == NULL) {
        fprintf(stderr, "could not read the file %s\n", img_path);
        usage();
      }
      pixel_print(resized_width, width, height, pixels);
      stbi_image_free(pixels);
    }
  }

  return 0;
}
