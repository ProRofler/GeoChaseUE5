# GeoChaseUE5

GeoChaseUE5 is a **Unreal Engine 5.4.4** multiplayer test project built from source.  
It demonstrates a simple competitive game where AI agents race to retrieve objects thrown by the player.  
The project was implemented in **C++ and Blueprints** with a balance between the two.

---

## 🎯 Game Concept

The core gameplay loop:

- The **player** moves freely across the field (WASD + Jump).  
- The player can select a **cube** or a **sphere** to throw:
  - Cube = 1 point  
  - Sphere = 3 points  
- When the player throws the toy, all AI characters notice it:
  - They start running toward the object.  
  - The one who reaches it first scores points.  
  - Others return to idle mode.  
  - AI that have no chance of reaching the toy stay in place, watching the player.  
- Only **one toy can exist at a time**. A new throw becomes available only after an AI has picked up the current toy.  
- The game continues until the timer ends. The AI with the most points wins.  

---

## 🤖 AI Behavior

- Configurable number of AI agents (2–10).  
- Each AI has a unique **name** (displayed above them).  
- Names are always red, but the leading AI’s name is highlighted in green.  
- Each AI has a unique movement speed (random or manually set).  
- Idle AIs always **face the player**.  
- When the toy is thrown:
  - All AIs rush toward it.  
  - The closest one collects it and scores.  
  - The toy disappears, signaling the player can throw again.  
- AI can be represented by simple meshes (cubes, mannequins, etc.) as long as orientation is clear.

---

## 🖥 UI & HUD

- **Scoreboard (top-left)**: List of AI names + scores.  
- **Timer (top-center)**: Countdown of the remaining match time.  
- **Endgame screen (center)**:
  - Displays winner’s name and score.  
  - If scores are tied → shows *"Draw"*.  
  - Contains two buttons:
    - **Restart**
    - **Exit**

---

## 🌐 Networking

- Built for **Windows** (client & dedicated server).  
- No third-party multiplayer solutions — only Unreal Engine’s native networking.  
- Multiplayer rules:
  - If one player throws a toy, others must wait until it is picked up before throwing again.  
- Verified setup:
  1. Start one **dedicated server** instance.  
  2. Connect multiple clients.  
  3. Players throw toys, AIs compete, and scoring is synced across all clients.

---

## 🛠 Technical Notes

- Project created from **UE5.4.4 source build**.  
- Based on a standard **UE template project**.  
- Implemented using a mix of **C++ and Blueprints** for clarity and maintainability.  
- Minimal unused assets and Blueprints.  
- Clean startup: pressing **Play** launches the match immediately.  

---
