//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// Modified slightly to separate from boost.
#ifndef BOOST_CONTEXT_DETAIL_FCONTEXT_X86_64_H
#define BOOST_CONTEXT_DETAIL_FCONTEXT_X86_64_H

#include <cstddef>
#include <stdint.h>

namespace io {

extern "C" {

struct stack_t
{
  void* sp;
  std::size_t size;

  stack_t() : sp(0), size(0) {}
};

struct fp_t
{
  uint32_t fc_freg[2];

  fp_t() : fc_freg() {}
};

struct fcontext_t
{
  uint64_t fc_greg[8];
  stack_t fc_stack;
  fp_t fc_fp;

  fcontext_t() : fc_greg(), fc_stack(), fc_fp() {}
};

} // extern "C"

} // namespace io

#endif // BOOST_CONTEXT_DETAIL_FCONTEXT_X86_64_H
