# TODOS

## Proof of Life
- [ ] Render GTK Application from declarations
- [ ] Render GTK Window from declarations
- [ ] Render GTK Button from declarations
- [x] Pass GTK context data (app and window) through render calls

## Tree caching and comparison
- [x] Migrate abstract node attributes to C types (e.g., uint32\_t, bool, or char)
- [ ] Migrate concrete node attributes to application types (e.g., name, children or width)
- [ ] Get string size of any given node
- [ ] Serialize nodes and attrs to string
- [ ] Introduce flag for string formatting / pretty print
- [ ] Hash string representation of each node

## Other
- [ ] Initial pass at selector queries
- [ ] Find a good C styleguide, linter and formatter
- [x] Rename dom to box to avoid confusion
- [x] Make attr_t.name into std int, but allow enums for concrete consumers
- [x] Extract tree.h and tree.c from dom implementation
- [x] Rename Element to node_t

