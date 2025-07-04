#pragma once
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Teleport.hpp"
#include "Scene/TestScene.hpp"

// 繩子結構：玩家可攀爬的繩子
struct Rope {
    int x;           // 繩子所在的水平位置 (像素)
    int bottomY;     // 繩子底部 Y 座標 (像素)
    int topY;        // 繩子頂部 Y 座標 (像素)
};

// 傳送點結構：玩家踩到 (x, y) 時跳轉到另一個地圖座標
// struct TeleportPoint {
//     int x, y;               // 觸發位置 (像素)
//     int targetMapId;        // 目標地圖編號 (預留)
//     int targetX, targetY;   // 傳送後玩家座標 (像素，預留)
// };

enum class MonsterType;
struct MonsterSpawnInfo {
    Engine::Point position;
    MonsterType type;
    // --- ADD THESE MEMBER VARIABLES ---
    float initialSpeed;
    float initialHP;
    int initialDamage;
    // ----------------------------------

    // Constructor to properly initialize all members
    MonsterSpawnInfo(Engine::Point pos, MonsterType t, float speed, float hp, int damage)
        : position(pos), type(t), initialSpeed(speed), initialHP(hp), initialDamage(damage) {}
};
class MapSystem {
public:
    MapSystem(ALLEGRO_DISPLAY* display);
    ~MapSystem();
    const std::vector<std::vector<int>>& GetMapDistance() const { return mapDistance; }
    bool loadMap(const std::string& mapFile,
                 const std::string& objectFile,
                 const std::string& monsterSpawnFile);
    void unloadMap();
    void update(float dt, int playerX, int playerY);
    void render(ALLEGRO_BITMAP* buffer = nullptr);
    const std::vector<TeleportPoint>& GetTeleports() const {
        return teleports;
    }
    const std::vector<MonsterSpawnInfo>& GetMonsterSpawns() const { return monsterSpawns; }
    //revise
    const std::vector<std::vector<int>>& GetTileData() const { return tileData; }
    int screenWidth, screenHeight;
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
    float GetCameraX() const { return cameraX; }
    float GetCameraY() const { return cameraY; }

private:
    std::vector<std::vector<int>> mapDistance;
    void parseTileData(const std::string& filename);
    void parseObjectData(const std::string& filename);
    void parseMonsterSpawnData(const std::string& filename);
    std::string pathForTileId(int id);

    ALLEGRO_DISPLAY* display_;
    
    float cameraX, cameraY;

    std::vector<std::vector<int>> tileData;
    std::vector<Rope>           ropes;
    std::vector<TeleportPoint>  teleports;
    std::vector<MonsterSpawnInfo> monsterSpawns;

    // **新增**：用来存放所有瓦片对象
    Engine::Group* tileGroup_;
};