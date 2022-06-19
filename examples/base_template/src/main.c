#include "jadeitite/entrypoint/entrypoint_glut.h"

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
