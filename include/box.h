#ifndef __box_h__
#define __box_h__

#include "node.h"

typedef enum BoxAttrTypes {
  BoxAttrTypesNone = 100,
  BoxAttrTypeHeight,
  BoxAttrTypeLayout,
  BoxAttrTypeName,
  BoxAttrTypeText,
  BoxAttrTypeWidth,
  BoxAttrTypeX,
  BoxAttrTypeY,
  BoxAttrTypeZ,
} BoxAttrTypes;

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
#define name(value) new_char_attr(BoxAttrTypeName, value)
#define text(value) new_char_attr(BoxAttrTypeText, value);
#define layout(value) new_uint_attr(BoxAttrTypeLayout, value)
#define width(value) new_uint_attr(BoxAttrTypeWidth, value)
// #define handler(value) new_pointer_attr(GestureHandlerAttr, value)
#define height(value) new_uint_attr(BoxAttrTypeHeight, value)
#define x(value) new_uint_attr(BoxAttrTypeX, value)
#define y(value) new_uint_attr(BoxAttrTypeY, value)
#define z(value) new_uint_attr(BoxAttrTypeZ, value)

// Attribute getter macros
#define get_name(node) get_char_attr_from_node(node, BoxAttrTypeName, DEFAULT_CHAR)
#define get_layout(node) get_uint_attr_from_node(node, BoxAttrTypeLayout, LayoutDefault)
#define get_width(node) get_uint_attr_from_node(node, BoxAttrTypeWidth, DEFAULT_ZERO)
#define get_height(node) get_uint_attr_from_node(node, BoxAttrTypeHeight, DEFAULT_ZERO)
#define get_x(node) get_uint_attr_from_node(node, BoxAttrTypeX, DEFAULT_ZERO)
#define get_y(node) get_uint_attr_from_node(node, BoxAttrTypeY, DEFAULT_ZERO)
#define get_z(node) get_uint_attr_from_node(node, BoxAttrTypeZ, DEFAULT_ZERO)

#endif // __box_h__
