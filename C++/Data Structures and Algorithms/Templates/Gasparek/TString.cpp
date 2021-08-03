#include "CommonLib.h"
#pragma hdrstop

#include "except.h"
#include "TString.h"

#pragma package(smart_init)

TString BlankString;

//---------------------------------------------------------------------------
// Default constructor
TString::TString()
{
  RealString = new TRealString;
}

//---------------------------------------------------------------------------
// Copy constructor.
// Cheap operation which simply increments the reference count of String's RealString member
TString::TString(const TString &String)
{
  RealString = String.RealString;
  RealString->FReferenceCount++;
}

//---------------------------------------------------------------------------
// Constructs a string 'Length' long of 'FillChr' characters.
// eg TString(9, 'X') would create "XXXXXXXXX"
TString::TString(int Length, int FillChr)
{
  RealString = new TRealString(Length, FillChr);
}

//---------------------------------------------------------------------------
// Constructs a copy of 'Text'.
// Allocates memory & copies 'Text'
TString::TString(const char *Text)
{
  RealString = new TRealString(Text, strlen(Text));
}

//---------------------------------------------------------------------------
// Constructs a copy of 'Text' restricted to 'Length'
// Allocates memory & copies 'Text'
TString::TString(const char *Text, int Length)
{
  RealString = new TRealString(Text, _min(Length, (int)strlen(Text)));
}

//---------------------------------------------------------------------------
// Constructs from 'Amount' eg "453"
TString::TString(int Amount)
{
  char Temp[32];
  ltoa(Amount, Temp, 10);

  RealString = new TRealString(Temp, strlen(Temp));
}

//---------------------------------------------------------------------------
// Constructs from 'Amount' using %4.2f eg "694.24"
TString::TString(double Amount)
{
  char Temp[64];
  int TempLength = ::sprintf(Temp, "%4.2f", Amount);

  RealString = new TRealString(Temp, TempLength);
}

//---------------------------------------------------------------------------
// Decrements the reference count & if it becomes zero, deallocates memory
TString::~TString()
{
  DestroyRealString();
}

//---------------------------------------------------------------------------
void TString::Cow()
{
  if(RealString->FReferenceCount > 1) {
    TRealString *OrigString = RealString;
    RealString = new TRealString(*RealString);
    OrigString->FReferenceCount--;
  }
}

//---------------------------------------------------------------------------
void TString::DestroyRealString()
{
  // This MUST test 'if(RealString)' due to its use in constructors above where 'RealString' is NULL
  if(RealString){
    if(RealString->FReferenceCount > 1)
      RealString->FReferenceCount--;
    else
      delete RealString;
    RealString = NULL;
  }
}

//---------------------------------------------------------------------------
// Cheap operation which simply increments the reference count of 'String's RealString member
TString& TString::operator= (const TString &String)
{
  DestroyRealString();
  RealString = String.RealString;
  RealString->FReferenceCount++;
  return *this;
}

//---------------------------------------------------------------------------
// Creates a copy of 'Text'
TString& TString::operator= (const char *Text)
{
  return (*this) = TString(Text);
}

//---------------------------------------------------------------------------
// Assigns from 'Amount' eg "453"
TString& TString::operator= (int Amount)
{
  return (*this) = TString(Amount);
}

//---------------------------------------------------------------------------
// Assigns from 'Amount' eg "694.24"
TString& TString::operator= (double Amount)
{
  return (*this) = TString(Amount);
}

//---------------------------------------------------------------------------
// Used by hash table container
unsigned int TString::HashValue() const
{
  unsigned int Val = 0;
  for(const unsigned char *p = (const unsigned char *) (const char *) RealString->FArray; *p; p++)
    Val += *p;
  return Val;
}

//---------------------------------------------------------------------------
// Allocate a RealString of 'Length' from memory for copying into later
// 'Length' does NOT include the terminating \0
void TString::PreAllocate(int Length)
{
  Cow();
  RealString->PreAllocate(Length);
}

//---------------------------------------------------------------------------
// Returns the index of 'Char' or -1 if not found
int TString::Find(int Char) const
{
  const char *Str = RealString->FArray;
  const char *p = strchr(Str, Char);
  return !p ? -1 : (int) (p - Str);
}

//---------------------------------------------------------------------------
// Returns the index of 'Char' or -1 if not found.
// Case is ignored
int TString::FindI(int Char) const
{
  TString String(RealString->FArray);
  String.ToUpper();
  return String.Find(toupper(Char));
}

