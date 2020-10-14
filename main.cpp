//Reference:https://www.learnopencv.com/opencv-qr-code-scanner-c-and-python/

#include <iostream>
#include <algorithm>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

typedef struct
{
    string type;
    string data;
    vector <Point> location;
}decodedObject;


// Find and decode barcodes and QR codes
void decodewithlocation(Mat &im, vector<decodedObject>&decodedObjects)
{

    // Create zbar scanner
    ImageScanner scanner;

    // Configure scanner
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);
    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray;
    cvtColor(im, imGray,COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    // Print results
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        cout << "Type : " << obj.type << endl;
        cout << "Data : " << obj.data << endl << endl;

        // Obtain location
        for(int i = 0; i< symbol->get_location_size(); i++)
        {
            obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }

      decodedObjects.push_back(obj);
    }
}



int main(int argc, char *argv[])
{

    // Read image
//    string imagepath = argv[1];
//    Mat im = imread(imagepath);

    vector<decodedObject> decodedObjects;

    VideoCapture *cam = new VideoCapture(0);
    ImageScanner scanner;

    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);
    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

    Mat imGray;






    while(cam->isOpened()){
        Mat image, clone;
        cam->read(image);
        cvtColor(image, imGray,COLOR_BGR2GRAY);
//        decodewithlocation(image, decodedObjects);
        Image img(image.cols, image.rows, "Y800", (uchar *)imGray.data, image.cols * image.rows);

        for(Image::SymbolIterator iterator = img.symbol_begin(); iterator!=iterator.end(); ++iterator){
            for(int i = 0; i< iterator->get_location_size();i++){

            }
        }


        cout<<decodedObjects.size()<<endl;
        for (int i=0; i<decodedObjects.size(); i++){
            //QR Object location in image stored in points variable
            vector<Point> points = decodedObjects[i].location;
            //Convex Hull is created if points are more than 4
            vector<Point> hull;
            if(points.size() > 4){
                convexHull(points, hull);
            }else{
                hull=points;
            }
            int n = hull.size();
            for(int j = 0; j < n; j++)
            {
                line(clone, hull[j], hull[ (j+1) % n], Scalar(0,255,90), 3);
            }
           // cout<<hull.size()<<endl;
        }

        imshow("image", clone);


        if(waitKeyEx(1)==99){
            break;
        }
    }

    // Variable for decoded objects

    // Find and decode barcodes and QR codes


    return 0;
}