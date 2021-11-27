//===- PassDetails.h - polygeist pass class details ----------------*- C++
//-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Stuff shared between the different polygeist passes.
//
//===----------------------------------------------------------------------===//

// clang-tidy seems to expect the absolute path in the header guard on some
// systems, so just disable it.
// NOLINTNEXTLINE(llvm-header-guard)
#ifndef DIALECT_POLYGEIST_TRANSFORMS_PASSDETAILS_H
#define DIALECT_POLYGEIST_TRANSFORMS_PASSDETAILS_H

#include "polygeist/Ops.h"
#include "mlir/Pass/Pass.h"
#include "polygeist/Passes/Passes.h"

namespace mlir {
namespace polygeist {

#define GEN_PASS_CLASSES
#include "polygeist/Passes/Passes.h.inc"

} // namespace polygeist
}

#endif // DIALECT_POLYGEIST_TRANSFORMS_PASSDETAILS_H
