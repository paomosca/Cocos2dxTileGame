#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "HudLayer.h"


class HelloWorld : public cocos2d::CCLayer
{
public:
    
    ~HelloWorld();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void setViewpointCenter(cocos2d::CCPoint point);
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void setPlayerPosition(cocos2d::CCPoint position);
    
    cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
        
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
    
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _foreground, Foreground);
    
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _meta, Meta);
    
    CC_SYNTHESIZE(cocos2d::CCSprite *, _player, Player);
    
    CC_SYNTHESIZE(HudLayer*, _hud, Hud);
    
    CC_SYNTHESIZE(int, _numCollected, NumCollected);


    
    
};

#endif // __HELLOWORLD_SCENE_H__
