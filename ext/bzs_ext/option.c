// Ruby bindings for bzip2 library.
// Copyright (c) 2022 AUTHORS, MIT License.

#include "bzs_ext/option.h"

#include "bzs_ext/error.h"

// -- values --

static inline VALUE get_raw_value(VALUE options, const char* name)
{
  return rb_funcall(options, rb_intern("[]"), 1, ID2SYM(rb_intern(name)));
}

// -- getters --

static inline bool get_bool_value(VALUE raw_value)
{
  int raw_type = TYPE(raw_value);
  if (raw_type != T_TRUE && raw_type != T_FALSE) {
    bzs_ext_raise_error(BZS_EXT_ERROR_VALIDATE_FAILED);
  }

  return raw_type == T_TRUE;
}

static inline int get_int_value(VALUE raw_value)
{
  Check_Type(raw_value, T_FIXNUM);

  return NUM2INT(raw_value);
}

static inline size_t get_size_value(VALUE raw_value)
{
  Check_Type(raw_value, T_FIXNUM);

  return NUM2SIZET(raw_value);
}

bool bzs_ext_get_bool_option_value(VALUE options, const char* name)
{
  VALUE raw_value = get_raw_value(options, name);

  return get_bool_value(raw_value);
}

size_t bzs_ext_get_size_option_value(VALUE options, const char* name)
{
  VALUE raw_value = get_raw_value(options, name);

  return get_size_value(raw_value);
}

// -- resolves --

bzs_ext_option_t bzs_ext_resolve_bool_option_value(VALUE options, const char* name, bzs_ext_option_t default_value)
{
  VALUE raw_value = get_raw_value(options, name);
  if (raw_value != Qnil) {
    return get_bool_value(raw_value);
  } else {
    return default_value;
  }
}

bzs_ext_option_t bzs_ext_resolve_int_option_value(VALUE options, const char* name, bzs_ext_option_t default_value)
{
  VALUE raw_value = get_raw_value(options, name);
  if (raw_value != Qnil) {
    return get_int_value(raw_value);
  } else {
    return default_value;
  }
}

// -- others --

void bzs_ext_option_exports(VALUE root_module)
{
  VALUE module = rb_define_module_under(root_module, "Option");

  rb_define_const(module, "MIN_BLOCK_SIZE", SIZET2NUM(BZS_MIN_BLOCK_SIZE));
  rb_define_const(module, "MAX_BLOCK_SIZE", SIZET2NUM(BZS_MAX_BLOCK_SIZE));
  rb_define_const(module, "DEFAULT_BLOCK_SIZE", SIZET2NUM(BZS_DEFAULT_BLOCK_SIZE));

  rb_define_const(module, "MIN_WORK_FACTOR", SIZET2NUM(BZS_MIN_WORK_FACTOR));
  rb_define_const(module, "MAX_WORK_FACTOR", SIZET2NUM(BZS_MAX_WORK_FACTOR));
  rb_define_const(module, "DEFAULT_WORK_FACTOR", SIZET2NUM(BZS_DEFAULT_WORK_FACTOR));

  rb_define_const(module, "MIN_SMALL", SIZET2NUM(BZS_MIN_SMALL));
  rb_define_const(module, "MAX_SMALL", SIZET2NUM(BZS_MAX_SMALL));
  rb_define_const(module, "DEFAULT_SMALL", SIZET2NUM(BZS_DEFAULT_SMALL));

  rb_define_const(module, "MIN_VERBOSITY", SIZET2NUM(BZS_MIN_VERBOSITY));
  rb_define_const(module, "MAX_VERBOSITY", SIZET2NUM(BZS_MAX_VERBOSITY));
  rb_define_const(module, "DEFAULT_VERBOSITY", SIZET2NUM(BZS_DEFAULT_VERBOSITY));
}
