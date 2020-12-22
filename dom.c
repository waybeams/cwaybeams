#include "dom.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

void freeAttr(Attr *attr) {
  free(attr->data);
}

void freeElement(Element *elem) {
  printf("FREE ELEM WITH PARENT: %d\n", elem->parentId);
  for (int i = 0; i < elem->attrCount; i++) {
    Attr attr = elem->attrs[i];
    freeAttr(&attr);
  }
  free(elem);
}

Attr *newAttr(void) {
  Attr *attr = malloc(sizeof(struct Attr));
  if (attr == NULL) {
    return NULL;
  }
  attr->dataSize = 0;
  return attr;
}

Element *newBox(unsigned int attrCount, ...) {
  int i;
  Element *elem = malloc(sizeof(struct Element));
  elem->id = lastId++;
  elem->parentId = 0;
  elem->attrCount = attrCount;
  elem->attrs = malloc(attrCount * sizeof(struct Attr));

  // Process Attrs
  va_list vargs;
  va_start(vargs, attrCount);
  for (i = 0; i < attrCount; i++) {
    elem->attrs[i] = va_arg(vargs, struct Attr);
  }
  va_end(vargs);

  return elem;
}

void printElement(Element *elem) {
  printf("------------------------\n");
  printf("elem.id: %d\n", elem->id);
  printf("elem.parentId: %d\n", elem->parentId);
}

Attr *name(char *n) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Name;
  s->dataSize = strlen(n) + 1;
  s->data = (unsigned char *)malloc(s->dataSize);
  memcpy(s->data, &n, s->dataSize);
  return s;
}

Attr *width(unsigned int w) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Width;
  s->dataSize = sizeof(unsigned int);
  s->data = (unsigned char *)malloc(s->dataSize);
  memcpy(s->data, &w, s->dataSize);
  return s;
}

Attr *height(unsigned int h) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Height;
  s->dataSize = sizeof(unsigned int);
  s->data = (unsigned char *)malloc(s->dataSize);
  memcpy(s->data, &h, s->dataSize);
  return s;
}

Attr *newChildren(unsigned int count, ...) {
  Attr *s = newAttr();
  if (s == NULL) {
    return NULL;
  }
  s->name = Children;
  // s->dataSize = count * sizeof(struct Element);

  va_list vargs;
  va_start(vargs, count);
  // s->data = malloc(s->dataSize);
  // if (s->data == NULL) {
    // return NULL;
  // }
  // for (int i = 0; i < count; i++) {
    // s->data[i] = (unsigned char *)va_arg(vargs, struct Element*);
  // }
  va_end(vargs);
  return s;
}

