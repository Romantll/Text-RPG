# Text-Based RPG – Save/Load & World Design

## Screenshot
<img width="1299" height="737" alt="Text-RPG" src="https://github.com/user-attachments/assets/fcd58256-6bf3-4e68-a3d6-7f18b20db26b" />

## 📜 Overview
This is a text-based RPG written in C to reinforce understanding of data structures and algorithms. The project features inventory systems, combat mechanics, room navigation, NPCs, leveling, and save/load functionality.

## ✨ Features
- Struct-based world and player modeling
- Linked list inventory management
- Combat system with XP and leveling
- Save and load game state to/from text files
- World grid support for automatic room generation (planned)

## 💾 Save/Load Format
Saves are stored in human-readable format like:
```
room: Kitchen
health: 100
maxHP: 100
level: 1
exp: 0
equippedWeapon: Iron Sword
inventory: Potion,Iron Sword
```

## ✍️ Story Writing Recommendation
When designing story scenes:
- Write in plain text or Markdown for fast iteration
- Then convert to structured formats like JSON/CSV
- Markdown example:
  ```markdown
  ## Kitchen
  You enter a greasy kitchen. A fridge hums in the corner.

  - [ ] Open the fridge → FridgeScene
  - [ ] Leave quietly → Hallway
  ```

## 🗃️ Data Structures Used
- Structs: Player, Item, Room, NPC
- Linked Lists: Inventory
- File I/O: Save/Load
- Graph: Room navigation

## 📌 Planned Features
- World auto-generation using 2D grid
- Combat log history
- Conditional attack types (parry, slash)
- Event-based story system

## 📂 Project Structure
```
rpg/
├── src/
│   ├── main.c
│   ├── player.c
│   ├── item.c
│   ├── npc.c
│   ├── world.c
│   ├── save_load.c
├── include/
│   ├── player.h
│   ├── item.h
│   ├── npc.h
│   ├── world.h
│   ├── save_load.h
├── saves/
├── Makefile
```

## 🙌 Author
Roman Rendon
