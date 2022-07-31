#ifndef JADEITITE_WINDOW_H
#define JADEITITE_WINDOW_H

/**
 * Window properties structure contain all necessary variables for initialize window with OpenGl/Glut.
 *
 * @struct width - Window width/X.
 * @struct height - Window height/Y.
 * @struct label - Window name/label.
 * @struct autoRefresh - If is true then enable auto refreshing window
 */
typedef struct {
  int width;
  int height;
  const char *label;
  int autoRefresh;
  unsigned char renderMultiplier;
} winProp_t;

#endif //JADEITITE_WINDOW_H
