#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/*
this program get a video and crop it based on the input values that an user type.
*/

int main()
{

    cv::Rect box; //box
    string path_video, path_outVideo; //get the input path and output path
    int width_crop, height_crop, x, y, width_frame, height_frame, done, count = 0;

    std::cout << "Type the input video path:" << std::endl;
    getline(cin, path_video);
    std::cout<<"Type the output video path (or Just press enter to save in this program directory):" << std::endl;
    getline(cin, path_outVideo);

    do{
        std::cout<<"Enter x value: "<<std::endl;
        scanf("%d", &x);
        std::cout<<"Enter y value: "<<std::endl;
        scanf("%d", &y);
        std::cout<<"Enter width value: "<<std::endl;
        scanf("%d", &width_crop);
        std::cout<<"Enter height value: "<<std::endl;
        scanf("%d", &height_crop);

        //Verify if x, y, width_crop, height_crop are less than zero
        if (x < 0 || y < 0 || width_crop < 0 || height_crop < 0){
            std::cout<<"No one the value (x, y, width, height) can be less than zero"<<std::endl;
        }
        else{
        cv::VideoCapture cap(path_video);

        //Verify if the video was successfully loaded
        if (!cap.isOpened()){
            std::cout<<"Video not found"<<std::endl;
            return -1;
        }

        cv::Mat frame;
        cap >> frame;

        width_frame = frame.size().width;
        height_frame = frame.size().height;

        //don't let the width_crop be bigger than the frame width size
        if (((x + width_crop) > width_frame)){
            width_crop = width_frame - x;
        }

        //don't let the height_crop be bigger than the frame height size
        if (((y+height_crop) > height_frame)){
            height_crop = height_frame - y;
        }

        box.width = width_crop;
        box.height = height_crop;
        box.x = x;
        box.y = y;

        cv::Size frame_size(width_crop,height_crop);

        //concatenate the output string to video name
        std::string out = path_outVideo + "outvideo" + std::to_string(count) + ".avi";

        cv::VideoWriter writer_video(out,CV_FOURCC('M','J','P','G'),20.0, frame_size, true);

        //in this while below the input video is read and cropped
        std::cout<<"Your video is being cropped..."<<std::endl;
        while(!frame.empty()){

            cv::Mat crop(frame, box);
            writer_video.write(crop);
            cap >> frame;

            char c=(char) cv::waitKey(25);
            if(c==27)
                break;
        }
        std::cout<<"Done!"<<std::endl;

        cap.release();
        writer_video.release();
        cv::destroyAllWindows();
        }
        std::cout<<"Press 1 if you want more crops for this video or 0 for not"<<std::endl;
        scanf("%d", &done);
        count++;

    }while(done == 1);

    std::cout<<"Program finished..."<<std::endl;

    return 0;
}
