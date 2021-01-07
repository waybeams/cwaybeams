#ifndef __hfsm_keyboard_h__
#define __hfsm_keyboard_h__

#include "node.h"

/**
 * This is an example that demonstrates how one might use node.h + hfsm.h to
 * create and create a new Finite State Machine or Hierarchical Finite State
 * Machine.
 *
 * The idea here, is that we can describe new containers, give them names and
 * then associate custom signal handlers so that when the machine is in a
 * particular state, the associated signal handler gets called with message
 * inputs.
 */
typedef int (SignalHandler)(char *buf, char *signal);

typedef enum KeyboardAttrTypes {
  KeyboardAttrTypeNone = 100,

  // Set the function handler enum value for all subsequent function handlers.
  // NOTE(lbayes): This is gross, find a better way!
  KeyboardAttrTypeFunction = AttrTypeFunction,
  AttrTypeSignal = 501,
} KeyboardAttrTypes;

Node *new_hfsm_keyboard(void);
int kb_send_signal(Node *machine, char *buf, char *signal);

Attr *kb_signal_handler(SignalHandler handler);

SignalHandler *kb_get_signal_handler(Node *machine);

#endif // __hfsm_keyboard_h__
