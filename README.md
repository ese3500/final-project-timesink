[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: TimeSink
    * Team Members: Jason Ventura, Eric Zou
    * Github Repository URL: https://github.com/ese3500/final-project-skylens
    * Github Pages Website URL: [for final submission]
    * Description of hardware: Laptop (For now)

## Final Project Proposal

### 1. Abstract

Our final project is TimeSink, an all-in-one bathroom tool to handle organization of common items, reducing mess and clutter on valuable counter real estate while offering a variety of features.

### 2. Motivation

Bathroom counters can be subject to some of the most pressing space constraints out of any place in the home. It can often be a daunting challenge to iterate on and settle on an arrangement of various home products like toothbrushes, toothpaste, and soap that conserves space while maintaining convenience. Additionally, the sink itself does little in the way of active assistance to the user, with no built-in functionality like lights, clocks, or self-cleaning capabilities. All of these issues combined can often result in the perfect storm, conspiring against users to leave the bathroom sink counter disorganized, unclean, and cluttered. 

We believe that TimeSink can help people organize their bathroom sink counter like never before. We want to make it easy to store and access the 20% of items and tools that will be used 80% of the time in a bathroom setting, reducing cognitive load in critical times such as the morning rush or bedtime and helping users establish a rhythm for their routines.

### 3. Goals

1. Have digital display with current time and weather (IOT?)
2. Have automatic dispensers for soap and toothpaste using ultrasonic sensors
3. Have a motion-activated night light
4. Have a UV light and moisture removal system for toothbrush holder
5. 4x4 inch maximum base dimensions
6. Wall-chargable
7. Waterproof

### 4. Software Requirements Specification (SRS)

- Software shall be written in C for ATmega328PB microcontroller
- Software written in C++ for ESP32 Feather microcontroller
- Software shall process ultrasonic sensor values to detect proximity
- Software shall maintain time and weather data via API calls over WiFi
- Software shall trigger motors to dispense soap and toothpaste with nearby stimulus
- Software shall trigger 3 minute UV light cycle with button press
- Software shall trigger LED light for 2 minutes when IR sensor detects motion
- Software shall handle user setting customization of location (may switch to simple geolocation)

### 5. Hardware Requirements Specification (HRS)

- Project shall contain a wall-based power supply that converts AC to 5V DC with relatively high current (3A)
- Project shall be contained within a 3D printed shell waterproofed by sealant
- Project shall use servo motors as trapdoors to dispense soap and toothpaste
- Project shall contain ultrasonic sensors to detect proximity
- Project shall contain IR sensor for motion detection
- Project shall contain photoresistor that detects surrounding brightness
- Project shall contain bright LED light that can light up room
- Project shall contain LCD that is wired to an ATmega328PB microcontroller
- Project shall contain UV light capable of sterilizing surfaces
- User interface shall be button-based
- ATmega328PB will be attached to ESP32 Feather Module utilizing SPI interface

### BLOCK DIAGRAM
We want to use a 3 microcontroller design for our product for simplicity/parallelism of development (one being the ESP 32 Feather).
![alt text](image.png)
![alt text](image-1.png)

### 6. MVP Demo

We hope to have the dispensers, basic LCD display software, and UV lights finished by the MVP.

### 7. Final Demo

We want IOT for the weather, motion-activated night light, and full LCD display control finished after the MVP, with everything fitting in the housing with waterproofing applied.

### 8. Methodology

We would like to 3D print a frame and housing for each of the components. Ideally, each would have their own compartments/sections in the superstructure for easy assembly. However, each component would essentially be independent, consisting of its own sensor/actuator pair. For example, a dispenser is composed of an ultrasonic sensor to detect proximity of hand or toothbrush, and a motor-based actuator to dispense the required substance.

### 9. Components

- ATmega328PB
- UV Light (MISSING)
- Motors (MISSING, Detkin might have)
- Bright LED
- LCD Screen
- Sealant (MISSING)
- ESP32 Feather WiFi Board
- Ultrasonic Sensors
- IR Sensor (TO TEST DETKIN ONES)
- Logic Level Shifter
- 5V wall power supply (MISSING)
- 3D Printed Shell (MISSING, MVP demo will use cardboard shell)

### TO BE ORDERED
- Flex seal
- 5V wall power supply
- UV Light
- (Possibly) Motors

### 10. Evaluation

#### Dispensers
- Dispensers detect hand positions correctly (within activation range or not) at least 9 times in 10 trials (stimulus)
- Dispensers actuate motors when stimulus is detected and do not otherwise with 100% success rate
- 0.5 g toothpaste is dispensed
- 0.5 g soap is dispensed

#### Display
- Display maintains a real-time synced with external clock or user-set (within 10s of set/real time)
- Display gathers current weather information from 3rd party IOT device and displays it (within 1 hr)

#### Lights
- UV light activates when button is pressed (runs for approximately 3 minutes)
- Motion-activated light turns on in dark when individual moves within 7 feet (8 in 10 success rate)

#### Aesthetics/Ergonomics/Reliability
- Wall/plug charging
- 4x4 inch base size
- Multitasking capability
- All processes should continue to occur over 100 trials of various tasks
- Should survive water splashes

### 11. Timeline

| **Week**            | **Task** | **Assigned To**    |
|----------           |--------- |------------------- |
| Week 1: 3/24 - 3/31 |  Block Diagram      | Jason |
| Week 1: 3/24 - 3/31 |  Select and Order Parts      |   Eric |
| Week 2: 4/1 - 4/7   |   Full 3D Schematic      |          Jason          |
| Week 2: 4/1 - 4/7   |    Software Setup (Git/Microcontroller/etc)   |          Eric          |
| Week 3: 4/8 - 4/14  |    Prototyping Parts with Microcontroller     |            Jason/Eric        |
| Week 4: 4/15 - 4/21 |   Finalize  Software/Hardware Logic for Clock/Display/Lights    |         Eric           |
| Week 4: 4/15 - 4/21 | Finalize   Software/Hardware Logic for Dispensers    |         Jason           |
| Week 5: 4/22 - 4/26 |     Quality Testing/Bug Fixing     |        Eric/Jason            |
| Week 5: 4/22 - 4/26 |     Final Assembly     |        Eric/Jason            |

### 12. Proposal Presentation

[Add your slides to the Final Project Proposal slide deck in the Google Drive.](https://docs.google.com/presentation/d/1ALSWUez5a50TZqg0WIl5mQYvlcQxWxVERMfJZsW72Y8/edit?usp=sharing)

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
