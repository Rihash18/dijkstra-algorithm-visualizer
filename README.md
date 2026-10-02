
# Dijkstra Visualizer

A simple interactive **Dijkstra's Algorithm Visualizer** built using **C++ and Raylib**.

This project visualizes how Dijkstra's shortest path algorithm finds the shortest path between a source node and a destination node on a weighted grid while avoiding obstacles.

## 🚀 Features

* Visualize Dijkstra's shortest path algorithm
* Interactive 30 × 40 grid
* Random weight assigned to every tile
* Create obstacles by dragging the mouse
* Set source and destination nodes
* Shortest path reconstruction using parent nodes
* Priority Queue implementation for selecting the next minimum-distance node
* Reset the grid and generate new random weights
* Runs at 60 FPS

## 🎮 Controls

| Input                    | Action                   |
| ------------------------ | ------------------------ |
| Left Mouse Button + Drag | Create obstacles         |
| S                        | Set source node          |
| E                        | Set destination node     |
| SPACE                    | Run Dijkstra's algorithm |
| R                        | Reset the grid           |

## 🕹️ How to Use

1. Run the program.
2. Drag the left mouse button across the grid to create obstacles.
3. Move the mouse over a tile and press `S` to set the source.
4. Move to another tile and press `E` to set the destination.
5. Press `SPACE` to run Dijkstra's algorithm.
6. The shortest path will be displayed in cyan.
7. Press `R` to reset the grid.

## 🧠 How It Works

The grid is represented as a weighted graph.

Each tile acts as a vertex, and each tile can connect to its four neighboring tiles:

* Up
* Down
* Left
* Right

Diagonal movement is not allowed.

Dijkstra's algorithm maintains the shortest known distance from the source to every tile.

Initially:

```text
distance[source] = 0
distance[all other nodes] = INF
```

A priority queue is used to process the tile with the smallest known distance.

For every valid neighboring tile:

```text
newDistance = currentDistance + neighborWeight
```

If the new distance is smaller than the previously known distance:

```text
distance[neighbor] = newDistance
parent[neighbor] = currentNode
```

The `parent` array is then used to reconstruct the shortest path from the destination back to the source.

## 🔢 Weighted Grid

Every tile is assigned a random weight between `1` and `10`.

```cpp
tile[i][j].weight = GetRandomValue(1, 10);
```

Obstacles are represented using `INF`.

```cpp
#define INF 9999
```

When a tile becomes an obstacle:

```cpp
tile[rowIndex][colIndex].weight = INF;
```

This prevents Dijkstra's algorithm from traveling through that tile.

## 🗺️ Grid Configuration

```text
Rows       : 30
Columns    : 40
Tile Size  : 20 × 20
Total Tiles: 1200
```

Each tile is represented using:

```cpp
struct Node {
    int x;
    int y;
    int weight;
    Color color;
};
```

## ⚡ Priority Queue

The project uses a C++ min-priority queue:

```cpp
using QueueElement = std::pair<int, std::pair<int, int>>;

std::priority_queue<
    QueueElement,
    std::vector<QueueElement>,
    std::greater<QueueElement>
> pq;
```

Each queue element contains:

```text
(distance, (row, column))
```

The tile with the smallest distance is processed first.

## 🔗 Path Reconstruction

The previous tile of every updated tile is stored using:

```cpp
Point parent[ROW][COL];
```

After Dijkstra's algorithm finishes, the path is reconstructed by following the parent nodes backward:

```text
Destination
     ↓
   Parent
     ↓
   Parent
     ↓
   Parent
     ↓
   Source
```

The resulting path is displayed using the cyan path color.

## 🎨 Color Legend

| Color           | Meaning                  |
| --------------- | ------------------------ |
| Deep Black-Blue | Background / Normal Tile |
| Slate           | Tile Border              |
| Red             | Obstacle                 |
| Cyan            | Shortest Path            |
| Green           | Source                   |
| Purple          | Destination              |

## 🛠️ Tech Stack

* C++
* Raylib
* C++ STL Priority Queue
* Dijkstra's Shortest Path Algorithm

## 📦 Requirements

* C++ compiler with C++17 support
* Raylib
* Git

## 🔨 Build and Run

Clone the repository:

```bash
git clone https://github.com/Rihash18/dijkstra-visualizer.git
cd dijkstra-visualizer
```

Compile:

```bash
g++ main.cpp -o dijkstra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Run:

```bash
./dijkstra
```

> The compilation command may vary depending on your operating system and Raylib installation.

## 📁 Project Structure

```text
dijkstra-visualizer/
│
├── main.cpp
├── README.md
└── ...
```

## 🔮 Future Improvements

* [ ] Animate Dijkstra's algorithm step-by-step
* [ ] Show visited nodes during execution
* [ ] Display tile weights
* [ ] Add BFS
* [ ] Add DFS
* [ ] Add A*
* [ ] Add Bellman-Ford
* [ ] Allow custom tile weights
* [ ] Add pause/resume functionality
* [ ] Add maze generation
* [ ] Add diagonal movement option
* [ ] Improve path animation

## 📚 What I Learned

Through this project, I practiced:

* Dijkstra's shortest path algorithm
* Weighted graphs
* Priority queues
* Graph traversal
* Path reconstruction
* 2D arrays
* Structs in C++
* Raylib graphics
* Mouse and keyboard input handling
* Real-time visualization

## ⭐ About

This project was built as a learning project to understand **Dijkstra's Algorithm and graph-based pathfinding** through an interactive visualization.

If you find the project useful, consider giving the repository a ⭐.
