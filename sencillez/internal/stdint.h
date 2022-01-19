/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Define a series of basic or normal integer segments for usage
 * when it is necessary to use a base type.
 *
 * NOTE: These normal integer types are only to be used internally.
 * It is imperative that this code base does not deviate from the
 * implementation of the standard C libraries but is an extension.
 */
#ifndef STDINT_SENCILLEZ_GNU99C_H
#define STDINT_SENCILLEZ_GNU99C_H

#include <bits/wordsize.h>

typedef char      stdint8_t;
typedef short     stdint16_t;
typedef int       stdint32_t;
#if __WORDSIZE == 64
typedef long      stdint64_t;
#else
__extension__
typedef long long stdint64_t;
#endif

#endif /* STDINT_SENCILLEZ_GNU99C_H */
