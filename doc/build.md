### Requirements

- Machine Vision Software MVS (Linux)
  > Download: [ [EN](https://www.hikrobotics.com/en/machinevision/service/download/?module=0 "MVS Download page (EN)") | [CN](https://www.hikrobotics.com/cn/machinevision/service/download/?module=0 "MVS Download page (CN)") ]
- OpenCV development package
  ```shell
  apt install libopencv-dev
  ```

### Meson

```meson
hikrobot_opencv = subproject('hikrobot-opencv-cpp')
hikrobot_opencv_dep = hikrobot_opencv.get_variable('hikrobot_opencv_dep')
```

> #### Build and run example
> 
> ```shell
> meson setup build
> meson compile -C build
> ```

### GNU Make

```Makefile
include hikrobot_opencv.mk
FLAGS += $(HIKCV_CV_FLAGS) $(HIKCV_MV_FLAGS) 
```

> #### Build and run example
> 
> ```shell
> make
> ./build/hikrobot_opencv_example
> ```