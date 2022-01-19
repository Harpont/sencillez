/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * A series of macro attribute declarations providing
 * additional information to the compiler about the state
 * of a particular function.
 */
#ifndef ATTR_STDLIB_SENCILLEZ_GNU99C_H
#define ATTR_STDLIB_SENCILLEZ_GNU99C_H

/*
 * Instructs compiler to enforce inlining.
 */
#define always_inline __attribute__ ((always_inline))
/*
 * Instructs compiler is unused.
 */
#define unused        __attribute__ ((unused))

#endif /* ATTR_STDLIB_SENCILLEZ_GNU99C_H */
