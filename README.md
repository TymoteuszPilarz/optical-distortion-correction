# Optical Distortion Correction
Application designed to correct optical distortions produced by zoom lenses in cameras.

This application implements Brown's Distortion Model in C++ to reproduce and eventually correct the distortion in the given image. Here's the [original paper](http://close-range.com/docs/Decentering_Distortion_of_Lenses_Brown_1966_may_444-462.pdf).

GUI was created with the help of wxWidgets library, image processing is done using OpenCV.

# Demonstration
|<img width="1101" alt="Screenshot 2024-03-27 at 4 29 38 AM" src="https://github.com/TymoteuszPilarz/optical-distortion-correction/assets/122737837/0f680cd4-58bd-4ad6-af9a-ebd4ecfc6452">|
|:--:|
|<b>Fig. 1 Barrel distortion </b>|
|<img width="1098" alt="Screenshot 2024-03-27 at 4 30 01 AM" src="https://github.com/TymoteuszPilarz/optical-distortion-correction/assets/122737837/8b38b0bf-9aee-48ee-9266-c9f91e4b9049">|
|<b>Fig. 2 Distortion corrected </b>|
|<img width="1099" alt="Screenshot 2024-03-27 at 4 32 01 AM" src="https://github.com/TymoteuszPilarz/optical-distortion-correction/assets/122737837/cf10e616-e2f7-4210-bdb0-746a8da2184a">|
|<b>Fig. 3 Modeling advanced distortions </b>|


# Building and running
To run this project, the following libraries must be installed fist:
- wxWidgets
- OpenCV
It is recommended to use available package manager on your system to install those requirements. Next, paste the following commands in your terminal in the directory where you cloned this project.
```
mkdir build
cd build
cmake ..
cmake --build .
```
