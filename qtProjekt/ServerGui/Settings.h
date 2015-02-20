//============================================================================
// Datei	: Settings.h
// Autor	: Christian Jungblut + Codebeispiel aus OpenCV
// Version	: 1.0
//============================================================================

#include <cstdlib>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define currentVersion "1.3.3.7"
#define cameraParmFile "configFiles/out_camera_data_work.xml"
#define calibConfigFile "configFiles/eagleEyeParams.xml"
#define cameraAdress "http://192.168.0.1:8080/?action=stream&amp;type=.mjpg"


#ifndef SETTINGS_H
#define	SETTINGS_H

/** Klasse zur Speicherung von Kalibrierparametern.
 *  @author		Christian
 *  @date		21.12.2014
 */
class Settings{

public:

    //Landmarks: Shapes
    int landMarkShapeOrigin;
    int landMarkShapeReference;

    //Landmarks: Color Ranges
    int landMarkColorOriginMin;
    int landMarkColorOriginMax;
    int landMarkColorReferenceMin;
    int landMarkColorReferenceMax;

    //Landmarks: Sizes(cm)
    int landMarkSizeOrigin;
    int landMarkSizeReference;

    //Object: Shape
    int objectShape;

    //Object: Color Range
    int objectColorMin;
    int objectColorMax;

    //Object: Size(cm)
    int objectSizeCM;

    //ObjectLocator: Harris Corner Parameters
    int harrisCornerBlockSize;
    int harrisCornerApertureSize;
    float harrisCornerVariance;
    int harrisCornerThresh;
    int harrisCornerMergeArea;

    //ObjectLocator: Hough Circle Parameters
    int houghCircleThreshold;

    //ObjectLocator: Gaussian Filter Parameters
    int gaussianStandardDeviation;
    int gaussianSize;

    //###Camera Calibration Parameters###//
	enum Pattern { NOT_EXISTING, CHESSBOARD};
	enum InputType { INVALID, CAMERA};

	Size boardSize;            // The size of the board -> Number of items by width and height
	Pattern calibrationPattern;// Chessboard pattern
	float squareSize;          // The size of a square in your defined unit (point, millimeter,etc).
	int nrFrames;              // The number of frames to use from the input for calibration
	float aspectRatio;         // The aspect ratio
	bool bwritePoints;         //  Write detected feature points
	bool bwriteExtrinsics;     // Write extrinsic parameters
	bool calibZeroTangentDist; // Assume zero tangential distortion
	bool calibFixPrincipalPoint;// Fix the principal point at the center
	string outputFileName;      // The name of the file where to write
    int calibPanelHeightMM;
	string input;               

	int cameraID;
	InputType inputType;
	bool goodInput;
	int flag;

private:
	string patternToUse;

public:

	
    /** Methode zum Einlesen von Parametern.
    *  	@return 	Erfolgreich: Ja/Nein
	*/
    bool readSettings();
	
    /** Methode zum Schreiben von Parametern.
    *  	@return 	Erfolgreich: Ja/Nein
    */
    bool writeSettings();

    /** Methode zum Zugriff auf die globale Instanz
     * @return      Globales Settings-Objekt
     */
    static Settings& instance();

private:
	
	/** Methode zur Interpretation der eingelesenen Daten.
	*/
    void interprate();

    /** Konstruktor.
    */
    Settings(){}

};


#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
