#include <queue>
#include <raylib.h>
#include <utility>
#define INF 9999
#define ROW 30
#define COL 40
#define TILE_SIZE 20

const Color BACKGROUND   = {  7,  12,  24, 255};  // Deep black-blue
const Color TILE_BORDER  = { 45,  55,  75, 255};  // Subtle slate
const Color OBSTACLE     = {239,  68,  68, 255};  // Neon red
const Color PATH         = { 34, 211, 238, 255};  // Cyan
const Color SOURCE       = { 34, 197,  94, 255};  // Green
const Color DESTINATION  = {168,  85, 247, 255};  // Purple

struct Node{
    int x, y, weight;
    Color color;
};
typedef struct Node Node;

Node tile[ROW][COL];


typedef struct Point{
    int r, c;
}Point;

Point startNode = {-1, -1};
Point endNode = {-1, -1};
int rowDir[4] = {0, 1, 0, -1}; // {top, right, bottom, left}
int colDir[4]= {-1, 0, 1, 0};

int visited[ROW][COL];
int dist[ROW][COL];
Point parent[ROW][COL];

void dijkstra(){

    if(startNode.r == -1) return;

    // (distance, Point {r, c})
    using QueueElement = std::pair<int, std::pair<int, int>>;
    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> pq;

    dist[startNode.r][startNode.c] = 0;

    pq.push({0, {startNode.r, startNode.c}});

    while (!pq.empty()){
            auto [currDist, currVertex] = pq.top();
            auto [currRow, currCol] = currVertex;
            pq.pop();

            visited[currRow][currCol] = 1;

            for (int v = 0; v < 4; v++) {
                int adjRow = currRow + rowDir[v];
                int adjCol = currCol + colDir[v];

                if((adjRow >= 0 && adjRow < ROW) && (adjCol >= 0 && adjCol < COL)){

                    if(!visited[adjRow][adjCol] && tile[adjRow][adjCol].weight != INF){
                        int newDist = dist[currRow][currCol] + tile[adjRow][adjCol].weight;
                        if(newDist < dist[adjRow][adjCol]){
                            dist[adjRow][adjCol] = newDist;
                            pq.push({newDist, {adjRow, adjCol}});
                            parent[adjRow][adjCol] = {.r = currRow, .c = currCol};
                        }
                    }
                }
            }
        }
}



void initialize(){
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            tile[i][j].color = BACKGROUND;
            tile[i][j].weight = GetRandomValue(1, 10);
            tile[i][j].x = j * TILE_SIZE;
            tile[i][j].y = i * TILE_SIZE;

            visited[i][j] = 0;
            dist[i][j] = INF;
        }
    }
}

void drawNodes(){
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            DrawRectangle(tile[i][j].x, tile[i][j].y, TILE_SIZE, TILE_SIZE, tile[i][j].color);
            DrawRectangleLines(tile[i][j].x, tile[i][j].y, TILE_SIZE, TILE_SIZE,TILE_BORDER);
        }
    }
}

void displayPath(){
    if(dist[endNode.r][endNode.c] == INF) return;

    Point curr = parent[endNode.r][endNode.c];
    while(curr.r != startNode.r || curr.c != startNode.c){
        tile[curr.r][curr.c].color = PATH;
        curr = parent[curr.r][curr.c];
    }
}

void drawObstacles(){
    Vector2 mousePos = GetMousePosition();

    //convert to array index
    int rowIndex = int(mousePos.y / TILE_SIZE);
    int colIndex = int(mousePos.x / TILE_SIZE);

    if((rowIndex >= 0 && rowIndex < ROW) && (colIndex >= 0 && colIndex < COL)){
        //is left mouse dragging
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            tile[rowIndex][colIndex].color = OBSTACLE;
            tile[rowIndex][colIndex].weight = INF;
        }
        if(IsKeyPressed(KEY_S)){
            if(startNode.r == -1){
                tile[rowIndex][colIndex].color = SOURCE;
                startNode = (Point){
                    .r = rowIndex,
                    .c = colIndex,
                };
            }
        }

        if(IsKeyPressed(KEY_E)){
            if(endNode.r == -1){
                tile[rowIndex][colIndex].color = DESTINATION;
                endNode = (Point){
                    .r = rowIndex,
                    .c = colIndex,
                };
            }
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        // if both (start, and end) nodes aren't marked
        if(startNode.r == -1 || endNode.r == -1) return;
        dijkstra();

        displayPath();
    }
    //reset
    if(IsKeyPressed(KEY_R)){
        initialize();
        startNode = {.r = -1, .c = -1};
        endNode = {.r = -1, .c = -1};
    }
}





int main () {

    InitWindow(COL * TILE_SIZE, ROW * TILE_SIZE, "Dijkstra Algorithm");
    initialize();
    SetTargetFPS(60);


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BACKGROUND);
        drawNodes();
        drawObstacles();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
