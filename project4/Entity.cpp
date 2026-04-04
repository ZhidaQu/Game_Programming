#include "Entity.h"
#include <cmath>
#include <cstdio>

// Constructors
Entity::Entity()
    : mPosition{0,0}, mMovement{0,0}, mVelocity{0,0}, mAcceleration{0,0},
      mScale{(float)DEFAULT_SIZE,(float)DEFAULT_SIZE},
      mColliderDimensions{(float)DEFAULT_SIZE,(float)DEFAULT_SIZE},
      mTexture{0}, mTextureType{SINGLE}, mAngle{0},
      mSpriteSheetDimensions{}, mDirection{RIGHT},
      mAnimationAtlas{{}}, mAnimationIndices{}, mFrameSpeed{0},
      mEntityType{NONE}
{
    mOwnsTexture = false;
}

Entity::Entity(Vector2 position, Vector2 scale,
               const char* textureFilepath, EntityType entityType)
    : mPosition{position}, mVelocity{0,0}, mAcceleration{0,0},
      mMovement{0,0}, mScale{scale}, mColliderDimensions{scale},
      mTexture{0}, mTextureType{SINGLE},
      mDirection{RIGHT}, mAnimationAtlas{{}}, mAnimationIndices{},
      mFrameSpeed{0}, mSpeed{DEFAULT_SPEED}, mAngle{0}, mEntityType{entityType}
{
    if (textureFilepath && textureFilepath[0] != '\0') {
        mTexture = LoadTexture(textureFilepath);
        mOwnsTexture = true;
    } else {
        mTexture = {0};
        mOwnsTexture = false;
    }
}

Entity::Entity(Vector2 position, Vector2 scale,
               const char* textureFilepath,
               TextureType textureType, Vector2 spriteSheetDimensions,
               std::map<Direction, std::vector<int>> animationAtlas,
               EntityType entityType)
    : mPosition{position}, mVelocity{0,0}, mAcceleration{0,0},
      mMovement{0,0}, mScale{scale}, mColliderDimensions{scale},
      mTexture{0}, mTextureType{textureType},
      mSpriteSheetDimensions{spriteSheetDimensions},
      mAnimationAtlas{animationAtlas}, mDirection{RIGHT},
      mAnimationIndices{}, mFrameSpeed{DEFAULT_FRAME_SPEED}, mAngle{0},
      mSpeed{DEFAULT_SPEED}, mEntityType{entityType}
{
    if (textureFilepath && textureFilepath[0] != '\0') {
        mTexture = LoadTexture(textureFilepath);
        mOwnsTexture = true;
    } else {
        mTexture = {0};
        mOwnsTexture = false;
    }

    if (mAnimationAtlas.count(RIGHT)) {
        mAnimationIndices = mAnimationAtlas.at(RIGHT);
    }
}

Entity::~Entity() {
    if (mOwnsTexture && mTexture.id != 0) {
        UnloadTexture(mTexture);
    }
}

//isColliding
bool Entity::isColliding(Entity* o) const {
    if (!o->isActive() || o == this) return false;
    float dx = fabsf(mPosition.x - o->mPosition.x)
               - (mColliderDimensions.x + o->mColliderDimensions.x) * 0.5f;
    float dy = fabsf(mPosition.y - o->mPosition.y)
               - (mColliderDimensions.y + o->mColliderDimensions.y) * 0.5f;
    return dx < 0.0f && dy < 0.0f;
}

// checkCollisionY
void Entity::checkCollisionY(Entity* ents, int n) {
    for (int i = 0; i < n; i++) {
        Entity* o = &ents[i];
        if (!isColliding(o)) continue;
        float yD = fabsf(mPosition.y - o->mPosition.y);
        float yOvlp = fabsf(yD - mColliderDimensions.y*0.5f - o->mColliderDimensions.y*0.5f);
        if (mVelocity.y > 0) {
            mPosition.y -= yOvlp; mVelocity.y = 0; mIsCollidingBottom = true;
            if (o->mEntityType == BLOCK) o->deactivate();
        } else if (mVelocity.y < 0) {
            mPosition.y += yOvlp; mVelocity.y = 0; mIsCollidingTop = true;
        }
    }
}

