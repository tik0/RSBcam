
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <MatConverter/MatConverter.hpp>

#include <boost/shared_ptr.hpp>
#include <rsb/Factory.h>
#include <rsb/converter/Repository.h>
#include <rsb/Event.h>
#include <rsb/Handler.h>
#include <rsb/filter/OriginFilter.h>
#include <rsc/threading/SynchronizedQueue.h>
#include <rsb/QueuePushHandler.h>


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

  // Create and start the listener
  rsb::ListenerPtr listener = factory.createListener("/image");
  boost::shared_ptr<rsc::threading::SynchronizedQueue<boost::shared_ptr<cv::Mat> > > imageQueue(
                      new rsc::threading::SynchronizedQueue<boost::shared_ptr<cv::Mat> >(1));

  listener->addHandler(rsb::HandlerPtr(new rsb::QueuePushHandler<cv::Mat>(imageQueue)));

  // Pop the images and show them
  while (true) {
        cv::Mat image = *imageQueue->pop().get();

        cv::imshow("input", image);
        cv::waitKey(1);
}

  return 0;

}
