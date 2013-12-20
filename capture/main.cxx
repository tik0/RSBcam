#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <MatConverter/MatConverter.hpp>

#include <boost/shared_ptr.hpp>
#include <rsb/Factory.h>
#include <rsb/converter/Repository.h>
#include <rsb/Event.h>
#include <rsb/Handler.h>
#include <rsb/filter/OriginFilter.h>


using namespace boost;
using namespace std;
//using namespace cv;
using namespace rsb;
using namespace converter_Mat;
using namespace rsb::converter;

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
  ////////////////////////////////////////////////////////////////////////////////////////////////////


  // Creating the cam object
  cv::VideoCapture cam;
  // Open the device /dev/video0
  cam.open(0);
  // Allocate a frame object to store the picture
//  cv::Mat frame;
  shared_ptr<cv::Mat> frame(new cv::Mat);

  // Process the cam forever
  for (; ;) {

    // Save the actual picture to the frame object
    cam >> *frame;
    cv::waitKey(1000);
    // Send the data.
    informer->publish(frame);

  }

  // Free the cam
  cam.release();

  return 0;

}