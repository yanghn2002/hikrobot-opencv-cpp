### Requirements

- Machine Vision Software MVS (Linux)
  > Download: [ [EN](https://www.hikrobotics.com/en/machinevision/service/download/?module=0 "MVS Download page (EN)") | [CN](https://www.hikrobotics.com/cn/machinevision/service/download/?module=0 "MVS Download page (CN)") ]
- OpenCV development package
  ```shell
  apt install libopencv-dev
  ```

### GNU Make

```Makefile
include hikrobot_opencv.mk
FLAGS += $(HIKCV_CV_FLAGS) $(HIKCV_MV_FLAGS) 
```

#### Build and run example

```shell
make
./hikrobot_opencv_example
```