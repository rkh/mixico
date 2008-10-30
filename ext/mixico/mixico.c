//
// mixico.c
// an extension for enabling and disabling mixins
//
// released under an MIT license
//
#include <ruby.h>

static VALUE mixin_eval, mixout_eval;

static VALUE
rb_mod_disable_mixin(VALUE module, VALUE super)
{
  VALUE p, kid;

  Check_Type(super, T_MODULE);
  for (kid = module, p = RCLASS(module)->super; p; kid = p, p = RCLASS(p)->super) {
    if (BUILTIN_TYPE(p) == T_ICLASS) {
      if (RBASIC(p)->klass == super) {
        RCLASS(kid)->super = RCLASS(p)->super;
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
  Check_Type(RBASIC(mixin)->klass, T_MODULE);
  for (p = module; p; p = RCLASS(p)->super) {
    if (RCLASS(p)->super == RCLASS(mixin)->super) {
      RCLASS(p)->super = mixin;
      rb_clear_cache_by_class(module);
      return RBASIC(mixin)->klass;
    }
  }

  return Qnil;
}

static VALUE
rb_mod_mixin_object(VALUE target, VALUE obj)
{
  VALUE singleton = rb_singleton_class(obj);
  NEWOBJ(iclass, struct RClass);
  OBJSETUP(iclass, rb_cClass, T_ICLASS);

  Check_Type(target, T_MODULE);
  if (!ROBJECT(obj)->iv_tbl)
    ROBJECT(obj)->iv_tbl = st_init_numtable();

  iclass->iv_tbl = ROBJECT(obj)->iv_tbl;
  iclass->m_tbl = RCLASS(singleton)->m_tbl;
  iclass->super = RCLASS(target)->super;
  RBASIC(iclass)->klass = singleton;

  OBJ_INFECT(iclass, obj);
  OBJ_INFECT(iclass, target);
  RCLASS(target)->super = iclass;
  rb_clear_cache_by_class(target);

  return Qnil;
}

void Init_mixico()
{
  rb_define_method(rb_cModule, "disable_mixin", rb_mod_disable_mixin, 1);
  rb_define_method(rb_cModule, "enable_mixin", rb_mod_enable_mixin, 1);
  rb_define_method(rb_cModule, "mixin_an_object", rb_mod_mixin_object, 1);

  rb_eval_string(
    "class Proc\n" \
    "  def includes_mixin? mod\n" \
    "    (class << binding.eval('self'); self end).include? mod\n" \
    "  end\n" \
    "  def mixin mod\n" \
    "    binding.eval('self').extend mod\n" \
    "  end\n" \
    "  def mixout mod\n" \
    "    (class << binding.eval('self'); self end).disable_mixin mod\n" \
    "  end\n" \
    "end\n" \
    "\n" \
    "class Module\n" \
    "  def mix_eval mod, &blk\n" \
    "    if blk.includes_mixin? mod\n" \
    "      blk.call\n" \
    "    else\n" \
    "      blk.mixin mod\n" \
    "      begin\n" \
    "        blk.call\n" \
    "      ensure\n" \
    "        blk.mixout mod\n" \
    "      end\n" \
    "    end\n" \
    "  end\n" \
    "end\n" \
  );
}
