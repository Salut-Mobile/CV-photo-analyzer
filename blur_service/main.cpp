//
// Created by Zaman Gabdrakhmanov on 16.02.2024.
//

#include <opencv2/opencv.hpp>

bool IsBlurry(const cv::Mat& gray, double& threshold) {
    //Cool, let's compute the laplacian of the gray image:
    cv::Mat laplacianImage;
    cv::Laplacian( gray, laplacianImage, CV_64F );

    //Prepare to compute the mean and standard deviation of the laplacian:
    cv::Scalar mean, stddev;
    cv::meanStdDev( laplacianImage, mean, stddev, cv::Mat() );

    //Let’s compute the variance:
    double variance = stddev.val[0] * stddev.val[0];

    double blurThreshold = 300;

    threshold = variance;

    return variance <= blurThreshold;
}

int divideImage(const cv::Mat& img, const int blockWidth, const int blockHeight, std::vector<cv::Mat>& blocks)
{
    // Checking if the image was passed correctly
    if (!img.data || img.empty())
    {
        std::wcout << "Image Error: Cannot load image to divide." << std::endl;
        return EXIT_FAILURE;
    }

    // init image dimensions
    int imgWidth = img.cols;
    int imgHeight = img.rows;
    std::wcout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;

    // init block dimensions
    int bwSize;
    int bhSize;

    int y0 = 0;
    while (y0 < imgHeight)
    {
        // compute the block height
        bhSize = ((y0 + blockHeight) > imgHeight) * (blockHeight - (y0 + blockHeight - imgHeight)) + ((y0 + blockHeight) <= imgHeight) * blockHeight;

        int x0 = 0;
        while (x0 < imgWidth)
        {
            // compute the block height
            bwSize = ((x0 + blockWidth) > imgWidth) * (blockWidth - (x0 + blockWidth - imgWidth)) + ((x0 + blockWidth) <= imgWidth) * blockWidth;

            // crop block
            blocks.push_back(img(cv::Rect(x0, y0, bwSize, bhSize)).clone());

            // update x-coordinate
            x0 = x0 + blockWidth;
        }

        // update y-coordinate
        y0 = y0 + blockHeight;
    }
    return EXIT_SUCCESS;
}


int main() {
//    путь выбирается относительно CMake IDE, то есть в данном случае, наша "отправная точка" - cmake-build-debug (CLion)
//    но можем поменять и изменить путь откуда будут браться остальные relative paths
//    НО ЭТО НИКАК НЕ ОТРАЖАЕТСЯ НА imwrite, только на то, что namespace cv::samples::
    cv::samples::addSamplesDataSearchPath("/Users/thechosenone/CV-photo-analyzer/blur_service/src/bad");

    std::string image_path = cv::samples::findFile("first.jpg");
    cv::Mat img = imread(image_path, cv::IMREAD_GRAYSCALE);
    // IMREAD_COLOR loads the image in the BGR 8-bit format. This is the default that is used here.
    // IMREAD_UNCHANGED loads the image as is (including the alpha channel if present)
    // IMREAD_GRAYSCALE loads the image as an intensity one

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

//    cv::imshow("Display window", img);
//
//    int k = cv::waitKey(0); // Wait for a keystroke in the window
//    if(k == 's')
//    {
//        cv::imwrite("starry_night.png", img);
//    }

    std::vector<cv::Mat> blocks{};

    divideImage(img, 100, 100, blocks);

    std::cout << blocks.size();


    std::vector<cv::Mat> blurredBlocks{};
    std::vector<cv::Mat> notBlurredBlocks{};

    for (cv::Mat& block : blocks) {
        double threshold = 0.0f;
        if (IsBlurry(block, threshold)) {
            std::string windowName = "B " + std::to_string(threshold);
            cv::imshow(windowName, block);
//            blurredBlocks.push_back(block);
        } else {
//            std::string windowName = "NB " + std::to_string(threshold);
//            cv::imshow(windowName, block);
//            notBlurredBlocks.push_back(block);
        }
    }

//    for (int i = 0; i < blurredBlocks.size(); i++) {
//        std::string windowNumber = std::to_string(i);
//
//        cv::imshow(windowName, blurredBlocks[i]);
//    }
//
//    for (int i = 0; i < notBlurredBlocks.size(); i++) {
//        std::string windowNumber = std::to_string(i);
//        std::string windowName = "Not blurred image: " + windowNumber;
//        cv::imshow(windowName, notBlurredBlocks[i]);
//        cv::waitKey(300);
//    }

    cv::waitKey(0);

}