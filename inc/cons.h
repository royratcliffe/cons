/*!
 * \file cons.h
 * \brief A simple implementation of cons cells for building linked lists.
 */

#ifndef CONS_H
#define CONS_H

/*
 * for NULL (the empty list)
 */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cons;

/*!
 * \brief The empty list (a \c NULL pointer).
 * \details Marks the end of a cons list.
 *
 * The \c CONS_NIL macro represents "the" empty list of cons cells. It is defined
 * as a \c NULL pointer for easily checking for the end of a list. When creating a
 * linked list of cons cells, the last cell's \c cdr field will point to
 * \c CONS_NIL, indicating that there are no more cells in the list.
 */
#define CONS_NIL ((struct cons *)NULL)

/*! \brief Returns \c true if the cons cell is \c CONS_NIL. */
#define CONS_NIL_P(_cell) ((_cell) == CONS_NIL)

/*! \brief Returns \c true if the cons cell is not \c CONS_NIL. */
#define CONS_NOT_NIL_P(_cell) ((_cell) != CONS_NIL)

/*! \brief Creates a new cons cell with the given \c car and \c cdr values. */
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

/*!
 * \brief Accessor for the car field of a cons cell.
 * \param cell The cons cell to access.
 * \return The value stored in the car field of the cons cell.
 */
static inline void *cons_car(const struct cons *cell) { return cell->car; }

/*!
 * \brief Accessor for the cdr field of a cons cell.
 * \param cell The cons cell to access.
 * \return Pointer to the next cons cell (or \c CONS_NIL).
 */
static inline struct cons *cons_cdr(const struct cons *cell) { return cell->cdr; }

static inline void cons_rplaca(struct cons *cell, void *car) { cell->car = car; }

static inline void cons_rplacd(struct cons *cell, struct cons *cdr) { cell->cdr = cdr; }

/*! \brief Initialises a cons cell with the given \c car value and \c cdr set to \c CONS_NIL. */
static inline void cons_init(struct cons *cell, void *car) {
  cons_rplaca(cell, car);
  cons_rplacd(cell, CONS_NIL);
}

/*!
 * \brief Prepends a cons cell to a list.
 * \param list Pointer to the list head to which the new cell will be prepended.
 * This is a pointer to a pointer to a cons cell, allowing the function to
 * update the list pointer to point to the new cell.
 * \param cell The cons cell to prepend to the list.
 * \return Pointer to the \c cdr field of the new cell for chaining. Use the
 * return value to further add elements to the list by chaining additional cons
 * cells together.
 * \details The \c cons function takes a pointer to a list (which is a pointer
 * to a cons cell) and a cons cell to prepend. It initialises the \c cdr of the
 * new cell to point to the existing list and updates the list pointer to point
 * to the new cell. This effectively adds the new cell to the front of the list.
 * The \c cons function is a fundamental operation in Lisp-like languages, where
 * it is used to construct lists and other complex data structures. The \c car
 * field of the new cell can hold any type of data, while the \c cdr field is
 * specifically designed to link to another cons cell, facilitating the
 * construction of linked lists and other complex data structures. The \c cons
 * function allows for efficient list manipulation by enabling the addition of
 * new elements to the front of the list without needing to traverse the entire
 * list, making it a powerful tool for building and modifying lists in a
 * flexible and efficient manner.
 */
struct cons **cons(struct cons **list, struct cons *cell);

/*!
 * \brief Destructively deletes the first cons cell with the specified \c car
 * value from the list.
 * \param list Pointer to the list head.
 * \param car The value to match for deletion.
 * \return Pointer to the deleted cons cell, or \c CONS_NIL if no matching cell
 * was found.
 * \details This function traverses the list of cons cells, looking for the
 * first cell whose \c car field matches the specified value. If such a cell is
 * found, it is removed from the list by updating the \c cdr pointer of the
 * previous cell (or the head pointer if the cell to delete is the first cell)
 * to point to the next cell, effectively bypassing the deleted cell. The
 * function then returns a pointer to the deleted cell. If no matching cell is
 * found after traversing the entire list, the function returns \c CONS_NIL to
 * indicate that no deletion occurred. This operation is destructive because it
 * modifies the original list structure by removing a cell from it. The caller
 * is responsible for managing the memory of the deleted cell if necessary, as
 * this function does not free the memory of the deleted cell; it only removes
 * it from the list.
 */
struct cons *cons_delete(struct cons **list, void *car);

/*!
 * \brief Reverses a linked list of cons cells in place.
 * \details This function takes a pointer to the head of a linked list of cons
 * cells and reverses the order of the cells in the list. It iteratively
 * traverses the list, reassigning the cdr pointers to point to the previous
 * cell, effectively reversing the list.
 * \param list The list to reverse. This is a pointer to the head of the list,
 * and it will be updated to point to the new head of the reversed list.
 */
void cons_reverse(struct cons **list);

#ifdef __cplusplus
}
#endif

#endif /* CONS_H */
