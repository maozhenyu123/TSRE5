#include <QString>

#ifndef TEXTURE_H
#define	TEXTURE_H

class Texture {
public:
    Texture();
    Texture(const Texture& orig);
    virtual ~Texture();
    
     unsigned char* imageData;		
     int bpp;	
     int imageSize;
     int bytesPerPixel;
     int compressed;
     int width;			
     int height;			
     int texID;			
     int type;		
     int typk;
     unsigned int* tex;
     QString pathid;
     bool loaded = false;
     int ref = 0;
     bool glLoaded = false;

    Texture(QString pathid) {
        this->pathid = pathid;
    }

    bool GLTextures();
    void delVBO();
private:

};

#endif	/* TEXTURE_H */
