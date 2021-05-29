## Multi-Client single server TCP/IP communication in cpp using multi-threading
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
-->


<!-- PROJECT LOGO -->
<!-- 
<br />
<p align="center">

  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
<p align="center">
  <h3 align="center">Best-README-Template</h3>

  <p align="center">
    An awesome README template to jumpstart your projects!
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template">View Demo</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Report Bug</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Request Feature</a>
  </p>
</p>
-->


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

This is an sample code of how to implement a single server mutilple clients communication mutli-threading
To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* tree
  ```sh
  sudo apt-get install tree
  ```
* cmake
  ```sh
  sudo apt-get install cmake
  ```
 * CPP standard: `CMAKE_CXX_STANDARD 17`
* boost 
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
   git clone https://github.com/zoumson/MultipleThreadMultipleClientSingleServerSocketCPP.git
   ```
2. Go to build
   ```sh
   cd ./build
   ```
3. Make sure build folder is empty, only .gitignore there is fine
* Command 
   ```sh
   tree -L 1
   ```
* Expected result
   ```sh
    .

    0 directories, 0 files
   ```
4. Then run the cmake file to generate the makefile
   ```sh
   cmake ..
   ```
5. Finally run the makefile to generate the executable `server` and `client`
   ```sh
   make
   ```


<!-- USAGE EXAMPLES -->
## Usage
Command line arguments
<br>
1.  Sever side 
* Command parser using boost options_program
```
Usage: options_description [options]
Allowed options:
  -h [ --help ]                         produce help message
  -p [ --port ] [=arg(=60000)] (=no)    server port number.
  -c [ --connexion ] [=arg(=10)] (=few) server max connexion.

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
  * Server log: `server.log`
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
2.  Sever side 
* Command parser using boost options_program
```
Usage: options_description [options]
Allowed options:
  -h [ --help ]         produce help message
  -i [ --ip ] arg       server IP address
  -p [ --port ] arg     server port number.

```
* Client log: `client.log`
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

Project Link: [https://github.com/zoumson/MultipleThreadMultipleClientSingleServerSocketCPP](https://github.com/zoumson/MultipleThreadMultipleClientSingleServerSocketCPP)



<!-- ACKNOWLEDGEMENTS -->
<!-- 
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)
-->




<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!-- 
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
-->
