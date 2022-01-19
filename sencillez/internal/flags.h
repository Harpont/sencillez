/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * An array of macro arguments set by the compiler, conditioning
 * this library of the usage or non-usage of standard C convetions.
 *
 * NOTE: Currently there is only one method of enabling and
 * disabling this library at compile time. However, in the future
 * additional methods will be added to this library to determine
 * when code is compiled conventionally and when unconventionally.
 */
#ifndef FLAGS_STDLIB_SENCILLEZ_GNU99C_H
#define FLAGS_STDLIB_SENCILLEZ_GNU99C_H

/*
 * Check for the `unconventional` macro
 * argument set by the compiler.
 */
#ifndef UNCONVENTIONAL
/*
 * Check whether or not debugging is enabled
 * by the compiler. If so, turn on additional
 * C validation conventions.
 */
#ifdef  STRICT
#define ENABLED_STRICT_SIMPLICITY
#endif
/*
 * As long as code is conventional. Turn on
 * non-debugging C standard conventions.
 */
#define ENABLED_SIMPLICITY
#endif

#endif /* FLAGS_STDLIB_SENCILLEZ_GNU99C_H */
