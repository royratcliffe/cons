/*!
 */

#ifndef CONS_H
#define CONS_H

/*
 * for NULL
 */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cons;

/*!
 * \brief An empty list, represented as a NULL pointer.
 * \details The CONS_NIL macro represents the empty list in our implementation
 * of cons cells. It is defined as a NULL pointer, which allows us to easily
 * check for the end of a list. When we create a linked list of cons cells, the
 * last cell's cdr will point to CONS_NIL, indicating that there are no more
 * cells in the list. This convention simplifies list operations, such as
 * traversal and manipulation, by providing a clear termination point for the
 * list.
 * \note A cons cell, the fundamental building block of linked lists in
 * Lisp-like languages. A cons cell is a simple data structure that contains two
 * fields: car and cdr. The car field can hold any type of data, and the cdr
 * field points to the next cons cell in the list. This allows us to create
 * linked lists of arbitrary length. The CONS macro provides a convenient way to
 * create cons cells, and the CONS_NIL macro represents the empty list. The
 * CONS_NIL_P and CONS_NOT_NIL_P macros are utility functions for checking if a
 * cons cell is the empty list or not.
 */
#define CONS_NIL ((struct cons *)NULL)

/*!
 * \brief Checks if a cons cell is the empty list (CONS_NIL).
 * \details The CONS_NIL_P macro is a utility function that checks if a given
 * cons cell is equal to CONS_NIL, which represents the empty list. This macro
 * is useful for determining if a cons cell is the end of a list or if it
 * contains data. It returns true if the cell is the empty list and false
 * otherwise.
 * \param _cell The cons cell to be checked against CONS_NIL.
 * \return A boolean value indicating whether the cons cell is the empty list
 * (CONS_NIL) or not.
 */
#define CONS_NIL_P(_cell) ((_cell) == CONS_NIL)

/*!
 * \brief Checks if a cons cell is not the empty list (CONS_NIL).
 * \details The CONS_NOT_NIL_P macro is a utility function that checks if a given
 * cons cell is not equal to CONS_NIL, which represents the empty list. This macro
 * is useful for determining if a cons cell contains data. It returns true if the
 * cell is not the empty list and false otherwise.
 * \param _cell The cons cell to be checked against CONS_NIL.
 * \return A boolean value indicating whether the cons cell is not the empty list
 * (CONS_NIL) or not.
 */
#define CONS_NOT_NIL_P(_cell) ((_cell) != CONS_NIL)

/*!
 * \brief Creates a new cons cell.
 * \details The CONS macro is a utility function that creates a new cons cell
 * with the specified `car` and `cdr` values. This macro simplifies the process
 * of creating cons cells by providing a convenient syntax for initialising the
 * fields of the cons cell. The `car` field holds the actual data, while the
 * `cdr` field points to the next cons cell in the list.
 * \param _car The value to be stored in the `car` field of the cons cell.
 * \param _cdr The value to be stored in the `cdr` field of the cons cell.
 * \return A new cons cell with the specified `car` and `cdr` values.
 */
#define CONS(_car, _cdr) ((struct cons){.car = (_car), .cdr = (_cdr)})

/*!
 * \brief Cons cell structure.
 * \details A cons cell is a fundamental data structure in Lisp-like languages,
 * where it is used to build lists and other complex data structures. The `car`
 * field typically holds the actual data or value, while the `cdr` field points
 * to the next cons cell in the list, allowing for the construction of linked
 * lists and other complex data structures. In this implementation, the `car`
 * field can hold any type of data, while the `cdr` field is specifically
 * designed to link to another cons cell, facilitating the construction of
 * linked lists and other complex data structures.
 *
 * The structure is recursive; it does not need a forward declaration.
 *
 * The car field can hold any type of data, and the cdr field points to the next
 * cons cell in the list. This allows us to create linked lists of arbitrary
 * length.
 *
 * Why "cons"? The term "cons" is derived from the word "construct", as cons
 * cells are used to construct lists and other data structures in Lisp-like
 * languages. The `cons` function is a fundamental operation in Lisp that
 * creates a new cons cell, allowing programmers to build complex data
 * structures by linking cons cells together. The name reflects the purpose of
 * the data structure, which is to construct and manipulate lists and other
 * composite data types.
 *
 * What does CAR and CDR mean? CAR stands for "Contents of the Address part of
 * Register" and CDR stands for "Contents of the Decrement part of Register".
 * These terms originate from the early days of Lisp programming and refer to
 * the two parts of a cons cell. The `car` field typically holds the actual data
 * or value, while the `cdr` field points to the next cons cell in the list,
 * allowing for the construction of linked lists and other complex data
 * structures.
 *
 * \note The `cdr` field is often used to create linked lists, where each cons
 * cell points to the next one in the sequence. This design allows for efficient
 * list manipulation and traversal, as each cons cell can be easily linked to
 * the next one in the sequence. The `car` field can hold any type of data,
 * while the `cdr` field is specifically designed to link to another cons cell,
 * facilitating the construction of linked lists and other complex data
 * structures.
 * \note The `cdr` field is typically used to point to the next cons cell in a
 * list, while the `car` field holds the actual data. This design allows for
 * efficient list manipulation and traversal, as each cons cell can be easily
 * linked to the next one in the sequence.
 */
