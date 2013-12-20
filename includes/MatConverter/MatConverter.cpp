/*
 * MatConverter.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: tiko
 */

#include "MatConverter.hpp"

namespace converter_Mat {

// We have to pass two arguments to the base-class constructor:
// 1. The data-type
// 2. The wire-schema
//
// Note: this could also be written as
// Converter<string>("matrix-image", RSB_TYPE_TAG(Mat))
// to infer the "string" name of the data-type using RTTI.
MatConverter::MatConverter() :
    Converter<string> ("cv::Mat", "matrix-image", true) {
}

string MatConverter::serialize(const AnnotatedData& data, string& wire) {
    // Ensure that DATA actually holds a datum of the data-type we
    // expect.
    assert(data.first == getDataType());

    // Force conversion to the expected data-type.
    //
    // NOTE: a dynamic_pointer_cast cannot be used from void*
    boost::shared_ptr<const Mat> matImage =
            static_pointer_cast<const Mat> (data.second);

    // Prepare the sending data
    //
    // Get the information of the matrix and store it
    int iCols = matImage->cols;
    int iRows = matImage->rows;
    int iType = matImage->type();

    // extract the information regarding image type
    uchar ucDepth = iType & CV_MAT_DEPTH_MASK;
    int   iDepth = 0;
    uchar ucChannels = 1 + (iType >> CV_CN_SHIFT);

    switch ( ucDepth ) {
      case CV_8U:  iDepth = 1; break; // "8U"; break;
      case CV_8S:  iDepth = 1; break; // "8S"; break;
      case CV_16U: iDepth = 2; break; // "16U"; break;
      case CV_16S: iDepth = 2; break; // "16S"; break;
      case CV_32S: iDepth = 4; break; // "32S"; break;
      case CV_32F: iDepth = 4; break; // "32F"; break;
      case CV_64F: iDepth = 8; break; // "64F"; break;
      default:     iDepth = 1; break; // "User"; break;
    }

    // Store the content to the selected binary layout.
    // Define the amount of sending data
    // Allocate cols (int -> 4), rows (int -> 4), type (int -> 4) and the data in bytes
    ssize_t uiImageSize = iCols * iRows * iDepth * ucChannels;
    wire.resize( 4 + 4 + 4 + uiImageSize );
    // Write the cols
    copy(((char*) &iCols), ((char*) &iCols) + 4, wire.begin());
    // Write the rows
    copy(((char*) &iRows), ((char*) &iRows) + 4, wire.begin() + 4);
    // Write the type
    copy(((char*) &iType), ((char*) &iType) + 4, wire.begin() + 8);
    // Write the data
    copy(matImage->data, matImage->data + uiImageSize, wire.begin() + 12 );


    // Return the wire-schema of the serialized representation in
    // WIRE.
    return getWireSchema(); // this->getWireSchema() == "matrix-image"
}

AnnotatedData MatConverter::deserialize(const string& wireSchema,
        const string& wire) {
    // Ensure that WIRE uses the expected wire-schema.
    assert(wireSchema == getWireSchema()); // this->getWireSchema() == "matrix-image"

    // Allocate a new SimpleImage object and set its data members from
    // the content of WIRE.
    //

    // Get the cols
    const int   iCols = *((int*)   &*wire.begin());
    // Get the rows
    const int   iRows = *((int*)   &*(wire.begin() + 4));
    // Get the type
    const int   iType = *((int*)   &*(wire.begin() + 8));

    uchar ucDepth = iType & CV_MAT_DEPTH_MASK;
    int   iDepth = 0;
    uchar ucChannels = 1 + (iType >> CV_CN_SHIFT);

    switch ( ucDepth ) {
      case CV_8U:  iDepth = 1; break; // "8U"; break;
      case CV_8S:  iDepth = 1; break; // "8S"; break;
      case CV_16U: iDepth = 2; break; // "16U"; break;
      case CV_16S: iDepth = 2; break; // "16S"; break;
      case CV_32S: iDepth = 4; break; // "32S"; break;
      case CV_32F: iDepth = 4; break; // "32F"; break;
      case CV_64F: iDepth = 8; break; // "64F"; break;
      default:     iDepth = 1; break; // "User"; break;
    }

    // Create the image and copy the pointer to the date
//    cv::Mat matImage(iCols, iRows, iType);
    cv::Mat * matImage = new cv::Mat( iRows, iCols, iType);
//    cv::Mat matImage(10, 10, CV_8UC3);
//    matImage.data = ((uchar*)   &*(wire.begin() + 12));
    matImage->data = ((uchar*)   &*(wire.begin() + 12));
//    copy(((uchar*)   &*(wire.begin() + 12)), ((uchar*)   &*(wire.begin() + 12 + iDepth * iRows + iCols)), matImage->data);
//    cv::imwrite( "Image.jpg", *matImage );
//    cv::imshow("Show It", *matImage);
    // Return (a shared_ptr to) the constructed object along with its
    // data-type.
    return make_pair(getDataType(), boost::shared_ptr<cv::Mat> (matImage));
}

}



