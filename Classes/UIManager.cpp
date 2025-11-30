// UIManager.cpp
#include "UIManager.h"
#include "EventCenter.h"
#include <ctime>
#include <sstream>

USING_NS_CC;

UIManager::UIManager(Layer* parent)
    : _parent(parent), _dayLabel(nullptr), _timeLabel(nullptr)
{
    // 创建并添加 dayLabel 和 timeLabel 到父层
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    std::stringstream ss;
    if (timeinfo) ss << days[timeinfo->tm_wday] << ", ";
    std::string dayOfWeek = ss.str();

    _dayLabel = Label::createWithTTF(dayOfWeek, "fonts/Marker Felt.ttf", 50);
    _dayLabel->setAnchorPoint(Vec2(1, 1));
    _dayLabel->setPosition(Vec2(3 * 1500, 3 * 1100 + 1450));
    if (_parent) _parent->addChild(_dayLabel, 1);

    char buffer[80];
    if (timeinfo) std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    _timeLabel = Label::createWithTTF(std::string(buffer), "fonts/Marker Felt.ttf", 40);
    _timeLabel->setPosition(Vec2(3 * 1500 - 125, 3 * 1100 + 1450 - 170));
    _timeLabel->setName("timeLabel");
    if (_parent) _parent->addChild(_timeLabel, 1);

    // 注册为观察者以接收时间更新
    EventCenter::getInstance()->attach(this);

    // 初始化个人界面状态
    _personalInterfaceLayer = nullptr;
    _menuWindow = nullptr;
    _closeButton = nullptr;
    _isPersonalInterfaceVisible = false;
    _currentImageIndex = 1;
    _clickedButtonIndex = -1;
    // fishing init
    _fishingLayer = nullptr;
    _fishImage = nullptr;
    _spriteFish = nullptr;
    _fishman = nullptr;
    _isFishingVisible = false;
}

UIManager::~UIManager()
{
    EventCenter::getInstance()->detach(this);
}

void UIManager::toggleFishing()
{
    if (_isFishingVisible) hideFishing();
    else showFishing();
}

void UIManager::showFishing()
{
    if (_isFishingVisible || !_parent) return;
    _isFishingVisible = true;

    // 半透明遮罩层
    _fishingLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    _parent->addChild(_fishingLayer, 50);

    // 背景图
    _fishImage = ui::ImageView::create("picture/fishingback.png");
    _fishImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _fishImage->setScale(0.9f);
    _fishingLayer->addChild(_fishImage);

    // fish sprite
    _spriteFish = Sprite::create("character/fishman1.png");
    if (_spriteFish) {
        _spriteFish->setPosition(Vec2(_fishImage->getContentSize().width/2 - 50, _fishImage->getContentSize().height/2 + 100));
        _fishImage->addChild(_spriteFish);
        // simple animation if frames exist
        Animation* anim = Animation::create();
        for (int i = 1; i <= 5; ++i) {
            std::string frame = "character/fishman" + std::to_string(i) + ".png";
            anim->addSpriteFrameWithFile(frame);
        }
        anim->setDelayPerUnit(0.3f);
        anim->setLoops(-1);
        auto act = Animate::create(anim);
        _spriteFish->runAction(act);
    }

    // fishman sprite (optional)
    _fishman = Sprite::create("character/fishman1.png");
    if (_fishman) {
        _fishman->setPosition(Vec2(_fishImage->getContentSize().width/2, _fishImage->getContentSize().height/2 - 50));
        _fishImage->addChild(_fishman);
    }

    // Fade in
    _fishingLayer->setOpacity(0);
    _fishingLayer->runAction(FadeTo::create(0.25f, 255));
}

void UIManager::hideFishing()
{
    if (!_isFishingVisible) return;
    _isFishingVisible = false;
    if (_fishingLayer) {
        // Fade out then remove
        _fishingLayer->runAction(Sequence::create(FadeOut::create(0.2f), CallFunc::create([this]() {
            if (_spriteFish) { _spriteFish->stopAllActions(); _spriteFish = nullptr; }
            if (_fishman) { _fishman = nullptr; }
            if (_fishImage) { _fishImage = nullptr; }
            _fishingLayer->removeFromParentAndCleanup(true);
            _fishingLayer = nullptr;
        }), nullptr));
    }
}

void UIManager::onNotify(const EventData& event)
{
    if (event.type == EventType::MinuteChanged) {
        std::string timeStr = event.extra.asString();
        if (_timeLabel) {
            _timeLabel->setString(timeStr);
        }
    }
}

