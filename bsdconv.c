#include <ruby.h>
#include <bsdconv.h>

void Init_bsdconv();
VALUE method_create(VALUE);
VALUE method_conv(VALUE, VALUE);

VALUE Bsdconv = Qnil;

void Init_bsdconv(){
	Bsdconv = rb_define_class("bsdconv", rb_cObject);
	rb_define_method(Bsdconv, "initialize", method_create, 1);
	rb_define_method(Bsdconv, "conv", method_conv, 1);
}

VALUE method_create(VALUE conversion){
	struct bsdconv_instance *ins;
	ins=bsdconv_create(RSTRING(conversion)->ptr);
	return Data_Wrap_Struct(Bsdconv, 0, bsdconv_destroy, ins);
}

VALUE method_conv(VALUE self, VALUE str){
	struct bsdconv_instance *ins;
	Data_Get_Struct(self, struct bsdconv_instance, ins);
	bsdconv_init(ins);
	ins->output_mode=BSDCONV_AUTOMALLOC;
	ins->input.data=RSTRING(str)->ptr;
	ins->input.len=RSTRING(str)->len;
	ins->input.flags=0;
	ins->flush=1;
	bsdconv(ins);
	return rb_str_new(ins->output.data, ins->output.len);
}