#include "FieldLocator.h"
#include "..//PositionService/ObjectLocator.h"
#include <stdio.h>

using namespace std;
using namespace cv;

FieldLocator::FieldLocator(){

	ps = new ObjectLocator();
	origin = LocatableObject(RECTANGLE, 0, 127, 20);
	reference = LocatableObject(RECTANGLE, 128, 255, 20);
}

FieldLocator::FieldLocator(LocatableObject _origin, LocatableObject _reference){

	ps = new ObjectLocator();
	origin = _origin;
	reference = _reference;
}

vector<LocatedObject> FieldLocator::locateField(Mat _src){

    vector<LocatedObject> result;

	//Alle Objekte finden, die aussehen wie das Muster
	vector<LocatedObject> ori = ps->getAllObjects(_src, origin);

	if (ori.size() == 1){
        result.push_back(ori[0]);
	}

	//Alle Objekte finden, die aussehen wie das Muster
	vector<LocatedObject> ref = ps->getAllObjects(_src, reference);

	if (ref.size() == 1){
        result.push_back(ref[0]);
	}

	return  result;
}
