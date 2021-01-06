#ifndef __layout_h__
#define __layout_h__

#include <dom.h>

typedef enum LayoutStatus {
    LayoutSuccess = 0,
} LayoutStatus;

LayoutStatus layoutNode(Node *elem);

#endif // __layout_h__

