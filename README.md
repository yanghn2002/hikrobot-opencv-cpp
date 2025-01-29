# Hikrobot OpenCV CPP

Header-only C++ library for capturing OpenCV `cv::Mat` from [Hikvision](https://www.hikvision.com/ "www.hikvision.com") industrial camera.

Requires MVS to be installed on Linux.
> Download: [ [EN](https://www.hikrobotics.com/en/machinevision/service/download/?module=0 "Download page (EN)") | [CN](https://www.hikrobotics.com/cn/machinevision/service/download/?module=0 "Download page (CN)") ]

### Tested devices

- GIGE
  - MV-CE020-10GC
- USBC
  - MV-CD020-10UC
  - MV-CS200-10UC

### Usage

```Makefile
include hikrobot_opencv.mk
FLAGS += $(HIKCV_CV_FLAGS) $(HIKCV_MV_FLAGS) 
```

#### Run example

```shell
make
./hikrobot_opencv_example
```