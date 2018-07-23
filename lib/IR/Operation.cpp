//===- Operation.cpp - MLIR Operation Class -------------------------------===//
//
// Copyright 2019 The MLIR Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#include "mlir/IR/Operation.h"
#include "AttributeListStorage.h"
#include "mlir/IR/Instructions.h"
#include "mlir/IR/Statements.h"
using namespace mlir;

Operation::Operation(Identifier name, bool isInstruction,
                     ArrayRef<NamedAttribute> attrs, MLIRContext *context)
    : nameAndIsInstruction(name, isInstruction) {
  this->attrs = AttributeListStorage::get(attrs, context);

#ifndef NDEBUG
  for (auto elt : attrs)
    assert(elt.second != nullptr && "Attributes cannot have null entries");
#endif
}

Operation::~Operation() {}

/// Return the number of operands this operation has.
unsigned Operation::getNumOperands() const {
  if (auto *inst = dyn_cast<OperationInst>(this)) {
    return inst->getNumOperands();
  } else {
    auto *stmt = cast<OperationStmt>(this);
    (void)stmt;
    // TODO: Add operands to OperationStmt.
    return 0;
  }
}

SSAValue *Operation::getOperand(unsigned idx) {
  if (auto *inst = dyn_cast<OperationInst>(this)) {
    return inst->getOperand(idx);
  } else {
    auto *stmt = cast<OperationStmt>(this);
    (void)stmt;
    // TODO: Add operands to OperationStmt.
    abort();
  }
}

void Operation::setOperand(unsigned idx, SSAValue *value) {
  if (auto *inst = dyn_cast<OperationInst>(this)) {
    inst->setOperand(idx, cast<CFGValue>(value));
  } else {
    auto *stmt = cast<OperationStmt>(this);
    (void)stmt;
    // TODO: Add operands to OperationStmt.
    abort();
  }
}

/// Return the number of results this operation has.
unsigned Operation::getNumResults() const {
  if (auto *inst = dyn_cast<OperationInst>(this)) {
    return inst->getNumResults();
  } else {
    auto *stmt = cast<OperationStmt>(this);
    (void)stmt;
    // TODO: Add results to OperationStmt.
    return 0;
  }
}

/// Return the indicated result.
SSAValue *Operation::getResult(unsigned idx) {
  if (auto *inst = dyn_cast<OperationInst>(this)) {
    return inst->getResult(idx);
  } else {
    auto *stmt = cast<OperationStmt>(this);
    (void)stmt;
    // TODO: Add operands to OperationStmt.
    abort();
  }
}

ArrayRef<NamedAttribute> Operation::getAttrs() const {
  if (!attrs)
    return {};
  return attrs->getElements();
}

/// If an attribute exists with the specified name, change it to the new
/// value.  Otherwise, add a new attribute with the specified name/value.
void Operation::setAttr(Identifier name, Attribute *value,
                        MLIRContext *context) {
  assert(value && "attributes may never be null");
  auto origAttrs = getAttrs();

  SmallVector<NamedAttribute, 8> newAttrs(origAttrs.begin(), origAttrs.end());

  // If we already have this attribute, replace it.
  for (auto &elt : newAttrs)
    if (elt.first == name) {
      elt.second = value;
      attrs = AttributeListStorage::get(newAttrs, context);
      return;
    }

  // Otherwise, add it.
  newAttrs.push_back({name, value});
  attrs = AttributeListStorage::get(newAttrs, context);
}

/// Remove the attribute with the specified name if it exists.  The return
/// value indicates whether the attribute was present or not.
auto Operation::removeAttr(Identifier name, MLIRContext *context)
    -> RemoveResult {
  auto origAttrs = getAttrs();
  for (unsigned i = 0, e = origAttrs.size(); i != e; ++i) {
    if (origAttrs[i].first == name) {
      SmallVector<NamedAttribute, 8> newAttrs;
      newAttrs.reserve(origAttrs.size() - 1);
      newAttrs.append(origAttrs.begin(), origAttrs.begin() + i);
      newAttrs.append(origAttrs.begin() + i + 1, origAttrs.end());
      attrs = AttributeListStorage::get(newAttrs, context);
      return RemoveResult::Removed;
    }
  }
  return RemoveResult::NotFound;
}