// checkCollisionX 
void Entity::checkCollisionX(Entity* ents, int n) {
    for (int i = 0; i < n; i++) {
        Entity* o = &ents[i];
        if (!isColliding(o)) continue;
        float yD = fabsf(mPosition.y - o->mPosition.y);
        float yOvlp = fabsf(yD - mColliderDimensions.y*0.5f - o->mColliderDimensions.y*0.5f);
        if (yOvlp < Y_COLLISION_THRESHOLD) continue;
        float xD = fabsf(mPosition.x - o->mPosition.x);
        float xOvlp = fabsf(xD - mColliderDimensions.x*0.5f - o->mColliderDimensions.x*0.5f);
        if      (mVelocity.x > 0) { mPosition.x -= xOvlp; mVelocity.x = 0; mIsCollidingRight = true; }
        else if (mVelocity.x < 0) { mPosition.x += xOvlp; mVelocity.x = 0; mIsCollidingLeft  = true; }
    }
}

// checkCollisionY
void Entity::checkCollisionY(Map* map) {
    if (!map) return;
    float hw = mColliderDimensions.x*0.5f, hh = mColliderDimensions.y*0.5f;
    Vector2 tC={mPosition.x,mPosition.y-hh}, tL={mPosition.x-hw,mPosition.y-hh}, tR={mPosition.x+hw,mPosition.y-hh};
    Vector2 bC={mPosition.x,mPosition.y+hh}, bL={mPosition.x-hw,mPosition.y+hh}, bR={mPosition.x+hw,mPosition.y+hh};
    float xo=0,yo=0;
    if ((map->isSolidTileAt(tC,&xo,&yo)||map->isSolidTileAt(tL,&xo,&yo)||map->isSolidTileAt(tR,&xo,&yo))
        && mVelocity.y<0 && xo<map->getTileSize()*0.4f)
        { mPosition.y+=yo*1.01f; mVelocity.y=0; mIsCollidingTop=true; }
    if ((map->isSolidTileAt(bC,&xo,&yo)||map->isSolidTileAt(bL,&xo,&yo)||map->isSolidTileAt(bR,&xo,&yo))
        && mVelocity.y>0)
        { mPosition.y-=yo*1.01f; mVelocity.y=0; mIsCollidingBottom=true; }
}

//checkCollisionX
void Entity::checkCollisionX(Map* map) {
    if (!map) return;
    float hw=mColliderDimensions.x*0.5f, hh=mColliderDimensions.y*0.5f;
    Vector2 lC={mPosition.x-hw,mPosition.y},lT={mPosition.x-hw,mPosition.y-hh},lB={mPosition.x-hw,mPosition.y+hh};
    Vector2 rC={mPosition.x+hw,mPosition.y},rT={mPosition.x+hw,mPosition.y-hh},rB={mPosition.x+hw,mPosition.y+hh};
    float xo=0,yo=0;
    if ((map->isSolidTileAt(rC,&xo,&yo)||map->isSolidTileAt(rT,&xo,&yo)||map->isSolidTileAt(rB,&xo,&yo))
        && mVelocity.x>0 && yo>=0.5f)
        { mPosition.x-=xo*1.01f; mVelocity.x=0; mIsCollidingRight=true; }
    if ((map->isSolidTileAt(lC,&xo,&yo)||map->isSolidTileAt(lT,&xo,&yo)||map->isSolidTileAt(lB,&xo,&yo))
        && mVelocity.x<0 && yo>=0.5f)
        { mPosition.x+=xo*1.01f; mVelocity.x=0; mIsCollidingLeft=true; }
}

// animate
void Entity::animate(float deltaTime) {
    if (mFrameSpeed <= 0) return;

    if (mAnimationAtlas.count(mDirection))
        mAnimationIndices = mAnimationAtlas.at(mDirection);

    if (mAnimationIndices.empty()) return;

    mAnimationTime += deltaTime;
    if (mAnimationTime >= 1.0f / (float)mFrameSpeed) {
        mAnimationTime = 0.0f;
        mCurrentFrameIndex = (mCurrentFrameIndex + 1) % (int)mAnimationIndices.size();
    }
}

