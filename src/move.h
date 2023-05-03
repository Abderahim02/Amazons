#ifndef _AMAZON_MOVE_H_
#define _AMAZON_MOVE_H_

#include <stddef.h>

struct move_t {
  unsigned int queen_src; // The id of the cell from where the queen moved
  unsigned int queen_dst; // The id of the cell where the queen moved to
  unsigned int arrow_dst; // The id of the cell where the arrow fell
};

struct moves_t {
  struct move_t* t;
  unsigned int current;
};

#endif // _AMAZON_MOVE_H_
