# iAts_pro(Antenna automatic tracking system pro)

Not long ago, I created an automatic tracking system that supports bluetooth connection and parameter configuration based on the open source project [amv-open360tracker](https://github.com/raul-ortega/amv-open360tracker/) (You can find my project at [here](https://github.com/akari-tun/iAts)).

This project was built with Ateml 328p. As it is an 8-bit chip, its performance was low, so I couldn't implement more functions on it.Therefore, I came up with the idea of redeveloping it built on chips with higher performance.

Through the project of [RavenLRS](https://github.com/RavenLRS), I got to know a module espressif-ESP32 designed for IOT, which is integration bluetooth and wifi, and has 240mhz main frequency and 2m+ flash. And the official provides good SDK for development, which meets my needs very much. Therefore, I redeveloped the antenna automatic tracking system on this module.

After I graduating from college, I never use C language to develop any project, using C language development this project is a big challenge to me, I need to relearn C language feature, and the need to better understand how to use of Point. 

[RavenLRS](https://github.com/RavenLRS) project is built on ESP32 module, its also the realization of the function of some of its similar to some of my ideas, I learn by [RavenLRS](https://github.com/RavenLRS) project by learned a lot of of C language development experience, and use a lot of RavenLRS code to my project,Thanks to [RavenLRS](https://github.com/RavenLRS) author [fiam](https://github.com/fiam) open source for such an excellent project.