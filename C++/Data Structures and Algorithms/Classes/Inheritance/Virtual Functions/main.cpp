#include <string.h>

#include <iostream>
#include <memory>

// Hint: for Polymorphism without inheritance see: Design Patterns/Composite/std_variant

class Entity {
 public:
  float X = 0;
  float Y = 0;

  Entity() { std::cout << "Entity constructor\n"; }

  virtual std::string GetName() const { return "Entitiy::GetName: Entity\n"; }

  virtual void public_fun() { std::cout << "Entity::public_fun\n"; }

 protected:
  virtual void protected_fun() { std::cout << "Entity::protected_fun\n"; }
};
//-------------------------------------------------------------------------------
class Player : public Entity {
 private:
  std::string name_;
  virtual void public_fun() { std::cout << "Player::public_fun\n"; }

 public:
  explicit Player(const std::string &name) : name_(name) {
    std::cout << "Player constructor\n";
    this->GetName();  // this doesn't do anything: C++ doesn't allow you to call
                      // the overridden method before the object is constructed
                      // yet.
    std::cout << "Player constructor leaving \n";
  }

  virtual void protected_fun() { std::cout << "Player::protected_fun\n"; }

  std::string GetName() const override {
    return "Player::GetName: " + name_ + "\n";
  }  // good style to use the override keyword
};

//-------------------------------------------------------------------------------
void PrintName(Entity *e) {
  std::cout << "PrintName(Entity *e): " << e->GetName();
}
//-------------------------------------------------------------------------------
void PrintNameByReference(const Entity& e) {
  std::cout << "PrintNameByReference(const Entity& e): " << e.GetName();
}
//-------------------------------------------------------------------------------
void PrintName(Entity e) { std::cout << "PrintName(Entity e): " << e.GetName(); }
//-------------------------------------------------------------------------------
void PrintName(std::shared_ptr<Entity> e) {
  std::cout << "PrintName(std::shared_ptr<Entity> e): " << e->GetName();
}
//-------------------------------------------------------------------------------
int main(int argc, const char *argv[]) {
  auto e = std::make_unique<Entity>();
  std::cout << e->GetName();                         // base class

  auto p = std::make_shared<Player>("Joe");
  std::cout << p->GetName();                         // derived class: overridden

  std::shared_ptr<Entity> e2 = p;
  std::cout << e2->GetName();               // polymorphically prints Player name through pointer to an Entity object
  PrintName(p);

  Player p2("Sepp");
  PrintName(p2);                            // without ptr or reference no polymorphism
  PrintNameByReference(p2);                            // with a reference polymorphism works
  PrintName(&p2);                           // with a pointer polymorphism works of course

  Entity e3;
  PrintName(e3);

  // Entity e4();
  // PrintName(e4);   // NOT working: the above actually
  // declares a function (most vexing parse - problem)

  Entity* entity_ptr = &p2;
  entity_ptr->public_fun();             // can be called although private in Player!
  // entity_ptr->protected_fun();       // you cannot make it public when it was protected (when going through Entity)!
  Player* player_ptr = &p2;
  player_ptr->protected_fun();          // but you can make the overridden function public (when going through Player)
  p2.protected_fun();

  return 0;
}