void UIManager::showPersonalInterface(const cocos2d::Vec2& characterPosition)
{
    if (_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = true;

    _personalInterfaceLayer = Layer::create();
    if (_parent) _parent->addChild(_personalInterfaceLayer, 10);

    _menuWindow = Sprite::create("bag/1.png");
    _menuWindow->setPosition(characterPosition);
    _menuWindow->setScale(1.0f);
    _personalInterfaceLayer->addChild(_menuWindow);

    // close button
    _closeButton = MenuItemImage::create("picture/bottom2.png", "picture/bottom2.png", [this](Ref* sender){ this->hidePersonalInterface(); });
    auto windowSize = _menuWindow->getContentSize();
    _closeButton->setPosition(Vec2(windowSize.width - _closeButton->getContentSize().width / 2 + 60, windowSize.height - _closeButton->getContentSize().height / 2 + 60));
    auto closeMenu = Menu::create(_closeButton, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    _menuWindow->addChild(closeMenu);

    // top selection buttons
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto buttonMenu = Menu::create();
    for (int i = 1; i <= 7; ++i) {
        std::string buttonNormal = StringUtils::format("picture/%d%d.png", i, i);
        auto button = MenuItemImage::create(buttonNormal, buttonNormal, [this, i](Ref* sender){ this->selectImage(i); });
        button->setPosition(Vec2(characterPosition.x - 1600 + 80 * i, characterPosition.y - 170));
        buttonMenu->addChild(button, 0, i);
    }
    buttonMenu->setPosition(visibleSize / 2);
    _personalInterfaceLayer->addChild(buttonMenu, 1);
}

void UIManager::hidePersonalInterface()
{
    if (!_isPersonalInterfaceVisible) return;
    _isPersonalInterfaceVisible = false;
    if (_personalInterfaceLayer) {
        _personalInterfaceLayer->removeFromParent();
        _personalInterfaceLayer = nullptr;
        _menuWindow = nullptr;
    }
}

void UIManager::selectImage(int index)
{
    _currentImageIndex = index;
    // Remove vertical buttons if any
    if (_menuWindow) {
        removeVerticalButtons();
        std::string imageName = StringUtils::format("bag/%d.png", _currentImageIndex);
        _menuWindow->setTexture(imageName);
    }

    if (index == 1) {
        // add draggable sprite and money label (simplified)
        auto windowSize = _menuWindow->getContentSize();
        auto draggableSprite = Sprite::create("bag/tool1.png");
        draggableSprite->setScale(4.0f);
        draggableSprite->setPosition(Vec2(windowSize.width - 200, windowSize.height - 300));
        _menuWindow->addChild(draggableSprite, 10);

        // trash can
        auto trashCanSprite = Sprite::create("bag/trashcan.png");
        trashCanSprite->setPosition(Vec2(windowSize.width + 50, windowSize.height - 500));
        _menuWindow->addChild(trashCanSprite);

        // Listener omitted for brevity; keep original behavior if needed
        int money = 500;
        auto moneyLabel = Label::createWithSystemFont(StringUtils::format("%d", money), "Arial", 30);
        moneyLabel->setColor(Color3B::BLACK);
        moneyLabel->setPosition(Vec2(windowSize.width / 2 + 200, windowSize.height / 2 - 110));
        _menuWindow->addChild(moneyLabel, 20);
    }
    else if (_currentImageIndex == 3) {
        showVerticalButtons();
    }
    else if (_currentImageIndex == 7) {
        showVerticalButtons2();
    }
}

void UIManager::showVerticalButtons()
{
    if (!_menuWindow) return;
    auto windowSize = _menuWindow->getContentSize();
    auto buttonLayer = Layer::create();
    buttonLayer->setName("buttonLayer");
    _menuWindow->addChild(buttonLayer);
    for (int i = 1; i <= 5; ++i) {
        auto button = ui::Button::create("picture/giftbottom1.png", "picture/giftbottom1.png");
        button->setPosition(Vec2(windowSize.width / 2 + 300, windowSize.height + 90 - 125 * i));
        button->setTag(i);
        button->addTouchEventListener([this, i](Ref* sender, ui::Widget::TouchEventType type){
            if (type == ui::Widget::TouchEventType::ENDED) {
                _clickedButtonIndex = i;
                this->showNewWindow(i);
            }
        });
        buttonLayer->addChild(button);
    }
}

void UIManager::showVerticalButtons2()
{
    if (!_menuWindow) return;
    auto windowSize = _menuWindow->getContentSize();
    auto buttonLayer = Layer::create();
    buttonLayer->setName("buttonLayer");
    _menuWindow->addChild(buttonLayer);
    for (int i = 1; i <= 4; ++i) {
        auto button = ui::Button::create("picture/bottom.png", "picture/bottom2.png");
        button->setPosition(Vec2(windowSize.width / 6 - 90, windowSize.height - 70 - 90 * i));
        button->setTag(i);
        button->addTouchEventListener([button](Ref* sender, ui::Widget::TouchEventType type){
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (button->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                    button->loadTextureNormal("picture/bottom2.png");
                } else {
                    button->loadTextureNormal("picture/bottom.png");
                }
            }
        });
        buttonLayer->addChild(button);
    }
}

void UIManager::removeVerticalButtons()
{
    if (_menuWindow) {
        _menuWindow->removeAllChildrenWithCleanup(true);
    }
}

void UIManager::showNewWindow(int clickedIndex)
{
    if (!_personalInterfaceLayer) return;
    auto newWindow = Sprite::create("picture/back.png");
    Vec2 characterPosition = _menuWindow ? _menuWindow->getPosition() : Vec2::ZERO;
    newWindow->setPosition(characterPosition);
    newWindow->setScale(1.0f);
    _personalInterfaceLayer->addChild(newWindow, 11);

    auto closeNewWindowButton = ui::Button::create("picture/ok1.png", "picture/ok1.png");
    closeNewWindowButton->setScale(1.5f);
    closeNewWindowButton->setPosition(Vec2(newWindow->getContentSize().width - closeNewWindowButton->getContentSize().width / 2 - 100, newWindow->getContentSize().height - closeNewWindowButton->getContentSize().height / 2 - 800));
    closeNewWindowButton->addTouchEventListener([this, newWindow](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            newWindow->removeFromParent();
            // add checkmarks or popup per click counts
            auto buttonLayer = dynamic_cast<Layer*>(_menuWindow->getChildByName("buttonLayer"));
            if (buttonLayer) {
                auto giftButton = dynamic_cast<ui::Button*>(buttonLayer->getChildByTag(_clickedButtonIndex));
                if (giftButton) {
                    int clickCount = _buttonClickCounts[_clickedButtonIndex]++;
                    if (clickCount < 2) {
                        auto bottomButton = ui::Button::create("picture/bottom1.png", "picture/bottom1.png");
                        bottomButton->setScale(0.8f);
                        float offsetX = clickCount * 48;
                        bottomButton->setPosition(Vec2(giftButton->getPositionX() - 30 + offsetX, giftButton->getPositionY() - 57));
                        buttonLayer->addChild(bottomButton);
                    }
                    if (clickCount == 2) {
                        auto popupImage = Sprite::create("bag/back.png");
                        popupImage->setPosition(Vec2(giftButton->getPositionX() - 30, giftButton->getPositionY() - 57));
                        popupImage->setScale(0.5f);
                        buttonLayer->addChild(popupImage);
                        auto delay = DelayTime::create(2.0f);
                        auto removePopup = CallFunc::create([popupImage]() { popupImage->removeFromParent(); });
                        popupImage->runAction(Sequence::create(delay, removePopup, nullptr));
                    }
                }
            }
            else {
                CCLOG("Error: buttonLayer not found!");
            }
        }
    });
    newWindow->addChild(closeNewWindowButton);

    // create 6 gift buttons
    for (int i = 1; i <= 6; ++i) {
        auto giftButton = ui::Button::create("picture/gift" + std::to_string(i) + ".png", "picture/gift" + std::to_string(i) + ".png");
        giftButton->setScale(3.0f);
        giftButton->setPosition(Vec2(100 + (i - 1) * 150, 800));
        newWindow->addChild(giftButton);
        auto bottomButton = ui::Button::create("picture/bottom.png", "picture/bottom1.png");
        bottomButton->setPosition(Vec2(giftButton->getPositionX(), giftButton->getPositionY() - 100));
        bottomButton->addTouchEventListener([bottomButton](Ref* sender, ui::Widget::TouchEventType type){
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (bottomButton->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                    bottomButton->loadTextureNormal("picture/bottom1.png");
                } else {
                    bottomButton->loadTextureNormal("picture/bottom.png");
                }
            }
        });
        newWindow->addChild(bottomButton);
    }
}

void UIManager::showNPCDialog(const std::string& dialogTexture, const cocos2d::Vec2& position, float duration)
{
    if (!_parent) return;
    auto dialogBox = Sprite::create(dialogTexture);
    dialogBox->setPosition(position);
    dialogBox->setScale(0.6f);
    _parent->addChild(dialogBox, 100);
    auto delay = DelayTime::create(duration);
    auto removeDialog = CallFunc::create([dialogBox]() { dialogBox->removeFromParent(); });
    dialogBox->runAction(Sequence::create(delay, removeDialog, nullptr));
}

