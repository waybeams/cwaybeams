#ifndef __hfsm_h__
#define __hfsm_h__

#include <stdint.h>
#include "dom.h"

#define DEFAULT_STATE "default"

// Entities
#define hfsm_container(...) newNode(TypeNone, PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attributes
#define hfsm_children(...) newChildren(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define hfsm_name(value) newCharAttr(NameAttr, value)
#define hfsm_default_state_name(value) newCharAttr(StateAttr, value)
#define hfsm_enter_handler(state_name, handler)
#define hfsm_exit_handler(state_name, handler)
#define hfsm_signal_handler(value) newSignalHandlerAttr(HandlerAttr, value)

// Interactions
#define hfsm_get_state_name(machine) getCharAttrFromNode(machine, StateAttr, DEFAULT_STATE)

int hfsm_signal(Node *machine, int signal);
int hfsm_set_state(Node *machine, char *state_name);

Node *hfsm_get_state(Node *machine);

#endif // __hfsm_h__
