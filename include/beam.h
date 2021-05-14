#ifndef __beam_h__
#define __beam_h__

#include "node.h"

typedef enum {
  BeamSuccess = 0,
  BeamAllocationFailure,
}beam_return_codes;

typedef enum beam_surface_type {
  BeamSurfaceGlfw = 1,
  BeamSurfaceGles,
  BeamSurfaceDirectX,
  BeamSurfaceMetal,
  BeamSurfaceVulkan
}beam_surface_type;

typedef enum beam_signal_type {
  // User Gestures:
  BeamSignalKeyPressed = 1,
  BeamSignalKeyReleased,
  BeamSignalMouseClicked,
  BeamSignalMouseDoubleClicked,
  BeamSignalMousePressed,
  BeamSignalMouseReleased,
  BeamSignalMouseMoved,

  BeamSignalMouseHovered,
  BeamSignalMouseEntered,
  BeamSignalMouseExited,
  BeamSignalWheelSpun,
  BeamSignalContextMenuRequested,

  BeamSignalTouchStarted,
  BeamSignalTouchMoved,
  BeamSignalTouchEnded,
  BeamSignalTouchCancelled,

  // Component Notifications:
  BeamSignalFocused,
  BeamSignalBlurred,
  BeamSignalButtonClicked,
  BeamSignalButtonPressed,
  BeamSignalButtonReleased,
  BeamSignalWindowResized,
  BeamSignalWindowMoved,

  // Lifecycle Notifications:
  BeamSignalFrameStarted,
  BeamSignalComposeStarted,
  BeamSignalComposeCompleted,
  BeamSignalLayoutStarted,
  BeamSignalLayoutCompleted,
  BeamSignalRenderStarted,
  BeamSignalRenderCompleted,
  BeamSignalFrameCompleted,
}beam_signal_type;

typedef struct {
  unsigned int type;
  unsigned char *source;
  unsigned char *payload;
}beam_signal_t;

typedef struct beam_surface_t {
  beam_surface_type type;
  void *platform;
}beam_surface_t;

typedef enum beam_attr_keys_t {
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
} beam_attr_keys_t;

typedef enum beam_type_t {
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
} beam_type_t;

typedef enum beam_layout_t {
  LayoutDefault = 0,
  LayoutStack,
  LayoutVertical,
  LayoutHorizontal,
} beam_layout_t;

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

beam_surface_t *beam_create_surface(beam_surface_type t);
int beam_render(beam_surface_t *s, beam_signal_t **signals, node_t *node);

beam_signal_t **beam_signals_gather(beam_surface_t *s);
int beam_window_should_close(beam_surface_t *s);

void beam_surface_free(beam_surface_t *s);

#endif // __beam_h__
