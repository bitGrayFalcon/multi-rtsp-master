# multi-rtsp-master
a rospackage for opening multiple rtsp streams

# use
clone and put the folder into a ros workspace.


# open your own rtsp streaming
edit file /src/muti-rtsp.cpp(it's just a mispell.)
in main() function:\n
add your own rtsp address and topic name.
remember run "catkin_make" after any changes

# run
make sure you have a ros master running, if not:
roscore
and in a new terminal:
(in your ros workspace dir)
catkin_make
source devel/setup.bash
rosrun multi_rtsp multi_rtsp_node
