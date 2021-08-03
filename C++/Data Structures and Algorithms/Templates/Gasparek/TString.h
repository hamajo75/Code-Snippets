#ifndef TStringH
#define TStringH

// Uses 'TRealString' to hold the actual text in a dynamically allocated buffer.
// Reference counting is used in 'TRealString' to allow cheap copying and returning of strings from functions
// eg assignments using operator= simply increment the reference count

#include "RealString.h"

class PACKAGE TString {
  protected:
    // The actual text is held in this dynamically allocated & growable buffer
    TRealString *RealString;

    // CopyOnWrite (Cow) allows reference counting of text
    void Cow();
    void DestroyRealString();

    // Supports the word wrapping functions
    int WordWrapLength(int Start, int MaxLength) const;
    int WordWrapNext(int Start) const;

  public:
    TString();
    TString(const TString &String);
    TString(int Length, int FillChr);
    TString(const char *Text);
    TString(const char *Text, int Length);
    TString(int Amount);
    TString(double Amount);
    ~TString();

    TString& operator= (const TString &String);
    TString& operator= (const char *Text);
    TString& operator= (int Amount);
    TString& operator= (double Amount);

    unsigned int HashValue() const;
    void PreAllocate(int Length);

    // Returns the number of characters
    int Length() const { return RealString->FLength; }
    // Returns the number of characters
    bool IsBlank() const { return !RealString->FLength; }

    TString Right(int Length) const;
    TString Left(int Length) const;
    TString Mid(int Position, int Length) const;

    bool WordWrapPart(TString &String, int Part, int MaxLength, bool KeepLeadingSpace = false) const;
    int Words() const;
    TString Word(int WordNo) const;
    int WordPos(int WordNo) const;
    int AsciiWords(int Separator, bool IgnoreQuotes = false) const;
    TString AsciiWord(int WordNo, int Separator, bool IgnoreQuotes = false) const;

    int Find(int Char) const;
    int FindI(int Char) const;
    // Calls Find(Char) or FindI(Char) depending on 'IgnoreCase'
    int Find(int Char, bool IgnoreCase) const { return IgnoreCase ? FindI(Char) : Find(Char); }
    int Find(const char *String) const;
    int FindI(const char *String) const;
    // Calls Find(String) or FindI(String) depending on 'IgnoreCase'
    int Find(const char *String, bool IgnoreCase) const { return IgnoreCase ? FindI(String) : Find(String); }
    int Count(int Char) const;

    void ToUpper();
    void ToUpperFirstChrs();
    void ToLower();

    // Returns integer value of numeric string
    int ToInt();

    // Calls IsBlank()
    bool operator! () const { return IsBlank(); }
    // Returns a pointer to the text in 'TRealString'
    const char *Text(int Char = 0) const { return RealString->FArray + Char; }
    // Returns a pointer to the text in 'TRealString'
    const char *operator() () const { return RealString->FArray; }
    // Casting operator - returns a pointer to the text in 'TRealString'
    // This enables a string to be used where ever a 'const char *' is required
    operator const char*() const { return RealString->FArray; }
    char operator[] (int Position) const;
    char &operator() (int Position);

    TString& operator++ ();  

    TString operator+ (const char *Text) const;
    // Appends 'Text' to this string
    void operator+= (const char *Text) { Insert(Text, Length()); }
    void operator+= (int Char);

    void Insert(const char *Text, int Length, int Position);
    // Inserts 'Text' into this string at 'Position'
    void Insert(const char *Text, int Position = 0) { Insert(Text, strlen(Text), Position); }
    // Inserts 'byte' (a single character eg 'X') into this string at 'Position'
	void Insert(int byte, int Position = 0) {
		byte &= 0xFF;
		Insert((const char *) &byte, Position);
	}
    // Inserts 'String' into this string at 'Position'
    void Insert(const TString &String, int Position) { Insert(String(), String.Length(), Position); }

    void Replace(const char *Text, int Length, int Position);
    // Replaces existing characters in this string with 'Text' at 'Position'
    void Replace(const char *Text, int Position) { Replace(Text, strlen(Text), Position); }
    // Replaces existing characters in this string with 'String' at 'Position'
    void Replace(const TString &String, int Position) { Replace(String(), String.Length(), Position); }
    // Replaces all old characters with a new one
    void Replace(char Old, char New);

    // Replaces existing characters in this string with 'Text' at 'Position'
    void Overtype(const char *Text, int Position) { Replace(Text, Position); }

    void Exchange(TString *String);

    int __cdecl sprintf(const char *Format,...);

    void Remove(int Position, int Length);
    void LimitLength(int MaxLength);
    void Remove(char Char);
    void Remove(const char *AnyChar);
    void Keep(const char *ValidChars);
    void RTrim();
    void LTrim();
    // Trims spaces from left and right ends              reverse
    void RLTrim() { RTrim(); LTrim(); }
    void RJust(int ToLength);
    void Centre(int LineWidth);
    void IntegerOnly();

    int Compare(const TString &String, bool IgnoreCase = true) const;
    bool Equals(const TString &String, bool IgnoreCase = true) const;

    bool operator== (const TString &String) const { return strcmp(RealString->FArray, String) == 0; }
    bool operator== (const char *Text) const { return strcmp(RealString->FArray, Text) == 0; }
    bool operator!= (const TString &String) const { return strcmp(RealString->FArray, String) != 0; }
    bool operator!= (const char *Text) const { return strcmp(RealString->FArray, Text) != 0; }
    bool operator> (const TString &String) const { return strcmp(RealString->FArray, String) > 0; }
    bool operator> (const char *Text) const { return strcmp(RealString->FArray, Text) > 0; }
    bool operator< (const TString &String) const { return strcmp(RealString->FArray, String) < 0; }
    bool operator< (const char *Text) const { return strcmp(RealString->FArray, Text) < 0; }
    bool operator>= (const TString &String) const { return strcmp(RealString->FArray, String) >= 0; }
    bool operator>= (const char *Text) const { return strcmp(RealString->FArray, Text) >= 0; }
    bool operator<= (const TString &String) const { return strcmp(RealString->FArray, String) <= 0; }
    bool operator<= (const char *Text) const { return strcmp(RealString->FArray, Text) <= 0; }

    //void Read(TFile *File, char Delimiter = 0, bool EatLineEnds = false, bool StopAtCtrlZ = true);
    //void Write(TFile *File) const;
    //void Write(TFile *File, const char *LineEnd, int LineEndLength) const;
};

extern TString PACKAGE BlankString;

#endif

