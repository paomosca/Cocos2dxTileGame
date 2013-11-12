//
//  HudLayer.h
//  TileGame
//
//  Created by paolo mosca on 12/11/13.
//
//

#ifndef __TileGame__HudLayer__
#define __TileGame__HudLayer__

#include "cocos2d.h"

class HudLayer : public cocos2d::CCLayer{
public:
    
    ~HudLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    void numCollectedChanged(int numCollected);
    
    CREATE_FUNC(HudLayer);
    CC_SYNTHESIZE(cocos2d::CCLabelTTF*, _label, Label);
    
    
};

#endif /* defined(__TileGame__HudLayer__) */
