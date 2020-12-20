#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

void applyNameAttr(Element *elem, char name[]) {
  printf("Apply name attr with: %ld\n", strlen(name));
  elem->name = malloc(strlen(name) + 1);
  strcpy(elem->name, name);
}

void applyChildrenAttr(Element *elem, unsigned int count, Element *kids) {
  elem->childCount = count;
  elem->children = calloc(count, sizeof(Element));
  memcpy(elem->children, kids, count * sizeof(Element));
  for (int i = 0; i < count; i++) {
    elem->children[i].parentId = elem->id;
  }
}

void applyAttr(Element *elem, Attr *attr) {
  if (attr->name == Name) {
    printf("Apply Name: %s\n", attr->charValue);
    applyNameAttr(elem, attr->charValue);
  } else if (attr->name == Width) {
    printf("Apply Width: %d\n", attr->uIntValue);
    elem->width = attr->uIntValue;
  } else if (attr->name == Height) {
    printf("Apply Height: %d\n", attr->uIntValue);
    elem->height = attr->uIntValue;
  } else if (attr->name == Children) {
    printf(">> Apply Children count: %d\n", attr->uIntValue);
    applyChildrenAttr(elem, attr->uIntValue, attr->children);
  } else {
    printf("UNKNOWN ELEMENT: %d\n", attr->name);
  }
}

void freeAttr(Attr *attr) {
  free(attr->charValue);
  free(attr->children);
  free(attr);
}

void freeElement(Element *elem) {
  if (elem->childCount > 0) {
    // for (int i = 0; i < elem->childCount; i++) {
      // freeElement(&elem->children[i]);
    // }
    free(elem->children);
  }
  free(elem->name);
  free(elem);
}

void freeRoot(Element *elem) {
  for (int i = 0; i < elem->childCount; i++) {
    freeElement(&elem->children[i]);
  }
}

Attr *newAttr(void) {
  Attr *attr = malloc(sizeof(Attr));
  if (attr == NULL) {
    return NULL;
  }
  attr->uIntValue = 0;
  attr->intValue = 0;
  attr->floatValue = 0.0;
  attr->charValue = NULL;
  attr->children = NULL;
  return attr;
}

Element *newBox(unsigned int attrCount, ...) {
  int i;
  Element *elem = malloc(sizeof(Element));
  // if (elem == NULL) {
    // malloc failed to get memory.
    // return NULL;
  // }
  elem->childCount = 0;
  elem->id = lastId++;
  elem->name = '\0';
  elem->children = NULL;
  elem->parentId = 0;

  // Process Attrs
  va_list vargs;
  va_start(vargs, attrCount);
  for (i = 0; i < attrCount; i++) {
    Attr *attr = va_arg(vargs, Attr*);
    applyAttr(elem, attr);
    freeAttr(attr);
  }
  va_end(vargs);

  return elem;
}

void printElement(Element *elem) {
  printf("------------------------\n");
  printf("elem.id: %d\n", elem->id);
  printf("elem.name: %s\n", elem->name);
  printf("elem.width: %d\n", elem->width);
  printf("elem.height: %d\n", elem->height);
  printf("elem.childCount: %d\n", elem->childCount);

  /*
  int depth = 0;
  char tabs[20] = "\0";
  printf("depth: %d\n", depth);
  for (int i = 0; i < depth; i++) {
    strcat(tabs, "\t");
  }

  // printf("%sname: %s layout: %d\n", tabs, elem->name, elem->layout);
  printf("%sid: %d parent: %d addr: %p\n", tabs, elem->id, elem->parentId, elem);
  printf("%sw: %d h: %d\n", tabs, elem->width, elem->height);
  printf("%schildCount: %d\n", tabs, elem->childCount);
  // for (int i = 0; i < elem->childCount; i++) {
    // Element *child = &elem->children[i];
    // printf("%s>> child[%d].id: %d\n", tabs, i, child->id);
    // printElement(child, depth + 1);
  // }
  printf("%s-----------------\n", tabs);
  */
}

/*
Element* vbox(unsigned int count, ...) {
  return container(LAYOUT_VERTICAL);
}

Element* hbox(unsigned int count, ...) {
  return container(LAYOUT_HORIZONTAL);
}

Element* box(unsigned int count, ...) {
  return container(LAYOUT_STACK);
}
*/

Attr *name(char *n) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Name;
  s->charValue = malloc(strlen(n) + 1);
  strcpy(s->charValue, n);
  return s;
}

Attr *width(unsigned int w) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Width;
  s->uIntValue = w;
  return s;
}

Attr *height(unsigned int h) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Height;
  s->uIntValue = h;
  return s;
}

Attr *newChildren(unsigned int count, ...) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Children;
  s->uIntValue = count;

  va_list vargs;
  va_start(vargs, count);
  s->children = malloc(count * sizeof(Element));
  if (s->children == NULL) {
    return NULL;
  }
  for (int i = 0; i < count; i++) {
    s->children[i] = va_arg(vargs, Element);
  }
  va_end(vargs);
  return s;
}

