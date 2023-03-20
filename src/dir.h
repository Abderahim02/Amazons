#ifndef _AMAZON_DIR_H_
#define _AMAZON_DIR_H_

// The concrete dirs are listed from FIRST_DIR to LAST_DIR
// The first dir is 0, thus allowing a graph without edges
// to be filled with zeroes
enum dir_t {
  NO_DIR=0,
  DIR_NORTH=1, DIR_NE=2,
  DIR_WEST=3,  DIR_SE=4,
  DIR_SOUTH=5, DIR_SW=6,
  DIR_EAST=7,  DIR_NW=8,
  FIRST_DIR=DIR_NORTH, LAST_DIR=DIR_NW,
  NUM_DIRS=8,
  DIR_ERROR
};

#endif // _AMAZON_DIR_H_