struct cons {
  /*!
   * \brief Content of Address part of Register (CAR).
   * \details The `car` field of a cons cell is a versatile component that can
   * hold any type of data. It serves as the primary storage for the value or
   * data associated with the cons cell. The `car` field can store various types
   * of data, such as integers, strings, or even pointers to other data
   * structures; this includes sub-cons cells recursively.
   *
   * This flexibility allows cons cells to be used in a wide range of
   * applications, from simple lists to more complex data structures. The `car`
   * field is a fundamental part of the cons cell, enabling it to hold and
   * manipulate data in a flexible manner.
   */
  void *car;

  /*!
   * \brief Content of Decrement part of Register (CDR).
   * \details The `cdr` field of a cons cell is a crucial component that serves
   * as a pointer to the next cons cell in a linked list. This design allows for
   * the construction of linked lists and other complex data structures by
   * linking cons cells together. The `cdr` field is specifically designed to
   * point to another cons cell, facilitating the creation of sequences of cons
   * cells that can represent lists, trees, and other composite data types.
   *
   * In a typical linked list implementation, the `cdr` field of each cons cell
   * points to the next cons cell in the list, while the last cons cell's `cdr`
   * points to CONS_NIL, indicating the end of the list. This structure allows
   * for efficient traversal and manipulation of lists and other data structures
   * built using cons cells.
   */
  struct cons *cdr;
};

static inline void *cons_car(const struct cons *cell) { return cell->car; }

static inline struct cons *cons_cdr(const struct cons *cell) { return cell->cdr; }

static inline void cons_rplaca(struct cons *cell, void *car) { cell->car = car; }

static inline void cons_rplacd(struct cons *cell, struct cons *cdr) { cell->cdr = cdr; }

/*!
 * \brief Initialises a cons cell with a given `car` value and sets the `cdr` to CONS_NIL.
 * \details The `cons_init` function is a utility function that initialises a
 * cons cell with a specified `car` value and sets the `cdr` field to CONS_NIL,
 * which represents the empty list. This function provides a convenient way to
 * create a new cons cell with a given value while ensuring that the `cdr` is
 * properly initialised to indicate that there are no further cells in the list.
 * By using `cons_init`, you can easily create a new cons cell with a specific
 * value and a well-defined end point for the list, making it easier to build
 * and manipulate linked lists and other data structures using cons cells.
 */
static inline void cons_init(struct cons *cell, void *car) {
  cons_rplaca(cell, car);
  cons_rplacd(cell, CONS_NIL);
}

/*!
 * \brief Prepend a cons cell to a list.
 * \details The `cons` function takes a pointer to a list (which is a pointer to
 * a cons cell) and a cons cell to prepend. It initialises the `cdr` of the new
 * cell to point to the existing list and updates the list pointer to point to
 * the new cell. This effectively adds the new cell to the front of the list.
 * The `cons` function is a fundamental operation in Lisp-like languages, where
 * it is used to construct lists and other complex data structures. The `car`
 * field of the new cell can hold any type of data, while the `cdr` field is
 * specifically designed to link to another cons cell, facilitating the
 * construction of linked lists and other complex data structures. The `cons`
 * function allows for efficient list manipulation by enabling the addition of
 * new elements to the front of the list without needing to traverse the entire
 * list, making it a powerful tool for building and modifying lists in a
 * flexible and efficient manner.
 * \param list Pointer to the list to which the new cell will be prepended. This
 * is a pointer to a pointer to a cons cell, allowing the function to update the
 * list pointer to point to the new cell.
 * \param cell The cons cell to prepend to the list. The `car` field of this
 * cell can hold any type of data, while the `cdr` field is specifically
 * designed to link to another cons cell, facilitating the construction of
 * linked lists and other complex data structures.
 * \return A pointer to the `cdr` field of the new cell, allowing for further
 * chaining of cons cells if needed. This return value can be used to easily add
 * more elements to the list by chaining additional cons cells together.
 */
struct cons **cons(struct cons **list, struct cons *cell);

/*!
 * \brief Reverses a linked list of cons cells, mutating the original list.
 * \details This function takes a pointer to the head of a linked list of cons
 * cells and reverses the order of the cells in the list. It iteratively
 * traverses the list, reassigning the cdr pointers to point to the previous
 * cell, effectively reversing the list. The function returns a pointer to the
 * new head of the reversed list.
 * \param cell A pointer to the head of the linked list of cons cells to be
 * reversed. The list is expected to be properly terminated with a NULL cdr.
 * \return A pointer to the head of the reversed linked list of cons cells.
 */
struct cons *cons_reverse(struct cons *list);

#ifdef __cplusplus
}
#endif

#endif /* CONS_H */
