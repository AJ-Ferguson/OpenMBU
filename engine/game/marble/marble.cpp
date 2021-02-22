//-----------------------------------------------------------------------------
// Torque Shader Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#include "game/marble/marble.h"

#include "audio/audioDataBlock.h"

//----------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(Marble);

U32 Marble::smEndPadId = 0;

Marble::Marble()
{
    // TODO: HiFi
    mTypeMask |= PlayerObjectType; // | GameBaseHiFiObjectType;

    // TODO: Finish Implementation of Marble
    mControllable = true;
}

Marble::~Marble()
{
    // TODO: Implement ~Marble
}

void Marble::initPersistFields()
{
    Parent::initPersistFields();

    addField("Controllable", TypeBool, Offset(mControllable, Marble));
}

//----------------------------------------------------------------------------

Marble::Contact::Contact()
{
    // TODO: Implement Contact
}

Marble::SinglePrecision::SinglePrecision()
{
    // TODO: Implement SinglePrecision
}

Marble::StateDelta::StateDelta()
{
    // TODO: Implement StateDelta
}

Marble::EndPadEffect::EndPadEffect()
{
    // TODO: Implement EndPadEffect
}

Marble::PowerUpState::PowerUpState()
{
    // TODO: Implement PowerUpState
}

Marble::PowerUpState::~PowerUpState()
{
    // TODO: Implement ~PowerUpState
}

//----------------------------------------------------------------------------

SceneObject* Marble::getPad()
{
    // TODO: Implement getPad
    return nullptr;
}

S32 Marble::getPowerUpId()
{
    // TODO: Implement getPowerUpId
    return 0;
}

const QuatF& Marble::getGravityFrame()
{
    // TODO: Implement getGravityFrame
    return QuatF();
}

U32 Marble::getMaxNaturalBlastEnergy()
{
    // TODO: Implement getMaxNaturalBlastEnergy
    return 0;
}

U32 Marble::getMaxBlastEnergy()
{
    // TODO: Implement getMaxBlastEnergy
    return 0;
}

F32 Marble::getBlastPercent()
{
    // TODO: Implement getBlastPercent
    return 0;
}

F32 Marble::getBlastEnergy() const
{
    // TODO: Implement getBlastEnergy
    return 0;
}

void Marble::setBlastEnergy(F32)
{
    // TODO: Implement setBlastEnergy
}

void Marble::setUseFullMarbleTime(bool)
{
    // TODO: Implement setUseFullMarbleTime
}

void Marble::setMarbleTime(U32)
{
    // TODO: Implement setMarbleTime
}

U32 Marble::getMarbleTime()
{
    // TODO: Implement getMarbleTime
    return 0;
}

void Marble::setMarbleBonusTime(U32)
{
    // TODO: Implement setMarbleBonusTime
}

U32 Marble::getMarbleBonusTime()
{
    // TODO: Implement getMarbleBonusTime
    return 0;
}

U32 Marble::getFullMarbleTime()
{
    // TODO: Implement getFullMarbleTime
    return 0;
}

Marble::Contact& Marble::getLastContact()
{
    // TODO: Implement getLastContact
    return Marble::Contact();
}

void Marble::setGravityFrame(const QuatF&, bool)
{
    // TODO: Implement setGravityFrame
}

void Marble::onSceneRemove()
{
    Parent::onSceneRemove();
}

void Marble::setPosition(const Point3D& pos, bool doWarp)
{
    MatrixF mat = mObjToWorld;
    mat[3] = pos.x;
    mat[7] = pos.y;
    mat[11] = pos.z;
    mPosition = pos;
    mSinglePrecision.mPosition = pos;

    Parent::setTransform(mat);

    setMaskBits(MoveMask);

    if (doWarp)
    {
        mLastRenderPos = pos;
        mLastRenderVel = mVelocity;
        mRenderScale = mObjScale;
        setMaskBits(WarpMask);
    }
}

void Marble::setPosition(const Point3D& pos, const AngAxisF& angAxis, float mouseY)
{
    MatrixF mat = mObjToWorld;
    mat[3] = pos.x;
    mat[7] = pos.y;
    mat[11] = pos.z;
    mPosition = pos;
    mSinglePrecision.mPosition = pos;

    Parent::setTransform(mat);

    angAxis.setMatrix(&mat);

    mMouseX = mAtan(mat[1], mat[5]);
    mMouseY = mouseY;
    mLastRenderPos = pos;
    mLastRenderVel = mVelocity;
    mRenderScale = mObjScale;

    setMaskBits(MoveMask | WarpMask);
}

