# The Night Before Christmas

A 2-player local co-op stealth game where two players sneak into the Grinch's house to take back the stolen presents and save Christmas. Made by a team of four as a first-year project at DigiPen Institute of Technology Singapore (CSD1401, Fall 2024).


https://github.com/user-attachments/assets/1aa916c8-11f1-493e-a9ff-c66fe4a15cb2


## About

Both players share one keyboard and play at the same time. Together they make their way through four levels, collecting every present while avoiding the Grinch. Each player collects the presents in their own colour, red for Player 1 and green for Player 2. The players share a set of lives, so getting caught affects the whole team.

Each level adds a new challenge:

| Level | Challenge |
|-------|-----------|
| 1 | **Tutorial:** learn to move and collect presents |
| 2 | **Red Light, Green Light:** collect presents, but freeze whenever the Grinch turns to face you |
| 3 | **Patrol:** move between rooms while the Grinch patrols the middle hallway |
| 4 | **Darkness:** a new map with more complex Grinch movement and a limited field of view |

## My Contribution

I designed and built **Level 2**, a "Red Light, Green Light" level similar to *Squid Game*:

- **The Grinch's turn cycle:** the Grinch stands at the top of the room and turns on a timer. While he faces away, players can move freely. When he faces the room, either player pressing a movement key costs the team a life.
- **Fair penalties:** each time the Grinch turns, the team can lose at most one life, so holding a key down doesn't drain every heart at once.
- **Random present placement:** each player's 6 presents are placed at random every time the level starts. The placement checks for overlaps, so presents never stack on top of each other and every run is different.
- **Collecting presents:** I wrote the pickup detection, the shared "Presents: x/12" counter and the on-screen goal box.
- **Exit condition:** the exit door turns green once all 12 presents are collected. Each player can only leave once they've collected their own 6. When both are through, the screen fades to black and Level 3 begins.
- **Level setup and cleanup:** I loaded the level's sprites, fonts and background, and freed them when the level ends.

## Controls

| Action | Player 1 | Player 2 |
|--------|----------|----------|
| Move | W A S D | Arrow keys |
| Back to main menu (progress is lost) | Esc | Esc |

## Tech Stack

- **Language:** C
- **Framework:** CProcessing (DigiPen's 2D graphics and game library)
- **Tools:** Visual Studio, Git

## Running Locally

**Requirements:** Windows, Visual Studio

1. Clone this repository.
2. Open the `.sln` file in Visual Studio.
3. Press **F5** to build and run.

## Team: Buggers

Low Jianlin, Yar Xuan, Gwen Leo Yuhan, Beh Shi Wei

## Acknowledgements

Created at DigiPen Institute of Technology Singapore.
All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
