#ifndef LIBLDW_TWINLITENET_DNN_H_
#define LIBLDW_TWINLITENET_DNN_H_

#include <opencv2/opencv.hpp>



class TwinLiteNet{
    public:
        TwinLiteNet(std::string model_path);
        ~TwinLiteNet();
        void Infer(const cv::Mat& image, cv::Mat& da_out, cv::Mat& ll_out);
        
    private:
        cv::dnn::Net net_;
        std::string model_path_;

        const std::vector<std::string> kModelOutputNames = {"da", "ll"};
        static const int kModelInputHeight = 360;
        static const int kModelInputWidth = 640;
        static const int kModeInputChannels = 3;

};



#endif // LIBLDW_TWINLITENET_DNN_H_