void Marble::setTransform(const MatrixF& mat)
{
    setPosition(Point3F(mat[3], mat[7], mat[11]), true);
}

Point3F& Marble::getPosition()
{
    return Point3F(mObjToWorld[3], mObjToWorld[7], mObjToWorld[11]);
}

void Marble::victorySequence()
{
    setVelocity(Point3F(0.0f, 0.0f, 0.1f));
}

void Marble::setMode(U32)
{
    // TODO: Implement setMode
}

void Marble::setOOB(bool isOOB)
{
    mOOB = isOOB;
    setMaskBits(OOBMask);
}

void Marble::interpolateTick(F32 delta)
{
    // TODO: Implement interpolateTick
    Parent::interpolateTick(delta);
}

S32 Marble::mountPowerupImage(ShapeBaseImageData*)
{
    // TODO: Implement mountPowerupImage
    return 0;
}

void Marble::updatePowerUpParams()
{
    // TODO: Implement updatePowerUpParams
}

bool Marble::getForce(Point3F& pos, Point3F* force)
{
    // TODO: Implement getForce in GameBase and StaticShape

    // TODO: Implement getForce
    return false;
}

U32 Marble::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
    // TODO: Implement packUpdate
    return Parent::packUpdate(conn, mask, stream);
}

void Marble::unpackUpdate(NetConnection* conn, BitStream* stream)
{
    // TODO: Implement unpackUpdate
    Parent::unpackUpdate(conn, stream);
}

U32 Marble::filterMaskBits(U32 mask, NetConnection* connection)
{
    // TODO: Implement filterMaskBits
    return Parent::filterMaskBits(mask, connection);
}

void Marble::writePacketData(GameConnection* conn, BitStream* stream)
{
    // TODO: Implement writePacketData
    Parent::writePacketData(conn, stream);
}

void Marble::readPacketData(GameConnection* conn, BitStream* stream)
{
    // TODO: Implement readPacketData
    Parent::readPacketData(conn, stream);
}

void Marble::renderShadowVolumes(SceneState*)
{
    // TODO: Implement renderShadowVolumes
}

void Marble::renderShadow(F32, F32)
{
    // TODO: Implement renderShadow
}

void Marble::renderImage(SceneState* state)
{
    // TODO: Implement renderImage
    Parent::renderImage(state);
}

void Marble::bounceEmitter(F32, const Point3F&)
{
    // TODO: Implement bounceEmitter
}

MatrixF Marble::getShadowTransform() const
{
    // TODO: Missing ShapeBase::getShadowTransform. Appears to be an unused function?
    //return Parent::getShadowTransform();

    // TODO: Implement getShadowTransform
    return MatrixF();
}

void Marble::setVelocity(const Point3F& vel)
{
    // TODO: Implement setVelocity
    Parent::setVelocity(vel);
}

Point3F Marble::getVelocity() const
{
    // TODO: Implement getVelocity
    return Parent::getVelocity();
}

Point3F Marble::getShadowScale() const
{
    // TODO: Missing SceneObject::getShadowScale and ShapeBase::getShadowScale. Appears to be an unused function?

    // TODO: Implement getShadowScale
    return Point3F();
}

Point3F Marble::getGravityRenderDir()
{
    // TODO: Implement getGravityRenderDir
    return Point3F();
}

void Marble::getShadowLightVectorHack(Point3F& lightVec)
{
    // TODO: Missing SceneObject::getShadowLightVectorHack in parent. BlobShadow needs to be implemented.

    // TODO: Implement getShadowLightVectorHack
}

bool Marble::onSceneAdd(SceneGraph* graph)
{
    // TODO: Implement onSceneAdd
    return Parent::onSceneAdd(graph);
}

bool Marble::onNewDataBlock(GameBaseData* dptr)
{
    if (!Parent::onNewDataBlock(dptr))
        return false;

    this->mDataBlock = dynamic_cast<MarbleData*>(dptr);
    if (this->mDataBlock)
    {
        Marble::updatePowerUpParams();

        if (this->mDataBlock->shape)
        {
            updateMass();
            return true;
        }
    }

    return false;
}

void Marble::onRemove()
{
    removeFromScene();

    if (mRollHandle)
    {
        alxStop(mRollHandle);
        mRollHandle = NULL;
    }

    if (mSlipHandle)
    {
        alxStop(mSlipHandle);
        mSlipHandle = NULL;
    }

    if (mMegaHandle)
    {
        alxStop(mMegaHandle);
        mMegaHandle = NULL;
    }

    Parent::onRemove();
}

bool Marble::updatePadState()
{
    // TODO: Implement updatePadState
    return false;
}

