// Copyright 2022 Jonas Möller. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef INCLUDE_V8_COVERAGE_H_
#define INCLUDE_V8_COVERAGE_H_

#include <vector>

#include "v8-local-handle.h"

namespace v8 {

class Isolate;

struct BlockCoverage {
  BlockCoverage(int start, int end, uint32_t count)
      : start(start), end(end), count(count) {}

  int start;
  int end;
  uint32_t count;
};

struct FunctionCoverage : public std::vector<BlockCoverage> {
  FunctionCoverage(Local<String> name) : name(name) {}
  Local<String> name;
};

struct ScriptCoverage : public std::vector<FunctionCoverage> {
  ScriptCoverage(int id, Local<String> name) : id(id), name(name) {}
  int id;
  Local<String> name;
};

struct FastCoverageReport : public std::vector<ScriptCoverage> {};

FastCoverageReport CollectFastCoverage(Isolate* isolate);

}  // namespace v8

#endif