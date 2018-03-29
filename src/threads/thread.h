#ifndef THREADS_THREAD_H
#define THREADS_THREAD_H

#include <debug.h>
#include <list.h>
#include <stdint.h>
#include "synch.h"
#include "threads/fixed-point.h"

/* States in a thread's life cycle. */
enum thread_status
  {
    THREAD_RUNNING,     /* Running thread. */
    THREAD_READY,       /* Not running but ready to run. */
    THREAD_BLOCKED,     /* Waiting for an event to trigger. */
    THREAD_DYING        /* About to be destroyed. */
  };

/* Thread identifier type.
   You can redefine this to whatever type you like. */
typedef int tid_t;
#define TID_ERROR ((tid_t) -1)          /* Error value for tid_t. */

/* Thread priorities. */
#define PRI_MIN 0                       /* Lowest priority. */
#define PRI_DEFAULT 31                  /* Default priority. */
#define PRI_MAX 63                      /* Highest priority. */
#define PRI_DONATION_MAX_DEPTH 8        /* Highest priority. */


/* A kernel thread or user process.

   Each thread structure is stored in its own 4 kB page.  The
   thread structure itself sits at the very bottom of the page
   (at offset 0).  The rest of the page is reserved for the
   thread's kernel stack, which grows downward from the top of
   the page (at offset 4 kB).  Here's an illustration:

        4 kB +---------------------------------+
             |          kernel stack           |
             |                |                |
             |                |                |
             |                V                |
             |         grows downward          |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             +---------------------------------+
             |              magic              |
             |                :                |
             |                :                |
             |               name              |
             |              status             |
        0 kB +---------------------------------+

   The upshot of this is twofold:

      1. First, `struct thread' must not be allowed to grow too
         big.  If it does, then there will not be enough room for
         the kernel stack.  Our base `struct thread' is only a
         few bytes in size.  It probably should stay well under 1
         kB.

      2. Second, kernel stacks must not be allowed to grow too
         large.  If a stack overflows, it will corrupt the thread
         state.  Thus, kernel functions should not allocate large
         structures or arrays as non-static local variables.  Use
         dynamic allocation with malloc() or palloc_get_page()
         instead.

   The first symptom of either of these problems will probably be
   an assertion failure in thread_current(), which checks that
   the `magic' member of the running thread's `struct thread' is
   set to THREAD_MAGIC.  Stack overflow will normally change this
   value, triggering the assertion. */
/* The `elem' member has a dual purpose.  It can be an element in
   the run queue (thread.c), or it can be an element in a
   semaphore wait list (synch.c).  It can be used these two ways
   only because they are mutually exclusive: only a thread in the
   ready state is on the run queue, whereas only a thread in the
   blocked state is on a semaphore wait list. */
struct thread
  {
    /* Owned by thread.c. */
    tid_t tid;                          /* Thread identifier. */
    enum thread_status status;          /* Thread state. */
    char name[16];                      /* Name (for debugging purposes). */
    uint8_t *stack;                     /* Saved stack pointer. */
    int priority;                       /* Priority, may be updated later */
    int InitialPriority;		/* Priority given at the beginning*/

    struct list_elem allelem;           /* List element for all threads list. */

    struct list locks;			/*Task1.2, list of locks held by current thread*/
    struct lock *LockWaitOn;   		/*Task1.2, The lock current thread is waiting on*/


    int64_t WakeupTime;			/* wakeup time*/

    /* Shared between thread.c and synch.c. */
    struct list_elem elem;              /* List element. */

    /*  advanced scheduler  */
    int nice;                           /* Task1.3,  nice value   */
    fixed_t recent_cpu;                 /* Task1.3,  recent_cpu  */

#ifdef USERPROG
    /* Owned by userprog/process.c. */
    uint32_t *pagedir;                  /* Page directory. */
#endif

    /* Owned by thread.c. */
    unsigned magic;                     /* Detects stack overflow. */
  };

/* If false (default), use round-robin scheduler.
   If true, use multi-level feedback queue scheduler.
   Controlled by kernel command-line option "-o mlfqs". */
extern bool thread_mlfqs;

void thread_init (void);
void thread_start (void);

void thread_tick (void);
void thread_print_stats (void);

typedef void thread_func (void *aux);
tid_t thread_create (const char *name, int priority, thread_func *, void *);

void thread_block (void);
void thread_unblock (struct thread *);

struct thread *thread_current (void);
tid_t thread_tid (void);
const char *thread_name (void);

void thread_exit (void) NO_RETURN;
void thread_yield (void);

/* Performs some operation on thread t, given auxiliary data AUX. */
typedef void thread_action_func (struct thread *t, void *aux);
void thread_foreach (thread_action_func *, void *);

int thread_get_priority (void);
void thread_set_priority (int);

int thread_get_nice (void);
void thread_set_nice (int);
int thread_get_recent_cpu (void);
int thread_get_load_avg (void);

/* check whether there exist priority donation when a thread is waiting on a lock*/
void check_priority_donation(struct thread *t, struct lock *lock);

/* update thread attributes when a thread hold a new lock*/
void thread_update_new_lock(struct thread *t, struct lock *lock);

/* update thread attributes when a thread delete a lock*/
void thread_delete_new_lock(struct thread *t, struct lock *lock);

/*update thread priority if there is change in lock list*/
void thread_update_priority_from_locks(struct thread *t);

/* check the change of current thread's priority to see if preemption is necessary*/
void thread_check_preemption();


/* Comparator of two threads' wakeup time when being ordered in a list*/
bool thread_wakeuptime_comparator(const struct list_elem *e1, const struct list_elem *e2, void *aux);

/* Comparator of two threads' priority when being ordered in a list*/
bool thread_priority_comparator(const struct list_elem *e1, const struct list_elem *e2, void *aux);

/* Every timer tick, recent_cpu is incremented by 1 for the running thread */
void thread_update_recent_cpu();

/* Every 4th tick, Priority is recalculated for each thread. Need foreach this function when excuting */
void thread_update_priority_each(struct thread *t);

/* Every second, recent cpu is recalculated for each thread. Need foreach this function when excuting*/
void thread_update_recent_cpu_each(struct thread *t, void *aux);

/* Every second, load_avg is recalculated*/
void scheduler_update_load_avg();

#endif /* threads/thread.h */
