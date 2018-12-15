![logo](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project/raw/master/data/Website/Chicky%20Graphs%20WEB/LOGOFOND.png)
# Chicky Graphs:
This project aimed to teach and be useful to people. Our idea is to make the “Theory of graphs” as sample as possible.
In order to do this, we present steps of the graph theory by different levels of difficulties and different missions.
Our Menu gives the opportunity to go to "adventure" in order to learn the theory of graphs or to go on the Sandbox to try by ownself the possibilities of our program. We also have created a site in order to present our work.

## Table of Contents:
* [Team Member](#Team-members)
* [Files](#Files)
* [Installation](#Installation)

## Team Members
- Gabriela Amorin De Almedia <vincent.mouillon@efrei.net>
- Chloe Carayon, <chloe.carayon@efrei.net>
- Vincent Mouillon, <vincent.mouillon@efrei.net>
- Luca Vaio, <luca.vaio@yahoo.fr>
- Victor Tailleu, <vic8.taillieu@gmail.com>

## Files:

```
Our program is divided in 3 important parts:
	-Controller :
		graphs.h
	-Renderring : 
		renderrringSLL.h
		sdl.h
		text.h
		texture.h
	-Data-layer:
		data.h 
```
	
## Installation

### Clone the repository
```console
git clone https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project.git
```

### Compile the code
Run those command<br>
Windows :
```console
gcc -g controller/*.c rendering/*.c data-layer/*.c -o build/Chicky
```
Mac and linux :
```console
make
```
