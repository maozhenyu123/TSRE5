#include "ForestObj.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <cstdlib>
#include "TexLib.h"
#include "Vector2f.h"
#include "TerrainLib.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ForestObj::ForestObj() {
    this->loaded = false;
}

ForestObj::ForestObj(const ForestObj& orig) {
}

ForestObj::~ForestObj() {
}

void ForestObj::load(int x, int y) {
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->loaded = true;
    this->size = -1;
    this->tex = -1;
    this->init = false;
}

void ForestObj::set(QString sh, FileBuffer* data) {
    if (sh == ("treetexture")) {
        treeTexture = ParserX::odczytajtc(data);
        return;
    }
    if (sh == ("scalerange")) {
        scaleRangeX = ParserX::parsujr(data);
        scaleRangeZ = ParserX::parsujr(data);
        return;
    }
    if (sh == ("area")) {
        areaX = ParserX::parsujr(data);
        areaZ = ParserX::parsujr(data);
        return;
    }
    if (sh == ("treesize")) {
        treeSizeX = ParserX::parsujr(data)*0.7;
        treeSizeZ = ParserX::parsujr(data);
        return;
    }
    if (sh == ("population")) {
        population = ParserX::parsujr(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void ForestObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov) {
    if (!loaded) return;
    //if (jestPQ < 2) return;
    //GLUU* gluu = GLUU::get();
    //if((this.position===undefined)||this.qDirection===undefined) return;

    /*if (size > 0) {
        if ((lod > size)) {
            float v1[2];
            v1[0] = pos[0] - (target[0]);
            v1[1] = pos[2] - (target[2]);
            float v2[2];
            v2[0] = posx;
            v2[1] = posz;
            float iloczyn = v1[0] * v2[0] + v1[1] * v2[1];
            float d1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
            float d2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1]);
            float zz = iloczyn / (d1 * d2);
            if (zz > 0) return;

            float ccos = cos(fov) + zz;
            float xxx = sqrt(2 * d2 * d2 * (1 - ccos));
            //if((ccos > 0) && (xxx > 200+50)) return;
            if ((ccos > 0) && (xxx > size + 150) && (skipLevel == 1)) return;
        }
    } else {
        if (ShapeLib::shape[shape]->loaded)
            size = ShapeLib::shape[shape]->size;
    }
*/
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, position[0], 0, position[2]);
    //float scale = sqrt(qDirection[0] * qDirection[0] + qDirection[1] * qDirection[1] + qDirection[2] * qDirection[2]);
    //float angle = ((acos(qDirection[3])*360) / M_PI);
    //Mat4::rotate(gluu->mvMatrix, gluu->mvMatrix, gluu->degToRad(-angle), -qDirection[0] * scale, -qDirection[1] * scale, qDirection[2] * scale);
    //Mat4::rotate(gluu->mvMatrix, gluu->mvMatrix, gluu->degToRad(180), 0, -1, 0);

    //if(selected){
    //    selected = !selected;
    //    selectionColor = 155;
    //}
    //gluu.setMatrixUniforms();

    //
    //var z = this.position[0]*mmm[9] + this.position[1]*mmm[7] + this.position[2]*mmm[9];

    Mat4::identity(gluu->objStrMatrix);    
    gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    gluu->m_program->setUniformValue(gluu->msMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->objStrMatrix));
    gluu->m_program->setUniformValue(gluu->shaderAlpha, 0.0f);
    gluu->enableTextures();
    drawShape();
};

void ForestObj::drawShape(){
    if (tex == -2) {
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
        if (tex == -1) {
            tex = TexLib::addTex(resPath, treeTexture);
            glDisable(GL_TEXTURE_2D);
        }
    }

    if (!init) {
            shape.iloscv = population*24;
            float* punkty = new float[shape.iloscv*8];
            int ptr = 0;

            int seed = (int)(position[0] + position[1] + position[2]);
            //Random random = new Random(seed);
            std::srand(seed);

            for(int uu = 0; uu < population; uu++){

                float tposx = ((float)((std::rand()%100))/100)*areaX-areaX/2;
                float tposz = ((float)((std::rand()%100))/100)*areaZ-areaZ/2;
                Vector2f uuu(tposx,tposz);
                uuu.rotate(((qDirection[2]+0.00001f)/fabs(qDirection[2]+0.00001f))*(float)-acos(qDirection[3])*2, 0);
                tposx = uuu.x;
                tposz = uuu.y;

                float wysokosc = TerrainLib::getHeight(x, y, tposx+position[0], tposz+position[2]);

                for(int j = -1; j < 2; j+=2){
                    for(int i = -1; i<2; i+=2){
                            punkty[ptr++] = -treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc+treeSizeZ;
                            punkty[ptr++] = -treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 0; punkty[ptr++] = 0;
                            
                            punkty[ptr++] = treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc+treeSizeZ;
                            punkty[ptr++] = treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 1; punkty[ptr++] = 0;
                            
                            punkty[ptr++] = treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc;
                            punkty[ptr++] = treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 1; punkty[ptr++] = 1;
                            
                            punkty[ptr++] = -treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc;
                            punkty[ptr++] = -treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 0; punkty[ptr++] = 1;
                            
                            punkty[ptr++] = -treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc+treeSizeZ;
                            punkty[ptr++] = -treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 0; punkty[ptr++] = 0;
                            
                            punkty[ptr++] = treeSizeX*i*j/2 + tposx;
                            punkty[ptr++] = wysokosc;
                            punkty[ptr++] = treeSizeX*i/2 + tposz;
                            punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                            punkty[ptr++] = 1; punkty[ptr++] = 1;
                    }
                }
            }
            
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        shape.VAO.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&shape.VAO);

        shape.VBO.create();
        shape.VBO.bind();
        shape.VBO.allocate(punkty, ptr * sizeof (GLfloat));
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), 0);
        f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), reinterpret_cast<void *> (6 * sizeof (GLfloat)));
        shape.VBO.release();
        //shape.iloscv = ptr/8;

        delete punkty;
        init = true;
    } else {
        
        if(TexLib::mtex[tex]->loaded){
            if(!TexLib::mtex[tex]->glLoaded) TexLib::mtex[tex]->GLTextures();
            glBindTexture(GL_TEXTURE_2D, TexLib::mtex[tex]->tex[0]);
        }
        
        QOpenGLVertexArrayObject::Binder vaoBinder1(&shape.VAO);
        glDrawArrays(GL_TRIANGLES, 0, shape.iloscv);
    }
}