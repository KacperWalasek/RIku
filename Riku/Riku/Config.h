//
// Created by kamil-hp on 06.09.2021.
//

#ifndef RIKU_FRONTENDCONFIG_H
#define RIKU_FRONTENDCONFIG_H

#include <string>

namespace front {
	class Config {
	public:
		bool load();
		bool save() const;

		int screenWidth = 800;
		int screenHeight = 600;
		bool isFullscreen = false;
		float angle = 80.f;
		float fov = 45.f;
		float maxZoomHeight = 60.f;
		float minZoomHeight = 3.f;
	};
}


#endif //RIKU_FRONTENDCONFIG_H
