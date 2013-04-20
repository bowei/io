CC_SRCS := \
	src/io/driver.cc

ASM_SRCS := \
	src/io/jump_x86_64_sysv_elf_gas.S \
	src/io/make_x86_64_sysv_elf_gas.S \

OBJS := $(CC_SRCS:.cc=.o)
OBJS += $(ASM_SRCS:.S=.o)

CXX_FLAGS := -std=gnu++0x -g -O0 -I src/ -fpic -L.

UNIT_TESTS := \
 	src/io/fcontext_test

#-----------------------------------------------------------------------------
all: libio.a $(UNIT_TESTS)

# include header dependency rules
-include $(OBJS:.o=.d)

libio.a: $(OBJS)
	ar rsc libio.a $(OBJS)

%.o: %.cc
	@g++ $(CXX_FLAGS) -c -MMD -o $(@) $(<)
	g++ $(CXX_FLAGS) -c -o $(@) $(<)

%.E: %.cc
	g++ $(CXX_FLAGS) -c -E -o $(@) $(<)

src/io/jump_x86_64_sysv_elf_gas.o: src/io/jump_x86_64_sysv_elf_gas.S
src/io/make_x86_64_sysv_elf_gas.o: src/io/make_x86_64_sysv_elf_gas.S
	as -g -o $(@) $(<)

src/io/fcontext_test: src/io/fcontext_test.cc
	g++ $(CXX_FLAGS) $(<) -o $(@) -lio

.PHONY: clean cleandep
clean: cleandep
	find src/ -name \*.o -delete
	rm -f $(UNIT_TESTS)

cleandep:
	find src/ -name \*.d -delete
