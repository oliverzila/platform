#include <ros/ros.h>

#include <std_msgs/Float64.h>

std_msgs::Float64 sigRoll;
std_msgs::Float64 sigPitch;
/*
rostopic pub /roll_controller/command std_msgs/Float64 "{data: 0.5}" -1
*/

//TODO add all sine values to config file

int main(int argc,char* argv[])
{
    ros::init(argc, argv, "platform_pose_pub");
    ros::NodeHandle node;

    ros::Publisher pub_roll=node.advertise<std_msgs::Float64>("roll_controller/command",1);
    ros::Publisher pub_pitch=node.advertise<std_msgs::Float64>("pitch_controller/command",1);

    double aRoll = 0.219;
    double aPitch = 0.219;
    double tRoll = 4.5;
    double tPitch = 2.25;
    double phiRoll = M_PI/2;
    double phiPitch = 0;


    ros::Rate loop(100);
    while(ros::ok())
    {
        double t = ros::Time::now().toSec();
        sigRoll.data=aRoll*std::sin(2*M_PI*t/tRoll+phiRoll);
        sigPitch.data=aPitch*std::sin(2*M_PI*t/tPitch+phiPitch);
        pub_roll.publish(sigRoll);
        pub_pitch.publish(sigPitch);

        ros::spinOnce();
        if(!loop.sleep()) ROS_WARN("Missed deadline!");
    }

    pub_roll.shutdown();
    pub_pitch.shutdown();

    return 0;
}