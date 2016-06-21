#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>

class QSlider;
class GLWidget;
class ObjTools;
class GeoTools;
class TerrainTools;
class ActivityTools;
class NaviBox;
class AboutWindow;
class NaviWindow;
class PropertiesAbstract;
class WorldObj;
class PreciseTileCoordinate;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();
    
public slots:
    void save();
    void show();
    void createPaths();
    void about();
    void setToolbox(QString name);
    void showProperties(WorldObj* obj);
    void updateProperties(WorldObj* obj);
    void hideShowToolWidget(bool show);
    void hideShowPropertiesWidget(bool show);
    void hideShowNaviWidget(bool);
    void viewWorldGrid(bool show);
    void viewTileGrid(bool show);
    void viewInteractives(bool show);
    void viewTrackDbLines(bool show);
    void viewTsectionLines(bool show);
    void viewPointer3d(bool show);
    void viewMarkers(bool show);
    void showToolsObject(bool show);
    void showToolsTerrain(bool show);
    void showToolsGeo(bool show);
    void showToolsActivity(bool show);
    void showTerrainTreeEditr();

signals:
    void exitNow();
    void sendMsg(QString text);

protected:
    void keyPressEvent(QKeyEvent *event);
    virtual void closeEvent(QCloseEvent * event );
    void hideAllTools();

private:
    QWidget* box;
    QWidget* box2;
    
    GLWidget *glWidget;
    ObjTools *objTools;
    GeoTools *geoTools;
    TerrainTools *terrainTools;
    ActivityTools *activityTools;
    //NaviBox *naviBox;
    
    std::vector<PropertiesAbstract*> objProperties;
    //PropertiesUndefined * propertiesUndefined;
    
    QMenu *routeMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *toolsMenu;
    
    QAction *saveAction;
    QAction *createPathsAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *propertiesAction;
    QAction *naviAction;
    QAction *toolsAction;
    QAction *objectsAction;
    QAction *terrainAction;
    QAction *terrainTreeEditr;
    QAction *trkEditr;
    QAction *geoAction;
    QAction *activityAction;
    
    AboutWindow* aboutWindow;
    NaviWindow* naviWindow;
};
//! [0]

#endif
