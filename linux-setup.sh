Needed version of GCC: >=10

#Needed packages:
#libassimp-dev (Assimp >=5.0)
#libglew-dev (GLEW >=2.1.0)
#libgl-dev (OpenGL)
#libglfw3-dev (GLFW >=3.3)
#libjsoncpp-dev (JsonCpp >=1.7.4)
#liblua5.3-dev (Lua 5.3)
#libcegui-mk2-dev (CEGUI >=0.8.7)
#libglm-dev (GL Math >=0.9)
#libxi-dev (Lib Xi)

sudo -i
apt install libgl-dev
apt install libglew-dev
apt install libglfw3-dev
apt install libassimp-dev
apt install libjsoncpp-dev
apt install liblua5.3-dev
apt install libcegui-mk2-dev
apt install libglm-dev
apt install libxi-dev
#install zmq
echo 'deb http://download.opensuse.org/repositories/network:/messaging:/zeromq:/release-stable/xUbuntu_20.04/ /' | sudo tee /etc/apt/sources.list.d/network:messaging:zeromq:release-stable.list
curl -fsSL https://download.opensuse.org/repositories/network:messaging:zeromq:release-stable/xUbuntu_20.04/Release.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/network_messaging_zeromq_release-stable.gpg > /dev/null
sudo apt update
sudo apt install libzmq3-dev
exit
