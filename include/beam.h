#ifndef _beam_h_
#define _beam_h_

#include "node.h"

/**
 * Beam composes and configures node elements to create user interface controls
 * that can be serialized into any number of rendering backends.
 */

typedef enum {
  BeamSuccess = 0,
  BeamAllocationFailure,
}beam_return_codes;

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

typedef enum beam_attr_keys_t {
  BeamAttrKeysNone = 100,
  BeamAttrKeysHandler,
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

typedef struct {
  u32_t type;
  u8_t *source;
  u8_t *payload;
} beam_signal_t;

// ABI compatible with SDL_Rect
typedef struct {
  s32_t x;
  s32_t y;
  s32_t w;
  s32_t h;
} beam_rect_t;

typedef struct {
  u8_t r;
  u8_t g;
  u8_t b;
  u8_t a;
} beam_color_t;

/**
 * Variadic macros for node creation
 */
#define app(...) new_node(BeamTypeApp, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define window(...) new_node(BeamTypeWindow, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define body(...) new_node(BeamTypeBody, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define button(...) new_node(BeamTypeButton, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define box(...) new_node(BeamTypeBox, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define vbox(...) new_node(BeamTypeVBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutVertical), __VA_ARGS__)
#define hbox(...) new_node(BeamTypeHBox, PP_NARG(__VA_ARGS__) + 1, layout(LayoutHorizontal), __VA_ARGS__)

// Attribute setter macros
attr_t *name(char *value);
attr_t *text(char *value);
attr_t *title(char *value);
attr_t *label(char *value);
attr_t *layout(beam_layout_t value);

attr_t *width(s32_t value);
attr_t *height(s32_t value);
attr_t *x(s32_t value);
attr_t *y(s32_t value);
attr_t *z(s32_t value);

// Attribute getter macros
char *get_name(node_t *node);
char *get_text(node_t *node);
char *get_label(node_t *node);

beam_layout_t get_layout(node_t *node);

s32_t get_width(node_t *node);
s32_t get_height(node_t *node);
char *get_title(node_t *node);
s32_t get_x(node_t *node);
s32_t get_y(node_t *node);
s32_t get_z(node_t *node);

#endif // _beam_h_
