CC_SRCS := \
	src/io/driver.cc

ASM_SRCS := \
	src/io/jump_x86_64_sysv_elf_gas.S \
	src/io/make_x86_64_sysv_elf_gas.S \

OBJS := $(CC_SRCS:.cc=.o)
OBJS += $(ASM_SRCS:.S=.o)

CXX_FLAGS := -std=gnu++0x -c -g -O0 -I src/ -fpic

# include header dependency rules
-include $(OBJS:.o=.d)

all: libio.a

libio.a: $(OBJS)
	ar rsc libio.a $(OBJS)

%.o: %.cc
	@g++ $(CXX_FLAGS) -MMD -o $(@) $(<) 
	g++ $(CXX_FLAGS) -o $(@) $(<) 

%.E: %.cc
	g++ $(CXX_FLAGS) -E -o $(@) $(<) 

src/io/jump_x86_64_sysv_elf_gas.o: src/io/jump_x86_64_sysv_elf_gas.S
src/io/make_x86_64_sysv_elf_gas.o: src/io/make_x86_64_sysv_elf_gas.S
	as -g -o $(@) $(<)

.PHONY: clean cleandep
clean: cleandep
	find src/ -name \*.o -delete

cleandep:
	find src/ -name \*.d -delete
