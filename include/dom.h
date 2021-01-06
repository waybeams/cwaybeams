#ifndef __dom_h__
#define __dom_h__

#include "node.h"

typedef enum DomAttrTypes {
  DomAttrTypesNone = 100,
  AttrTypeHeight,
  AttrTypeLayout,
  AttrTypeWidth,
  AttrTypeX,
  AttrTypeY,
  AttrTypeZ,
} DomAttrTypes;

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
#define name(value) new_char_attr(AttrTypeName, value)
#define layout(value) new_uint_attr(AttrTypeLayout, value)
#define width(value) new_uint_attr(AttrTypeWidth, value)
// #define handler(value) new_pointer_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(AttrTypeHeight, value)
#define x(value) new_uint_attr(AttrTypeX, value)
#define y(value) new_uint_attr(AttrTypeY, value)
#define z(value) new_uint_attr(AttrTypeZ, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, AttrTypeName, DEFAULT_CHAR)
#define get_layout(node) get_uint_attr_from_node(node, AttrTypeLayout, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, AttrTypeWidth, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, AttrTypeHeight, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, AttrTypeX, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, AttrTypeY, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, AttrTypeZ, DEFAULT_ZERO)

#endif // __dom_h__
