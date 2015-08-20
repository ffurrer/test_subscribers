/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test_subscribers/test_gazebo_plugin.h"

namespace gazebo {

TestGazeboPlugin::~TestGazeboPlugin() {
  event::Events::DisconnectWorldUpdateBegin(update_connection_);
  if (node_handle_) {
    node_handle_->shutdown();
    delete node_handle_;
  }
}

void TestGazeboPlugin::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
  number_ = _sdf->GetElement("number")->Get<int>();
  std::cout<<"loading: "<< number_ << std::endl;

  node_handle_ = new ros::NodeHandle("");
  test_sub_ = node_handle_->subscribe("test_msg", 1, &TestGazeboPlugin::TestCallback, this);

  update_connection_ = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&TestGazeboPlugin::OnUpdate, this, _1));
}

void TestGazeboPlugin::OnUpdate(const common::UpdateInfo& _info) {}

void TestGazeboPlugin::TestCallback(const std_msgs::String::ConstPtr& msg) {
  // std::cout << "number: " << number_ << ", data: " << msg->data << std::endl;
  std::cout << number_ << msg->data;
  if (number_ == 90) {
    std::cout << std::endl;
  }
}

GZ_REGISTER_MODEL_PLUGIN(TestGazeboPlugin);
}
