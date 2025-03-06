project('hikrobot_opencv', 'cpp')


hikrobot_opencv_dep = declare_dependency(
  include_directories: include_directories('/opt/MVS/include'),
  dependencies: [ dependency('opencv4') ],
  link_args : ['-L/opt/MVS/lib/64', '-lMvCameraControl']
)


executable('hikrobot_opencv_example',
  'hikrobot_opencv_example.cpp',
  dependencies: [ hikrobot_opencv_dep ]
)
