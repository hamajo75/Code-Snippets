//---------------------------------------------------------------------------
#ifndef RealStringH
#define RealStringH

//---------------------------------------------------------------------------
// This class is ONLY used with the TString class & must never be used on its own.
// It is the holder of the text used in TString.
// It uses reference counting to allow cheap copying & assigning of strings.
// All members are private and only TString is a friend.
class PACKAGE TRealString {
  friend class TString;

  enum {
    szHysteresis = 4
  };

  private:
    TArrayPtr<char> FArray;
    int FLength;
    int FArrayLength;
    int FReferenceCount;

    // Calculates blocks of 8 bytes & allows for terminating zero
    // Used to determine FArrayLength
    static int BlockLength(int Length) { return (Length + 8) & 0xFFFFFFF8; }

    TRealString();
    TRealString(const TRealString &RealString);
    TRealString(const char *Text, int Length);
    TRealString(int Length, int FillChr);
    ~TRealString();

    TRealString& operator= (const TRealString &String);

    void Create(const char *Text, int Length);
    void PreAllocate(int Length);
    void AppendCharacter(int Character);
    void Insert(const char *Text, int Length, int Position);
    void Replace(const char *Text, int Length, int Position);
    void Remove(int Position, int Length);
};

#endif