//---------------------------------------------------------------------------
// Returns the index of 'String' or -1 if not found.
int TString::Find(const char *String) const
{
  const char *Str = RealString->FArray;
  const char *p = strstr(Str, String);
  return(p == NULL) ? -1 : (int) (p - Str);
}

//---------------------------------------------------------------------------
// Returns the index of 'String' or -1 if not found.
// Case is ignored
int TString::FindI(const char *String) const
{
  TString String1(RealString->FArray);
  String1.ToUpper();
  TString String2(String);    
  String2.ToUpper();
  return String1.Find(String2);
}

//---------------------------------------------------------------------------
// Returns the total number of 'Char' found in this string or 0 if not found
int TString::Count(int Char) const
{
  const char *Str = RealString->FArray;
  int Total = 0;
  for(int Ch = 0; Str[Ch]; Ch++) {
    if(Str[Ch] == Char)
      Total++;
  }
  return Total;
}

//---------------------------------------------------------------------------
// Convers string value into an integer. Conversion stops after first non numeric digit.
int TString::ToInt()
{
  return atoi(RealString->FArray);
}

//---------------------------------------------------------------------------
// Converts this string to upper case
void TString::ToUpper()
{
  Cow();
  strupr(RealString->FArray);
}

//---------------------------------------------------------------------------
// Converts the first letter of each word in this string to upper case
void TString::ToUpperFirstChrs()
{
  if(Length()) {
    Cow();

    // Convert the first character of each new word to uppercase.
    RealString->FArray[0] = (char) toupper(RealString->FArray[0]);
    for(int Ch = 1; RealString->FArray[Ch]; Ch++) {
      if(RealString->FArray[Ch - 1] == ' ')
        RealString->FArray[Ch] = (char) toupper(RealString->FArray[Ch]);
    }
  }
}

//---------------------------------------------------------------------------
// Converts this string to lower case
void TString::ToLower()
{
  Cow();
  strlwr(RealString->FArray);
}

//---------------------------------------------------------------------------
// Appends 'Char' to the end of this string.
// eg String += 'X'
void TString::operator+= (int Char)
{
  Cow();
  RealString->AppendCharacter(Char);
}

//---------------------------------------------------------------------------
// Inserts up to 'Length' characters of 'Text' into this string at 'Position'.
// If 'Position' is past the end, the string is extended
void TString::Insert(const char *Text, int Length, int Position)
{
  Cow();
  RealString->Insert(Text, Length, Position);
}

//---------------------------------------------------------------------------
// Replaces up to 'Length' characters of 'Text' into this string at 'Position'.
// If 'Position' is past the end, the string is extended
void TString::Replace(const char *Text, int Length, int Position)
{
  Cow();
  RealString->Replace(Text, Length, Position);
}

//---------------------------------------------------------------------------
// Replaces all old characters with a new one
void TString::Replace(char Old, char New)
{
  for (int i=0; i < RealString->FLength; i++)
    if (RealString->FArray[i] == Old)
       RealString->FArray[i] = New;
}

//---------------------------------------------------------------------------
// Swaps the contents of 'String' with the contents of this string
void TString::Exchange(TString *String)
{
  TRealString *Temp;

  Temp = RealString;
  RealString = String->RealString;
  String->RealString = Temp;
};

//---------------------------------------------------------------------------
// Creates a new string using the standard 'sprintf'.
// There is a limit of 512 characters
int __cdecl TString::sprintf(const char *Format,...)
{
  Cow();

  va_list arg_ptr;
  va_start(arg_ptr, Format);

  char Temp[512];
  vsprintf(Temp, Format, arg_ptr);
  assert(strlen(Temp) < 512);

  *this = Temp;
  return Length();
}

//---------------------------------------------------------------------------
// Removes 'Length' characters starting at 'Position'
void TString::Remove(int Position, int Length)
{
  Cow();
  RealString->Remove(Position, Length);
}

//---------------------------------------------------------------------------
// Truncates this string to 'MaxLength' characters
void TString::LimitLength(int MaxLength)
{
  if(Length() > MaxLength)
    Remove(MaxLength, Length() - MaxLength);
}

