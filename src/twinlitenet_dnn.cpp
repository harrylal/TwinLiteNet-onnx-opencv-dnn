#include "twinlitenet_dnn.hpp"

TwinLiteNet::TwinLiteNet(std::string model_path) : model_path_(model_path)
{

    net_ = cv::dnn::readNetFromONNX(model_path_);

#ifdef ENABLE_CUDA
    net_.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA); // Use CUDA backend
    net_.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);   // Use CUDA target
#endif
}

TwinLiteNet::~TwinLiteNet()
{
}

void TwinLiteNet::Infer(const cv::Mat &image, cv::Mat &da_out, cv::Mat &ll_out)
{
    assert(image.rows == kModelInputHeight && image.cols == kModelInputWidth && image.channels() == kModeInputChannels);

    cv::Mat input_img = image.clone();

    // Preprocess the input image
    cv::Mat blob = cv::dnn::blobFromImage(input_img, 1.0/255.0,
                                          cv::Size(kModelInputWidth, kModelInputHeight),
                                          cv::Scalar(), true, false);

    // Set the input to the network
    net_.setInput(blob);

    // Run the inference
    std::vector<cv::Mat> results;
    net_.forward(results, kModelOutputNames);

    // // Postprocess the output
    cv::Mat x1, x2;
    results[0].col(1).reshape(0, kModelInputHeight).convertTo(x1, CV_8UC1, 255.0);
    results[1].col(1).reshape(0, kModelInputHeight).convertTo(x2, CV_8UC1, 255.0);

    da_out = x1.clone();
    ll_out = x2.clone();
}