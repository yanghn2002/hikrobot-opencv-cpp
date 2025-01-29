include hikrobot_opencv.mk

CXX = g++

build_example: hikrobot_opencv_example.cpp
	$(CXX) hikrobot_opencv_example.cpp -o hikrobot_opencv_example $(HIKCV_CV_FLAGS) -lopencv_highgui $(HIKCV_MV_FLAGS) -O3
