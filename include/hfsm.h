#ifndef __hfsm_h__
#define __hfsm_h__

#include <stdint.h>
#include "dom.h"

// Entities
#define hfsm_state(...) newElement(TypeNone, PP_NARG(__VA_ARGS__), __VA_ARGS__)

// Attributes
#define hfsm_children(...) newChildren(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define hfsm_name(value) newCharAttr(NameAttr, value)
#define hfsm_enter_handler()
#define hfsm_exit_handler()
#define hfsm_signal_handler(value) newHandlerAttr(HandlerAttr, value)

#endif // __hfsm_h__
