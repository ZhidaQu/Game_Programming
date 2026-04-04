#pragma once
#include "Map.h"
#include <map>
#include <vector>

enum Direction    { LEFT, UP, RIGHT, DOWN              };
enum EntityStatus { ACTIVE, INACTIVE                   };
enum EntityType   { PLAYER, BLOCK, PLATFORM, NPC, NONE };
enum AIType       { WANDERER, FOLLOWER, FLYER_AI       };
enum AIState      { WALKING, IDLE, FOLLOWING           };
enum EnemyState   { ENEMY_ALIVE, ENEMY_DEAD            };

class Entity {
private:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;
    Vector2 mAcceleration;
    Vector2 mScale;
    Vector2 mColliderDimensions;

    Texture2D   mTexture;
    TextureType mTextureType;
    Vector2     mSpriteSheetDimensions;

    std::map<Direction, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    Direction        mDirection;
    int              mFrameSpeed;

    int   mCurrentFrameIndex = 0;
    float mAnimationTime     = 0.0f;

    bool  mIsJumping    = false;
    float mJumpingPower = 0.0f;
    int   mSpeed        = 200;
    float mAngle        = 0.0f;

    bool mIsCollidingTop    = false;
    bool mIsCollidingBottom = false;
    bool mIsCollidingRight  = false;
    bool mIsCollidingLeft   = false;

    EntityStatus mEntityStatus = ACTIVE;
    EntityType   mEntityType;
    AIType       mAIType  = WANDERER;
    AIState      mAIState = IDLE;
    EnemyState   mEnemyState = ENEMY_ALIVE;

    // Extra patrol/fly data
    float mPatrolMin = 0.0f;
    float mPatrolMax = 200.0f;
    float mFlyOffset = 0.0f;

    bool mOwnsTexture = true;

    // Internal helpers 
    bool isColliding(Entity* other) const;
    void checkCollisionY(Entity* entities, int count);
    void checkCollisionY(Map* map);
    void checkCollisionX(Entity* entities, int count);
    void checkCollisionX(Map* map);
    void resetColliderFlags() {
        mIsCollidingTop = mIsCollidingBottom =
        mIsCollidingRight = mIsCollidingLeft = false;
    }
    void animate(float deltaTime);
    void AIActivate(Entity* target);
    void AIWander();
    void AIFollow(Entity* target);
    void AIFly(Entity* target);

public:
    static constexpr int   DEFAULT_SIZE        = 64;
    static constexpr int   DEFAULT_SPEED       = 200;
    static constexpr int   DEFAULT_FRAME_SPEED = 8;
    static constexpr float Y_COLLISION_THRESHOLD = 0.5f;
    static constexpr float MAX_FALL_SPEED      = 1200.0f; 

    Entity();
    Entity(Vector2 position, Vector2 scale,
           const char* textureFilepath, EntityType entityType);
    Entity(Vector2 position, Vector2 scale,
           const char* textureFilepath,
           TextureType textureType, Vector2 spriteSheetDimensions,
           std::map<Direction, std::vector<int>> animationAtlas,
           EntityType entityType);
    ~Entity();

    // Core
    void update(float deltaTime, Entity* player, Map* map,
                Entity* collidableEntities, int count);
    void render();
    void normaliseMovement() { Normalise(&mMovement); }
    void displayCollider();

    // Actions
    void jump()       { mIsJumping = true;        }
    void activate()   { mEntityStatus = ACTIVE;   }
    void deactivate() { mEntityStatus = INACTIVE;  }
    void kill()       { mEnemyState = ENEMY_DEAD; mEntityStatus = INACTIVE; }

    // Movement
    void moveUp()        { mMovement.y = -1; mDirection = UP;    }
    void moveDown()      { mMovement.y =  1; mDirection = DOWN;  }
    void moveLeft()      { mMovement.x = -1; mDirection = LEFT;  }
    void moveRight()     { mMovement.x =  1; mDirection = RIGHT; }
    void resetMovement() { mMovement = {0.0f, 0.0f};              }

    // Getters
    Vector2     getPosition()           const { return mPosition;           }
    Vector2     getVelocity()           const { return mVelocity;           }
    Vector2     getMovement()           const { return mMovement;           }
    Vector2     getAcceleration()       const { return mAcceleration;       }
    Vector2     getScale()              const { return mScale;              }
    Vector2     getColliderDimensions() const { return mColliderDimensions; }
    Texture2D   getTexture()            const { return mTexture;            }
    TextureType getTextureType()        const { return mTextureType;        }
    Direction   getDirection()          const { return mDirection;          }
    int         getFrameSpeed()         const { return mFrameSpeed;         }
    float       getJumpingPower()       const { return mJumpingPower;       }
    bool        isJumping()             const { return mIsJumping;          }
    int         getSpeed()              const { return mSpeed;              }
    float       getAngle()              const { return mAngle;              }
    EntityType  getEntityType()         const { return mEntityType;         }
    AIType      getAIType()             const { return mAIType;             }
    AIState     getAIState()            const { return mAIState;            }
    EnemyState  getEnemyState()         const { return mEnemyState;         }
    bool isActive()          const { return mEntityStatus == ACTIVE;        }
    bool isDead()            const { return mEnemyState == ENEMY_DEAD;      }
    bool isCollidingTop()    const { return mIsCollidingTop;                }
    bool isCollidingBottom() const { return mIsCollidingBottom;             }
    bool isCollidingLeft()   const { return mIsCollidingLeft;               }
    bool isCollidingRight()  const { return mIsCollidingRight;              }

    Rectangle getColliderRect() const {
        return { mPosition.x - mColliderDimensions.x * 0.5f,
                 mPosition.y - mColliderDimensions.y * 0.5f,
                 mColliderDimensions.x, mColliderDimensions.y };
    }

    // Setters
    void setPosition(Vector2 v)           { mPosition = v;                  }
    void setVelocity(Vector2 v)           { mVelocity = v;                  }
    void setMovement(Vector2 v)           { mMovement = v;                  }
    void setAcceleration(Vector2 v)       { mAcceleration = v;              }
    void setScale(Vector2 v)              { mScale = v;                     }
    void setColliderDimensions(Vector2 v) { mColliderDimensions = v;        }
    void setSpeed(int s)                  { mSpeed = s;                     }
    void setFrameSpeed(int s)             { mFrameSpeed = s;                }
    void setJumpingPower(float p)         { mJumpingPower = p;              }
    void setAngle(float a)                { mAngle = a;                     }
    void setEntityType(EntityType t)      { mEntityType = t;                }
    void setAIType(AIType t)              { mAIType = t;                    }
    void setAIState(AIState s)            { mAIState = s;                   }
    void setPatrol(float mn, float mx)    { mPatrolMin = mn; mPatrolMax = mx; }
    void setFlyOffset(float o)            { mFlyOffset = o;                 }
    void setTexture(Texture2D tex)        { mTexture = tex; mOwnsTexture = false; }
    void setDirection(Direction d) {
        mDirection = d;
        if (mTextureType == ATLAS && mAnimationAtlas.count(d))
            mAnimationIndices = mAnimationAtlas.at(d);
    }
    std::map<Direction, std::vector<int>> getAnimationAtlas() const
        { return mAnimationAtlas; }
};