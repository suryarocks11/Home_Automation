# Home_Automation
Program to make  Automate the AC Current Switch Boards

Working of this project is easily understandable. 
When we press any button of IR Remote then remote sends a code in form of train of encoded pulses using 38Khz modulating frequency. 
These pulses are received by TSOP1738 sensor and read by Arduino and then Arduino decodes received train of pulse into a hex value and compares that decoded value with the predefined hex value of the pressed button. 
 
 Here in this project we have used 4 Relay switch Board