//---------------------------------------------------------------------------
// Removes all characters which match 'Char'
void TString::Remove(char Char)
{
  for(int Ch = 0; RealString->FArray[Ch]; ) {
    if(RealString->FArray[Ch] == Char)
      Remove(Ch, 1);
    else
      Ch++;
  }
}

//---------------------------------------------------------------------------
// Removes all characters which match any character from 'AnyChar'
void TString::Remove(const char *AnyChar)
{
  for(int Ch = 0; RealString->FArray[Ch]; ) {
    if(strchr(AnyChar, RealString->FArray[Ch]) != NULL)
      Remove(Ch, 1);
    else
      Ch++;
  }
}

//---------------------------------------------------------------------------
// Trims spaces from the end
void TString::RTrim()
{
  int Position;
  for(Position = Length(); (Position > 0) && (RealString->FArray[Position - 1] == ' '); Position--);
  if(Position != Length())
    Remove(Position, Length() - Position);
}

//---------------------------------------------------------------------------
// Trims spaces from the start
void TString::LTrim()
{
  if(Length()) {
    int Len = strspn(RealString->FArray, " ");
    if(Len)
      Remove(0, Len);
  }
}

//---------------------------------------------------------------------------
// Adds spaces to the left to right justify this string for a total field length of 'ToLength'
void TString::RJust(int ToLength)
{
	int Padding = _max(0, ToLength - Length());
	if(Padding)
		Insert(TString(Padding, ' '), 0);
}

//---------------------------------------------------------------------------
// Adds spaces to the left to centre this string for a total line width of 'LineWidth'
void TString::Centre(int LineWidth)
{
	int Padding = _max(0, (LineWidth - Length()) / 2);
	if(Padding)
		Insert(TString(Padding, ' '), 0);
}

//---------------------------------------------------------------------------
// Removes all characters except 0-9
void TString::IntegerOnly()
{
  for(int Ch = 0; RealString->FArray[Ch]; ) {
    if(!isascii(RealString->FArray[Ch]) || !isdigit(RealString->FArray[Ch]))
      Remove(Ch, 1);
    else
      Ch++;
  }
}

//---------------------------------------------------------------------------
// Returns a TString of the last 'Length' characters from this string
TString TString::Right(int Length) const
{
  return TString(RealString->FArray + _max(0, TString::Length() - Length));
}

//---------------------------------------------------------------------------
// Returns a TString of the first 'Length' characters from this string
TString TString::Left(int Length) const
{
  return TString(RealString->FArray, _min(TString::Length(), Length));
}

//---------------------------------------------------------------------------
// Returns a TString of 'Length' characters from 'Position' from this string
TString TString::Mid(int Position, int Length) const
{
  Position = _min(Position, TString::Length());
  return TString(RealString->FArray + Position, _min(TString::Length() - Position, Length));
}

//---------------------------------------------------------------------------
// Gets a word wrapped line of text from a large string.
// Assigns to 'String' the text as though it was word wrapped in a window of '_max(Length' characters wide.
// Param 'Part' is the line number starting at 0.
// 'KeepLeadingSpace' allows a 1 character indent from the second line down.
// Returns: false when 'Part' (line number) is past the end of the text.
bool TString::WordWrapPart(TString &String, int Part, int maxLength, bool KeepLeadingSpace) const
{
	// Find start
	const char *Str = RealString->FArray;
	int Start = 0;
	for(;; Part--) {
		int Length = WordWrapLength(Start, maxLength);
    if(!Part) {
      String = TString(Str + Start, Length);
      return *String;
    }

    Start += Length;
    if(!KeepLeadingSpace)
      Start += WordWrapNext(Start);
  }
}

//---------------------------------------------------------------------------
// Returns the length of the largest sub-string of whole words from this string,
// starting at position 'Start', which is a _max(imum of '_max(Length' characters
int TString::WordWrapLength(int Start, int maxLength) const
{
  const char *Text = RealString->FArray + Start;
  const char *p = Text;
  int TextLength = strlen(Text);
  int Longest = 0;

  for(;;) {
    const char *Space = strchr(p, ' ');
    int Length = Space ? int(Space - Text) : TextLength;

    if(Length <= maxLength) {
      if(Length == TextLength)
        return TextLength;

      // Move p to one chr past the space
      p = Text + Length + 1;
      Longest = Length;
    }
    else
      return Longest ? Longest : maxLength;
  }
}

