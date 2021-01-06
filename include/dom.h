#ifndef __dom_h__
#define __dom_h__

#include "node.h"

typedef enum Layout {
  LayoutDefault = 0,
  LayoutStack,
  LayoutVertical,
  LayoutHorizontal,
} Layout;

/**
 * Wrap variadic macros with expected names.
 */
#define app(...) new_node(TypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) new_node(TypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) new_node(TypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define vbox(...) new_node(TypeVBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) new_node(TypeHBox, PP_NARG(__VA_ARGS__) + 1, \
    layout(LayoutHorizontal), __VA_ARGS__)

// Attribute setter macros
#define name(value) new_char_attr(NameAttr, value)
#define layout(value) new_uint_attr(LayoutAttr, value)
#define width(value) new_uint_attr(WidthAttr, value)
#define handler(value) new_handler_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(HeightAttr, value)
#define x(value) new_uint_attr(XAttr, value)
#define y(value) new_uint_attr(YAttr, value)
#define z(value) new_uint_attr(ZAttr, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, NameAttr, DEFAULT_CHAR)
#define get_layout(node) get_uint_attr_from_node(node, LayoutAttr, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, WidthAttr, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, HeightAttr, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, XAttr, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, YAttr, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, ZAttr, DEFAULT_ZERO)

#endif // __dom_h__
