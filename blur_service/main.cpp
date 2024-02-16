//
// Created by Zaman Gabdrakhmanov on 16.02.2024.
//

#include <opencv2/opencv.hpp>


int main() {
//    путь выбирается относительно CMake IDE, то есть в данном случае, наша "отправная точка" - cmake-build-debug (CLion)
//    но можем поменять и изменить путь откуда будут браться остальные relative paths
//    НО ЭТО НИКАК НЕ ОТРАЖАЕТСЯ НА imwrite, только на то, что namespace cv::samples::
    cv::samples::addSamplesDataSearchPath("/Users/thechosenone/CV-photo-analyzer/blur_service/src/bad");

    std::string image_path = cv::samples::findFile("Копия photo2.jpg");
    cv::Mat img = imread(image_path, cv::IMREAD_GRAYSCALE);
    // IMREAD_COLOR loads the image in the BGR 8-bit format. This is the default that is used here.
    // IMREAD_UNCHANGED loads the image as is (including the alpha channel if present)
    // IMREAD_GRAYSCALE loads the image as an intensity one

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    cv::imshow("Display window", img);

    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        cv::imwrite("starry_night.png", img);
    }

}