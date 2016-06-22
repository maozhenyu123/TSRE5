#ifndef FORESTOBJ_H
#define	FORESTOBJ_H

#include "WorldObj.h"
#include <QString>

class OglObj;

class ForestObj : public WorldObj{
public:
    /*struct Shape{
        int iloscv;
        QOpenGLBuffer VBO;
        QOpenGLVertexArrayObject VAO;
    };*/
    struct ForestList{
        QString name;
        QString texture;
        float scaleRangeX = 0;
        float scaleRangeZ = 0;
        float treeSizeX = 0;
        float treeSizeZ = 0;
    };
    static std::vector<ForestList> forestList;
    QString treeTexture = "";
    float scaleRangeX = 0;
    float scaleRangeZ = 0;
    float areaX = 0;
    float areaZ = 0;
    float treeSizeX = 0;
    float treeSizeZ = 0;
    float population = 0;
    ForestObj();
    ForestObj(const ForestObj& orig);
    bool allowNew();
    void load(int x, int y);
    void set(int sh, FileBuffer* data);
    void set(QString sh, int val);
    void set(QString sh, float val);
    void set(QString sh, FileBuffer* data);
    void save(QTextStream* out);
    void deleteVBO();
    void render(GLUU* gluu, float lod, float posx, float posz, float* playerW, float* target, float fov, int selectionColor);
    static void loadForestList();
    virtual ~ForestObj();
private:
    void drawShape();
    int tex;
    bool init;
    OglObj shape;
    QString * texturePath = NULL;
};

#endif	/* FORESTOBJ_H */

