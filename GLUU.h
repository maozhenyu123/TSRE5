#ifndef GLUU_H
#define	GLUU_H

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include "Vector4f.h"
//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLUU {
public:
    QOpenGLShaderProgram *m_program;
    unsigned int shaderProgram;
    
    unsigned int vertexPositionAttribute;
    unsigned int textureCoordAttribute;
    unsigned int pMatrixUniform;
    unsigned int mvMatrixUniform;
    unsigned int msMatrixUniform;
    unsigned int samplerUniform;
    unsigned int lod;
    unsigned int sun;
    unsigned int brightness;
    unsigned int skyColor;
    unsigned int skyLight;
    unsigned int shaderAlpha;
    unsigned int shaderAlphaTest;
    unsigned int shaderTextureEnabled;
    unsigned int shaderShapeColor;
    
    float alpha;
    float alphaTest;
    
    float skyc[4]{230.0/255.0,248.0/255,255.0/255.0, 1.0};
    float sky[3]{1.0, 1.0, 1.0};
    
    float* mvMatrixStack[1000];
    int imvMatrixStack;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    //QMatrix4x4 m_proj;
    //QMatrix4x4 m_camera;
    //QMatrix4x4 m_world;
    float* pMatrix;
    float* mvMatrix;
    float* objStrMatrix;
    static GLUU *get();
    GLUU();
    virtual ~GLUU();
    void initShader();
    void setMatrixUniforms();
    void mvPushMatrix();
    void mvPopMatrix();
    float degToRad(float degrees);
    void disableTextures(Vector4f* color);
    void enableTextures();
private:
    const char* getShader(QString shaderScript, QString type);
    bool textureEnabled;
    Vector4f shapeColor;
};

#endif	/* GLUU_H */