void Marble::doPowerUpBoost(S32)
{
    // TODO: Implement doPowerUpBoost
}

void Marble::doPowerUpPower(S32)
{
    // TODO: Implement doPowerUpPower
}

void Marble::updatePowerups()
{
    // TODO: Implement updatePowerups
}

void Marble::updateMass()
{
    // TODO: Implement updateMass
    Parent::updateMass();
}

void Marble::trailEmitter(U32)
{
    // TODO: Implement trailEmitter
}

void Marble::updateRollSound(F32, F32)
{
    // TODO: Implement updateRollSound
}

void Marble::playBounceSound(Marble::Contact&, F64)
{
    // TODO: Implement playBounceSound
}

void Marble::setPad(SceneObject*)
{
    // TODO: Implement setPad
}

void Marble::findRenderPos(F32)
{
    // TODO: Implement findRenderPos
}

void Marble::advanceTime(F32 dt)
{
    // TODO: Implement advanceTime
    Parent::advanceTime(dt);
}

void Marble::computeNetSmooth(F32 backDelta)
{
    // TODO: GameBase::computeNetSmooth is missing. Need to implement hifi for this.

    // TODO: Implement computeNetSmooth
}

void Marble::doPowerUp(S32)
{
    // TODO: Implement doPowerUp
}

void Marble::prepShadows()
{
    // TODO: Implement prepShadows
}

bool Marble::onAdd()
{
    if (!Parent::onAdd())
        return false;

    if (mNetFlags.test(RestrictXYZMode))
    {
        mRollHandle = alxPlay(this->mDataBlock->sound[0], &getTransform(), &Point3F(0, 0, 0));
        mSlipHandle = alxPlay(this->mDataBlock->sound[3], &getTransform(), &Point3F(0, 0, 0));
        mMegaHandle = alxPlay(this->mDataBlock->sound[1], &getTransform(), &Point3F(0, 0, 0));

        this->mVertBuff.set(GFX, 33, GFXBufferTypeStatic);
        this->mPrimBuff.set(GFX, 33, 2, GFXBufferTypeStatic);
        prepShadows();
    }

    addToScene();

    return true;
}

void Marble::processMoveTriggers(const Move *)
{
    // TODO: Implement processMoveTriggers
}

void Marble::processItemsAndTriggers(const Point3F&, const Point3F&)
{
    // TODO: Implement processItemsAndTriggers
}

void Marble::setPowerUpId(U32, bool)
{
    // TODO: Implement setPowerUpId
}

void Marble::processTick(const Move* move)
{
    // TODO: Implement processTick
    Parent::processTick(move);
}

//----------------------------------------------------------------------------

ConsoleMethod(Marble, setPosition, void, 4, 4, "(transform, mouseY)")
{
    Point3F posf;
    AngAxisF angAxis;
    dSscanf(argv[2], "%f %f %f %f %f %f %f", &posf.x, &posf.y, &posf.z, &angAxis.axis.x, &angAxis.axis.y, &angAxis.axis.z, &angAxis.angle);

    object->setPosition(Point3D(posf.x, posf.y, posf.z), angAxis, dAtof(argv[3]));
}

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(MarbleData);

MarbleData::MarbleData()
{
    minVelocityBounceSoft = 2.5f;
    minVelocityBounceHard = 12.0f;
    bounceMinGain = 0.2f;
    minVelocityMegaBounceSoft = 2.5f;
    maxJumpTicks = 3;
    bounceEmitter = NULL;
    minVelocityMegaBounceHard = 8.0f;
    trailEmitter = NULL;
    mudEmitter = NULL;
    bounceMegaMinGain = 0.5f;
    grassEmitter = NULL;
    maxRollVelocity = 25.0f;
    angularAcceleration = 18.0f;
    brakingAcceleration = 8.0f;
    gravity = 20.0f;
    size = 1.0f;
    megaSize = 2.0f;
    staticFriction = 1.0f;
    kineticFriction = 0.89999998f;
    bounceKineticFriction = 0.2f;
    maxDotSlide = 0.1f;
    bounceRestitution = 0.89999998f;
    airAcceleration = 5.0f;
    energyRechargeRate = 1.0f;
    jumpImpulse = 1.0f;
    maxForceRadius = 1.0f;
    cameraDistance = 2.5f;
    minBounceVel = 0.1f;
    minTrailSpeed = 10.0f;
    minBounceSpeed = 1.0f;
    memset(sound, 0, sizeof(sound));
    genericShadowLevel = 0.40000001f;
    noShadowLevel = 0.0099999998f;
    blastRechargeTime = 1;
    maxNaturalBlastRecharge = 1;
    powerUps = NULL;
    mDecalData = NULL;
    mDecalID = 0;
    startModeTime = 320;
    stopModeTime = 32;
}

