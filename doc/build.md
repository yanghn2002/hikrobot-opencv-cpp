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
> ./build/hikrobot_opencv_example
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