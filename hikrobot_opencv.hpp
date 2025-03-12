#ifndef HIKROBOTOPENCVCPP_HIKROBOT_OPENCV_HPP
#define HIKROBOTOPENCVCPP_HIKROBOT_OPENCV_HPP


#include "MvCameraControl.h"
#include <opencv2/opencv.hpp>
#include <cstring>
#include <map>
#include <string>
#include <stdexcept>


namespace hikcv {


struct Error: std::runtime_error {
    explicit Error(const std::string& msg): std::runtime_error(msg) { }
};

struct CameraError: Error {
    explicit CameraError(const std::string& msg): Error("'"+msg+"' failed") { }
};

struct PixelTypeError: Error {
    explicit PixelTypeError(void): Error("Invalid pixel type") { }
};


constexpr unsigned HIKROBOT_CV_TIMEOUT_MSEC = 20000;
constexpr int ENUM_DEVICE_TYPE = MV_USB_DEVICE|MV_GIGE_DEVICE;


class OpencvCamera final {

    friend class MvContext;

    OpencvCamera(MV_CC_DEVICE_INFO* deviceInfo): _handle(nullptr), _started(false), _have_data(false) {

        if(MV_CC_CreateHandle(&_handle, deviceInfo) != MV_OK)
            throw CameraError("MV_CC_CreateHandle");

        if(MV_CC_OpenDevice(_handle) != MV_OK)
            throw CameraError("MV_CC_OpenDevice");
        
        if(MV_CC_SetEnumValue(_handle, "TriggerMode", 0) != MV_OK)
            throw CameraError("MV_CC_SetEnumValue");

    }

    public:

        ~OpencvCamera(void) {

            if(_started) stop();

            MV_CC_CloseDevice(_handle);
            MV_CC_DestroyHandle(_handle);
            MV_CC_FreeImageBuffer(_handle, &_frame);

        }

    private:

        void* _handle;

        bool _started;

        MV_FRAME_OUT _frame;
        bool _have_data;

    public:

        void start(void) {

            if(_started) return;

            if(MV_CC_StartGrabbing(_handle) != MV_OK)
                throw CameraError("MV_CC_StartGrabbing");

            _started = true;

        }

        void stop(void) {

            if(!_started) return;

            if(MV_CC_StopGrabbing(_handle) != MV_OK)
                throw CameraError("MV_CC_StopGrabbing");

            _started = false;

        }

        cv::Mat ref_cv_mat(unsigned timeout_msec=HIKROBOT_CV_TIMEOUT_MSEC) {
            
            if(_have_data) {
                if(MV_CC_FreeImageBuffer(_handle, &_frame) != MV_OK)
                    throw CameraError("MV_CC_FreeImageBuffer");
                _have_data = false;
            }

            if(MV_CC_GetImageBuffer(_handle, &_frame, timeout_msec) != MV_OK)
                throw CameraError("MV_CC_GetImageBuffer");
            
            unsigned width = _frame.stFrameInfo.nExtendWidth;
            unsigned height = _frame.stFrameInfo.nExtendHeight;

            enum MvGvspPixelType pixel_type = _frame.stFrameInfo.enPixelType;

            int cv_pixel_type;
            unsigned pixel_size = (MV_GVSP_PIX_EFFECTIVE_PIXEL_SIZE_MASK&pixel_type)>>MV_GVSP_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT;
            switch(pixel_type&MV_GVSP_PIX_COLOR_MASK) {
                case MV_GVSP_PIX_MONO: {
                    cv_pixel_type = CV_MAKETYPE(pixel_size, 1);
                }   break;
                case MV_GVSP_PIX_COLOR: {
                    cv_pixel_type = CV_MAKETYPE(pixel_size/3, 3);
                }   break;
                default: throw PixelTypeError();
            }

            _have_data = true;
            
            return cv::Mat(height, width, cv_pixel_type, _frame.pBufAddr);
            
        }

        cv::Mat get_cv_mat(unsigned timeout_msec=HIKROBOT_CV_TIMEOUT_MSEC) {
            return get_cv_mat(timeout_msec).clone();
        }

};


class MvContext final {

    public:

        typedef std::map<unsigned, std::string> DeviceIndex;
        
    private:
        
        MvContext(void) {

            memset(&_deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

            if(MV_CC_Initialize() != MV_OK)
                throw CameraError("MV_CC_Initialize");

            enumDevices(ENUM_DEVICE_TYPE);

        }

        MV_CC_DEVICE_INFO_LIST _deviceList;
        DeviceIndex _index_to_serial_number_map; // index -> serial number
        std::map<std::string, unsigned> _serial_number_to_index_map; // serial number -> index

    public:

        static MvContext& instance() { // get the only instance
            static MvContext instance;
            return instance;
        }

        ~MvContext(void) {
        	MV_CC_Finalize();
        }
    
        DeviceIndex enumDevices(int device_types=ENUM_DEVICE_TYPE) {

            memset(&_deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

            if(MV_CC_EnumDevices(device_types, &_deviceList) != MV_OK)
                throw CameraError("MV_CC_Initialize");
            
            _index_to_serial_number_map.clear();
            _serial_number_to_index_map.clear();
            for(unsigned int index = 0; index < _deviceList.nDeviceNum; index++) {
                MV_CC_DEVICE_INFO* deviceInfo = _deviceList.pDeviceInfo[index];
                if(!deviceInfo) break;
                switch(deviceInfo->nTLayerType) {
                    case MV_USB_DEVICE: {
                        _index_to_serial_number_map[index] = (char*)deviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber;
                        _serial_number_to_index_map[(char*)deviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber] = index;
                    } break;
                    case MV_GIGE_DEVICE: {
                        _index_to_serial_number_map[index] = (char*)deviceInfo->SpecialInfo.stGigEInfo.chSerialNumber;
                        _serial_number_to_index_map[(char*)deviceInfo->SpecialInfo.stGigEInfo.chSerialNumber] = index;
                    } break;
                    default:
                        continue;
                }
            }

            return _index_to_serial_number_map;

        }

        OpencvCamera createCapture(const unsigned index) {
            return OpencvCamera(_deviceList.pDeviceInfo[index]);
        }
        OpencvCamera createCapture(const std::string& serial_number) {
            return OpencvCamera(_deviceList.pDeviceInfo[_serial_number_to_index_map[serial_number]]);
        }

};

}

#endif//HIKROBOTOPENCVCPP_HIKROBOT_OPENCV_HPP
