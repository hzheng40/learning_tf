#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <turtlesim/Velocity.h>
#include <turtlesim/Spawn.h>
#include <ros/console.h>
#include <stdio.h>

int main(int argc, char** argv){
  ROS_DEBUG("hello %s","World");
  ROS_DEBUG_STREAM("Hello " << "World");
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;
  
  // This part create a second turtle using spawn function
  // It's called turtle2
  /*
  ros::service::waitForService("spawn");
  ros::ServiceClient add_turtle =
       node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn srv;
  add_turtle.call(srv);
  */

  // turtle_vel is the publisher for turtle2's velocity
  ros::Publisher turtle_vel =
  node.advertise<turtlesim::Velocity>("turtle1/command_velocity", 10);

  // This creates a TransformListener
  tf::TransformListener listener;
  
  ros::Rate rate(10.0);
  
  // length is a varible that record the distance between 
  // a person's head to torso. 
  double disp_x = 0.0;
  double disp_y = 0.0;
  double disp_z = 0.0;
  double rotation = 0.0;
  
  // The max speed for turtlebot	
  const double MAX_LINEAR_SPEED = 1.5;
  const double MAX_ANGULAR_SPEED = 1.5;

  // This part looks for the tf 
  while (node.ok()){
    tf::StampedTransform transform;
    try{
    //ros::Time now = ros::Time::now();
    //listener.waitForTransform("torso_1", "head_1", now, ros::Duration(10.0));
    //listener.lookupTransform("torso_1", "head_1", now, transform);
        listener.lookupTransform("torso_1", "right_hand_1", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
  }
  disp_x = transform.getOrigin().x();
  disp_y = transform.getOrigin().y();
  disp_z = transform.getOrigin().z();
  rotation = 2 * transform.getRotation().z();
  
    


};