void MarbleData::initPersistFields()
{
    addField("maxRollVelocity", TypeF32, Offset(maxRollVelocity, MarbleData));
    addField("angularAcceleration", TypeF32, Offset(angularAcceleration, MarbleData));
    addField("brakingAcceleration", TypeF32, Offset(brakingAcceleration, MarbleData));
    addField("staticFriction", TypeF32, Offset(staticFriction, MarbleData));
    addField("kineticFriction", TypeF32, Offset(kineticFriction, MarbleData));
    addField("bounceKineticFriction", TypeF32, Offset(bounceKineticFriction, MarbleData));
    addField("gravity", TypeF32, Offset(gravity, MarbleData));
    addField("size", TypeF32, Offset(size, MarbleData));
    addField("megaSize", TypeF32, Offset(megaSize, MarbleData));
    addField("maxDotSlide", TypeF32, Offset(maxDotSlide, MarbleData));
    addField("bounceRestitution", TypeF32, Offset(bounceRestitution, MarbleData));
    addField("airAcceleration", TypeF32, Offset(airAcceleration, MarbleData));
    addField("energyRechargeRate", TypeF32, Offset(energyRechargeRate, MarbleData));
    addField("jumpImpulse", TypeF32, Offset(jumpImpulse, MarbleData));
    addField("maxForceRadius", TypeF32, Offset(maxForceRadius, MarbleData));
    addField("cameraDistance", TypeF32, Offset(cameraDistance, MarbleData));
    addField("minBounceVel", TypeF32, Offset(minBounceVel, MarbleData));
    addField("minTrailSpeed", TypeF32, Offset(minTrailSpeed, MarbleData));
    addField("minBounceSpeed", TypeF32, Offset(minBounceSpeed, MarbleData));
    addField("bounceEmitter", TypeParticleEmitterDataPtr, Offset(bounceEmitter, MarbleData));
    addField("trailEmitter", TypeParticleEmitterDataPtr, Offset(trailEmitter, MarbleData));
    addField("mudEmitter", TypeParticleEmitterDataPtr, Offset(mudEmitter, MarbleData));
    addField("grassEmitter", TypeParticleEmitterDataPtr, Offset(grassEmitter, MarbleData));
    addField("powerUps", TypeGameBaseDataPtr, Offset(powerUps, MarbleData));
    addField("blastRechargeTime", TypeS32, Offset(blastRechargeTime, MarbleData));
    addField("maxNaturalBlastRecharge", TypeS32, Offset(maxNaturalBlastRecharge, MarbleData));
    addField("RollHardSound", TypeAudioProfilePtr, Offset(sound[0], MarbleData));
    addField("RollMegaSound", TypeAudioProfilePtr, Offset(sound[1], MarbleData));
    addField("RollIceSound", TypeAudioProfilePtr, Offset(sound[2], MarbleData));
    addField("SlipSound", TypeAudioProfilePtr, Offset(sound[3], MarbleData));
    addField("Bounce1", TypeAudioProfilePtr, Offset(sound[4], MarbleData));
    addField("Bounce2", TypeAudioProfilePtr, Offset(sound[5], MarbleData));
    addField("Bounce3", TypeAudioProfilePtr, Offset(sound[6], MarbleData));
    addField("Bounce4", TypeAudioProfilePtr, Offset(sound[7], MarbleData));
    addField("MegaBounce1", TypeAudioProfilePtr, Offset(sound[8], MarbleData));
    addField("MegaBounce2", TypeAudioProfilePtr, Offset(sound[9], MarbleData));
    addField("MegaBounce3", TypeAudioProfilePtr, Offset(sound[10], MarbleData));
    addField("MegaBounce4", TypeAudioProfilePtr, Offset(sound[11], MarbleData));
    addField("JumpSound", TypeAudioProfilePtr, Offset(sound[12], MarbleData));
    Con::addVariable("Game::endPad", TypeS32, &Marble::smEndPadId);

    Parent::initPersistFields();
}

//----------------------------------------------------------------------------

bool MarbleData::preload(bool server, char errorBuffer[256])
{
    // TODO: Implement preload
    return Parent::preload(server, errorBuffer);
}

void MarbleData::packData(BitStream* stream)
{
    // TODO: Implement packData
    Parent::packData(stream);
}

void MarbleData::unpackData(BitStream* stream)
{
    // TODO: Implement unpackData
    Parent::unpackData(stream);
}

//----------------------------------------------------------------------------