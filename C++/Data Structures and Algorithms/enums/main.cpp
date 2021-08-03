#include <iostream>
#include <string.h>

class Token {
public:
  enum Category {
    kTypeKeyword, 
    kStart, 
    kIdentifier,
    kSemicolon,
    kNoMore
  };
  
  Token(Category k): kind(k){}
  
  Category getKind() {
    return kind;
  }
private:
  Category kind;
};

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Token token {Token::kSemicolon};  
  Token::Category kind {Token::kStart};

  if (token.getKind() != kind) {
    std::cout << "Not my kind\n";
  }

  return 0;
}




