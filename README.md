**GRC Al-Cam development board example application**

This folder contains the code for nRF52833 microcontroller, which is the part of GRC Al-Cam Development Board.
It is the Zephyr OS based application, that is intended to be built using nRF Сonnect SDK.
Some of the features demonstrated in this example are:

- implementation of the protocol (based on AT commands) beetween PC and Development Board, USB-UART or
Bluetooth interfaces can be used for the control of the device, getting camera pictures and recognition
results and for some others reasons;
- implementation of SPI intercommunication between nRF and Himax microcontrollers
- distances to object measurement by using Time-of-flight-Sensor, the wake-up procedure of the
nRF52833 microcontroller by external events, in the situation when an object has appeared
- saving the history of the recognized objects, history can be sent to the host at any time later

**Getting started**

Before getting started, make sure You have a proper nRF Connect SDK development environment.
The current version of the project is used with nRF Connect SDK v.2.9.0 and Toolchain of the same version.

How prepare the environment:

- install nRF for Desktop v.5.0.2
- install nRF Connect SDK v.2.9.0
- install Visual Studio Code with the necessary extensions 
  - nRF Connect for VS Code
  - nRF Connect for VS Code Extension Pack
  - nRF DeviceTree
  - nRF Kconfig
  - nRF Terminal

How to build the project:

- clone this repository
- run VS Code, and open the folder which containing this project
- click on the "nRF Connect" icon on the left vertical panel
- choose APPLICATION - objdet - "Add build configuration" and create the configuration 
for nRF52833_allcam/nRF52833 board
- mark checkbox "Use sysbuid", unless sysbuild is the default mode
- press the "Build Configuration" button at the bottom of the "Edit Build Configuration" window
- wait until the project is built

**Bootloader**

GRC Al-Cam Development Board contains the bootloader utility. It is a small program pre-installed 
on Your microcontroller nRF52833, it gives possible to upload new firmware without any special 
programming tools.

You need to install mcumgr utility, which You can find here -  <https://github.com/apache/mynewt-mcumgr>.

For turning on the bootloader mode on the development board You have to do next:

- turn off usb connector from the board
- press and hold the SW2 button on the board (closest to LED),
- turn on usb connector from the board

After that You can use mcumgr for uploading You software. 
The script mcumgr_run.bat is intended to help You with this task.

**Control interfaces**

Bluetooth interface is implemented as NUS (Nordic Uart Service):
  Service UUID      : 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
  RX Characteristic : 6E400002-B5A3-F393-E0A9-E50E24DCCA9E
  TX Characteristic : 6E400003-B5A3-F393-E0A9-E50E24DCCA9E

USB-UART interface is implemented as VCP (Virtual Com Port):
  Baudrate          : 115200
  Data bits         : 8
  Parity            : none
  Stop bit          : one stop bit
  Flow control      : none

**Most usefull commands**

AT commands. wich are sent to device, must be ended by symbol '\n'.
AT commands system is the same for both interfaces and most used commands
is gave in the tables below.

1. Auxiliary commands

<table border="1">
  <tr>
    <th>Command</th>
    <th>Answer / Example of the answer</th>
    <th>Functionality</th>
  </tr>
  <tr>
    <td>AT\n</td>
    <td>AT\n</td>
    <td>AT\n will be returned</td>
  </tr>
  <tr>
    <td>AT^ECHO=&lt;string&gt;\n</td>
    <td>&lt;string&gt;\n</td>
    <td>Echo mode, sent string will be returned</td>
  </tr>
  <tr>
    <td>AT^REBOOT\n</td>
    <td>OK\n</td>
    <td>The nRF device will be rebooted in two seconds</td>
  </tr>
</table>


2. Commands for getting the information about the device

