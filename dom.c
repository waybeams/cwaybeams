#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

void applyNameAttr(Element *elem, char name[]) {
  int nameLen = strlen(name) + 1;
  char *elemName = malloc(nameLen);
  strcpy(elemName, name);
  elem->name = elemName;
}

void applyAttr(Element *elem, Attr *attr) {
  if (attr->name == Name) {
    applyNameAttr(elem, attr->charValue);
  } else if (attr->name == Width) {
    elem->width = attr->uIntValue;
  } else if (attr->name == Height) {
    elem->height = attr->uIntValue;
  } else if (attr->name == Children) {
    elem->children = attr->children;
    elem->childCount = attr->uIntValue;
  } else {
    printf("UNKNOWN ELEMENT: %d\n", attr->name);
  }
}

Element *newElement(unsigned int attrCount, ...) {
  int i;
  Element *elem = malloc(sizeof(Element));
  if (elem == NULL) {
    // malloc failed to get memory.
    return NULL;
  }

  elem->id = lastId++;
  elem->children = NULL;

  // Process Attrs
  va_list vargs;
  Attr *attr;
  va_start(vargs, attrCount);
  for (i = 0; i < attrCount; i++) {
    attr = va_arg(vargs, Attr*);
    applyAttr(elem, attr);
    free(attr);
  }

  va_end(vargs);

  return elem;
}

void freeElement(Element *elem) {
  unsigned int childCount = elem->childCount;
  for (int i = 0; i < childCount; i++) {
    free(&elem->children[i]);
  }
  free(elem->children);
  free(elem->name);
  free(elem);
}

void printElement(Element *elem) {
  printf("------------------------\n");
  printf("elem.id: %d\n", elem->id);
  printf("elem.name: %s\n", elem->name);
  printf("elem.width: %d\n", elem->width);
  printf("elem.height: %d\n", elem->height);

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
  Attr *s = malloc(sizeof(Attr));
  if (s == NULL) {
    return NULL;
  }
  s->name = Name;
  s->charValue = n;
  return s;
}

Attr *width(unsigned int w) {
  Attr *s = malloc(sizeof(Attr));
  if (s == NULL) {
    return NULL;
  }
  s->name = Width;
  s->uIntValue = w;
  return s;
}

Attr *height(unsigned int h) {
  Attr *s = malloc(sizeof(Attr));
  if (s == NULL) {
    return NULL;
  }
  s->name = Height;
  s->uIntValue = h;
  return s;
}

Attr *children(unsigned int count, ...) {
  Attr *s = malloc(sizeof(Attr) + (count * sizeof(Element)));
  if (s == NULL) {
    return NULL;
  }
  s->name = Children;
  va_list vargs;
  va_start(vargs, count);
  Element *kids[count];
  for (int i = 0; i < count; i++) {
    kids[i] = va_arg(vargs, Element*);
  }
  memcpy(&s->children, kids, sizeof(kids));
  va_end(vargs);
  // Save the child count to another field.
  s->uIntValue = count;
  return s;
}
