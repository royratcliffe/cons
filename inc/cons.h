/* SPDX-License-Identifier: MIT */

/*!
 * \file cons.h
 * \brief A simple implementation of cons cells for building linked lists.
 * \copyright 2026, Roy Ratcliffe, Northumberland, United Kingdom
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
 * \brief Construct cell structure for building linked lists.
 * \details The \c car field holds data, the \c cdr field points to the next
 * cons cell.
 *
 * A cons cell is a fundamental data structure in Lisp-like languages, where it
 * is used to build lists and other complex data structures. The \c car field
 * holds the actual data or value, while the \c cdr field points to the next
 * cons cell in the list, allowing for the construction of linked lists and
 * other complex data structures of arbitrary length.
 *
 * Why "cons"? The term "cons" is derived from the word "construct," as cons
 * cells are used to construct lists and other data structures. The \c cons
 * function is a fundamental operation in Lisp that creates a new cons cell,
 * allowing programmers to build complex data structures by linking cons cells
 * together. The name reflects the purpose of the data structure, which is to
 * construct and manipulate lists and other composite data types.
 *
 * What does CAR and CDR mean? CAR stands for "Contents of Address Register" and
 * CDR stands for "Contents of Decrement Register." These terms originate from
 * the early days of Lisp programming and refer to the two parts of a cons cell.
 */
struct cons {
  /*!
   * \brief Contents of Address Register (CAR).
   * \details Data field (can hold any type).
   *
   * The \c car field of a cons cell is a versatile component that can hold any
   * type of data. It serves as the primary pointer-sized storage for the value
   * or data associated with the cons cell; this optionally includes sub-cons
   * cells \e recursively.
   */
  void *car;

  /*!
   * \brief Contents of Decrement Register (CDR).
   * \details Pointer to the next cons cell (or \c CONS_NIL).
   */
  struct cons *cdr;
};

/*!
 * \brief Accessor for the \c car field of a cons cell.
 * \param cell The cons cell to access.
 * \return The value stored in the \c car field of the cons cell.
 */
static inline void *cons_car(const struct cons *cell) { return cell->car; }

/*!
 * \brief Accessor for the \c cdr field of a cons cell.
 * \param cell The cons cell to access.
 * \return Pointer to the next cons cell (or \c CONS_NIL).
 */
static inline struct cons *cons_cdr(const struct cons *cell) { return cell->cdr; }

/*!
 * \brief Mutator for the \c car field of a cons cell.
 * \param cell The cons cell to modify.
 * \param car The new value to set in the \c car field of the cons cell.
 */
static inline void cons_rplaca(struct cons *cell, void *car) { cell->car = car; }

/*!
 * \brief Mutator for the \c cdr field of a cons cell.
 * \param cell The cons cell to modify.
 * \param cdr The new value to set in the \c cdr field of the cons cell.
 */
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
 * \brief Destructively deletes the \e first cons cell with the specified \c car
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

/*!
 * \brief Computes the length of a linked list of cons cells.
 * \param cell The head of the list to compute the length of, or \c CONS_NIL for
 * an empty list.
 * \return The number of cons cells in the list.
 * \details This function iteratively traverses the linked list of cons cells,
 * counting the number of cells until it reaches the end of the list (indicated
 * by \c CONS_NIL). It returns the total count as the length of the list.
 */
size_t cons_length(const struct cons *cell);

/*!
 * \brief Returns the last cons cell in a linked list of cons cells.
 * \param cell The head of the list to find the last cell of, or \c CONS_NIL for
 * an empty list.
 * \return Pointer to the last cons cell in the list, or \c CONS_NIL if the
 * list is empty.
 * \details This function iteratively traverses the linked list of cons cells
 * until it reaches the last cell, which is identified by having its \c cdr field
 * equal to \c CONS_NIL. It returns a pointer to this last cell. If the input
 * list is empty (i.e., if the input pointer is \c CONS_NIL), the function
 * returns \c CONS_NIL to indicate that there are no cells in the list.
 */
struct cons *cons_last(struct cons *cell);

/*!
 * \brief Returns the n'th cons cell in a linked list of cons cells.
 * \param cell The head of the list to find the n'th cell of, or \c CONS_NIL for
 * an empty list.
 * \param nth The zero-based index of the cell to retrieve.
 * \return Pointer to the n'th cons cell in the list, or \c CONS_NIL if the index
 * is out of bounds.
 * \details Iteratively traverses the linked list of cons cells, counting the
 * cells as it goes. When the count reaches the specified index \c nth, it
 * returns a pointer to the \e current cell. If the end of the list is reached
 * before finding the n'th cell (i.e., if the input pointer becomes \c CONS_NIL),
 * the function returns \c CONS_NIL to indicate that the index is out of bounds.
 */
struct cons *cons_nth(struct cons *cell, size_t nth);

#ifdef __cplusplus
}
#endif

#endif /* CONS_H */
