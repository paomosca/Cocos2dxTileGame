//
//  HudLayer.cpp
//  TileGame
//
//  Created by paolo mosca on 12/11/13.
//
//

#include "HudLayer.h"

USING_NS_CC;


HudLayer::~HudLayer(){
    CC_SAFE_RELEASE_NULL(_label);
}


bool HudLayer::init(){
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    _label = cocos2d::CCLabelTTF::create("0","Verdana-Bold",18.0);
    _label->retain();
    _label->setColor(ccc3(0,0,0));
    
    int margin = 10;
    _label->setPosition(ccp(winSize.width - (_label->getContentSize().width/2) - margin, _label->getContentSize().height/2 + margin));
    this->addChild(_label);
                            
    
    return true;
}
                        

void HudLayer::numCollectedChanged(int numCollected){
    
    _label->setString(CCString::createWithFormat("%d",numCollected)->getCString());
}

