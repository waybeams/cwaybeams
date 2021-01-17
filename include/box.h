#ifndef __box_h__
#define __box_h__

#include "node.h"

typedef enum BoxAttrKeysKeys {
  BoxAttrKeysNone = 100,
  BoxAttrKeysHeight,
  BoxAttrKeysLabel,
  BoxAttrKeysLayout,
  BoxAttrKeysName,
  BoxAttrKeysText,
  BoxAttrKeysTitle,
  BoxAttrKeysWidth,
  BoxAttrKeysX,
  BoxAttrKeysY,
  BoxAttrKeysZ,
} BoxAttrKeysKeys;

typedef enum BoxType {
  BoxTypeNone = 0,
  BoxTypeApp,
  BoxTypeBody,
  BoxTypeBox,
  BoxTypeButton,
  BoxTypeHBox,
  BoxTypeHead,
  BoxTypeLink,
  BoxTypeStyle,
  BoxTypeVBox,
  BoxTypeWindow,
} BoxType;

typedef enum BoxLayout {
  LayoutDefault = 0,
  LayoutStack,
  LayoutVertical,
  LayoutHorizontal,
} BoxLayout;

typedef struct BoxServices {
} BoxServices;

/**
 * Wrap variadic macros with expected names.
 */
#define app(...) new_node(BoxTypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) new_node(BoxTypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define body(...) new_node(BoxTypeBody, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define button(...) new_node(BoxTypeButton, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) new_node(BoxTypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define vbox(...) new_node(BoxTypeVBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) new_node(BoxTypeHBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutHorizontal), __VA_ARGS__)

// Attribute setter macros
#define name(value) new_char_attr(BoxAttrKeysName, value)
#define text(value) new_char_attr(BoxAttrKeysText, value)
#define title(value) new_char_attr(BoxAttrKeysTitle, value)
#define label(value) new_char_attr(BoxAttrKeysLabel, value)
#define layout(value) new_uint_attr(BoxAttrKeysLayout, value)
#define width(value) new_uint_attr(BoxAttrKeysWidth, value)
// #define handler(value) new_ext_ptr_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(BoxAttrKeysHeight, value)
#define x(value) new_uint_attr(BoxAttrKeysX, value)
#define y(value) new_uint_attr(BoxAttrKeysY, value)
#define z(value) new_uint_attr(BoxAttrKeysZ, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, BoxAttrKeysName, DEFAULT_CHAR)
#define get_text(node) get_char_attr_from_node(node, BoxAttrKeysText, DEFAULT_CHAR)
#define get_label(node) get_char_attr_from_node(node, BoxAttrKeysLabel, DEFAULT_CHAR)

#define get_layout(node) get_uint_attr_from_node(node, BoxAttrKeysLayout, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, BoxAttrKeysWidth, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, BoxAttrKeysHeight, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, BoxAttrKeysX, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, BoxAttrKeysY, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, BoxAttrKeysZ, DEFAULT_ZERO)

#endif // __box_h__
