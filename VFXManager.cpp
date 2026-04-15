#include "VFXManager.h"
#include "Time.h"
#include "TextureManager.h"

VFXManager* VFXManager::instance = nullptr;

VFXManager::~VFXManager()
{
    SDL_Log("VFXManager dtor");
    delete instancePool;
}

VFXManager* VFXManager::Initialise()
{
    VFXManager* instance = GetInstance();
    instance->instancePool = new std::vector<VFXInstance>();
    instance->instancePool->reserve(1000);
    return instance;
}

void VFXManager::SetCamera(Camera* camera)
{
    GetInstance()->camera = camera;
}

void VFXManager::Update()
{
    VFXManager* instance = GetInstance();
    bool needsCullObjs = false;

    for (VFXInstance& vfxInst : *instance->instancePool)
    {
        if (!vfxInst.enabled)
            continue;

        VFXTexData texData = vfxInst.texData;

        vfxInst.timeLeft -= Time::deltaTime;
        vfxInst.timer += Time::deltaTime;

        int targetFrameIdx = (texData.rows * texData.cols);

        if (vfxInst.timer >= 1.0f / vfxInst.fps)
        {
            vfxInst.frameIdx++;
            vfxInst.timer = Time::deltaTime;

            if (vfxInst.loop && vfxInst.frameIdx >= targetFrameIdx)
                vfxInst.frameIdx = 0;
        }

        if ((vfxInst.loop && vfxInst.timeLeft <= 0) || vfxInst.frameIdx > targetFrameIdx)
        {
            vfxInst.enabled = false;
            vfxInst.frameIdx = 0;
            vfxInst.timeLeft = 0;
            needsCullObjs = true;
        }
    }

    if (!needsCullObjs)
        return;

    std::vector<VFXInstance> tmpObjs;

    for (VFXInstance& vfxInst : *instance->instancePool)
    {
        if (vfxInst.enabled)
            tmpObjs.push_back(vfxInst);
    }

    std::swap(tmpObjs, *instance->instancePool);
}

void VFXManager::Render(SDL_Renderer* renderer)
{
    VFXManager* instance = GetInstance();

    for (VFXInstance& vfxInst : *instance->instancePool)
    {
        if (!vfxInst.enabled)
            continue;

        VFXTexData texData = vfxInst.texData;

        int x = vfxInst.frameIdx % texData.cols;
        int y = vfxInst.frameIdx / texData.cols;

        SDL_Rect rctSrc{ x * texData.frameSizeX, y * texData.frameSizeY, texData.frameSizeX, texData.frameSizeY };
        SDL_FRect rctDst{ vfxInst.position.x, vfxInst.position.y, (float)texData.frameSizeX, (float)texData.frameSizeY };

        if (instance->camera != nullptr)
        {
            rctDst = instance->camera->CalculateBounds(rctDst);
            rctDst.x -= rctDst.w / 2;
            rctDst.y -= rctDst.h / 2;
        }

        SDL_RenderCopyExF(renderer, texData.tex->GetSDLTexture(), &rctSrc, &rctDst, vfxInst.angleDegrees, NULL, SDL_FLIP_NONE);
    }
}

void VFXManager::LoadEffect(Texture* tex, const std::string& effectKey, int cols, int rows, const Vector2& frameSize)
{
    VFXManager* instance = GetInstance();

    VFXTexData texData;
    texData.tex = tex;
    texData.cols = cols;
    texData.rows = rows;
    texData.frameSizeX = frameSize.x;
    texData.frameSizeY = frameSize.y;

    instance->effectTexMap[effectKey] = texData;
}

void VFXManager::SpawnEffect(const Vector2& position, const std::string& key, float fps, float angle, bool loop, float timeLeft)
{
    VFXManager* instance = GetInstance();

    if (instance->effectTexMap.find(key) == instance->effectTexMap.end())
        return;

    VFXTexData texData = instance->effectTexMap[key];
    Texture* tex = texData.tex;

    if (tex == nullptr)
        return;

    VFXInstance vfxInst;
    vfxInst.angleDegrees = angle;
    vfxInst.loop = loop;
    vfxInst.enabled = true;
    vfxInst.position = position;
    vfxInst.timeLeft = timeLeft;
    vfxInst.timer = 0.0f;
    vfxInst.fps = fps;

    vfxInst.frameIdx = 0;
    vfxInst.texData = texData;

    instance->instancePool->push_back(vfxInst);
}

VFXManager* VFXManager::GetInstance()
{
    if(instance == nullptr)
        instance = new VFXManager();

    return instance;
}
