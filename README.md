# AndroidSecurityCam
Do you have an old Android phone collecting dust? Turn it into a personal home security camera! You can monitor your home from a distance and even detect motion! In this repo is a C++ application to help you with that.

# Hardware
Blu View 5 - 64GB ($30 new)<br>
2018 Macbook Pro - Intel

# Set-up
1. Set up Android phone
    - Enable developer mode and USB debugging: https://developer.android.com/studio/debug/dev-options
3. Set up computer
    - https://youtu.be/daVygBAm1zs?si=olO191Lk8e9ZqMgy
    - `brew install opencv`
4. Set up ADB over Wi-Fi
    - Pair Android and computer: https://youtu.be/_JjpbufTMew?si=aIq0UF8aaCMnPRDy]

# Run program
Warning: Out of the box, application clears Android phone's saved photos library on startup to save phone's memory.<br>
1. `make clean`
2. `make`
3. `./camera <phone_ip_address>:<phone_port> <path to computer folder for temp images> <path to computer folder for motion images> <path to phone saved images folder>"`<br><br>
For example: `./camera 192.168.0.188:40427 Images/ Images/Motion/ /sdcard/DCIM/Camera/`<br><br>
4. Leave Android phone camera pointed where you want to monitor.

# Resources
- https://youtu.be/uOPcUjVl2YQ?si=ZE6an89KVADLmNJ2
