[![LinkedIn][linkedin-shield]][linkedin-url]
<!--
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]


[![Github][github-shield]][github.com/zoumson?tab=repositories]
[![Stack Overflow][stackoverflow-shield]][stackoverflow.com/users/11175375/adam]
[![Leetcode][leetcode-shield]][eetcode.com/Hard_Code/]
-->
## Multi-Client single server using multi-threading
![image](https://user-images.githubusercontent.com/38358621/120076656-41d75780-c0d9-11eb-97fc-7f56e4cfa9bf.png)



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#file-structure">Files Structure</a>
      <ul>
        <li><a href="#folders">Folders</a></li>
        <li><a href="#entire-files-structure">Entire Files Structure</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>




<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

The primary intention of writing this project is to give an overview of how one can entertain multiple client requests to a server in parallel. 
In this project a TCP/IP server is created. The server can receive multiple client requests at the same time and entertain each client request 
in parallel so that no client will have to wait for server time. 

The TCP/IP server has been designed with multi-threading for parallel processing.
The server itself is defined as a class. There is another class called myThread that handles the multi-threading mecanism.
A special processor derived class (ProcessSingleClient) to just handle a client that sends a clock time information to the server.

* First of all, the server is initialized then bound to a specific port number
* Next, the server starts listenning to a new connexion
* A new accepted client will get a thread allocated to it and start exhanging with the server

* Parallelly the server will still be listenng to a new connexion

* Logs are generated for both server and client using the boost log library
* Also the command to pass the option to the main function use the boost program_options library

A list of commonly used resources that I find helpful are listed in the acknowledgements.

### Built With


* [boost](https://boost.org/)
* [cmake](https://cmake.org/)
* [gnu](https://www.gnu.org/)



<!-- GETTING STARTED -->
## Getting Started

This is an sample code of how to implement a single server mutilple clients communication mutli-threading.
<br>
To get a local copy up and running follow these simple steps.

## File Structure

### Folders

* [include/](include/): c++ declarations.
* [src/](src/): c++ definitions.


### Entire Files Structure 

```
.
├── CMakeLists.txt
├── include
│   ├── GetLocalAddress.h
│   ├── Manager.h
│   ├── MyClient.h
│   ├── MyProcessor.h
│   ├── MyServer.h
│   ├── MyThread.h
│   └── ProcessSingleClient.h
├── README.md
└── src
    ├── demo
    │   ├── CMakeLists.txt
    │   ├── demoClient
    │   │   └── demoClient.cpp
    │   └── demoServer
    │       └── demoServer.cpp
    └── lib
        ├── CMakeLists.txt
        ├── myClient
        │   └── MyClient.cpp
        └── myServer
            ├── GetLocalAddress.cpp
            ├── MyProcessor.cpp
            ├── MyServer.cpp
            ├── MyThread.cpp
            └── ProcessSingleClient.cpp

8 directories, 19 files

```

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* cmake
  ```sh
  sudo apt-get install cmake
  ```

* [boost](https://stackoverflow.com/questions/8430332/uninstall-boost-and-install-another-version)
  ```sh
  cd /opt
  mkdir boost
  sudo apt-get -y install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev
  wget http://downloads.sourceforge.net/project/boost/boost/1.76.0/boost_1_76_0.tar.gz
  tar -zxvf boost_1_76_0.tar.gz
  cd boost_1_76_0
  # get the no of cpucores to make faster
  cpuCores=`cat /proc/cpuinfo | grep "cpu cores" | uniq | awk '{print $NF}'`
  echo "Available CPU cores: "$cpuCores
  ./bootstrap.sh  # this will generate ./b2
  sudo ./b2 --with=all -j $cpuCores install
  ```
 * Check boost version
  ```sh
  cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
  ```
 * Result
  ```sh
  // BOOST_LIB_VERSION must be defined to be the same as BOOST_VERSION
  #define BOOST_LIB_VERSION "1_76_0"
  ```
  
### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/zoumson/Multi-ClientServer.git
   ```
2. Go to the project directory source
   ```sh
   cd Multi-ClientServer
   ```
3. Create empty directories 
   ```sh
   mkdir build &&  mkdir bin && mkdir log && mkdir lib 
   ```
5. Generate the executables and move them to `bin`
   ```sh
   cd build && cmake .. && make -j4 && cd ..
   ```

<!-- USAGE EXAMPLES -->
## Usage
Command line arguments
<br>
1.  Sever side 

* Command parser using [boost program_options](https://www.boost.org/doc/libs/1_76_0/doc/html/program_options.html)

```
Usage: options_description [options]
Allowed options:
  -h [ --help ]                         produce help message
  -p [ --port ] [=arg(=60000)] (=no)    server port number.
  -c [ --connexion ] [=arg(=10)] (=few) server max connexion.
  -l [ --log ] [=arg(=server.log)] (=server.log)
                                        server log name
```
* Dafaut server port number: random available port from host
   ```sh
   ./server 
   ```
* Implicit server port number: 60000
   ```sh
   ./server -p
   ```
 * Self defined server port number: myPort
   ```sh
   ./server -p myPort
   ```
  * Server log: `2021_05_28_02_08_11_server.log`
  * Sample server log
  
  
  ```
  [2021-05-28 02:08:11]<6>: Server IP: [192.168.1.106]
  [2021-05-28 02:08:11]<6>: Server max connexion: [5]
  [2021-05-28 02:08:11]<6>: Creating a server socket ...
  [2021-05-28 02:08:11]<6>: A client socket created
  [2021-05-28 02:08:11]<6>: Binding to a local port ...
  [2021-05-28 02:08:11]<6>: Bind success
  [2021-05-28 02:08:11]<6>: Server Port Number: [60000]
  [2021-05-28 02:08:11]<6>: Listenning to a new connexion...
  [2021-05-28 02:08:11]<6>: A client connected to a server
  [2021-05-28 02:08:11]<6>: Accepting a connexion...
  [2021-05-28 02:08:42]<6>: Connexion accepted
  [2021-05-28 02:08:42]<6>: Client IP: [192.168.1.106]
  [2021-05-28 02:08:42]<6>: Client Port Number: [49034]
  [2021-05-28 02:08:42]<6>: Accepting a connexion...
  [2021-05-28 02:08:42]<6>: Time received from the client 6: 02:08:42
  [2021-05-28 02:08:48]<6>: Time received from the client 6: 02:08:48
  [2021-05-28 02:08:54]<6>: Time received from the client 6: 02:08:54
  [2021-05-28 02:09:00]<6>: Time received from the client 6: 02:09:00
  [2021-05-28 02:09:06]<6>: Time received from the client 6: 02:09:06
  [2021-05-28 02:09:12]<6>: Time received from the client 6: 02:09:12
  [2021-05-28 02:09:18]<6>: Connexion accepted
  [2021-05-28 02:09:18]<6>: Client IP: [192.168.1.106]
  [2021-05-28 02:09:18]<6>: Client Port Number: [49036]
  [2021-05-28 02:09:18]<6>: Accepting a connexion...
  [2021-05-28 02:09:18]<6>: Time received from the client 7: 02:09:18
  [2021-05-28 02:09:18]<6>: Time received from the client 6: 02:09:18
  [2021-05-28 02:09:24]<6>: Time received from the client 7: 02:09:24
  [2021-05-28 02:09:24]<6>: Time received from the client 6: 02:09:24
  [2021-05-28 02:09:30]<6>: Closing connexion with client: 7
  [2021-05-28 02:09:30]<6>: A Server closing an accpeted connexion ...
  [2021-05-28 02:09:30]<6>: Accepted connexion closed
  [2021-05-28 02:09:30]<6>: Time received from the client 6: 02:09:30
  [2021-05-28 02:09:36]<6>: Closing connexion with client: 6
  [2021-05-28 02:09:36]<6>: A Server closing an accpeted connexion ...
  [2021-05-28 02:09:36]<6>: Accepted connexion closed
  ```
2.  Client side 
* Command parser using [boost program_options](https://www.boost.org/doc/libs/1_76_0/doc/html/program_options.html)


```
Usage: options_description [options]
Allowed options:
  -h [ --help ]                         produce help message
  -i [ --ip ] arg                       server IP address
  -p [ --port ] arg                     server port number.
  -l [ --log ] [=arg(=client.log)] (=client.log)
                                        client log path

```
* Client log: `2021_05_28_02_08_42_client.log`
* Sample client log
  ```
  [2021-05-28 02:08:42]<6>: A Client sending a request ...
  [2021-05-28 02:08:42]<6>: Request sent to a server
  [2021-05-28 02:08:42]<6>: A Client receiving a response ...
  [2021-05-28 02:08:42]<6>: Response from a server
  [2021-05-28 02:08:42]<6>: sucess
  [2021-05-28 02:08:48]<6>: A Client sending a request ...
  [2021-05-28 02:08:48]<6>: Request sent to a server
  [2021-05-28 02:08:48]<6>: A Client receiving a response ...
  [2021-05-28 02:08:48]<6>: Response from a server
  [2021-05-28 02:08:48]<6>: sucess
  [2021-05-28 02:08:54]<6>: A Client sending a request ...
  [2021-05-28 02:08:54]<6>: Request sent to a server
  [2021-05-28 02:08:54]<6>: A Client receiving a response ...
  [2021-05-28 02:08:54]<6>: Response from a server
  [2021-05-28 02:08:54]<6>: sucess
  [2021-05-28 02:09:00]<6>: A Client sending a request ...
  [2021-05-28 02:09:00]<6>: Request sent to a server
  [2021-05-28 02:09:00]<6>: A Client receiving a response ...
  [2021-05-28 02:09:00]<6>: Response from a server
  [2021-05-28 02:09:00]<6>: sucess
  [2021-05-28 02:09:06]<6>: A Client sending a request ...
  [2021-05-28 02:09:06]<6>: Request sent to a server
  [2021-05-28 02:09:06]<6>: A Client receiving a response ...
  [2021-05-28 02:09:06]<6>: Response from a server
  [2021-05-28 02:09:06]<6>: sucess
  [2021-05-28 02:09:12]<6>: A Client sending a request ...
  [2021-05-28 02:09:12]<6>: Request sent to a server
  [2021-05-28 02:09:12]<6>: A Client receiving a response ...
  [2021-05-28 02:09:12]<6>: Response from a server
  [2021-05-28 02:09:12]<6>: sucess
  [2021-05-28 02:09:18]<6>: A Client sending a request ...
  [2021-05-28 02:09:18]<6>: Request sent to a server
  [2021-05-28 02:09:18]<6>: A Client receiving a response ...
  [2021-05-28 02:09:18]<6>: Response from a server
  [2021-05-28 02:09:18]<6>: sucess
  [2021-05-28 02:09:24]<6>: A Client sending a request ...
  [2021-05-28 02:09:24]<6>: Request sent to a server
  [2021-05-28 02:09:24]<6>: A Client receiving a response ...
  [2021-05-28 02:09:24]<6>: Response from a server
  [2021-05-28 02:09:24]<6>: sucess
  [2021-05-28 02:09:30]<6>: A Client sending a request ...
  [2021-05-28 02:09:30]<6>: Request sent to a server
  [2021-05-28 02:09:30]<6>: A Client receiving a response ...
  [2021-05-28 02:09:30]<6>: Response from a server
  [2021-05-28 02:09:30]<6>: sucess
  ```
  4. Back to the initial file structure configuration
   ```sh
   rm -r bin build log lib
   ```
      
   
<!-- ROADMAP -->
## Roadmap

All the headers files are well docummented, read through the comments



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Adama Zouma - <!-- [@your_twitter](https://twitter.com/your_username) -->- stargue49@gmail.com

Project Link: [https://github.com/zoumson/Multi-ClientServer](https://github.com/zoumson/Multi-ClientServer.git)



<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements
* [Google](https://www.google.com/)
* [Stack Overflow](https://stackoverflow.com/)
* [Github](https://github.com/)
* [Git Concept from Telusko](https://www.youtube.com/watch?v=WbwIoQYP6no)
* [Git comands from The Coding Train](https://www.youtube.com/watch?v=yXT1ElMEkW8)
* [Git basics from Programming with Mosh ](https://www.youtube.com/watch?v=8JJ101D3knE)
* [Oh My ZSH](https://medium.com/@ivanaugustobd/your-terminal-can-be-much-much-more-productive-5256424658e8)
* [nerd-fonts](https://github.com/ryanoasis/nerd-fonts/tree/master/patched-fonts)
* [powerlevel9k/powerlevel9](https://github.com/Powerlevel9k/powerlevel9k#available-prompt-segments)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
