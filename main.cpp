//Reference:https://www.learnopencv.com/opencv-qr-code-scanner-c-and-python/

#include <iostream>
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
    //Clear decoded Object to keep only one QR code in memory at a time.
    decodedObjects.clear();
    // Configure scanner
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
//    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

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

    vector<decodedObject> decodedObjects;

    VideoCapture *cam = new VideoCapture(0);

    while(cam->isOpened()){
        Mat image;
        cam->read(image);
//        cvtColor(image, image,COLOR_BGR2GRAY);
        decodewithlocation(image, decodedObjects);

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
                line(image, hull[j], hull[ (j+1) % n], Scalar(0,255,90), 3);
            }

        }

        imshow("image", image);


        if(waitKeyEx(1)==99){
            break;
        }
    }

    // Variable for decoded objects

    // Find and decode barcodes and QR codes


    return 0;
}