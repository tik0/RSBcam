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
#include <rsc0.9/rsc/threading/SynchronizedQueue.h>
#include <rsb0.9/rsb/QueuePushHandler.h>



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

// Print out the recieved octree
void getMessage(rsb::EventPtr event);

int main() {


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // Register our converter within the collection of converters for
  // the string wire-type (which is used for arrays of octets in
  // C++).
  shared_ptr<MatConverter> converter(new MatConverter());
  converterRepository<std::string>()->registerConverter(converter);


  rsb::Factory &factory = rsb::Factory::getInstance();

//  // Create the informer
//  Informer<cv::Mat>::Ptr informer = getFactory().createInformer<cv::Mat> (Scope("/image"));

  // Create and start the listener
  rsb::ListenerPtr listener = factory.createListener("/image");
  boost::shared_ptr<rsc::threading::SynchronizedQueue<boost::shared_ptr<cv::Mat> > > imageQueue(
                      new rsc::threading::SynchronizedQueue<boost::shared_ptr<cv::Mat> >(1));

  listener->addHandler(rsb::HandlerPtr(new rsb::QueuePushHandler<cv::Mat>(imageQueue)));

  while (true) {

//        cv::Mat image = cv::Mat(imageQueue->pop().get(), true);
        cv::Mat image = *imageQueue->pop().get();

        cv::imshow("input", image);
        cv::waitKey(1);
}

//  listener->addHandler(rsb::HandlerPtr(new rsb::EventFunctionHandler(&getMessage)));


  ////////////////////////////////////////////////////////////////////////////////////////////////////

  // Process the cam as long as it is open
//  cam.isOpened()
  std::string a;
  for (; ;) {

    std::cin >> a;
  }


  return 0;

}

//int i = 0;
//void getMessage(rsb::EventPtr event) {
//
//        // Get the data
//    shared_ptr<cv::Mat> message_rec = static_pointer_cast<cv::Mat>(event->getData());
//
//
////    std::cout << "blah" << std::endl;
//    // Write OcTree to file
//    cv::imshow("Show It", *message_rec);
//    std::cout << i++ << std::endl;
//    cv::waitKey (30);
////    cv::imwrite( "Image.jpg", *message_rec );
//}
