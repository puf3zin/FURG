#summary system requirements and instructions
#labels psimulator2,Phase-Requirements,Phase-Deploy


= System requirements =

 * *Java Runtime Environment version 7+*
 http://www.oracle.com/technetwork/java/javase/downloads/

 * *Telnet client*
 You can use the built-in client but if you don't like it you can download putty (http://www.putty.org/) on Windows or just use telnet in case of linux/unix system.

 * *Connection psimulator2 to real network*
 See *Use case #3*



= Instructions for installing psimulator2 = 

Download and unzip: [http://code.google.com/p/psimulator/downloads/list]



= Instructions for running psimulator2 =
Psimulator2 is devided into two parts - frontend and backend. Frontend is designed to easily create network topology and display sent or dropped packets in network. Backend handles simulations and everything else under the hood.

== Use case #1: Create and configure network, send packets, display sent and dropped packets ==
=== Create network ===
Run the simulator frontend (GUI) in the command line:

java -jar psimulator2_frontend.jar

 (with the correct path to the jar file) or with double-click (it depends how your OS is set).

In frontend choose New Project then create your own desired network (hint: F1 -> 1. Network creation).
I assume you created your network topology. If you want you can set IP addresses on interfaces with right-click on devices.

Now you can save created network to configuration file via menu: File -> Save.

=== Configure network ===
Run simulator backend (simulation server) in command line:

java -jar psimulator2_backend.jar path_to_the_config_file_you_created.xml

(with the correct path to the jar file). The program prints after startup telnet ports of all virtual network devices you can connect to (typically started on 11000) and the telnet port on which can be connected the frontend to listen simulator events (typically on 12000).


To connect to virtual network device type in linux command line: 

telnet localhost <port of the requested device>

 on windows use putty with telnet protocol and port of the requested device.

Devices can be configured via built-in graphical telnet client:
 # right-click on desired device
 # click on Open telnet


Then you can configure linux and cisco routers in command line environment.


=== Display sent and dropped packets ===
In fronted click on Simulator tab in the top right conner. Then click on Connect to server and fill in IP address of your PC (127.0.0.1) and port of Event server (should be 12000). Port of EventServer is written in backend console, example:

[IMPORTANT] EVENTS_SERVER: PACKET FLOW SERVER: : Server sucessfully started, listening on port: 12000


After successful connection to the Event server you can turn on packet capturing: Capture button.


Send ICMP request from one device to another:
 # connect to device1 via telnet
 # type ping IP, with IP address of some interface on device2
Now you can watch captured packets in frontend.


=== Saving configuration ===
For saving configuration of all devices you can run save command on any device:

save

This command saves configured network to the currently open configuration file.
Or you can save it to a different file:

save new_configuration_file.xml






== Use case #2: Configure already created network with built-in graphical telnet client ==
 # Run frontend, then open already created network file.
 # Run backend with the same configuration file.
 # Connect fronted to backend - Connect to server button in frontend.
 # Right-click on device and "Open telnet".
And now you are ready to type commands with this new telnet window.




== Use case #3: Connect psimulator2 to real network ==
Connecting psimulator2 to real network is available only on linux/unix systems because of some limitations of Winpcap.

=== System requirements and instalation ===
This extra requirements are needed for connecting simulator to real network:
library libpcap - install from repository (this library is used by tcpdump, maybe you alrady have it)
library libjnetpcap.so - provided in psimulator2 package, copy or link it to /usr/lib
VDE2 - program for creating virtual network interfaces, install from repository (on debian: aptitude install vde2)


=== Creating link between virtual and real network ===
For connection to real network work it has to exist 2 virtual interface on (real) host system. First (tap0) will be used for communication of host system with simulator and the second (sim0) will be used and controlled by simulator. These two interfaces has to be connected to each other by virtual cable (with help of VDE util and script virt_iface.sh). Interface sim0 has to be tied together with some switchport of device in virtual network. Interface sim0 shouldn't be configured in host system.

 # In frontend add Real PC to virtual network (icon with house), attach cable to this new Real PC and some other device. Save this configuration to a file and run backend with this file.
 # On host system run script: (this script creates 2 virtual interfaces connected with cable to each other)

./virt_iface.sh pair sim0 tap0
 
 # In backend you have make connection to some device and run command rnetconn. This command was created for joining swichtport from simulator with sim0 from host system. This command you can run from any device. Command 

router0:~# rnetconn list
Device name     switchport no.  state

  will print list of all switchports in simulator which can be tied to interface sim0. If in the simulator doesn't exist any Real PC this command produce empty list of switchports. In that case you have shutdown backend and add Real PC in frontend (back to point 1).
 # Tie interface sim0 with switchport from output of rnetconn list:

rnetconn tie router2 1 sim0
 
This command ties switchport number 1 on device router2 with interface sim0 (host system interface).

Configure interface tap0 on host system (/proc/sys/net/ipv4/ip_forward and NAT if needed).




<hr>

*If you encounter any exception, please send us exception log ([http://groups.google.com/group/psimulator2-developers mailing list]) - in current directory should be file named "psimulator2_exceptions_yyyy-mm-dd.txt" with short description what you were just doing. Thank you!*