<table border="1">
  <tr>
    <th>Command</th>
    <th>Answer / Example of the answer</th>
    <th>Functionality</th>
  </tr>
  <tr>
    <td>AT^SWNVER\n</td>
    <td>01.00.00\n</td>
    <td>nRF firmware version</td>
  </tr>
  <tr>
    <td>AT^HWNVER\n</td>
    <td>01.00.02\n</td>
    <td>nRF hardware revision</td>
  </tr>
  <tr>
    <td>AT^SWHVER\n</td>
    <td>01.00.03\n</td>
    <td>Himax firmware version</td>
  </tr>
  <tr>
    <td>AT^HWHVER\n</td>
    <td>01.00.04\n</td>
    <td>Himax hardware revision</td>
  </tr>
  <tr>
    <td>AT^DTVER\n</td>
    <td>Feb 3 2025,09:39:30;\n</td>
    <td>The last build timestamp of the nRF firmware</td>
  </tr>
</table>

3. Commands for reading images from camera

<table border="1">
  <tr>
    <th>Command</th>
    <th>Answer / Example of the answer</th>
    <th>Functionality</th>
  </tr>
  <tr>
    <td>AT&IMAGE\n</td>
    <td>OK\n</td>
    <td>Take the camera picture</td>
  </tr>
  <tr>
    <td>AT&RDIMG\n</td>
    <td>#240&lt;B0&gt;&lt;B1&gt;&lt;B2&gt;..&lt;B239&gt;</td>
    <td rowspan="2">byte 0 : '!' - last fragment, '#' - no last fragment
      <br>bytes 1..3 : the number of binary data (001..240)
      <br>bytes 4.. : binary data, a chunk of jpeg image</td>
  </tr>
  <tr>
    <td>AT&RINEXT\n</td>
    <td>#240&lt;B0&gt;&lt;B1&gt;&lt;B2&gt;..&lt;B239&gt; (no last chunk)<br>!016&lt;B0&gt;&lt;B1&gt;&lt;B2&gt;..&lt;B16&gt; (last chunk)</td>
  </tr>
</table>

The reading image procedure:
  - Send command AT&IMAGE
  - Read jpeg fragments, merge them to the buffer, if we have read last fragment - stop

4. Commands for reading the list of recognized objects

<table border="1">
  <tr>
    <th>Command</th>
    <th>Answer / Example of the answer</th>
    <th>Functionality</th>
  </tr>
  <tr>
    <td>AT+LRREAD=&lt;count&gt;\n</td>
    <td rowspan="2">hedgehog,2025-04-05 00:00:30,N;cat,2025-04-06 <br> 12:11:33,Y;tiger 2025-04-06 12:55:11,N\n</td>
    <td rowspan="2">The sequence of &lt;count&gt; records (count can be 1..7)<br>&lt;REC1&gt;;&lt;REC2&gt;;..&lt;RECcount&gt; each of them have format<br>&lt;objname&gt;,&lt;timestamp&gt;,&lt;flag&gt;<br>&lt;objname&gt; - the name of the object<br>&lt;timestamp&gt; - date and time of the recognition point<br>(format YYYY-MM-DD HH:MM:SS)<br>flag - object was expected or not, Y or N</td>
  </tr>
  <tr>
    <td>AT+LRRDNEXT=&lt;count&gt;\n</td>
  </tr>
</table>

The reading history procedure:
  - send command AT+LRREAD, read the first chunk of the list
  - send commands AT+LRRDNEXT repeatedly, each will read the next chunk of the list, until empty string will be returned

5. Commands witch are related to TOF sensor

<table border="1">
  <tr>
    <th>Command</th>
    <th>Answer / Example of the answer</th>
    <th>Functionality</th>
  </tr>
  <tr>
    <td>AT&SMODE=&lt;mode&gt;\n</td>
    <td>OK\n</td>
    <td>Set work mode for TOF sensor, mode can be TIMER, OFF, AUTO+</td>
  </tr>
  <tr>
    <td>AT&RDDIST\n</td>
    <td>10,64351\n (bad result)<br>0,222\n (good result)</td>
    <td>The string &lt;status&gt;&lt;distance&gt; will be returned.<br>Status - the error code of measurement (UM2133, “Table 1. Range status”.)<br>Distance - the distance to object, mm</td>
  </tr>
</table>

The distance measurement procedure:
  - send command AT&SMODE=TIMER for turning on the sensor
  - send one or more commands AT&RDDIST to get the measurement results
