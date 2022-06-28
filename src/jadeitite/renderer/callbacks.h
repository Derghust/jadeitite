#ifndef JADEITITE_CALLBACKS_H
#define JADEITITE_CALLBACKS_H

//======================================
//             Structures
//======================================

/**
 * Callbacks structure contain all necessary callback for functional OpenGl.
 * Used for setting up callback for Jadeitite framework
 *
 * @struct onUpdate(void) - Called every frame. Used for drawing and other update event.
 * @struct onKeyboardDown(unsigned char, int, int) - Called on any key down.
 * @struct onKeyboardUp(unsigned char, int, int) - Called on any key up.
 * @struct onAttach(int, char **) - Called after initialized Amber framework and OpenGl.
 * @struct onDetach(int, char **) - Called on close/end.
 */
typedef struct {
  void (*onUpdate)(void);
  void (*onKeyboardDown)(unsigned char, int, int);
  void (*onKeyboardUp)(unsigned char, int, int);
  void (*onAttach)(int, char **);
  void (*onDetach)(int, char **);
  void (*onResize)(int, int);
} callbacks_t;

#endif //JADEITITE_CALLBACKS_H