//---------------------------------------------------------------------------
// Returns the position of the start of the next word to the right of position 'Start' in this string
int TString::WordWrapNext(int Start) const
{
  return strspn(RealString->FArray + Start, " ");
}

//---------------------------------------------------------------------------
// Returns the total number of words in this string
int TString::Words() const
{
  const char *p = RealString->FArray;

  // Skip leading blanks
  p += strspn(p, " ");

  // Count
  int n;
  for(n = 0; *p;) {
    n++;
    p = strchr(p, ' ');
    if(!p)
      break;
    // Skip blanks
    p += strspn(p, " ");
  }

  return n;
}

//---------------------------------------------------------------------------
// Returns a string containing the word which is 'WordNo' words into this string
TString TString::Word(int WordNo) const
{
  const char *p = RealString->FArray;

  // Skip leading blanks
  p += strspn(p, " ");

  // Count & skip words
  for(int n = 0; (n < WordNo) && *p;) {
    n++;
    p = strchr(p, ' ');
    if(!p)
      break;
    // Skip blanks
    p += strspn(p, " ");
  }

  if(p) {
    int WordLen = strcspn(p, " ");
    return TString(p, WordLen);
  }

  return TString();
}

//---------------------------------------------------------------------------
// Returns a position the word which is 'WordNo' words into this string
int TString::WordPos(int WordNo) const
{
  const char *p = RealString->FArray;
  const char *Start = p;

  // Skip leading blanks
  p += strspn(p, " ");

  // Count & skip words
  for (int n = 0; (n < WordNo) && *p;) {
    n++;
    p = strchr(p, ' ');
    if (!p)
      break;
    // Skip blanks
    p += strspn(p, " ");
  }

  if (p)
    return p - Start;

  return -1;
}

//---------------------------------------------------------------------------
// Returns the number of sub-strings within this string which are separated by character 'Separator'
int TString::AsciiWords(int Separator, bool IgnoreQuotes) const
{
  const char *p = RealString->FArray;

  // Skip leading blanks and return with zero if there is no string
  p += strspn(p, " ");
  if (!*p)
    return 0;

  // Count
  int n = 0;
  for (bool Done = false, InQuotes = false, NextField = false; !Done; p++) {
    if (!IgnoreQuotes && *p == '\"')
      InQuotes = !InQuotes;
    else if (*p == Separator) {
      if (!InQuotes)
        NextField = true;
    }
    else if (!*p) {
      NextField = true;
      Done = true;
    }

    if (NextField) {
      n++;
      NextField = false;
    }
  }

  return n;
}
//---------------------------------------------------------------------------
// Returns a sub-string from this string. The sub-strings are separated by 'Separator'.
// The returned sub-string is the Nth from the start, where N = 'WordNo'
TString TString::AsciiWord(int WordNo, int Separator, bool IgnoreQuotes) const
{
  const char *p = RealString->FArray;
  TString temp;

  // Skip leading blanks
  p += strspn(p, " ");

  // Count
  int n = 0;
  for (bool Done = false, InQuotes = false, NextField = false; !Done; p++) {
    if (!IgnoreQuotes && *p == '\"')
      InQuotes = !InQuotes;
    else if (*p == Separator) {
      if (InQuotes)
        temp += *p;
      else
        NextField = true;
    }
    else if (!*p) {
      NextField = true;
      Done = true;
    }
    else
      temp += *p;

    if (NextField) {
      if (n < WordNo) {
        temp = "";
        NextField = false;
        n++;
      }
      else {
        temp.RLTrim();
        break;
      }
    }
  }

  if(n == WordNo)
    return temp;

  return TString();
}

//---------------------------------------------------------------------------
// Returns the character at 'Position' from this string.
// That character cannot be modified.
// To modify, use operator()(int)
char TString::operator[] (int Position) const
{
  assert(Position <= Length());
  return RealString->FArray[Position];
}

//---------------------------------------------------------------------------
// Returns the character at 'Position' from this string.
// That character can be modified
char& TString::operator() (int Position)
{
  assert(Position <= Length());
  Cow();
  return RealString->FArray[Position];
}

