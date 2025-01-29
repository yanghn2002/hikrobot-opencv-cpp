HIKCV_MV_INC_PATH = /opt/MVS/include
HIKCV_MV_LIB_PATH = /opt/MVS/lib/64
HIKCV_MV_LIB_LINK = MvCameraControl

HIKCV_CV_FLAGS = $(shell pkg-config opencv4 --cflags) -lopencv_core 
HIKCV_MV_FLAGS = -I$(HIKCV_MV_INC_PATH) -L$(HIKCV_MV_LIB_PATH) -l$(HIKCV_MV_LIB_LINK) 