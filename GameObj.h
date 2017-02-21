/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef GAMEOBJ_H
#define	GAMEOBJ_H

class GameObj {
public:
    enum TypeObj {
        none = 0,
        undefined = 1,
        worldobj = 2,
        terrainobj = 3
    };
    
    TypeObj typeObj = this->undefined;
    
    GameObj();
    GameObj(const GameObj& orig);
    virtual ~GameObj();
    
    virtual bool select();
    virtual bool select(int value);
    virtual bool unselect();
    virtual bool isSelected();
    virtual void updateSim(float deltaTime);
    virtual void translate(float px, float py, float pz);
    virtual void rotate(float x, float y, float z);
    virtual void resize(float x, float y, float z);
    virtual void setPosition(int x, int z, float* p);
    virtual void setPosition(float* p);
    virtual void setMartix();

protected:
    bool selected;
};

#endif	/* GAMEOBJ_H */

