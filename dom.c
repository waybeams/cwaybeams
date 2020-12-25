#include "dom.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ElementId lastId = 1;

void freeAttr(Attr *attr) {
  free(attr->data);
  free(attr);
}

void freeElement(Element *elem) {
  debug("FREE ELEM WITH PARENT: %d\n", elem->parentId);
  // for (int i = 0; i < elem->attrCount; i++) {
    // Attr *attr = elem->attrs[i];
    // freeAttr(attr);
  // }
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

/**
 * Create a new Attr with the provided char value.
 */
Attr *newCharAttr(AttrName name, char *value) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->dataSize = strlen(value) + 1;
  attr->data = (unsigned char *)malloc(attr->dataSize);
  memcpy(attr->data, value, attr->dataSize);
  return attr;
}

/**
 * Get the data from a Char Attr as char *
 */
char *charAttrData(Attr *attr) {
  return (char *)attr->data;
}

Attr *newUintAttr(AttrName name, unsigned int value) {
  Attr *attr = newAttr();
  if (attr == NULL) {
    return NULL;
  }
  attr->name = name;
  attr->dataSize = sizeof(unsigned int);
  attr->data = (unsigned char *)malloc(attr->dataSize);
  memcpy(attr->data, &value, attr->dataSize);
  return attr;
}

/**
 * Get the provided Attribute data as an
 * unsigned integer.
 */
unsigned int uintAttrData(Attr *attr) {
  return (unsigned int)*attr->data;
}

/**
 * Concrete Attr names bound to types.
 */

Attr *name(char *value) {
  return newCharAttr(Name, value);
}

Attr *width(unsigned int value) {
  return newUintAttr(Width, value);
}

Attr *height(unsigned int value) {
  return newUintAttr(Height, value);
}

Element *newBox(unsigned int attrCount, ...) {
  // struct Attr **attr;
  // Process Attrs
  /*
  // int i;
  va_list vargs;
  va_start(vargs, attrCount);
  for (i = 0; i < attrCount; i++) {
    int ptr = va_arg(vargs, Attr);
    // free(&ptr);
    // debug("YIIIII %d", i);
    // debug("YUUUUUU %u", (unsigned char)attr.data);
    // elem->attrs[i] = &attr;
  }
  va_end(vargs);
  */

  Element *elem = malloc(sizeof(struct Element));
  elem->id = lastId++;
  elem->parentId = 0;
  elem->attrCount = attrCount;
  // elem->attrs = malloc(attrCount * sizeof(struct Attr));

  return elem;
}

void printElement(Element *elem) {
  printf("------------------------\n");
  printf("elem.id: %d\n", elem->id);
  printf("elem.parentId: %d\n", elem->parentId);
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


