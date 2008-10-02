//
// mixico.c
// an extension for enabling and disabling mixins
//
// released under an MIT license
//
#include <ruby.h>

static VALUE
rb_mod_disable_mixin(VALUE module, VALUE super)
{
  VALUE p, kid;

  Check_Type(super, T_MODULE);
  for (kid = module, p = RCLASS(module)->super; p; kid = p, p = RCLASS(p)->super) {
    if (BUILTIN_TYPE(p) == T_ICLASS) {
      if (RBASIC(p)->klass == super) {
        RCLASS(kid)->super = RCLASS(p)->super;
        return p;
      }
    }
  }

  return Qnil;
}

static VALUE
rb_mod_enable_mixin(VALUE module, VALUE mixin)
{
  VALUE p;

  Check_Type(mixin, T_ICLASS);
  Check_Type(RBASIC(mixin)->klass, T_MODULE);
  for (p = module; p; p = RCLASS(p)->super) {
    if (RCLASS(p)->super == RCLASS(mixin)->super) {
      RCLASS(p)->super = mixin;
      return RBASIC(mixin)->klass;
    }
  }

  return Qnil;
}

void Init_mixico()
{
  rb_define_method(rb_cModule, "disable_mixin", rb_mod_disable_mixin, 1);
  rb_define_method(rb_cModule, "enable_mixin", rb_mod_enable_mixin, 1);
}