//---------------------------------------------------------------------------
// Increment a number at the end by 1.
// eg SMIT0001 becomes SMIT0002
TString& TString::operator++ ()
{
  // Find the first digit(ie last digit starting from the end)
  int DigitPosition, DigitLength;
  for(DigitPosition = Length(), DigitLength = 0; DigitPosition && isdigit(RealString->FArray[DigitPosition - 1]); DigitPosition--, DigitLength++);

  // Insert the incremented number
  char Temp[32];
	::sprintf(Temp, "%0*li", _max(1, DigitLength), atol(RealString->FArray + DigitPosition) + 1);
  Replace(Temp, DigitPosition);

  return *this;
}

//---------------------------------------------------------------------------
// Returns a TString which is the concatenation of this string and 'Text'
TString TString::operator+ (const char *Text) const
{
  TString Temp(RealString->FArray);
  Temp += Text;
  return Temp;
}

//---------------------------------------------------------------------------
// Removes characters from this string, except where they match any character from 'ValidChars'
void TString::Keep(const char *ValidChars)
{
  for(int Ch = 0; RealString->FArray[Ch]; ) {
    if(strchr(ValidChars, RealString->FArray[Ch]) == NULL)
      Remove(Ch, 1);
    else
      Ch++;
  }
}

//---------------------------------------------------------------------------
// Returns an int which is:
// 0 if this string == 'String',
// negative if this string < 'String',
// positive if this string > 'String'.
// Case sensitivity is set by 'IgnoreCase'
int TString::Compare(const TString &String, bool IgnoreCase) const
{
  return IgnoreCase ? stricmp(RealString->FArray, String) : strcmp(RealString->FArray, String);
}

//---------------------------------------------------------------------------
// Returns true if this string == 'String'.
// Case sensitivity is set by 'IgnoreCase'
bool TString::Equals(const TString &String, bool IgnoreCase) const
{
  return(IgnoreCase ? (stricmp(RealString->FArray, String) == 0) : (strcmp(RealString->FArray, String) == 0));
}

//---------------------------------------------------------------------------
// Reads text from 'File' until the 'Delimiter' character is reached or EOF.
// If 'EatLineEnds' is true, "\r\n" sequences are removed.
// Reading stops at CTRL+Z if 'StopAtCtrlZ' is true
/*
void TString::Read(TFile *File, char Delimiter, bool EatLineEnds, bool StopAtCtrlZ)
{
  // This fn uses a stack based buffer 'first_line' for the first 'buf_step' chrs Read in
  // then allocates memory buffers
  const int InitialBufferSize = 100;
  int BufferLength = InitialBufferSize;
	int Buffer_max = InitialBufferSize - 4;
	char FirstLine[InitialBufferSize];
	char *TempLine = FirstLine;
	TArrayPtr<char> HeapLine;

	int Position = 0;
	for(;;) {
		// Adjust TempLine
		if(Position >= Buffer_max) {
			BufferLength <<= 1;
      Buffer_max = BufferLength - 4;
      if(TempLine == FirstLine) {
        TempLine = HeapLine = new char[BufferLength];
        memcpy(TempLine, FirstLine, Position);
      }
      else {
        TempLine = HeapLine = (char*)realloc(HeapLine, BufferLength);
        if(!HeapLine)
          throw Exception("Out of memory");
      }
    }

    // EOF
    if(File->AtEof())
      break;

    // READ Ch
    int Ch = File->ReadByte();

    // End of String
    if(Ch == Delimiter) {
      // Eat the following \n
      if(EatLineEnds && (Delimiter == '\r') && !File->AtEof())
        File->ReadByte();
      break;
    }

    // Eat CR, LF
    if(EatLineEnds && ((Ch == '\n') || (Ch == '\r')))
      continue;

    // CTRL-Z
    if(StopAtCtrlZ && (Ch == 0x1A)) {
      File->SetEof(true);
      break;
    }

    // End of String \0
    if(Ch == 0) {
      File->SetEof(true);
      break;
    }

    // Any other chrs
    TempLine[Position++] = (char) Ch;
  }

  TempLine[Position] = 0;

  (*this) = TempLine;
}

//---------------------------------------------------------------------------
// Writes this string to 'File' including the terminating \0
void TString::Write(TFile *File) const
{
  File->Write(RealString->FArray, Length() + 1);
}

//---------------------------------------------------------------------------
// Writes this string to 'File'.
// A sequence of 'LineEnd' characters of length 'LineEndLength' is then written
void TString::Write(TFile *File, const char *LineEnd, int LineEndLength) const
{
  if(Length())
    File->Write(RealString->FArray, Length());
  File->Write(LineEnd, LineEndLength);
}

*/
