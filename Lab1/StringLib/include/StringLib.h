#ifndef STRINGLIB_H
#define STRINGLIB_H

#define MAX_LENGTH 25

/**
 * @brief Replaces a given character and provides the address of the new string
 * with the replaced character.
 *
 * @param src String to find character from.
 * @param dst Destination of where will the new string will be allocated.
 * @param find The character to find inside the string.
 * @param replacement The character to replace once found.
 *
 * @note The `dst` pointer will point to a valid memory location on the heap.
 * The caller is responsible for deallocating this memory using `free()` after
 * use.
 */
void Replace(char* src, char* dst, char find, char replacement);

/**
 * @brief Concatenates a string into another one when it finds the specified
 * character.
 *
 * @param src String to insert into
 * @param dst Destination of where will the result will be stored
 * @param find The character to replace
 * @param ins String to insert between the source character
 *
 * @note The `dst` pointer will point to a valid memory location on the heap.
 * The caller is responsible for deallocating this memory using `free()` after
 * use.
 */
void Insert(char* src, char* dst, char find, char* ins);

#endif  // STRINGLIB_H