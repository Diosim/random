
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int, char** argv)
{
    
    cv::String path("/Users/Diosim/Downloads/folder copy/*.png"); //select only png
    vector<cv::String> fn;
    vector<cv::Mat> data;
    cv::glob(path,fn,true); // recurse
    for (size_t k=0; k<fn.size(); ++k)
    {
        
        cv::Mat im = cv::imread(fn[k]);
        cv::Mat im_bgra; // declare a temp space for the image with alphas
        if (im.empty()) continue; //only proceed if sucsessful
        // you probably want to do some preprocessing
        
        cv::cvtColor(im, im_bgra, CV_BGR2BGRA);
        
        // find all white pixel and set alpha value to zero:
        for (int y = 0; y < im_bgra.rows; ++y)
            for (int x = 0; x < im_bgra.cols; ++x)
            {
                cv::Vec4b & pixel = im_bgra.at<cv::Vec4b>(y, x);
                // if pixel is white
                int thres = 100; // where thres is some value smaller but near to 255.
                if (pixel[0] >= thres&& pixel[1] >= thres && pixel[2] >= thres)
                {
                    // set alpha to zero:
                    pixel[3] = 0;
                }
            }
        
        // save back as .png file (which supports alpha channels/transparency)
        cv::imwrite(fn[k], im_bgra);
        
        data.push_back(im);
    }
    
    
    //char c = cvWaitKey(33);
    //if (c == 27) break;
    cv::waitKey(10);
    std::cout << "operation completed";
    return 0;
}
    


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


    /*
    
// load as color image BGR
cv::Mat input = cv::imread("/Users/Diosim/Downloads/1pt_preview.png");

cv::Mat input_bgra;
cv::cvtColor(input, input_bgra, CV_BGR2BGRA);

// find all white pixel and set alpha value to zero:
for (int y = 0; y < input_bgra.rows; ++y)
for (int x = 0; x < input_bgra.cols; ++x)
{
    cv::Vec4b & pixel = input_bgra.at<cv::Vec4b>(y, x);
    // if pixel is white
    int thres = 100; // where thres is some value smaller but near to 255.
    if (pixel[0] >= thres&& pixel[1] >= thres && pixel[2] >= thres)
    {
        // set alpha to zero:
        pixel[3] = 0;
    }
}

// save as .png file (which supports alpha channels/transparency)
cv::imwrite("/Users/Diosim/Downloads/1pt_preview_transp.png", input_bgra);

cv::imshow("transparent", input_bgra);
//cv::imshow("frame", frame);
//char c = cvWaitKey(33);
//if (c == 27) break;
cv::waitKey(10);
std::cout << "operation completed";
return 0;
}
*/
