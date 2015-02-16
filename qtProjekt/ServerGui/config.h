#ifndef CONFIG_HH_
#define CONFIG_HH_

#define currentVersion "1.3.3.7"
#define cameraParmFile "/home/user/ServerGui/configFiles/out_camera_data.xml"
#define calibConfigFile "/home/user/ServerGui/configFiles/in_VID5.xml"
#define cameraAdress "http://192.168.0.1:8080/?action=stream&amp;type=.mjpg"


//Landmarks: Shapes
#define landMarkShapeOrigin 4
#define landMarkShapeReference 4

//Landmarks: Color Ranges
#define landMarkColorOriginMin 0
#define landMarkColorOriginMax 127
#define landMarkColorReferenceMin 128
#define landMarkColorReferenceMax 255

//Landmarks: Sizes(cm)
#define landMarkSizeOrigin 10
#define landMarkSizeReference 10

//Object: Shape
#define objectShape 3

//Object: Color Range
#define objectColorMin 0
#define objectColorMax 127

//Object: Size(cm)
#define objectSizeCM 10

//ObjectLocator: Harris Corner Parameters
#define harrisCornerBlockSize 4
#define harrisCornerApertureSize 3
#define harrisCornerVariance 0.1
#define harrisCornerThresh 180
#define harrisCornerMergeArea 3

//ObjectLocator: Hough Circle Parameters
#define houghCircleThreshold 50

//ObjectLocator: Gaussian Filter Parameters
#define gaussianStandardDeviation 3
#define gaussianSize 9

#endif // CONFIG_HH_

