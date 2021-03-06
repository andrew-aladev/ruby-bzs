// Ruby bindings for bzip2 library.
// Copyright (c) 2022 AUTHORS, MIT License.

#if !defined(BZS_EXT_OPTIONS_H)
#define BZS_EXT_OPTIONS_H

#include <stdbool.h>
#include <stdlib.h>

#include "ruby.h"

#define BZS_MIN_BLOCK_SIZE     1
#define BZS_MAX_BLOCK_SIZE     9
#define BZS_DEFAULT_BLOCK_SIZE BZS_MAX_BLOCK_SIZE

#define BZS_MIN_WORK_FACTOR     0
#define BZS_MAX_WORK_FACTOR     250
#define BZS_DEFAULT_WORK_FACTOR BZS_MIN_WORK_FACTOR

#define BZS_MIN_SMALL     0
#define BZS_MAX_SMALL     1
#define BZS_DEFAULT_SMALL BZS_MAX_SMALL

#define BZS_MIN_VERBOSITY     0
#define BZS_MAX_VERBOSITY     4
#define BZS_DEFAULT_VERBOSITY BZS_MIN_VERBOSITY

#define BZS_DEFAULT_QUIET 1

// Bzip2 options are integers instead of unsigned integers.
typedef int bzs_ext_option_t;

bool   bzs_ext_get_bool_option_value(VALUE options, const char* name);
size_t bzs_ext_get_size_option_value(VALUE options, const char* name);

#define BZS_EXT_GET_BOOL_OPTION(options, name) bool name = bzs_ext_get_bool_option_value(options, #name);
#define BZS_EXT_GET_SIZE_OPTION(options, name) size_t name = bzs_ext_get_size_option_value(options, #name);

bzs_ext_option_t bzs_ext_resolve_bool_option_value(VALUE options, const char* name, bzs_ext_option_t default_value);
bzs_ext_option_t bzs_ext_resolve_int_option_value(VALUE options, const char* name, bzs_ext_option_t default_value);

#define BZS_EXT_RESOLVE_BOOL_OPTION(options, name, default_value) \
  bzs_ext_option_t name = bzs_ext_resolve_bool_option_value(options, #name, default_value);
#define BZS_EXT_RESOLVE_INT_OPTION(options, name, default_value) \
  bzs_ext_option_t name = bzs_ext_resolve_int_option_value(options, #name, default_value);

#define BZS_EXT_RESOLVE_VERBOSITY_OPTION(options)                 \
  BZS_EXT_RESOLVE_BOOL_OPTION(options, quiet, BZS_DEFAULT_QUIET); \
  bzs_ext_option_t verbosity = quiet ? BZS_MIN_VERBOSITY : BZS_MAX_VERBOSITY;

#define BZS_EXT_RESOLVE_COMPRESSOR_OPTIONS(options)                          \
  BZS_EXT_RESOLVE_INT_OPTION(options, block_size, BZS_DEFAULT_BLOCK_SIZE);   \
  BZS_EXT_RESOLVE_INT_OPTION(options, work_factor, BZS_DEFAULT_WORK_FACTOR); \
  BZS_EXT_RESOLVE_VERBOSITY_OPTION(options);

#define BZS_EXT_RESOLVE_DECOMPRESSOR_OPTIONS(options)             \
  BZS_EXT_RESOLVE_BOOL_OPTION(options, small, BZS_DEFAULT_SMALL); \
  BZS_EXT_RESOLVE_VERBOSITY_OPTION(options);

void bzs_ext_option_exports(VALUE root_module);

#endif // BZS_EXT_OPTIONS_H
