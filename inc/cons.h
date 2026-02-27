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

#define CONS(_car, _cdr) ((struct cons){.car = (_car), .cdr = (_cdr)})

/*!
 * The structure is recursive; it does not need a forward declaration.
 *
 * The car field can hold any type of data, and the cdr field points to the next
 * cons cell in the list. This allows us to create linked lists of arbitrary
 * length.
 */
struct cons {
  void *car;
  struct cons *cdr;
};

static inline void *cons_car(const struct cons *cell) { return cell->car; }

static inline struct cons *cons_cdr(const struct cons *cell) { return cell->cdr; }

static inline void cons_rplaca(struct cons *cell, void *car) { cell->car = car; }

static inline void cons_rplacd(struct cons *cell, struct cons *cdr) { cell->cdr = cdr; }

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
