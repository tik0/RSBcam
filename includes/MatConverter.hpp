#pragma once

#include <rsb0.9/rsb/converter/Converter.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace boost;
using namespace cv;
using namespace rsb;
using namespace rsb::converter;

namespace converter_Mat {

/**
 * A simple converter for the Mat object.
 */
class MatConverter: public rsb::converter::Converter<std::string> {
public:
    MatConverter();

    std::string serialize(const rsb::AnnotatedData& data,
            std::string& wire);

    rsb::AnnotatedData deserialize(const std::string& wireSchema,
            const std::string& wire);
};

}
