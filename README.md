# Esp32-WiFi-Hacking

Libraries: It includes the necessary libraries for WiFi connectivity, DNS server functionality, web server functionality, and SPIFFS (SPI Flash File System) for file storage on the ESP32.

Constants: It defines constants such as the WiFi SSID and password, an IP address for the access point (AP), file names for storing login information and images, and the duration since the ESP32 was powered on.

HTML Content: It defines HTML content for the login page (index() function) and assigns it to the index variable. This HTML content includes a basic form for entering email and password.

Handler Functions: It defines functions to handle different HTTP requests:

handlePost(): Handles POST requests, extracts email and password from the request, saves them to a log file along with the current time, and redirects the user to the /info page.

handlePass(): Generates a page displaying the logged-in information from the log file.

handleDelete(): Deletes the log file.

handleInfo(): Handles requests for displaying an image.

handleDownload(): Handles requests for downloading the log file.

Time Formatting Function: It defines a function (formatTimeSinceStart()) to format the time since the ESP32 was powered on in days, hours, minutes, and seconds.

Setup Function:

Initializes serial communication.
Configures WiFi to operate in both AP and station (STA) mode.
Sets up the SPIFFS file system.
Starts the DNS server and configures it to spoof DNS requests to redirect HTTP traffic to the ESP32.
Configures routes for different HTTP requests to call the corresponding handler functions.
Starts the web server.
Loop Function: It continuously processes DNS requests and handles web server client requests.

Overall, this code turns the ESP32 into a web server that hosts a login page, stores login information in a log file, and serves images. It also provides functionality to delete the log file and download it.

/pass <- Address to view information for your account

/down <- Download the information in the pass.

/info <- Enter the information and show the picture as a reward.  Photo information: 1.png ]

/delete <- Delete the entered information.


All legal issues are not with the developer, and the person responsible for exploiting the code is with the code downloader

WARNING: The developer is making an error and is a wife who is likely to lose her data. The risk of using it is your responsibility and the responsibility of the end user. There is a "99%" but a "1%" is terrible!

I made it with reference. : https://github.com/Alpha-1729/ESP_WiFi_Captive_Portal
Loved the code for esp8266, so I made it for esp32. Not the same code. Made it easier to write. Understand what the code says.
