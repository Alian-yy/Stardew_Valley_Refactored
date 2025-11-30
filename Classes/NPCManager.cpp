// NPCManager.cpp
#include "NPCManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

NPCManager::NPCManager(Layer* parent, std::function<Vec2()> getPlayerPos,
                       std::function<void(const std::string&, const Vec2&, float)> showDialogCallback)
    : _parent(parent), _getPlayerPos(getPlayerPos), _showDialogCallback(showDialogCallback)
{

}

NPCManager::~NPCManager()
{
    clear();
}

void NPCManager::spawnNPC(const NPCSpec& spec)
{
    if (!_parent) return;

    using namespace ui;
    auto btn = Button::create(spec.normalTexture, spec.selectedTexture);
    btn->setPosition(spec.position);
    btn->setScale(spec.scale);
    _parent->addChild(btn, 5);

    // touch handler captures spec by value
    btn->addTouchEventListener([this, spec, btn](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            Vec2 npcPos = btn->getPosition();
            Vec2 playerPos = Vec2::ZERO;
            if (_getPlayerPos) playerPos = _getPlayerPos();

            // 使用2D距离计算，而不是只计算x坐标
            float distance = playerPos.distance(npcPos);
            if (distance < spec.proximityThreshold) {
                btn->loadTextureNormal(spec.selectedTexture);
                // use callback to show dialog (UIManager provided by outside)
                if (_showDialogCallback) {
                    _showDialogCallback(spec.dialogTexture, spec.dialogPosition, 3.0f);
                }
                // restore texture after duration
                auto seq = Sequence::create(DelayTime::create(3.0f), CallFunc::create([btn, spec]() {
                    btn->loadTextureNormal(spec.normalTexture);
                }), nullptr);
                btn->runAction(seq);
            }
        }
    });

    _buttons.push_back(btn);
}

void NPCManager::clear()
{
    for (auto b : _buttons) {
        if (b && _parent) {
            b->removeFromParent();
        }
    }
    _buttons.clear();
}
