/**
* Copyright 2014 Social Robotics Lab, University of Freiburg
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    # Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*    # Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*    # Neither the name of the University of Freiburg nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \author Billy Okal <okal@cs.uni-freiburg.de>
*/

// ros and big guys
#include <ros/ros.h>
#include <ros/console.h>

// messages and services
#include <pedsim_msgs/AgentState.h>
#include <pedsim_msgs/AllAgentsState.h>

#include <pedsim_srvs/SetAgentState.h>
#include <pedsim_srvs/SetAllAgentsState.h>
#include <pedsim_srvs/GetAgentState.h>
#include <pedsim_srvs/GetAllAgentsState.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <std_msgs/Header.h>
#include <nav_msgs/GridCells.h>
#include <geometry_msgs/Point.h>

#include <pedsim_simulator/orientationhandler.h>

#include <boost/foreach.hpp>

#include <pedsim_simulator/scene.h>
#include <pedsim_simulator/element/agent.h>
#include <pedsim_simulator/element/agentgroup.h>
#include <pedsim_simulator/scenarioreader.h>
#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/element/attractionarea.h>


class Simulator
{
public:
	Simulator(const ros::NodeHandle &node);
	virtual ~Simulator();

	bool initializeSimulation();
	void runSimulation();

	/// publishers
	void publishAgentVisuals();
	void publishGroupVisuals();
	void publishObstacles();
	void publishWalls();
	void publishAttractions();
	
	/// subscriber helpers
    void callbackRobotCommand ( const pedsim_msgs::AgentState::ConstPtr &msg );

private:

	// robot agent
	Agent* robot_;
	
	ros::NodeHandle nh_;

	// publishers
	ros::Publisher pub_obstacles_;
    ros::Publisher pub_agent_visuals_;
    ros::Publisher pub_group_centers_;
	ros::Publisher pub_group_lines_;
	ros::Publisher pub_walls_;
	ros::Publisher pub_all_agents_;
	ros::Publisher pub_attractions_;
	ros::Publisher pub_queues_;
	
	// subscribers
    ros::Subscriber sub_robot_command_;

    OrientationHandlerPtr orientation_handler_;

};