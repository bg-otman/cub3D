# 🕹️ cub3D — A Raycasting Engine in C

A lightweight 3D engine built from scratch using raycasting, inspired by classic games like **Wolfenstein 3D**. This project uses the **MiniLibX** library to render a pseudo-3D world with walls, doors, and interactive elements. Designed with performance and modularity in mind.

---

## 📸 Features

### ✅ Mandatory Part
- 🎮 First-person view maze rendering using raycasting.

- 🧱 Wall textures with directional support (North/South/East/West).

- 🌈 Configurable floor and ceiling colors.

- 📁 .cub map parser with a custom configuration format.

- 🕹️ Keyboard movement: W, A, S, D to move, ← → to rotate view.

- ❌ Clean exit with ESC key or window close.

- 💡 MiniLibX-based rendering.

- 🧪 Full memory safety (no leaks or crashes).

### 🌟 Bonus Features
- 🎯 Advanced Interaction

- 🔫 Shooting system: right-click to fire.

- 🧠 Animated sprites.

- 🚪 Openable doors: textured, animated sliding doors.

- 🧱 Customizable wall/door placement logic that adapts to map input.

- 🧭 Minimap with camera tracking: shows player, walls, and objects in real-time with view direction.

- 🖱️ Mouse-based rotation: the mouse controls view direction smoothly.

- 🔒 Mouse lock: pointer stays centered in window for immersive control.
  
- 🎨 Multiple sprite and texture support through the .cub config file.

- 🧰 Map builder-friendly system: you can create your own maps with logic-controlled assets (textures, objects, etc).

## 🧠 Implementation Highlights

- 💡 Raycasting engine: DDA algorithm for wall detection.

- 📦 Texture mapping: handles wall, sprite, and door textures with fine-grained offset logic.

- 🚶 Door animation engine: interpolates open/close with visual transition using fractional hit width.

- 🧭 Minimap rendering: scales dynamically and reflects player view direction in real time.

---

## 🧠 Technical Overview

### ✅ Raycasting

Each vertical screen slice casts a ray into the world:
- Determines wall hits and distance
- Calculates perpendicular projection to avoid fish-eye effect
- Determines door position and how much is visible based on animation progress

### ✅ Doors

Doors animate using a `progress` value between `0.0` (closed) and `1.0` (fully open). When open:
- Collision is disabled when `progress >= 1.0`
- A thin part of the door remains drawn for visual consistency

### ✅ Mouse Lock & Look

Mouse movement rotates the player's angle smoothly. The mouse is reset to the screen center after every frame to simulate continuous rotation.

## 🗺️ Map Format (.cub)

```cub
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 30,30,30

111111
1N0D01
101101
1D0001
111111
```
- 0 → empty space

- 1 → wall

- D → door (must be surrounded by at least two walls either vertically or horizontally)

- N/S/E/W → player start and orientation

---

## 🚀 Getting Started

### Requirements
- Linux
- [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) (included or installed)
- GCC or Clang

### Compile

```bash
git clone https://github.com/bg-otman/cub3D.git
cd cub3D
make bonus
./cub3D maps/your_map.cub
```
---
## 📸 Screenshots

![Screenshot from 2025-06-25 18-25-20](https://github.com/user-attachments/assets/0c925068-e8ad-4565-950e-5fb5bf894b59)
![Screenshot from 2025-06-25 18-28-56](https://github.com/user-attachments/assets/16dd90cf-0b73-42d7-9d6f-38e9c10adfb5)
![Screenshot from 2025-06-25 18-30-18](https://github.com/user-attachments/assets/6eac0b82-79bc-47b8-82b6-23c3d0aae69d)
![Screenshot from 2025-06-25 18-30-38](https://github.com/user-attachments/assets/407f709a-4e5a-4b3d-85a9-f3b223de7331)
![Screenshot from 2025-06-25 18-31-18](https://github.com/user-attachments/assets/18591326-a47c-4b12-ba52-e0bfbd12667b)

---
🙌 Credits
Developed by @bg-otman and @Aymanesaj, as part of 42/1337 Network’s Cub3D project.


