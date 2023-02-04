#include "jadeitite_gl.h"

void onAttach(int p_argc, char **p_argv);
void onDetach(int p_argc, char **p_argv);
void onUpdate(void);
void onKeyboardDown(unsigned char p_key, int p_x, int p_y);
void onKeyboardUp(unsigned char p_key, int p_x, int p_y);
void onResize(int p_width, int p_height);

static jdt_winProp_t s_winProp = (jdt_winProp_t) {480, 320, "BASE TEMPLATE", 1};
jdt_term_asset_t *l_asset;

int jdt_setup(jdt_callbacks_t *p_callbacks, jdt_winProp_t *p_winProp, int p_argc, char *p_argv[]) {
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

  return JDT_RS_OK;
}

void onAttach(int p_argc, char **p_argv) {
  render_set_clear_color(0.1f, 0.1f, 0.1f);
  render_set_projection_2DOrthographic(s_winProp.width, s_winProp.height);

  // Example for writing data
  typedef struct {
    u8 num_a;
    u8 num_b;
  } test_data_t;
  test_data_t l_test_data_1 = (test_data_t) {16, 32};
  jdt_file_write("test_data.dat", &l_test_data_1, sizeof(test_data_t));
  test_data_t *read_data = (test_data_t *) jdt_file_read(
    "test_data.dat",
    sizeof(test_data_t));
  JDT_LOG_INFO("Test Data 1 [%d; %d]", read_data->num_a, read_data->num_b);
  free(read_data);

  l_asset = jdt_asset_read("font8x8.dat");

  onUpdate();
}

void onKeyboardDown(unsigned char p_key, int p_x, int p_y) {
  switch (p_key) {
  case 'q': {
    glutLeaveMainLoop();
    break;
  }
  default:JDT_LOG_DEBUG("Missing bind p_key on KeyboardDown for \"%c\"!", p_key);
    break;
  }

//  onUpdate(); // only if auto refresh is disabled
}

void onKeyboardUp(unsigned char p_key, int p_x, int p_y) {
  switch (p_key) {
  default:JDT_LOG_DEBUG("Missing bind p_key on KeyboardUp for \"%c\"!", p_key);
    break;
  }

//  onUpdate(); // only if auto refresh is disabled
}

u32 s_text_pos_x = 0;
bool s_text_pos_x_increasing = true;

void onUpdate(void) {
  if (s_text_pos_x >= 32) {
    s_text_pos_x_increasing = false;
  } else if (s_text_pos_x == 0) {
    s_text_pos_x_increasing = true;
  }

  if (s_text_pos_x_increasing) {
    s_text_pos_x++;
  } else {
    s_text_pos_x--;
  }

  jdt_render_begin();

  jdt_set_render_color(255, 0, 0);
  jdt_draw_bitmaps(8, 8, l_asset->data, 32 + s_text_pos_x, 32, "Hello, World!", s_winProp.renderMultiplier);

  jdt_render_end();
}

void onDetach(int p_argc, char **p_argv) {
  JDT_LOG_INFO("Detaching...");
  free(l_asset);
}

void onResize(int p_width, int p_height) {

}
