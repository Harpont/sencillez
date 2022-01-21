/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Define the input/output operations used by the static analyzer.
 */
#ifndef IO_SENCILLEZ_H
#define IO_SENCILLEZ_H

#include <stddef.h>

int disk_write(void *fdata, char *fpath, size_t fsize);
int disk_read(void *buffer, char *fpath);

#endif /* IO_SENCILLEZ_H */
