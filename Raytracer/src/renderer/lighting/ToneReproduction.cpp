
#include "renderer/lighting/ToneReproduction.h"

using namespace std;

static vector<vector<Vector>> ToneReproduction::LinearScale(vector<vector<Vector>> radiances){

	double maxR=0,maxG=0,maxB=0;

	//scan for max values in input
	for (int i = 0; i < radiances.size(); i++) {
		for (int j = 0; j < radiances[i].size(); j++) {
			Vector cur = radiances[i][j];

			if(cur.vec[0]>maxR) maxR=cur.vec[0];

			if(cur.vec[1]>maxG) maxG=cur.vec[1];

			if(cur.vec[2]>maxB) maxB=cur.vec[2];
		}
	}

	vector<vector<Vector>> pixels;

	//normalize and set output list
	for (int i = 0; i < radiances.size(); i++) {
		pixels.push_back(vector<Vector>());

		for (int j = 0; j < radiances[i].size(); j++) {
			Vector cur = radiances[i][j];

			double r = (cur.vec[0]/maxR) * 255,
				g = (cur.vec[1]/maxG) * 255,
				b = (cur.vec[2]/maxB) * 255;

			pixels[i].push_back(Vector(r,g,b));
		}
	}

	return pixels;
}
