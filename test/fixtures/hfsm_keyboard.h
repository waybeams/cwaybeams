#ifndef __hfsm_keyboard_h__
#define __hfsm_keyboard_h__

#include "dom.h"

typedef enum KeyboardState {
  KEYBOARD_ROOT = 0,
  KEYBOARD_SHIFT_UP,
  KEYBOARD_SHIFT_DOWN,
} KeyboardState;

Element *new_hfsm_keyboard(void);


#endif // __hfsm_keyboard_h__
