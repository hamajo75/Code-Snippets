/**************************************************************************************
* WString
* Companion class to TString handling wide character based strings.
* WString can be used as drop-in replacement for TString.
* Underlying storage is UnicodeString. WString uses 0-based index that is
* internally converted to 1-based index used by UnicodeString.
**************************************************************************************/
#include "CommonLib.h"
#pragma hdrstop

#include "TWString.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
// Sets the initial value by converting IntVal to string
WString::WString(int IntVal)
{
  FText.sprintf(L"%d", IntVal);
}
//---------------------------------------------------------------------------
// Sets the initial string length and fills the string with FillChr.
WString::WString(int Length, wchar_t FillChr)
{
  FText = UnicodeString::StringOfChar(FillChr, _max(0, Length));
}

//---------------------------------------------------------------------------
// Trims whitespace from both sides.
// When New parameter is true a new UnicodeString string is returned leaving this
// one unchanged.
WString WString::Trim(bool New)
{
  if (New)
    return WString(FText.Trim());

  RLTrim();
  return *this;
}
//---------------------------------------------------------------------------
// Trims whitespace from right sides.
// When New parameter is true a new UnicodeString string is returned leaving this
// one unchanged.
WString WString::TrimRight(bool New)
{
  if (New)
    return WString(FText.TrimRight());

  RTrim();
  return *this;
}
//---------------------------------------------------------------------------
// Trims whitespace from left sides.
// When New parameter is true a new UnicodeString string is returned leaving this
// one unchanged.
WString WString::TrimLeft(bool New)
{
  if (New)
    return WString(FText.TrimLeft());

  LTrim();
  return *this;
}
//---------------------------------------------------------------------------
// Converts all characters to upper case.
// When New parameter is true a new UnicodeString string is returned leaving this
// one unchanged.
WString WString::UpperCase(bool New)
{
  if (New)
    return WString(FText.UpperCase());

  ToUpper();
  return *this;
}
//---------------------------------------------------------------------------
// Converts all characters to lower case.
// When New parameter is true a new UnicodeString string is returned leaving this
// one unchanged.
WString WString::LowerCase(bool New)
{
  if (New)
    return WString(FText.LowerCase());

  ToLower();
  return *this;
}
//---------------------------------------------------------------------------
// Returns the index of first occurence of specified character.
// -1 is returned if not found.
int WString::Find(int Chr) const
{
  wchar_t Str[] = { Chr, 0 };
  return Pos(Str);
}
//---------------------------------------------------------------------------
// Returns a sub-string from this string. The sub-strings are separated by 'Separator'.
// The returned sub-string is the Nth from the start, where N = 'WordNo'
WString WString::Word(int WordNo, int Separator, bool IgnoreQuotes) const
{
	UnicodeString word;
  wchar_t *Text = FText.c_str();

	// Skip leading blanks
	int p = 0;
	while (Text[p] == ' ')
		p++;

	// Count
	int n = 0;
	for (bool Done = false, InQuotes = false, NextField = false; !Done; p++) {
		if (!IgnoreQuotes && Text[p] == '\"')
			InQuotes = !InQuotes;
		else if (Text[p] == Separator) {
			if (InQuotes)
				word += Text[p];
			else
				NextField = true;
		}
		else if (Text[p] == 0) {
			NextField = true;
			Done = true;
		}
		else
			word += Text[p];

		if (NextField) {
			if (n < WordNo) {
				word = "";
				NextField = false;
				n++;
			}
			else {
				word.Trim();
				break;
			}
		}
	}

	return n == WordNo ? WString(word.c_str()) : WString();
}

//---------------------------------------------------------------------------
// Returns the number of sub-strings within this string which are separated by character 'Separator'
int WString::Words(int Separator, bool IgnoreQuotes) const
{
  wchar_t *Text = FText.c_str();

	// Skip leading blanks and return with zero if there is no string
	int p = 0;
	while (Text[p] == ' ')
		p++;
	if (Text[p] == 0)
		return 0;

	// Count
	int n = 0;
	for (bool Done = false, InQuotes = false, NextField = false; !Done; p++) {
		if (!IgnoreQuotes && Text[p] == '\"')
			InQuotes = !InQuotes;
		else if (Text[p] == Separator) {
			if (!InQuotes)
				NextField = true;
		}
		else if (Text[p] == 0) {
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
WString &WString::sprintf(const wchar_t* format, ...)
{
  va_list args;
  va_start(args, format);
  FText.vprintf(format, args);
  va_end(args);
  return *this;
}
//---------------------------------------------------------------------------
WString WString::operator +(const WString& Other) const
{
  UnicodeString Str = FText + Other.FText;
  return WString(Str);
}
//---------------------------------------------------------------------------
// Removes all characters which match 'Char'
void WString::Remove(char Char)
{
  for (int i = 1; i <= FText.Length(); ) {
    if (FText[i] == Char)
      FText.Delete(i, 1);
    else
      i++;
  }
}

//---------------------------------------------------------------------------
// Removes all characters which match any character from 'AnyChar'
void WString::Remove(const wchar_t *AnyChar)
{
  for (int i = 1; i <= FText.Length(); ) {
    if(StrChrW(AnyChar, FText[i]) != NULL)
      Remove(i, 1);
    else
      i++;
  }
}

//---------------------------------------------------------------------------
// Returns the index of 'String' or -1 if not found.
// Case is ignored
int WString::FindI(const UnicodeString &String) const
{
  WString String1 = FText.UpperCase();
  WString String2 = String.UpperCase();
  return String1.Find(String2.Text());
}

//---------------------------------------------------------------------------
// Replaces all old characters with a new one
void WString::Replace(wchar_t Old, wchar_t New)
{
  for (int i = 1; i <= FText.Length(); i++)
    if (FText[i] == Old)
       FText[i] = New;
}
//---------------------------------------------------------------------------
// Returns the total number of 'Char' found in this string or 0 if not found
int WString::Count(int Char) const
{
  int Total = 0;
  for (int i = 1; i <= FText.Length(); i++) {
    if (FText[i] == Char)
      Total++;
  }
  return Total;
}

