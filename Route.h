/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef ROUTE_H
#define	ROUTE_H
#include <unordered_map>
#include <QString>
#include "GLUU.h"
#include "TDB.h"
#include "WorldObj.h"
#include "Ref.h"

class Tile;
class Brush;
class Coords;
class Trk;
class SoundList;
class GLWidget;

class Route : public QObject {
    Q_OBJECT
public:
    std::unordered_map<int, Tile*> tile;
    std::vector<int> activityId;
    bool loaded = false;
    TSectionDAT *tsection; 
    SoundList* soundList;
    Ref *ref;
    bool placementStickToTarget = false;
    float placementAutoLength = 50;
    bool placementAutoTwoPointRot = true;
    int placementAutoTargetType = 0;
    float placementAutoTranslationOffset[3];
    float placementAutoRotationOffset[3];
    Route();
    Route(const Route& orig);
    virtual ~Route();
    WorldObj* getObj(int x, int z, int uid);
    void save();
    void saveTrk();
    void createNewPaths();
    void createNew();
    void loadMkrList();
    void loadActivities();
    void newTile(int x, int z);
    void reloadTile(int x, int z);
    void deleteObj(WorldObj* obj);
    void undoPlaceObj(int x, int y, int UiD);
    void removeTrackFromTDB(WorldObj* obj);
    void nextDefaultEnd();
    void setTerrainToTrackObj(WorldObj* obj, Brush* brush);
    int getTileObjCount(int x, int z);
    int getTileHiddenObjCount(int x, int z);
    int getStartTileX();
    int getStartTileZ();
    float getStartpX();
    float getStartpZ();
    Trk *getTrk();
    std::unordered_map<std::string, Coords*> getMkrList();
    void setMkrFile(QString name);
    void getUnsavedInfo(std::vector<QString> &items);
    void showTrkEditr(Trk * val = NULL);
    void paintHeightMap(Brush* brush, int x, int z, float* p);
    WorldObj* makeFlexTrack(int x, int z, float* pos);
    WorldObj* placeObject(int x, int z, float* p);
    WorldObj* placeObject(int x, int z, float* p, float* q);
    WorldObj* placeObject(int x, int z, float* p, float* q, Ref::RefItem* r);
    WorldObj* autoPlaceObject(int x, int z, float* p);
    void replaceWorldObjPointer(WorldObj* o, WorldObj* n);
    void autoPlacementDeleteLast();
    void deleteTDBTree(WorldObj* obj);
    void deleteTDBVector(WorldObj* obj);
    void toggleToTDB(WorldObj* obj);
    void addToTDBIfNotExist(WorldObj* obj);
    void addToTDB(WorldObj* obj);
    void newPositionTDB(WorldObj* obj, float* post, float* pos);
    void linkSignal(int x, int z, float* p, WorldObj* obj);
    void transalteObj(int x, int z, float px, float py, float pz, int uid);
    void setTDB(TDB* tdb, bool road);
    void render(GLUU *gluu, float* playerT, float* playerW, float* target, float playerRot, float fov, int renderMode);
    void renderShadowMap(GLUU *gluu, float* playerT, float* playerW, float* target, float playerRot, float fov, bool selection);

signals:
    objSelected(WorldObj* obj);

private:
    void loadTrk();
    TDB *trackDB;
    TDB *roadDB; 
    std::unordered_map<std::string, Coords*> mkrList;
    Coords * mkr = NULL;
    Trk * trk = NULL;
    QVector<WorldObj*> autoPlacementLastPlaced;
};

#endif	/* ROUTE_H */

