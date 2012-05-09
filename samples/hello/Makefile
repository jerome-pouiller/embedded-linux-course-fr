
default : all

VPATH = .

HELLO_SRC = hello.c
hello: $(HELLO_SRC:%.c=%.o)

-include $(HELLO_SRC:%.c=%.d)

%.d: %.c
	$(CC) $(CFLAGS) -w -MM -MF $@ $<
	sed -i -e 's,\($*\.o\) *:,\1 $@ :,g' $@

define MKTARGET
x86$(1):
	[ -d x86$(1) ] || mkdir x86$(1)
	make -f ../Makefile -C x86$(1)        VPATH=.. $(2) hello

arm$(1):
	[ -d arm$(1) ] || mkdir arm$(1) 
	make -f ../Makefile -C arm$(1)        VPATH=.. $(2) CC=arm-linux-gcc hello
TARGETS += x86$(1) arm$(1)
endef

$(call MKTARGET,,"CFLAGS=-Wall")
$(call MKTARGET,-static,"CFLAGS=-Wall" "LDFLAGS=-static")
$(call MKTARGET,-dbg,"CFLAGS=-Wall -g3")
$(call MKTARGET,-cov,"CFLAGS=-Wall -g3 --coverage" "LDFLAGS=--coverage")
$(call MKTARGET,-prof,"CFLAGS=-Wall -g3 -pg")

.PHONY: $(TARGETS)
all: $(TARGETS)

#
#x86:
#	[ -d x86 ] || mkdir x86
#	make -f ../Makefile -C x86        VPATH=.. "CFLAGS=-Wall" hello
#
#arm:
#	[ -d arm ] || mkdir arm 
#	make -f ../Makefile -C arm        VPATH=.. "CFLAGS=-Wall" CC=arm-linux-gcc hello
#
#x86-static:
#	[ -d x86-static ] || mkdir x86-static
#	make -f ../Makefile -C x86-static VPATH=.. "CFLAGS=-Wall" LDFLAGS="-static" hello
#
#arm-static:
#	[ -d arm-static ] || mkdir arm-static
#	make -f ../Makefile -C arm-static VPATH=.. "CFLAGS=-Wall" LDFLAGS="-static" C=arm-linux-gcc hello
#
#x86-dbg:
#	[ -d x86-dbg ] || mkdir x86-dbg
#	make -f ../Makefile -C x86-dbg    VPATH=.. "CFLAGS=-Wall -ggdb" hello
#
#arm-dbg:
#	[ -d arm-dbg ] || mkdir arm-dbg
#	make -f ../Makefile -C arm-dbg    VPATH=.. "CFLAGS=-Wall -ggdb" CC=arm-linux-gcc hello
#
#x86-cov:
#	[ -d x86-cov ] || mkdir x86-cov
#	make -f ../Makefile -C x86-cov    VPATH=.. "CFLAGS=-Wall -g3 --coverage" "LDFLAGS=--coverage" hello
#
#arm-cov:
#	[ -d arm-cov ] || mkdir arm-cov
#	make -f ../Makefile -C arm-cov    VPATH=.. "CFLAGS=-Wall -g3 --coverage" "LDFLAGS=--coverage" CC=arm-linux-gcc hello
#
#x86-prof:
#	[ -d x86-prof ] || mkdir x86-prof
#	make -f ../Makefile -C x86-prof   VPATH=.. "CFLAGS=-Wall -pg" hello
#
#arm-prof:
#	[ -d arm-prof ] || mkdir arm-prof
#	make -f ../Makefile -C arm-prof   VPATH=.. "CFLAGS=-Wall -pg" CC=arm-linux-gcc hello
#
#hello-cov: hello.c
#        $(CC) -g3 --coverage $< -o $@
#
#hello-prof: hello.c
#        $(CC) -g3 -pg $< -o $@
#
#hello-instr: hello.c profile.c
#         $(CC) -g3 -fstack-protector-all -finstrument-functions hello.c profile.c -o $@
#
clean:
	rm -r $(TARGETS)

