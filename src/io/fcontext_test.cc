#include <iostream>
#include <cstdlib>
#include "io/fcontext.h"

namespace {

io::fcontext_t* ctx_main;
io::fcontext_t* ctx1;
io::fcontext_t* ctx2;

int count = 0;

void FcnA(intptr_t) {
  for (int i=0; i<10; ++i) {
    std::cout << "hello from A" << std::endl;
    ++count;
    io::jump_fcontext(ctx1, ctx2, 0);
  }

  io::jump_fcontext(ctx1, ctx_main, 0);
}

void FcnB(intptr_t) {
  for (int i=0; i<10; ++i) {
    std::cout << "hello from B" << std::endl;
    ++count;
    io::jump_fcontext(ctx2, ctx1, 0);
  }
}

} // namespace

int
main(int argc, char* argv[])
{
  printf("hello\n");

  const size_t stack_size = 32*1024;

  char* stack;

  stack = static_cast<char*>(malloc(stack_size));
  ctx_main = io::make_fcontext(stack + stack_size, stack_size, FcnA);

  stack = static_cast<char*>(malloc(stack_size));
  ctx1 = io::make_fcontext(stack + stack_size, stack_size, FcnA);

  stack = static_cast<char*>(malloc(stack_size));
  ctx2 = io::make_fcontext(stack + stack_size, stack_size, FcnB);

  io::jump_fcontext(ctx_main, ctx1, 0);

  std::cout << "count " << count << std::endl;

  return 0;
}
