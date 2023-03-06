#include "EmptyTile.hpp"

EmptyTile::EmptyTile(const sf::Vector2f& size,const sf::Vector2f& position) : Tile(size, position){
    this->tileType = 3;
    // this->mainShape.setFillColor(sf::Color(200,200,200));
}
EmptyTile::~EmptyTile(){
    
}

void EmptyTile::mouseLeftPressed(){
    //none
}
void EmptyTile::mouseRightPressed(){
    // none
}
void EmptyTile::mouseMiddlePressed(){
    // none
}
void EmptyTile::mouseWheelMovedUp(){
    // none
}
void EmptyTile::mouseWheelMovedDown(){
    // none
}
void EmptyTile::keyboardKeys(const sf::Keyboard::Key&){
    // none
}

void EmptyTile::update(){
    
}
void EmptyTile::render(sf::RenderTarget* window){
    // window->draw(this->mainShape);
    // none
}

std::string EmptyTile::getData() const{
    return "-";
}
void EmptyTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    // none
}