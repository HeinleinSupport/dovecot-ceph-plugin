// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Copyright (c) 2017-2018 Tallence AG and the authors
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 */

#ifndef SRC_TESTS_DICT_RADOS_TESTCASE_H_
#define SRC_TESTS_DICT_RADOS_TESTCASE_H_

#include <string>

#include "rados/librados.h"
#include "rados/librados.hpp"
#include "gtest/gtest.h"

typedef struct pool *pool_t;

/**
 * These test cases create a temporary pool that lives as long as the
 * test case.  Each test within a test case gets a new ioctx and striper
 * set to a unique namespace within the pool.
 *
 * Since pool creation and deletion is slow, this allows many tests to
 * run faster.
 */
class DictTest : public ::testing::Test {
 public:
  DictTest() {}
  ~DictTest() override {}

  static pool_t get_test_pool() { return s_test_pool; }

 protected:
  static void SetUpTestCase();
  static void TearDownTestCase();

  static rados_t s_cluster;
  static rados_ioctx_t s_ioctx;

  static std::string pool_name;
  static std::string uri;
  static struct ioloop *s_test_ioloop;
  static pool_t s_test_pool;

  void SetUp() override;
  void TearDown() override;
};

#endif  // SRC_TESTS_DICT_RADOS_TESTCASE_H_
