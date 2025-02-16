/******************************************************************************
 * Copyright (c) 2023, NKU Mobile & Flying Robotics Lab
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Jian Wen (nkuwenjian@gmail.com)
 *****************************************************************************/

#pragma once

#include "astar_planner_ros/node.h"
#include "astar_planner_ros/utils.h"

namespace astar_planner_ros {

class Node2d : public Node {
 public:
  Node2d() = default;
  Node2d(const int grid_x, const int grid_y)
      : grid_x_(grid_x), grid_y_(grid_y) {}
  ~Node2d() override = default;
  void set_g(const int g) {
    g_ = g;
    f_ = g_ + h_;
  }
  void set_h(const int h) {
    h_ = h;
    f_ = g_ + h_;
  }
  void set_f(const int f) { f_ = f; }
  void set_pre_node(const Node2d* pre_node) { pre_node_ = pre_node; }
  void set_iterations(const size_t iterations) { iterations_ = iterations; }
  int grid_x() const { return grid_x_; }
  int grid_y() const { return grid_y_; }
  int g() const { return g_; }
  int h() const { return h_; }
  int f() const { return f_; }
  size_t iterations() const { return iterations_; }
  const Node2d* pre_node() const { return pre_node_; }
  bool operator==(const Node2d& rhs) const {
    return grid_x_ == rhs.grid_x_ && grid_y_ == rhs.grid_y_;
  }

 private:
  int grid_x_ = 0;
  int grid_y_ = 0;
  int g_ = kInfiniteCost;
  int h_ = 0;
  int f_ = kInfiniteCost;
  const Node2d* pre_node_ = nullptr;
  size_t iterations_ = 0;
};

}  // namespace astar_planner_ros
