# Within Ashes

![Static Badge](https://img.shields.io/badge/Built_with-Python-blue?logo=python&logoColor=%23FFFFFF)

*Within Ashes* is a surivial roguelike with aspects of resource management. The main goal is to explore the area you're in and survive as long as possible while staying sane, healthy, and in one piece. *Within Ashes* takes place in a partially reclaimed city, in the future after some catastrophic event lead to the destruction of the city. Within the boundaries of this former city you can find an array of buildings to freely explore for resources to keep yourself alive and defended.

You can choose where to survive, when the game first starts. Some areas are harder than others and have differing benefits overall.

## Why Python?

Python is performant, if done properly. This game is by no means of massive scale, and is in no way graphically intensive. Python also allows for extremely rapid development and iteration, our only downtime comes when building executables via `pyinstaller`. While C++ and other languages were considered for the full game, Python was eventually chosen for it's iterative speed and surprising performance.

Due to Steamworks (Valve's API for communicating with Steam as a service) being in C++, we also created a bridge between Python and Steamworks which is available in the `pysteam` directory.

## Where are the Assets?

The assets for this project, like all other projects, are proprietary. All artwork, music, characters, dialogue, and other game assets are **not covered** by the license in the repository. These remain the exclusive property of **Lunarwing Games** and may not be copied, modified, or redistributed.

<sub>© Lunarwing Games, 2025. All rights reserved.</sub>
