#include "Program.hpp"

void Program::initData(){
    std::fstream file;
    file.open("data.txt", std::ios::in);
    if(!file.good()){
        printf("File data.txt was not found!\n");
        this->exitApp();
    }
    std::string line;
    while(getline(file,line)){
        std::vector<std::string> line_of_data;
        std::istringstream sentence(line);
        std::string word;
        while(getline(sentence,word,';'))
            line_of_data.push_back(word);
        this->data.push_back(line_of_data);
    }
    file.close();
}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WINDOW_POS_X/2,WINDOW_POS_Y/2));
    this->window->setFramerateLimit(FPS);
}

void Program::initShapes(){
    // this->test = new GradeTile(sf::Vector2f(122.f, 122.f),sf::Vector2f(122.f, 122.f));
    for(int i=0; i<this->data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            printf("%s     ",data[i][j].c_str());
            this->tiles.push_back(new GradeTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + i,10.f + TILE_SIZE.y * j + j)));
        }
        printf("\n");
    }
}

void Program::exitApp(){
    this->delShapes();
    delete this->window;
}

void Program::delShapes(){
    // for(int i=0; i<this->tiles.size(); i++){
    //     delete this->tiles[i];
    //     this->tiles.erase(this->tiles.begin() + i)
    // }
    while(!this->tiles.empty()){
        delete this->tiles.back();
        this->tiles.pop_back();
    }
}

Program::Program(){
    this->initData();
    this->initWindow();
    this->initShapes();
}

Program::~Program(){
    this->exitApp();
}

void Program::pollEvent(){
    while(this->window->pollEvent(this->currentEvent)){
        switch (this->currentEvent.type){
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->currentEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            for(Tile* t : this->tiles){
                // if(t.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window)))){
                    
                // }
                if(this->currentEvent.mouseButton.button == sf::Mouse::Left)
                    t->mouseLeftPressed(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Right)
                    t->mouseRightPressed(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle)
                    t->mouseMiddlePressed(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
            }
            break;
        default:
            break;
        }
    }
}

void Program::mouseHoverDetection(){
    for(Tile* t : this->tiles){
        if(t->getBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))))
            t->mouseHover(true);
        else
            t->mouseHover(false);
    }
}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    for(Tile* t : this->tiles)
        t->update();
}

void Program::render(){
    this->window->clear(sf::Color::White);

    for(Tile* t : this->tiles)
        t->render(this->window);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
