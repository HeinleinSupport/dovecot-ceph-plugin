/* Copyright (c) 2017 Tallence AG and the authors, see the included COPYING file */

#ifndef SRC_LIBRMB_RADOS_STORAGE_H_
#define SRC_LIBRMB_RADOS_STORAGE_H_

#include <list>
#include <string>
#include <cstdint>

#include <rados/librados.hpp>
#include "rados-mail-object.h"

namespace librmb {

class RadosStorage {
 public:
  RadosStorage(librados::IoCtx* ctx, const int max_write_size);
  virtual ~RadosStorage();

  librados::IoCtx& get_io_ctx() { return io_ctx; }

  const int get_max_write_size() const { return max_write_size; }
  const int get_max_write_size_bytes() const { return max_write_size * 1024 * 1024; }

  int split_buffer_and_exec_op(const char *buffer, size_t buffer_length, RadosMailObject *current_object,
                               librados::ObjectWriteOperation *write_op_xattr, uint64_t max_write);

 private:
  librados::IoCtx io_ctx;
  int max_write_size;
};

}  // namespace librmb

#endif  // SRC_LIBRMB_RADOS_STORAGE_H_
