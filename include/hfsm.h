#ifndef __hfsm_h__
#define __hfsm_h__

#include <stdint.h>
#include "dom.h"

#define DEFAULT_STATE "default"

// Entities
#define hfsm_container(...) newElement(TypeNone, PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attributes
#define hfsm_children(...) newChildren(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define hfsm_name(value) newCharAttr(NameAttr, value)
#define hfsm_state(value) newCharAttr(StateAttr, value)
#define hfsm_enter_handler(state_name, handler)
#define hfsm_exit_handler(state_name, handler)
#define hfsm_signal_handler(value) newSignalHandlerAttr(HandlerAttr, value)

// Interactions
#define hfsm_get_state(machine) getCharAttrFromElement(machine, StateAttr, DEFAULT_STATE)

int hfsm_signal(Element *machine, int signal);
int hfsm_set_state(Element *machine, char *state_name);

#endif // __hfsm_h__
