# 🛣️ Highway Electric Vehicle Management System

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structures](https://img.shields.io/badge/Data%20Structures-BST%20%7C%20Linked%20Lists-green.svg)]()
[![Algorithm](https://img.shields.io/badge/Algorithm-Greedy%20%7C%20Graph%20Traversal-orange.svg)]()

> A sophisticated C implementation for managing electric vehicle rental stations along a highway with intelligent route planning capabilities.

## 🚗 Overview

This project simulates a modern highway ecosystem where electric vehicle rental stations are strategically positioned at various kilometer markers. Each station maintains a fleet of electric vehicles with different battery ranges, and the system intelligently plans optimal routes between any two stations while minimizing stops and environmental impact.

## ✨ Features

- 🏗️ **Dynamic Station Management** - Add/remove gas stations with unique positioning
- 🚙 **Fleet Management** - Comprehensive vehicle inventory control with autonomy tracking  
- 🧭 **Smart Route Planning** - AI-powered pathfinding with optimal stop minimization
- ↔️ **Bidirectional Travel** - Support for both forward and reverse journey planning
- 🎯 **Intelligent Tie-Breaking** - Advanced logic for selecting optimal routes when multiple paths exist

## 🏗️ Architecture & Data Structures

### 🌳 Binary Search Tree - Station Network
```c
typedef struct nodeStation {
    int32_t distance;
    int32_t max_autonomy_car;
    struct car *park;
    struct nodeStation *left, *right, *parent;
} nodeStation;
```
- **Efficient Operations**: O(log n) insertion, deletion, and search
- **Smart Traversal**: In-order successor/predecessor for neighbor discovery

### 🔗 Linked Lists - Vehicle Fleet
```c
typedef struct car {
    int autonomy;
    struct car* next;
} car;
```
- **Dynamic Management**: Real-time vehicle addition/removal
- **Optimized Queries**: Instant maximum range vehicle lookup

### 📦 Buffer System - Route Storage
- **Forward Routes**: Optimized for sequential planning
- **Reverse Routes**: Specialized for backward journey optimization

## 🚀 Algorithm Strategy

### 🎯 Forward Route Planning
```
🏁 Start → 🔍 Find Furthest Reachable → 🔄 Repeat → 🏆 Destination
```

### 🔄 Backward Route Planning  
```
🏆 Destination → 🔍 Find Optimal Predecessors → 🎯 Optimize Path → 🏁 Origin
```

## 🎮 Command Interface

| Command | Description | Example |
|---------|-------------|---------|
| `aggiungi-stazione` | 🏗️ Add new station | `aggiungi-stazione 100 3 50 75 80` |
| `demolisci-stazione` | 🏗️ Remove station | `demolisci-stazione 100` |
| `aggiungi-auto` | 🚗 Add vehicle | `aggiungi-auto 100 90` |
| `rottama-auto` | 🚗 Remove vehicle | `rottama-auto 100 90` |
| `pianifica-percorso` | 🧭 Plan route | `pianifica-percorso 0 500` |

## ⚡ Performance Metrics

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Station Management | O(log n) | O(1) |
| Route Planning | O(n log n) | O(n) |
| Vehicle Operations | O(1) - O(m) | O(1) |

*Where n = number of stations, m = vehicles per station*


### Sample Input
```
aggiungi-stazione 0 2 100 200
aggiungi-stazione 150 1 100
aggiungi-stazione 300 1 150
pianifica-percorso 0 300
```

### Expected Output
```
aggiunta
aggiunta  
aggiunta
0 150 300
```

## 🎯 Key Innovations

- **🧠 Intelligent Caching**: Maximum autonomy pre-computed for O(1) lookups
- **🔄 Memory Optimization**: Comprehensive cleanup preventing memory leaks  
- **🎪 Edge Case Mastery**: Robust handling of impossible routes and corner cases
- **⚖️ Smart Tie-Breaking**: Sophisticated route selection favoring optimal paths



## 📄 License

This project is part of an academic assignment focusing on advanced data structures and algorithms implementation in C.

---

<div align="center">
  <strong>🚗 Drive Smart, Code Smarter 🛣️</strong>
</div>