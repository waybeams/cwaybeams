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
}beam_signal_t;

typedef struct beam_surface_t {
  beam_surface_type type;
  void *platform;
}beam_surface_t;

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
s32_t get_x(node_t *node);
s32_t get_y(node_t *node);
s32_t get_z(node_t *node);

beam_surface_t *beam_create_surface(beam_surface_type t);
int beam_render(beam_surface_t *s, beam_signal_t **signals, node_t *node);

beam_signal_t **beam_signals_gather(beam_surface_t *s);
int beam_window_should_close(beam_surface_t *s);

void beam_surface_free(beam_surface_t *s);

#endif // __beam_h__
