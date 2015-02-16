//============================================================================
// Datei	: ObjectLocator.cpp
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include "ObjectLocator.h"
#include "config.h"

ObjectLocator::ObjectLocator(): blockSize(harrisCornerBlockSize), apertureSize(harrisCornerApertureSize), k(harrisCornerVariance), thresh(harrisCornerThresh) {

}

ObjectLocator::~ObjectLocator(){

}

vector<LocatedObject> ObjectLocator::getAllObjects(Mat _src, LocatableObject _spec) {

	//Ergebnisvektor anlegen
	vector<LocatedObject> objects;

	//Bild in 8-Bit grau umwandeln
	Mat src_gray;
	cvtColor(_src, src_gray, CV_BGR2GRAY);

	//Rauschen rausfiltern
	Mat src_gray_blurred;
    GaussianBlur(src_gray, src_gray_blurred, Size(gaussianSize, gaussianSize), gaussianStandardDeviation, gaussianStandardDeviation);

	//Hough Transformation fuer Kreise anwenden
    HoughCircles(src_gray_blurred, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 20, 200, houghCircleThreshold, 0, 0);

	//Die gefundenen Kreise auswerten
    if (circles.size() > 0){

		for (unsigned int i = 0; i < circles.size(); i++)
		{

			//Bild zuschneiden, extra Behandlung an Bildraendern
            int referencePx = circles[i][0] - circles[i][2];
            int referencePy = circles[i][1] - circles[i][2];

			int width = 2 * circles[i][2];
			int height = 2 * circles[i][2];

			if (circles[i][0] < circles[i][2]){

				width = 2 * circles[i][2] + referencePx;
				referencePx = 0;
			}

			if (circles[i][1] < circles[i][2]){

				height = 2 * circles[i][2] + referencePy;
				referencePy = 0;
			}

			if ((_src.cols - circles[i][0]) < circles[i][2]){

				width = _src.cols - referencePx;
			}

			if ((_src.rows - circles[i][1]) < circles[i][2]){

				height = _src.rows - referencePy;
			}

			Rect area(referencePx, referencePy, width, height);
			Mat cropped = src_gray(area);

			//Harris Kantenerkennung
			Mat corners, corners_norm, corners_norm_scaled;
			cornerHarris(cropped, corners, blockSize, apertureSize, k, BORDER_DEFAULT);

			//Normalisierung
			normalize(corners, corners_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
			convertScaleAbs(corners_norm, corners_norm_scaled);

			//Kanten im zugeschnittenen Bild ermitteln
			for (int j = 0; j < corners_norm.rows; j++)
			{
				for (int k = 0; k < corners_norm.cols; k++)
				{
					if ((int)corners_norm.at<float>(j, k) > thresh)
					{
						bool foundNew = true;

						for (unsigned int l = 0; l < cornerP.size(); l++){

                            if (abs(cornerP[l].x - k) <= harrisCornerMergeArea && abs(cornerP[l].y - j) <= harrisCornerMergeArea){

								foundNew = false;
								cornerP[l].x = (cornerP[l].x + k) / 2;
								cornerP[l].y = (cornerP[l].y + j) / 2;
								break;
							}
						}

						if (foundNew){

							cornerP.push_back(Point(k, j));
						}
					}
				}
			}

            //Pruefen, ob passende Form gefunden wurde
			if (cornerP.size() == _spec.form){

				//Offset wieder draufaddieren, Zentrum berechnen
				Point center(0, 0);
				for (unsigned int m = 0; m < cornerP.size(); m++){

					cornerP[m].x += referencePx;
					center.x += cornerP[m].x;
					cornerP[m].y += referencePy;
					center.y += cornerP[m].y;
				}

				center.x = center.x / cornerP.size();
				center.y = center.y / cornerP.size();


				//Farbe im zentralen Punkt pruefen
				if (src_gray_blurred.at<uchar>(Point(center.x, center.y)) <= _spec.colorMax &&
					src_gray_blurred.at<uchar>(Point(center.x, center.y)) >= _spec.colorMin){

					//Laenge einer Aussenkante berechnen (Euklid)
					//Funktioniert fuer Dreiecke und Vierecke
					int distance = (int)sqrt(pow(cornerP[0].x - cornerP[1].x, 2) + pow(cornerP[0].y - cornerP[1].y, 2));

					//Gefundenes Objekt speichern
					objects.push_back(LocatedObject(Point(center.x, center.y), distance, _spec));
				}

			}

			cornerP.clear();

		}

		circles.clear();
	}


	return objects;
}
