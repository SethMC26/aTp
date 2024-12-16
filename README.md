Readme from chatGPT cuz im lazy
# Usage
~~if your not on a Linux system god help you~~ 

Linux install: 
```bash
git clone https://github.com/SethMC26/tag_pointer_fun.git
cd tag_pointer_fun 
gcc tagged_pointers 
./a.out
```
# Pointer Tagging in C

This program demonstrates how to add, remove, and read a 16-bit "tag" from a pointer using bitwise operations.

## Functions

### `print_ptr(void* ptr)`
Prints the binary representation of the pointer for debugging.

### `set_tag(void* ptr, short tag)`
Sets a 16-bit tag to the upper bits (48-63) of the pointer.

- **Returns**: The pointer with the tag set.

### `remove_tag(void* ptr)`
Removes the tag from the pointer, leaving the original pointer intact.

- **Returns**: The pointer with the tag removed.

### `read_tag(void* ptr)`
Reads the tag from a tagged pointer.

- **Returns**: The 16-bit tag value.

