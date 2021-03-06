/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "flashlight/pkg/speech/criterion/CriterionUtils.h"

#include "flashlight/pkg/runtime/common/DistributedUtils.h"
#include "flashlight/lib/sequence/criterion/cpu/CriterionUtils.h"
#include "flashlight/lib/sequence/criterion/cpu/ViterbiPath.h"

using CriterionUtils = fl::lib::cpu::CriterionUtils<float>;
using ViterbiPath = fl::lib::cpu::ViterbiPath<float>;

namespace fl {
namespace pkg {
namespace speech {

af::array viterbiPath(const af::array& input, const af::array& trans) {
  auto B = input.dims(2);
  auto T = input.dims(1);
  auto N = input.dims(0);

  if (N != trans.dims(0) || N != trans.dims(1)) {
    throw std::invalid_argument("viterbiPath: mismatched dims");
  } else if (input.type() != f32) {
    throw std::invalid_argument("viterbiPath: input must be float32");
  } else if (trans.type() != f32) {
    throw std::invalid_argument("viterbiPath: trans must be float32");
  }

  auto inputVec = fl::pkg::runtime::afToVector<float>(input);
  auto transVec = fl::pkg::runtime::afToVector<float>(trans);
  std::vector<int> pathVec(B * T);
  std::vector<uint8_t> workspaceVec(ViterbiPath::getWorkspaceSize(B, T, N));

  ViterbiPath::compute(
      B,
      T,
      N,
      inputVec.data(),
      transVec.data(),
      pathVec.data(),
      workspaceVec.data());

  return af::array(T, B, pathVec.data());
}

af::array getTargetSizeArray(const af::array& target, int maxSize) {
  int B = target.dims(1);
  int L = target.dims(0);

  auto targetVec = fl::pkg::runtime::afToVector<int>(target);
  std::vector<int> targetSizeVec(B);

  CriterionUtils::batchTargetSize(
      B, L, maxSize, targetVec.data(), targetSizeVec.data());

  return af::array(B, targetSizeVec.data());
}
} // namespace speech
} // namespace pkg
} // namespace fl
