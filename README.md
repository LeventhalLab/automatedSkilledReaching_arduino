# Automated Skilled Reaching Arduino
Developed for use with a mouse single-pellet skilled reaching task. A remote controls an actuator to move a rod, retreiving sugar pellets for mice to reach for.

Behavioral chamber designed based on Farr and Wishaw, 2002 <sup>[1]</sup> and the automated system is developed from Ellens, et al., 2016 <sup>[2]</sup>.


![Version: 2.0](https://img.shields.io/badge/version-2.0-informational)
[![License: AFL-3.0](https://img.shields.io/badge/License-Academic%20Free%20License%20v3.0-Yellow)](https://opensource.org/licenses/AFL-3.0)


[![mouse single-pellet skilled reaching system](https://github.com/kristakernodle/automatedSkilledReaching_arduino/blob/master/docs/pics/mouse_autoSR_chamber.png)](https://leventhal.lab.medicine.umich.edu/projects/rodent-model-of-task-specific-dystonia)

---

## Installation
- [Download and install the Arduino IDE](https://www.arduino.cc/en/main/software)
- [Install Adafruit Motor Sheild V2 library](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-software)
- To verify the motor shield v2 library is installed correctly, attempt to compile the software. 
- Clone this repository to the local computer
- Open the file: skilledReaching_finalProgram/skilledReaching_finalProgram.ino
- With the arduino plugged into the computer, upload the software to the arduino.

You should now be able to use the automated skilled reaching set up. 

---

## Set Up

- Behavioral chamber designed based on Farr and Wishaw, 2002 <sup>[1]</sup> and the automated system is developed from Ellens, et al., 2016 <sup>[2]</sup>.
- Hardware wiring diagrams are available. Click [here for the arduino enclosure](https://app.lucidchart.com/documents/view/3c985da0-a261-4bc2-9ef6-2c803c5bdd07) and [here for the remote](https://app.lucidchart.com/documents/view/a5575cea-aeed-4930-a110-d00aac3ece58). For more information, please contact @KristaKernodle
- Update pin locations to represent the relevant hardware
- Verify that all switches and the LED are wired such that they are only HIGH when pressed/on.

<a href="https://app.lucidchart.com/documents/view/3c985da0-a261-4bc2-9ef6-2c803c5bdd07"><img src="https://github.com/kristakernodle/automatedSkilledReaching_arduino/blob/master/docs/pics/mouse_autoSR_arduinoBox.png" alt="Mouse single-pellet skilled reaching system, Arduino" width="500"/></a>
<a href="https://app.lucidchart.com/documents/view/a5575cea-aeed-4930-a110-d00aac3ece58"><img src="https://github.com/kristakernodle/automatedSkilledReaching_arduino/blob/master/docs/pics/mouse_autoSR_remote.png" alt="Mouse single-pellet skilled reaching system, remote" width="175"/></a>

---

## References

<sup>[1]</sup>: https://www.ncbi.nlm.nih.gov/pubmed/12105368

<sup>[2]</sup>: https://www.ncbi.nlm.nih.gov/pubmed/27450925
