#include "HelloWorldScene.h"

USING_NS_CC;



CCScene* HelloWorld::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    HudLayer *hud = HudLayer::create();
    
    scene->addChild(hud);
    
    layer->_hud = hud;
    
    
    
    
    

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld(){
    CC_SAFE_RELEASE_NULL(_tileMap);
    CC_SAFE_RELEASE_NULL(_background);
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_meta);
}


// on "init" you need to initialize your instance
bool HelloWorld::init(){
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    this->setTouchEnabled(true);
    
    _tileMap = CCTMXTiledMap::create("TileMap.tmx");
    _tileMap->retain();
    
    _tileMap->setZOrder(-1);
    _background = _tileMap->layerNamed("Background");
    _background->retain();
    
    _foreground = _tileMap->layerNamed("Foreground");
    _foreground->retain();
    
    
    _meta = _tileMap->layerNamed("Meta");
    _meta->retain();
    
    _meta->setVisible(false);
    
    
    
    CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Objects");
    CCAssert(objects != NULL, "'Objects' object group not found");

    CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
    CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
    
    
    int x = spawnPoint->valueForKey("x")->intValue();
    int y = spawnPoint->valueForKey("y")->intValue();
    
    CCLOG ("x: %d y: %d", x, y);
    
    _player = CCSprite::create("Player.png");
    _player->retain();
    
    _player->setPosition(ccp (x, y));
    
    this->addChild(_player);
        
    this->setViewpointCenter(_player->getPosition());
    
    this->addChild(_tileMap);

    return true;
}

void HelloWorld::setViewpointCenter(CCPoint position){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width/2);
    x = MIN(x, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    
    this->setPosition(viewPoint);
}


void HelloWorld::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
}


bool HelloWorld::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    //CCPoint touchPoint = touch->getLocation();
    
    return true;
}



void HelloWorld::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    // Choose one of the touches to work with
    
    
    
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    location = this->convertToNodeSpace(location);

    
    CCPoint playerPos = _player->getPosition();
    CCPoint diff = ccpSub(location, playerPos);
    
    
    
    if ( abs(diff.x) > abs(diff.y) ) {

        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width;
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += _tileMap->getTileSize().height;
        } else {
            playerPos.y -= _tileMap->getTileSize().height;
        }
    }
    
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
        this->setPlayerPosition(playerPos);
    }
    
    this->setViewpointCenter(_player->getPosition());
    
}


cocos2d::CCPoint HelloWorld::tileCoordForPosition(cocos2d::CCPoint position) {
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}



void HelloWorld::setPlayerPosition(cocos2d::CCPoint position) {
    
    CCPoint tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->tileGIDAt(tileCoord);
    
    if (tileGid) {
        
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
        
        if (properties) {
            CCString *collision = ccs(properties->valueForKey("Collidable")->getCString());
            
            if((collision)&&(collision->compare(ccs("True")->getCString()) == 0)){
                
                return;
            }
            
            CCString *collectible = ccs(properties->valueForKey("Collectable")->getCString());

            if((collectible)&&(collectible->compare(ccs("True")->getCString()) == 0)){
                
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
                
                _numCollected++;
                
                _hud->numCollectedChanged(_numCollected);
                
                
                
            }
            
            
        }
    }
    
	_player->setPosition(position);
}


