[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: Skylens
    * Team Members: Jason Ventura, Eric Zou
    * Github Repository URL: https://github.com/ese3500/final-project-skylens
    * Github Pages Website URL: [for final submission]
    * Description of hardware: Laptop (For now)

## Final Project Proposal

### 1. Abstract

Our final project is SkyLens, an automated drone camera. The user can select various modes to take pictures or videos of themselves and their surroundings from novel angles without needing to control the drone themselves. 

### 2. Motivation

We believe the product can be the best of both worlds between selfie sticks and drones, especially well suited to tourism, streaming/vlogging, and atheltics, where convenience is a key consideration in filming equipment.

Regular selfie sticks require someone to hold them, which gives an inherent limitation to the types of shots that can be taken with a selfie stick. Additionally, the selfie stick will need to be removed from the picture either with a camera adjustment that can decrease image quality or editing afterwards.

Drone photos can avoid this issue, but they are much more difficult to take. An operator is required, oftentimes separate from the user if they are in the photo. They also require some degree of familiarity with drones, else the user risks crashing them and losing both the drone and the camera.

We aim to make an autonomous drone that offers similar functionality to a selfie stick without the inherent limits, while avoiding some of the technical expertise required to successfully perate a drone.

### 3. Goals

1. Achieve autonomous control of drone with software
2. Stream camera input to IOT device
3. Attach camera and sensors to drone
4. Enable flight from hand and back

### 4. Software Requirements Specification (SRS)

- Mode selection shall be possible through IOT Device
- Software shall enable sending and receiving photos through IOT Device
- Software shall be able to instruct the drone to ascend 1m and move forward 1m, take a picture, and return to same location
- Software shall be able to instruct the drone to ascend 1m and move forward 1m, then circle around origin to take a video for 5 seconds, then return to original position
- Software shall be able to instruct the drone to ascend above the user and face a specified direction, take a video in focus for 5 seconds, and return to original position

### 5. Hardware Requirements Specification (HRS)

- Drone shall have 4 ultrasonic sensors to measure distance to obstacles at maximum distance of 20 cm
- Drone shall have shall ESC capability for quad-rotor drone with PWM
- Drone shall have small camera connected to ESP32 camera module attached
- Drone shall have WiFi board to send photos to IOT device
- Drone shall have pressure sensor to deactivate flight when hand is detected
- Drone shall have button to begin photo capture sequence
- Project shall be based on ATMega328PB Microcontroller
- Project should use Raspberry Pi for camera data processing

### 6. MVP Demo

We hope to have a drone that can perform the basic action of lifting off, moving to a higher position that is further away, taking a photo, and returning to the same location and hovering to await a deactivation response from the user (grabbing the drone).

### 7. Final Demo

We want to have the various video modes completed (Zoom, Circle). We also want to create touch sensors for stopping the drone when it returns to the hand. 

### 8. Methodology

We'd like to teardown the control system of a 3rd party drone to send control inputs through this device from a microcontroller, which would also have a WiFi board to send signals. On the drone, we would mount a camera system with a WiFi controller for broadcasting messages to an IOT device, and an IMU and ultrasonic sensors for control purposes.

### 9. Components

- Drone
- ATMega328PB
- Possibly Raspberry Pi
- Camera
- Gimbal
- Camera Board
- Pressure Sensor
- WiFi Board
- Batteries
- IMU

### 10. Evaluation

- Drone shall be functional after 10 repeated runs
- Drone shall capture photos
- Drone shall not impact any obstacles in any scenario
- Drone shall send captured photos to IOT device

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task** | **Assigned To**    |
|----------           |--------- |------------------- |
| Week 1: 3/24 - 3/31 |  Block Diagram      | Jason |
| Week 1: 3/24 - 3/31 |  Select and Order Parts      |   Eric |
| Week 2: 4/1 - 4/7   |    Teardown Drone/Controller, Control Planning      |          Jason          |
| Week 2: 4/1 - 4/7   |    Camera and Drone Control Software Start   |          Eric          |
| Week 3: 4/8 - 4/14  |    Drone Attachment/Assembly      |            Jason/Eric        |
| Week 4: 4/15 - 4/21 |     Video Mode     |         Eric           |
| Week 4: 4/15 - 4/21 |     Ultrasonic Sensor Integration     |         Jason           |
| Week 5: 4/22 - 4/26 |     Quality Testing/Bug Fixing     |        Eric/Jason            |
| Week 5: 4/22 - 4/26 |     Touch Sensor Assembly     |        Eric/Jason            |

### 12. Proposal Presentation

[Add your slides to the Final Project Proposal slide deck in the Google Drive.](https://docs.google.com/presentation/d/1-Z5W7xg-WeICQvAZcTpaSmDrNKGdcdJ_jiM9-PyDwvM/edit?usp=sharing)

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

[Insert final project video here]

### 2. Images

[Insert final project images here]

### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
