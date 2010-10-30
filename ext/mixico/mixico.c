//
// mixico.c
// an extension for enabling and disabling mixins
//
// released under an MIT license
//
#include <ruby.h>
#include "compat.h"

static VALUE mixin_eval, mixout_eval;

static VALUE
rb_mod_disable_mixin(VALUE module, VALUE super)
{
  VALUE p, kid;

  Check_Type(super, T_MODULE);
  for (kid = module, p = RCLASS_SUPER(module); p; kid = p, p = RCLASS_SUPER(p)) {
    if (BUILTIN_TYPE(p) == T_ICLASS) {
      if (KLASS_OF(p) == super) {
        RCLASS_SUPER(kid) = RCLASS_SUPER(p);
        rb_clear_cache_by_class(module);
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
  Check_Type(KLASS_OF(mixin), T_MODULE);
  for (p = module; p; p = RCLASS_SUPER(p)) {
    if (RCLASS_SUPER(p) == RCLASS_SUPER(mixin)) {
      RCLASS_SUPER(p) = mixin;
      rb_clear_cache_by_class(module);
      return KLASS_OF(mixin);
    }
  }

  return Qnil;
}

static VALUE
rb_mod_mixin_object(VALUE target, VALUE obj)
{
  VALUE singleton = rb_singleton_class(obj);
  VALUE iclass = create_class(T_ICLASS, rb_cClass);

  Check_Type(target, T_MODULE);
  if (!RCLASS_IV_TBL(obj))
    RCLASS_IV_TBL(obj) = st_init_numtable();

  RCLASS_IV_TBL(iclass) = RCLASS_IV_TBL(obj);
  RCLASS_M_TBL(iclass) = RCLASS_M_TBL(singleton);
  RCLASS_SUPER(iclass) = RCLASS_SUPER(target);
  KLASS_OF(iclass) = singleton;

  OBJ_INFECT(iclass, obj);
  OBJ_INFECT(iclass, target);
  RCLASS_SUPER(target) = (VALUE)iclass;
  rb_clear_cache_by_class(target);

  return Qnil;
}

void Init_mixico()
{
  rb_define_method(rb_cModule, "disable_mixin", rb_mod_disable_mixin, 1);
  rb_define_method(rb_cModule, "enable_mixin", rb_mod_enable_mixin, 1);
  rb_define_method(rb_cModule, "mixin_an_object", rb_mod_mixin_object, 1);
}
