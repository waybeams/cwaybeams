#ifndef __hfsm_keyboard_h__
#define __hfsm_keyboard_h__

#include "node.h"

typedef int (SignalHandler)(int signal);

typedef enum KeyboardAttrTypes {
  KeyboardAttrTypeNone = 100,

  // Set the function handler enum value for all subsequent function handlers.
  // NOTE(lbayes): This is gross, find a better way!
  KeyboardAttrTypeFunction = AttrTypeFunction,
  AttrTypeSignal,
} KeyboardAttrTypes;

Node *new_hfsm_keyboard(void);

Attr *signal_handler(SignalHandler handler);

#endif // __hfsm_keyboard_h__
