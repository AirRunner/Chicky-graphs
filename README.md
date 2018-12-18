![logo](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project/raw/master/data/Website/LOGOFOND.png)
# Chicky Graphs:
This project is aimed to teach and be useful to people. Our idea is to make the “Theory of graphs” as sample as possible.
In order to do this, the theory of graphs is taught step by step in an interactive way through different levels of difficulty and different missions.
Our Menu allows to click on "adventure" in order to learn the theory of graphs or to go on the Sandbox to try by oneself the possibilities of our program. We also have created a website in order to present our work.

## Table of Contents:
* [Prerequisites](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project#prerequisites)
* [Installation](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project#installation)
* [Download](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project#download)
* [Team Members](https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project#team-members)

## Prerequisites
- A C compiler
- SDL2
- SDL Images
- SDL TTF

## Installation

### Clone the repository
```console
git clone https://gitlab.platypus.academy/efrei-2a-sdd-p2022-Tardigradu/project.git
```

### Compile the code
Run those command<br>
Windows :
```console
gcc -L SDL2/lib -I SDL2/include rendering/*.c data-layer/*.c controller/*.c -o build/chicky -lSDL2 -lSDL2_ttf -lSDL2_image
```
Mac and linux :
```console
make
```

## Download
Downloads for [mac and linux](mettre un lien) or for [windows](mettre un autre lien)

## Team Members
- Teaching Manager : <br>**Gabriela Amorin De Almedia**  <gabriela.amorim.de.almeida@efrei.net>
- Communication Manager : <br>**Chloe Carayon**  <chloe.carayon@efrei.net>
- Project Manager : <br>**Vincent Mouillon**  <vincent.mouillon@efrei.net>
- Technical Manager : <br>**Victor Tailleu**  <victor.taillieu@efrei.net>
- Design Manager : <br>**Luca Vaio**  <luca.vaio@efrei.net>
