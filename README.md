# multi-rtsp-master
a rospackage for opening multiple rtsp streams

# use
clone and put the folder into a ros workspace.


# open your own rtsp streaming
edit file /src/muti-rtsp.cpp(it's just a mispell).<br/>
in main() function:<br/>
add your own rtsp address and topic name.<br/>
remember to run "catkin_make" after any changes.<br/>

# run
make sure you have a ros master running, if not:<br/>
roscore<br/>
and in a new terminal:<br/>
(in your ros workspace dir)<br/>
catkin_make<br/>
source devel/setup.bash<br/>
rosrun multi_rtsp multi_rtsp_node
