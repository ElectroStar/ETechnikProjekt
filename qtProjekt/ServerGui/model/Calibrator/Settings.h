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


#ifndef SETTINGS_H
#define	SETTINGS_H

/** Klasse zur Speicherung von Kalibrierparametern.
 *  @author		Christian
 *  @date		21.12.2014
 */
class Settings{

public:

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
	string input;               

	int cameraID;
	InputType inputType;
	bool goodInput;
	int flag;

private:
	string patternToUse;

public:

	/** Konstruktor.
	*/
	Settings() : goodInput(false) {}
	
	/** Methode zum Einlesen der Kalibrierparameter.
	*  	@param[in] _a 	XML-Datei
	*/
	void readSettings(const FileNode& node);
	
private:
	
	/** Methode zur Interpretation der eingelesenen Daten.
	*/
	void interprate();

};


#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        