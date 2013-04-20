
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// Modified to split off from boost.

#ifndef BOOST_CONTEXT_FCONTEXT_H
#define BOOST_CONTEXT_FCONTEXT_H

namespace io {

extern "C"
intptr_t
jump_fcontext(
  fcontext_t* ofc,
  fcontext_t const* nfc,
  intptr_t vp,
  bool preserve_fpu = true
  );

extern "C"
fcontext_t*
make_fcontext(
  void * sp,
  std::size_t size,
  void (* fn)( intptr_t)
  );

} // namespace io

#endif // BOOST_CONTEXT_FCONTEXT_H
