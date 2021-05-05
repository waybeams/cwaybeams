#ifndef __beam_h__
#define __beam_h__

#include "node.h"

typedef enum BeamAttrKeysKeys {
  BeamAttrKeysNone = 100,
  BeamAttrKeysHeight,
  BeamAttrKeysLabel,
  BeamAttrKeysLayout,
  BeamAttrKeysName,
  BeamAttrKeysText,
  BeamAttrKeysTitle,
  BeamAttrKeysWidth,
  BeamAttrKeysX,
  BeamAttrKeysY,
  BeamAttrKeysZ,
} BeamAttrKeysKeys;

typedef enum BeamType {
  BeamTypeNone = 0,
  BeamTypeApp,
  BeamTypeBody,
  BeamTypeBox,
  BeamTypeButton,
  BeamTypeHBox,
  BeamTypeHead,
  BeamTypeLink,
  BeamTypeStyle,
  BeamTypeVBox,
  BeamTypeWindow,
} BeamType;

typedef enum BeamLayout {
  LayoutDefault = 0,
  LayoutStack,
  LayoutVertical,
  LayoutHorizontal,
} BeamLayout;

/**
 * Wrap variadic macros with expected names.
 */
#define app(...) new_node(BeamTypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) new_node(BeamTypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define body(...) new_node(BeamTypeBody, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define button(...) new_node(BeamTypeButton, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) new_node(BeamTypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define vbox(...) new_node(BeamTypeVBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) new_node(BeamTypeHBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutHorizontal), __VA_ARGS__)

// Attribute setter macros
#define name(value) new_char_attr(BeamAttrKeysName, value)
#define text(value) new_char_attr(BeamAttrKeysText, value)
#define title(value) new_char_attr(BeamAttrKeysTitle, value)
#define label(value) new_char_attr(BeamAttrKeysLabel, value)
#define layout(value) new_uint_attr(BeamAttrKeysLayout, value)
#define width(value) new_uint_attr(BeamAttrKeysWidth, value)
// #define handler(value) new_ext_ptr_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(BeamAttrKeysHeight, value)
#define x(value) new_uint_attr(BeamAttrKeysX, value)
#define y(value) new_uint_attr(BeamAttrKeysY, value)
#define z(value) new_uint_attr(BeamAttrKeysZ, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, BeamAttrKeysName, DEFAULT_CHAR)
#define get_text(node) get_char_attr_from_node(node, BeamAttrKeysText, DEFAULT_CHAR)
#define get_label(node) get_char_attr_from_node(node, BeamAttrKeysLabel, DEFAULT_CHAR)

#define get_layout(node) get_uint_attr_from_node(node, BeamAttrKeysLayout, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, BeamAttrKeysWidth, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, BeamAttrKeysHeight, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, BeamAttrKeysX, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, BeamAttrKeysY, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, BeamAttrKeysZ, DEFAULT_ZERO)

#endif // __beam_h__
