#include "jadeitite/renderer/glut/entrypoint.h"
#include "jadeitite/file.h"

void onAttach(int p_argc, char **p_argv);
void onDetach(int p_argc, char **p_argv);
void onUpdate(void);
void onKeyboardDown(unsigned char p_key, int p_x, int p_y);
void onKeyboardUp(unsigned char p_key, int p_x, int p_y);
void onResize(int p_width, int p_height);

static winProp_t s_winProp = (winProp_t){480, 320, "BASE TEMPLATE", 0};

int setup(callbacks_t *p_callbacks, winProp_t *p_winProp, int p_argc, char *p_argv[]) {
  p_callbacks->onAttach = onAttach;
  p_callbacks->onDetach = onDetach;
  p_callbacks->onKeyboardDown = onKeyboardDown;
  p_callbacks->onKeyboardUp = onKeyboardUp;
  p_callbacks->onUpdate = onUpdate;
  p_callbacks->onResize = onResize;

  p_winProp->width = s_winProp.width;
  p_winProp->height = s_winProp.height;
  p_winProp->label = s_winProp.label;
  p_winProp->autoRefresh = s_winProp.autoRefresh;

  return 1;
}

void onAttach(int p_argc, char **p_argv) {
  render_set_projection_2DOrthographic(s_winProp.width, s_winProp.height);
  render_fix_corner();
  render_set_clear_color(0 ,0, 0);

  // Example for writing data
  typedef struct {
    u8 num_a;
    u8 num_b;
  } test_data_t;
  test_data_t l_test_data_1 = (test_data_t){16, 32};
  file_write("test_data.dat", &l_test_data_1, sizeof(test_data_t));
  test_data_t *read_data = (test_data_t *)file_read(
    "test_data.dat",
    sizeof(test_data_t));
  LOG_INFO("Test Data 1 [%d; %d]", read_data->num_a, read_data->num_b);
  free(read_data);
}

void onKeyboardDown(unsigned char p_key, int p_x, int p_y) {
  switch (p_key) {
  default:LOG_DEBUG("Missing bind p_key on KeyboardDown for \"%c\"!", p_key);
    break;
  }

  onUpdate(); // only if auto refresh is disabled
}

void onKeyboardUp(unsigned char p_key, int p_x, int p_y) {
  switch (p_key) {
  default:LOG_DEBUG("Missing bind p_key on KeyboardUp for \"%c\"!", p_key);
    break;
  }

//  onUpdate(); // only if auto refresh is disabled
}

void onUpdate(void) {
  render_begin();

  // Render things here
  render_color(255, 0, 0);
  draw_point_fast_l1_int(5, 5);
  draw_circle_filled_int(25, 25, 8, 8);
  draw_circle_int(50, 50, 16, 32);

  render_end();
}

void onDetach(int p_argc, char **p_argv) {
  // Do something on detach
}

void onResize(int p_width, int p_height){
//  if (p_width > 0 && p_height > 0) {
//    LOG_INFO("Resizing display [width=%d;height=%d]", p_width, p_height);
//    window_resize(p_width, p_height);
//  }
}
