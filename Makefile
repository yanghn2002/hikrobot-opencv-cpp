CXX = g++

include hikrobot_opencv.mk

build_example: hikrobot_opencv_example.cpp
	mkdir -p build
	$(CXX) hikrobot_opencv_example.cpp -o build/hikrobot_opencv_example $(HIKCV_CV_FLAGS) $(HIKCV_MV_FLAGS) -O3 \
	-lopencv_imgproc -lopencv_highgui
