/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include <gtest/gtest.h>

#include "paddle/fluid/inference/ascendie/convert/op_converter.h"
#include "paddle/fluid/inference/ascendie/convert/ut_helper.h"

namespace paddle {
namespace inference {
namespace ascendie {

TEST(concat_op, test) {
  std::unordered_set<std::string> parameters({""});
  framework::Scope scope;
  AscendIEConvertValidation validator(10, parameters, scope, 1000);
  int64_t shape1[3] = {10, 3, 1};
  validator.DeclInputVar("concat_x1", AscendIE::Dims(3, shape1));
  int64_t shape2[3] = {3, 3, 1};
  validator.DeclInputVar("concat_x2", AscendIE::Dims(3, shape2));
  int64_t shape3[3] = {7, 3, 1};
  validator.DeclInputVar("concat_x3", AscendIE::Dims(3, shape3));
  int64_t shape4[3] = {20, 3, 1};
  validator.DeclOutputVar("concat_out", AscendIE::Dims(3, shape4));

  // Prepare Op description
  framework::OpDesc desc;
  desc.SetType("concat");
  desc.SetInput("X", {"concat_x1", "concat_x2", "concat_x3"});
  desc.SetOutput("Out", {"concat_out"});

  int axis = 1;
  desc.SetAttr("axis", axis);

  validator.SetOp(*desc.Proto());

  validator.Execute(5);
}

}  // namespace ascendie
}  // namespace inference
}  // namespace paddle
// USE_OP(concat);
