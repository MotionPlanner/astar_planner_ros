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

#include <memory>
#include <string>
#include <vector>

#include "costmap_2d/costmap_2d_ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_core/base_global_planner.h"
#include "ros/ros.h"

#include "astar_planner_ros/grid_search/grid_search.h"

namespace astar_planner_ros {

class AStarPlannerROS : public nav_core::BaseGlobalPlanner {
 public:
  /**
   * @brief  Default constructor for the AStarPlannerROS object
   */
  AStarPlannerROS() = default;

  /**
   * @brief  Initialization function for the AStarPlannerROS object
   * @param  name The name of this planner
   * @param  costmap_ros A pointer to the ROS wrapper of the costmap to use
   */
  void initialize(std::string name,
                  costmap_2d::Costmap2DROS* costmap_ros) override;

  /**
   * @brief Given a goal pose in the world, compute a plan
   * @param start The start pose
   * @param goal The goal pose
   * @param plan The plan... filled by the planner
   * @return True if a valid plan was found, false otherwise
   */
  bool makePlan(const geometry_msgs::PoseStamped& start,
                const geometry_msgs::PoseStamped& goal,
                std::vector<geometry_msgs::PoseStamped>& plan) override;

  ~AStarPlannerROS() override = default;

 private:
  bool UpdateCostmap(costmap_2d::Costmap2DROS* costmap_ros);

  void LoadRosParamFromNodeHandle(const ros::NodeHandle& nh);

  uint8_t ComputeCircumscribedCost() const;

  static void GetStartAndEndConfigurations(
      const geometry_msgs::PoseStamped& start,
      const geometry_msgs::PoseStamped& goal, double resolution,
      double origin_x, double origin_y, int* start_x, int* start_y, int* end_x,
      int* end_y);

  static std::vector<std::vector<uint8_t>> GetGridMap(
      const uint8_t* char_map, unsigned int size_x, unsigned int size_y,
      bool treat_unknown_as_free);

  static void PopulateGlobalPlan(const grid_search::GridAStarResult& result,
                                 const std_msgs::Header& header,
                                 double resolution, double origin_x,
                                 double origin_y,
                                 std::vector<geometry_msgs::PoseStamped>* plan);

  static void PublishGlobalPlan(
      const std::vector<geometry_msgs::PoseStamped>& plan,
      const ros::Publisher& pub);

  std::unique_ptr<grid_search::GridSearch> astar_planner_ = nullptr;
  bool initialized_ = false;
  std::string name_;
  const costmap_2d::Costmap2DROS* costmap_ros_ = nullptr;
  const costmap_2d::Costmap2D* costmap_2d_ = nullptr;
  costmap_2d::LayeredCostmap* layered_costmap_ = nullptr;
  unsigned char circumscribed_cost_;
  bool treat_unknown_as_free_ = true;
  ros::Publisher plan_pub_;
};

}  // namespace astar_planner_ros
