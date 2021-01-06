#ifndef __hfsm_h__
#define __hfsm_h__

#include <stdint.h>
#include "node.h"

#define DEFAULT_STATE "default"

typedef enum HfsmAttrTypes {
  HfsmAttrTypeNone = 100,
  AttrTypeState,
} HfsmAttrTypes;

// Entities
#define hfsm_container(...) new_node(TypeNone, PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attributes
#define hfsm_children(...) new_children(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define hfsm_name(value) new_char_attr(AttrTypeName, value)
#define hfsm_default_state_name(value) new_char_attr(AttrTypeState, value)
#define hfsm_enter_handler(state_name, handler)
#define hfsm_exit_handler(state_name, handler)
#define hfsm_signal_handler(value) new_signal_attr(AttrTypeHandler, value)

// Interactions
#define hfsm_get_state_name(machine) get_char_attr_from_node(machine, AttrTypeState, DEFAULT_STATE)

int hfsm_signal(Node *machine, int signal);
int hfsm_set_state(Node *machine, char *state_name);

Node *hfsm_get_state(Node *machine);

#endif // __hfsm_h__
