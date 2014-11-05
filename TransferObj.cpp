#include "TransferObj.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include <cstdlib>
#include "TexLib.h"
#include "Vector2f.h"
#include "TerrainLib.h"
#include <QOpenGLShaderProgram>

TransferObj::TransferObj() {
}

TransferObj::TransferObj(const TransferObj& orig) {
}

TransferObj::~TransferObj() {
}

void TransferObj::load(int x, int y) {
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->loaded = true;
    this->size = -1;
    this->tex = -1;
    this->init = false;
}

void TransferObj::set(QString sh, FileBuffer* data) {
    if (sh == ("filename")) {
        texture = ParserX::odczytajtc(data);
        return;
    }
    if (sh == ("width")) {
        width = ParserX::parsujr(data);
        return;
    }
    if (sh == ("height")) {
        height = ParserX::parsujr(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void TransferObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov) {
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
    gluu->enableTextures();
    drawShape();
};

void TransferObj::drawShape(){
    if (tex == -2) {
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
        if (tex == -1) {
            tex = TexLib::addTex(resPath, texture);
            glDisable(GL_TEXTURE_2D);
        }
    }
    float scale = (float) sqrt(qDirection[0] * qDirection[0] + qDirection[1] * qDirection[1] + qDirection[2] * qDirection[2]);
    float off = ((qDirection[1]+0.000001f)/fabs(scale+0.000001f))*(float)-acos(qDirection[3])*2;
        
    if (!init) {
            Vector2f x1y1(-width/2,-height/2, off, 0);
            Vector2f x1y2(-width/2,height/2, off, 0);
            Vector2f x2y1(width/2,-height/2, off, 0);
            Vector2f x1y12 = x1y2.subv(x1y1);
            Vector2f x12y1 = x2y1.subv(x1y1);
            float x1y12d = x1y12.getDlugosc();
            float x12y1d = x12y1.getDlugosc();
            
            float step = 2.0;
            bool addR = true;
            if(x12y1d*x1y12d < 2000) {
                step = 1;
                addR = false;
            }
                
            shape.iloscv = (int)((x12y1d/step)+1)*(int)((x1y12d/step)+1);
            float* punkty = new float[shape.iloscv*48];
            
            //shape.iloscv = shape.iloscv*4;
            int ptr = 0;
            float wysokosc = 0;
            for(float j = 0; j < x12y1d; j+=step){
                float jj = j+step;
                if(jj>x12y1d) jj = x12y1d;
                for(float i = 0; i < x1y12d; i+=step){

                        float ii = i+step;
                        if(ii>x1y12d) ii = x1y12d;
                        
                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = i/x1y12d;

                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = ii/x1y12d;
                        
                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = ii/x1y12d;

                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = i/x1y12d;

                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = ii/x1y12d;
                        
                        wysokosc = TerrainLib::getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = i/x1y12d;
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
        shape.iloscv = ptr/8;

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