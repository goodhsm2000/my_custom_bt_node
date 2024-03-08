#include "movebase_client.h"


void MoveBase::cancelgoal() {
  ROS_INFO("Cancel current Goal");
  // _client.cancelAllGoals();
  _client.cancelAllGoals();
  _aborted = true;
  return;
}

BT::NodeStatus MoveBase::tick() {
  // if no server is present, fail after 2 seconds
  // 지정된 시간 동안 서버가 연결되지 않으면 false를 반환
  if (!_client.waitForServer(ros::Duration(2.0))) {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }

  // Take the goal from the InputPort of the Node
  Rbiz goal;
  // 입력 포트에 있는 것을 읽어 goal에 저장
  if (!getInput<Rbiz>("goal", goal)) {
    // if I can't get this, there is something wrong with your BT.
    // For this reason throw an exception instead of returning FAILURE
    throw BT::RuntimeError("missing required input [goal]");
  }

  // Reset this flag
  _aborted = false;

  ROS_INFO("Sending goal %f %f %f %f", goal.x, goal.y, goal.quaternion_z, goal.quaternion_w);

  // // Build the message from Pose2D
  // // move_base_msgs::MoveBaseGoal 형식의 목표 메시지(msg)를 생성
  // move_base_msgs::MoveBaseGoal msg;
  // msg.target_pose.header.frame_id = "map";
  // msg.target_pose.header.stamp = ros::Time::now();
  // msg.target_pose.pose.position.x = goal.x;
  // msg.target_pose.pose.position.y = goal.y;
  // msg.target_pose.pose.orientation.z = goal.quaternion_z;
  // msg.target_pose.pose.orientation.w = goal.quaternion_w;

  move_base_msgs::MoveBaseGoal msg;
  msg.target_pose.header.frame_id = "map";
  msg.target_pose.header.stamp = ros::Time::now();
  msg.target_pose.pose.position.x = goal.x;
  msg.target_pose.pose.position.y = goal.y;
  msg.target_pose.pose.orientation.z = goal.quaternion_z;
  msg.target_pose.pose.orientation.w = goal.quaternion_w;


  //_client를 사용하여 목표 메시지(msg)를 move_base 서버로 보냅
  _client.sendGoal(msg);
  
  // 이동 작업이 완료될 때까지 대기하는 부분
  // _aborted 플래그가 true로 설정되지 않고, _client.waitForResult() 함수가 완료 신호를 받지 않으면 계속해서 0.02초 간격으로 폴링하여 작업 완료를 확인
  while (!_aborted && !_client.waitForResult(ros::Duration(0.02))) {
    // polling at 50 Hz. No big deal in terms of CPU
  }

  if (_aborted) {
    // this happens only if method halt() was invoked
    //_client.cancelAllGoals();
    ROS_ERROR("MoveBase aborted");
    return BT::NodeStatus::FAILURE;
  }

  if (_client.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_ERROR("MoveBase failed");
    return BT::NodeStatus::FAILURE;
  }

  ROS_INFO("Target reached");
  return BT::NodeStatus::SUCCESS;
}
