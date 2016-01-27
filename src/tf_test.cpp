#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <ros/console.h>
#include <stdio.h>

void publish(double, double, double, double);

ros::Publisher pub;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	tf::TransformListener listener;
	ros::Rate rate(10.0);
	pub = node.advertise<geometry_msgs::Quaternion>("gesture", 1);

	double disp_x = 0.0;
 	double disp_y = 0.0;
  	double disp_z = 0.0;
  	double hover = 0.0;

	while (node.ok()) {
		tf::StampedTransform transform;
		tf::StampedTransform transform2;
		try {
			listener.lookupTransform("torso_1", "left_hand_1", ros::Time(0), transform);
			listener.lookupTransform("torso_1", "right_hand_1", ros::Time(0), transform2);
		} catch (tf::TransformException ex) {
			ROS_ERROR("%s",ex.what());
		}
		disp_x = transform.getOrigin().x();
	  	disp_y = transform.getOrigin().y();
	 	disp_z = transform2.getOrigin().z();
	 	hover = transform2.getOrigin().y();

	 	ROS_INFO("x axis displacement: %f    y axis displacement: %f    z axis displacement: %f    rotation: %f",
	 			disp_x, disp_y, disp_z, hover);
	 	publish(disp_x,disp_y,disp_z,hover);

	    rate.sleep();
	}
	return 0;
}
void publish(double disp_x, double disp_y, double disp_z, double rotation) {
	geometry_msgs::Quaternion msg;
	msg.x = disp_x;
	msg.y = disp_y;
	msg.z = disp_z;
	msg.w = rotation;
	pub.publish(msg);
}