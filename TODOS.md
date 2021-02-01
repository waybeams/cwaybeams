# TODOS

## Tree caching and comparison
- [ ] Migrate abstract node attributes to C types (e.g., uint32\_t, bool, or char)
- [ ] Migrate concrete node attributes to application types (e.g., name, children or width)
- [ ] Get string size of any given node
- [ ] Serialize nodes and attrs to string
- [ ] Introduce flag for string formatting / pretty print
- [ ] Hash string representation of each node
- [ ] Move gesture / event features out of node into box?

## Other
- [ ] Initial pass at selector queries
- [ ] Find a good C styleguide, linter and formatter
- [x] Rename dom to box to avoid confusion
- [x] Make Attr.name into std int, but allow enums for concrete consumers
- [x] Extract tree.h and tree.c from dom implementation
- [x] Rename Element to Node

