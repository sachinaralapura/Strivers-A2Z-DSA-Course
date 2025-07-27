// Given a square matrix mat[][] of size n x n, such that mat[i][j] = 1 means ith person knows jth person, the task is
// to find the celebrity. A celebrity is a person who is known to all but does not know anyone. Return the index of the
// celebrity, if there is no celebrity return -1.
#ifndef CELEBRITY_PROBLEM
#define CELEBRITY_PROBLEM
#include "../../00-common/common.h"

using namespace common;

int celebrity(Matrix);
int celebrityOpt(Matrix);

#endif
