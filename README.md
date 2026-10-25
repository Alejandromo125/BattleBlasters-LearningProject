# BattleBlasters – Learning Project

A top-down tank shooter built with **Unreal Engine 5.6** and **C++**, created as a hands-on learning project for Unreal's gameplay framework, Enhanced Input, UMG and Niagara.

Drive your tank, aim with the mouse, and destroy every enemy tower in the level before they destroy you. Clear all three levels to win the game.

> **Note:** This is a personal learning project, not a production-ready game. Code and structure may change as I keep learning.

<!-- Optional: add a screenshot or GIF of the game here
![Gameplay](Docs/gameplay.gif)
-->

## Gameplay

- Each level starts with a **3-second countdown** (3 … 2 … 1 … GO!). Player input is locked until it reaches "GO!".
- The player controls a **tank** with a rotating turret that follows the mouse cursor.
- **Towers** are stationary enemies that track the tank and shoot when it enters their range.
- Every actor with a health component can be destroyed by projectiles.
- **Victory:** destroy all towers in the level → next level loads after a short delay.
- **Defeat:** the tank is destroyed → the current level restarts.
- After the last level (`Level_3`), the game loops back to `Level_1`.

## Features

- **C++ gameplay core** (module `BattleBlaster`) extended through Blueprints
- **Shared pawn base class** (`ABaseProjectPawn`) for the tank and the towers: capsule collision, base and turret meshes, projectile spawn point, turret rotation, firing and destruction effects
- **Enhanced Input** for movement, rotation and firing
- **Reusable health system** via `UHealthComponent`, driven by Unreal's damage events
- **Projectiles** with Niagara trail and hit effects, sound, damage and camera shake
- **Game flow** handled by a custom `GameMode` (countdown, win/lose detection) and `GameInstance` (level progression)
- **UMG screen message widget** for the countdown and the Victory / Defeat messages
- 3 playable levels (`Level_1` – `Level_3`)

## Requirements

- **Unreal Engine 5.6** (via the Epic Games Launcher)
- **Visual Studio 2022** with the components listed in [`.vsconfig`](.vsconfig) (*Game development with C++*)
- **Windows 10/11** (recommended)
- Git (and Git LFS if you add large binary assets)

The C++ module depends on: `Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`, `UMG` and `Niagara`.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Alejandromo125/BattleBlasters-LearningProject.git
cd BattleBlasters-LearningProject
```

### 2. Install the required Visual Studio components

Open `.vsconfig` with the **Visual Studio Installer** (*More → Import configuration*).

### 3. Generate project files

Right-click `BattleBlaster.uproject` and choose **Generate Visual Studio project files**.

### 4. Build and run

**From Visual Studio**
1. Open `BattleBlaster.sln`.
2. Select the **Development Editor** configuration and the **Win64** platform.
3. Build and start (`F5`).

**From the Unreal Editor**
1. Double-click `BattleBlaster.uproject`.
2. When prompted, rebuild the missing modules.

The project opens on `Level_1` by default.

## Controls

| Action | Input |
|--------|-------|
| Move forward / backward | <!-- TODO: key(s) --> |
| Rotate tank left / right | <!-- TODO: key(s) --> |
| Aim turret | Mouse cursor |
| Fire | <!-- TODO: button --> |

Bindings are defined in the `IMC_Default` input mapping context (`Content/Input`) with the actions `IA_Move`, `IA_Rotate` and `IA_Fire`.

## Project Structure

```
BattleBlasters-LearningProject/
├── Config/                         # Engine, input, game and editor settings
├── Content/
│   ├── Maps/                       # Level_1, Level_2, Level_3 (+ Main)
│   ├── BluePrints/                 # BP_Tank, BP_Tower, BP_Projectile, GameMode, GameInstance, widgets, camera shakes
│   ├── Input/                      # Enhanced Input actions and mapping context
│   └── Assets/                     # Meshes, materials, textures, audio, Niagara effects
├── Source/
│   └── BattleBlaster/
│       ├── BaseProjectPawn.*       # Shared base for tank and towers
│       ├── Tank.*                  # Player pawn (input, camera, movement)
│       ├── Tower.*                 # Enemy turret AI (range check, fire timer)
│       ├── projectile.*            # Projectile actor (damage, hit effects)
│       ├── HealthComponent.*       # Health and damage handling
│       ├── BattleBlasterGameMode.* # Countdown, win/lose logic
│       ├── BattleBlastersGameInstance.* # Level progression
│       └── ScreenMessage.*         # UMG widget for on-screen messages
├── BattleBlaster.uproject
├── .vsconfig
└── LICENSE
```

## Architecture Overview

```
ABaseProjectPawn
├── ATank   – player-controlled, Enhanced Input, spring arm + camera
└── ATower  – stationary enemy, fires at the tank within range

Aprojectile ──ApplyDamage──▶ UHealthComponent ──ActorDied──▶ ABattleBlasterGameMode
                                                                  │
                                              UBattleBlastersGameInstance (load next / restart level)
```

### Tweakable properties (editable in Blueprints)

| Class | Property | Default |
|-------|----------|---------|
| `ATank` | `speed` | 300 |
| `ATank` | `rotationDegrees` | 100 |
| `ATower` | `fireRange` | 700 |
| `ATower` | `fireRate` | 2 s |
| `Aprojectile` | `damage` | 25 |
| `UHealthComponent` | `maxHealth` | 100 |
| `ABattleBlasterGameMode` | `countDownDelay` | 3 s |
| `ABattleBlasterGameMode` | `GameOverDelay` | 3 s |
| `UBattleBlastersGameInstance` | `lastLevelIndex` | 3 |

## What I'm Learning

- Unreal's gameplay framework (Pawns, GameMode, GameInstance, Components)
- Writing gameplay code in C++ and exposing it to Blueprints
- Enhanced Input, UMG and Niagara integration
- Level flow, timers and damage events

## Contributing

This is a personal learning project, but feedback and suggestions are welcome. Feel free to open an [issue](https://github.com/Alejandromo125/BattleBlasters-LearningProject/issues) or submit a pull request.

## License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.

## Author

**Alejandro** – [@Alejandromo125](https://github.com/Alejandromo125)