//AI 
void Entity::AIWander() {
    if      (mPosition.x >= mPatrolMax) moveLeft();
    else if (mPosition.x <= mPatrolMin) moveRight();
    else if (mMovement.x == 0)          moveRight();
}

void Entity::AIFollow(Entity* t) {
    if (mAIState == IDLE) {
        if (fabsf(mPosition.x - t->getPosition().x) + fabsf(mPosition.y - t->getPosition().y) < 200.0f) mAIState = FOLLOWING;
    } else {
        if (mPosition.x > t->getPosition().x) moveLeft();
        else moveRight();
    }
}

void Entity::AIFly(Entity* t) {
    if (mPosition.x > t->getPosition().x) moveLeft();
    else                                   moveRight();
    mFlyOffset  += 0.05f;
    mVelocity.y  = sinf(mFlyOffset) * (float)mSpeed * 0.6f;
    mAcceleration.y = 0.0f;
}

void Entity::AIActivate(Entity* t) {
    if (!t) return;
    switch (mAIType) {
        case WANDERER: AIWander();    break;
        case FOLLOWER: AIFollow(t);   break;
        case FLYER_AI: AIFly(t);      break;
    }
}

// update
void Entity::update(float deltaTime, Entity* player, Map* map,
                    Entity* collidableEntities, int count) {
    if (mEntityStatus == INACTIVE) return;

    if (mEntityType == NPC) AIActivate(player);

    resetColliderFlags();

    mVelocity.x  = mMovement.x * (float)mSpeed;
    mVelocity.x += mAcceleration.x * deltaTime;
    mVelocity.y += mAcceleration.y * deltaTime;

    if (mVelocity.y > MAX_FALL_SPEED) mVelocity.y = MAX_FALL_SPEED;

    if (mIsJumping) { mIsJumping = false; mVelocity.y -= mJumpingPower; }

    mPosition.x += mVelocity.x * deltaTime;
    if (collidableEntities) checkCollisionX(collidableEntities, count);
    checkCollisionX(map);

    mPosition.y += mVelocity.y * deltaTime;
    if (collidableEntities) checkCollisionY(collidableEntities, count);
    checkCollisionY(map);

    if (mTextureType == ATLAS && GetLength(mMovement) != 0.0f) animate(deltaTime);
}

//render
static Rectangle getUVRect(Texture2D* tex, int idx, float cols, float rows) {
    float fw = tex->width / cols, fh = tex->height / rows;
    return {(idx % (int)cols)*fw, (idx / (int)cols)*fh, fw, fh};
}

void Entity::render() {
    if (mEntityStatus == INACTIVE) return;

    Rectangle dst    = {mPosition.x, mPosition.y, mScale.x, mScale.y};
    Vector2   origin = {mScale.x * 0.5f, mScale.y * 0.5f};

    if (mTexture.id == 0 || mTexture.width <= 0 || mTexture.height <= 0) {
        Color debugColor = (mEntityType == PLAYER) ? BLUE : RED;
        DrawRectangleRec(
            {mPosition.x - origin.x, mPosition.y - origin.y, mScale.x, mScale.y},
            debugColor
        );
        return;
    }

    Rectangle src;
    if (mTextureType == ATLAS &&
        !mAnimationIndices.empty() &&
        mSpriteSheetDimensions.x > 0 &&
        mSpriteSheetDimensions.y > 0) {
        src = getUVRect(&mTexture,
                        mAnimationIndices[mCurrentFrameIndex],
                        mSpriteSheetDimensions.x,
                        mSpriteSheetDimensions.y);
    } else {
        src = {0, 0, (float)mTexture.width, (float)mTexture.height};
    }

    if (mEntityType == PLAYER && mDirection == LEFT) {
        src.width = -src.width;
    }

    DrawTexturePro(mTexture, src, dst, origin, mAngle, WHITE);
}

//displayCollider
void Entity::displayCollider() {
    Rectangle box = getColliderRect();
    DrawRectangleLinesEx(box, 1.0f, GREEN);
}