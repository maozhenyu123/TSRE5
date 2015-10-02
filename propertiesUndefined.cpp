#include "PropertiesUndefined.h"
#include "WorldObj.h"

PropertiesUndefined::PropertiesUndefined()
    : QWidget(){
    
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setContentsMargins(0,1,1,1);
    infoLabel = new QLabel("Select to see properties.");
    infoLabel->setStyleSheet("QLabel { color : #999999; }");
    infoLabel->setContentsMargins(3,0,0,0);
    vbox->addWidget(infoLabel);
    
    
    vbox->addStretch(1);
    this->setLayout(vbox);
}

PropertiesUndefined::~PropertiesUndefined() {
}

void PropertiesUndefined::showObj(WorldObj* obj){
    if(obj == NULL)
        infoLabel->setText("Select to see properties.");
    else
        infoLabel->setText("Unsupported: "+obj->type);
}