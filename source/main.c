/*
 * MIT License
 *
 * main.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *        (c) 2022 Harpont, Inc. All rights reserved.
 *
 * The start point for the static analyzer program.
 */
#include "parse.h"

int main(void)
{
  parse("examples/example.in.c");
  return 0;
}
