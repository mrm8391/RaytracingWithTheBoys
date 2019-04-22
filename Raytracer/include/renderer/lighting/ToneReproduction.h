/*
Tone reproduction functionality.

Implemented as static functions, as the world/camera
shouldn't need to "own" a single type of reproduction.
In practice, several different methods can be applied
in a pipeline to postprocess results.

Currently, methods operate on 2D vectors of radiance values
*/

#ifndef RT_TONEREPRO_H
#define RT_TONEREPRO_H

#include <vector>
#include "renderer/Vector.h"

class ToneReproduction{
public: 
	/*
	Very basic conversion to RGB. For each of R, G, B radiances:
	[0-max] -> [0–1.0] -> [0-255]

	@param radiances Input radiances in 2d list of RGB vectors. Radiances unbounded.

	@return RGB pixel values, normalized from radiance input. Bounded [0-255]
	*/
	static std::vector<std::vector<Vector>> LinearScale(std::vector<std::vector<Vector>> radiances);

	/*
	Ward conversion to RGB. 

	@param radiances Input radiances in 2d list of RGB vectors. Radiances unbounded.

	@return RGB pixel values, normalized from radiance input. Bounded [0-255]
	*/
	static std::vector<std::vector<Vector>> WardScale(std::vector<std::vector<Vector>> radiances);

};

#endif
