#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "twinlitenet_dnn.hpp"

int main()
{

    // Model Loading and associated initalisations
    TwinLiteNet twinlitenet("/mnt/sdd1/personal/TwinLiteNet-opencv-dnn/models/best.onnx");
    std::cout << "Model Loaded" << std::endl;

    // Read the image
    cv::Mat img = cv::imread("/mnt/sdd1/personal/TwinLiteNet-opencv-dnn/images/cc97fab0-f9a08d07.jpg");

    if (img.empty())
    {
        std::cerr << "Error: Could not read the image." << std::endl;
        exit(1);
    }
    
    // Resize the image to 360x640 as the model expects this size
    cv::resize(img, img, cv::Size(640, 360));
    cv::Mat img_vis = img.clone();

    cv::Mat da_out, ll_out;

    // Run the inference
    twinlitenet.Infer(img, da_out, ll_out);
    std::cout << "Inference Done" << std::endl;

    // Plot the predictions
    img_vis.setTo(cv::Scalar(255, 0, 127), da_out);
    img_vis.setTo(cv::Scalar(0, 0, 255), ll_out);

    // save the annotated image
    cv::imwrite("results.jpg", img_vis);
    std::cout << "Results saved" << std::endl;

    return 0;
}
