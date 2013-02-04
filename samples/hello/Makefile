
default : all

VPATH = .

HELLO_SRC = hello.c
hello: $(HELLO_SRC:%.c=%.o)

-include $(HELLO_SRC:%.c=%.d)

%.o: %.c
	$(COMPILE.c) -MMD -o $@ $<

define _MKTARGET
x86$(1):
	[ -d x86$(1) ] || mkdir x86$(1)
	make -f ../Makefile -C x86$(1) VPATH=.. $(2) hello
arm$(1):
	[ -d arm$(1) ] || mkdir arm$(1) 
	make -f ../Makefile -C arm$(1) VPATH=.. $(2) CC=arm-linux-gcc hello
TARGETS += x86$(1) arm$(1)
endef

define MKTARGET
$(eval $(call _MKTARGET,$(1),$(2)))
endef

$(call MKTARGET,       ,CFLAGS="-g3")
$(call MKTARGET,-static,CFLAGS="-Wall" LDFLAGS="-static")
$(call MKTARGET,-dbg   ,CFLAGS="-Wall -g3")
$(call MKTARGET,-cov   ,CFLAGS="-Wall -g3 --coverage" LDFLAGS="--coverage")
$(call MKTARGET,-prof  ,CFLAGS="-Wall -g3 -pg")
#$(call MKTARGET,-instr ,CFLAGS="-Wall -fstack-protector-all -finstrument-functions" HELLO_SRC="hello.c profile.c")

.PHONY: $(TARGETS)
all: $(TARGETS)

help:
	echo Possible targets: $(TARGETS)

#hello-instr: hello.c profile.c
#         $(CC) -g3 -fstack-protector-all -finstrument-functions hello.c profile.c -o $@
#

clean:
	rm -fr $(TARGETS)

