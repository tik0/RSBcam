//
#include <iostream>
//
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "MatConverter.hpp"

#include <boost/shared_ptr.hpp>
#include <rsb0.9/rsb/Factory.h>
#include <rsb0.9/rsb/converter/Repository.h>
#include <rsb0.9/rsb/Event.h>
#include <rsb0.9/rsb/Handler.h>
#include <rsb0.9/rsb/filter/OriginFilter.h>



//
//
using namespace boost;
using namespace std;
//using namespace cv;
using namespace rsb;
using namespace converter_Mat;
using namespace rsb::converter;

const int KEY_ESC = 27;
const int DELAY = 30;

//const string WIN_NAME = "Camera View";

//// Print out the recieved octree
//void getMessage(rsb::EventPtr event);

int main() {


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // Register our converter within the collection of converters for
  // the string wire-type (which is used for arrays of octets in
  // C++).
  shared_ptr<MatConverter> converter(new MatConverter());
  converterRepository<std::string>()->registerConverter(converter);


  rsb::Factory &factory = rsb::Factory::getInstance();

  // Create the informer
  Informer<cv::Mat>::Ptr informer = getFactory().createInformer<cv::Mat> (Scope("/image"));

//  // Create and start the listener
//  rsb::ListenerPtr listener = factory.createListener("/image");
//  listener->addHandler(rsb::HandlerPtr(new rsb::EventFunctionHandler(&getMessage)));


  ////////////////////////////////////////////////////////////////////////////////////////////////////


  // Creating the cam object
  cv::VideoCapture cam;
  // Open the device /dev/video0
  cam.open(0);
  // Allocate a frame object to store the picture
//  cv::Mat frame;
  shared_ptr<cv::Mat> frame(new cv::Mat);

  // Read the key
//  int key = cv::waitKey(DELAY);

  // Process the cam as long as it is open
//  cam.isOpened()
  for (; ;) {

    // Save the actual picture to the frame object
    cam >> *frame;
    cv::waitKey(1000);
//    // Show the picture
//    cv::imshow(WIN_NAME, frame);
    // Send the data.
          informer->publish(frame);

//    // Read a keystroke
//    key = cv::waitKey(DELAY);
//
//    // If the keystroke was ESC, then break
//    if (KEY_ESC == key)
//      break;
  }

  // Free the cam
  cam.release();

  return 0;

}


//void getMessage(rsb::EventPtr event) {
//
//        // Get the data
//    shared_ptr<cv::Mat> message_rec = static_pointer_cast<cv::Mat>(event->getData());
//
////    std::cout << "blah" << std::endl;
//    // Write OcTree to file
////    cv::imshow("Show It", *message_rec);
////    cv::imwrite( "Image.jpg", *message_rec );
//}
