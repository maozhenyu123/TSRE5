#ifndef ACELIB_H
#define	ACELIB_H

#include <QThread>
#include "Texture.h"

class AceLib : public QThread
 {
     Q_OBJECT

public:
    AceLib();
    AceLib(const AceLib& orig);
    virtual ~AceLib();
    //static bool LoadACE(Texture* texture);
    Texture* texture;
private:
    
protected:
     void run();
};

#endif	/* ACELIB_H */
