#ifndef __box_h__
#define __box_h__

#include "node.h"

typedef enum BoxAttr {
  BoxAttrNone = 100,
  BoxAttrHeight,
  BoxAttrLayout,
  BoxAttrName,
  BoxAttrText,
  BoxAttrWidth,
  BoxAttrX,
  BoxAttrY,
  BoxAttrZ,
} BoxAttr;

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

/**
 * Wrap variadic macros with expected names.
 */
#define app(...) new_node(BoxTypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) new_node(BoxTypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) new_node(BoxTypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define vbox(...) new_node(BoxTypeVBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) new_node(BoxTypeHBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutHorizontal), __VA_ARGS__)

// Attribute setter macros
#define name(value) new_char_attr(BoxAttrName, value)
#define text(value) new_char_attr(BoxAttrText, value);
#define layout(value) new_uint_attr(BoxAttrLayout, value)
#define width(value) new_uint_attr(BoxAttrWidth, value)
// #define handler(value) new_pointer_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(BoxAttrHeight, value)
#define x(value) new_uint_attr(BoxAttrX, value)
#define y(value) new_uint_attr(BoxAttrY, value)
#define z(value) new_uint_attr(BoxAttrZ, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, BoxAttrName, DEFAULT_CHAR)
#define get_layout(node) get_uint_attr_from_node(node, BoxAttrLayout, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, BoxAttrWidth, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, BoxAttrHeight, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, BoxAttrX, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, BoxAttrY, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, BoxAttrZ, DEFAULT_ZERO)

#endif // __box_h__
