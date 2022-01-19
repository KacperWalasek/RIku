#!/bin/bash
mkdir bin
cp -r Riku/assets bin/assets
cp -r Riku/mini_assets bin/mini_assets
cp -r Riku/GUI bin/GUI
cp -r Riku/lang bin/lang
cp -r Riku/shaders bin/shaders
cp Riku/frontend_config.json bin/frontend_config.json
cp Riku/linux-launch.sh bin/linux-launch.sh
mkdir bin/bin
cp -r Riku/cmake-build-debug/Riku bin/bin

