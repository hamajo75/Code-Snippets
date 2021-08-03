#include <boost/signals2.hpp>
#include <iostream>
#include <string>

//using namespace boost;

//-----------------------------------------------------------------------------
struct EventData {
  virtual void print() const = 0;
};
//-----------------------------------------------------------------------------
struct PlayerScoredData : EventData {
  std::string player_name;
  int goals_scored_so_far;

  PlayerScoredData(const std::string name,
    int goals_scored_so_far)
      : player_name{name},
        goals_scored_so_far{goals_scored_so_far} {}

  void print() const override {
    std::cout << player_name << "has scored!\n";
  }
};
//-----------------------------------------------------------------------------
// this is the mediator
struct Game {
  boost::signals2::signal<void(EventData*)> events;
};
//-----------------------------------------------------------------------------
struct Player {
  std::string name;
  int goals_scored = 0;
  Game& game;

  Player(const std::string& name, Game& game)
    : name{name}, game{game} {}

  void score() {
    goals_scored++;
    PlayerScoredData ps{name, goals_scored};
    game.events(&ps);
 }
};
//-----------------------------------------------------------------------------
struct Coach {
  Game& game;
  Coach(Game& game) : game(game) {
    game.events.connect([](EventData* e) {
      PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
      if (ps && ps->goals_scored_so_far < 3) {
        std::cout << "coach says: well done " << ps->player_name << "!\n";
      }
    });
  }
};
//-----------------------------------------------------------------------------
int main() {
  Game game;
  Player player{"Sam", game};
  Coach coach{game};

  player.score();
  player.score();
  player.score();

  return 0;
}
